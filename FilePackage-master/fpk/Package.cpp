//
//  Package.cpp
//  FilePackage
//
//  Created by Luwei on 15/1/13.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "Package.h"
#include "Utility/all.h"
#include "Error.h"
#include <assert.h>
using namespace LM;

Package::Package()
:m_updateDirty(false)
{
}

Package::~Package()
{
    this->Unload();
}

bool Package::Load(const std::string &package)
{
    if (package.empty())
        return FPK_Error(Error::FILE_PATH_EMPTY);
    if (m_file.IsOpen())
        return FPK_Error(Error::PKG_ALREADY_OPEN);
    
    bool ok = true;
    ok = m_file.Exist(package);
    if (!ok) {
        ok = this->Build(package);
        if (!ok)
            return FPK_Error(Error::PKG_BUILD);
    }
    
    // open package
    ok = m_file.Open(package, "rb+");
    if (!ok)
        return FPK_Error(Error::PKG_OPEN);
    
    // read package header
    m_header.Clear();
    ok = m_header.Read(&m_file);
    if (!ok) {
        m_file.Close();
        return FPK_Error(Error::PKG_INVALID);
    }
    
    // check package valid
    ok = m_header.Check();
    if (!ok) {
        m_file.Close();
        return FPK_Error(Error::PKG_INVALID);
    }
    
    // read package footer
    m_footer.Clear();
    ok = m_footer.Read(&m_file, &m_header);
    if (!ok) {
        m_file.Close();
        return FPK_Error(Error::PKG_INVALID);
    }
    
    return ok;
}

bool Package::Unload()
{
    bool ok = this->Flush();
    if (!ok)
        return FPK_Error(Error::PKG_UPDATE);
    
    m_header.Clear();
    m_footer.Clear();
    ok = m_file.Close();
    if (!ok)
        return FPK_Error(Error::PKG_CLOSE);
    return true;
}

bool Package::IsValid()
{
    return (m_file.IsOpen() && m_header.Check());
}

bool Package::Append(const std::string &diskfile)
{
    if (diskfile.empty())
        return FPK_Error(Error::FILE_PATH_EMPTY);
    if (!this->IsValid())
        return FPK_Error(Error::PKG_INVALID);
    
    // read data from disk
    size_t length = 0;
    char *pBuffer = (char*)File::GetBinary(diskfile, &length);
    if (!pBuffer)
        return FPK_Error(Error::FILE_READ);
    
    uint64_t name_id = String::GenID(diskfile);
    bool ok = this->Append(name_id, pBuffer, length);
    Memory::Get().Free(pBuffer);

    return ok;
}

bool Package::Append(const std::string &keypath, const char* pBuffer, size_t length)
{
    if (keypath.empty())
        return FPK_Error(Error::FILE_PATH_EMPTY);
    if (!this->IsValid())
        return FPK_Error(Error::PKG_INVALID);

    // try to resolve name hash-id conflict
    uint64_t name_id = String::GenID(keypath);
    return this->Append(name_id, pBuffer, length);
}

bool Package::Remove(const std::string &filepath)
{
    if (filepath.empty())
        return FPK_Error(Error::FILE_PATH_EMPTY);
    if (!this->IsValid())
        return FPK_Error(Error::PKG_INVALID);

    uint64_t name_id = String::GenID(filepath);
    LM::Entry *pEntry = m_footer.Find(name_id);
    if (pEntry && pEntry->m_entry.flag == Entry::State::NORMAL) {
        pEntry->m_entry.flag = Entry::State::REMOVE;
        m_updateDirty = true;
        return true;
    }
    
    return false;
}

bool Package::Flush()
{
    if (!m_updateDirty)
        return true;
    m_updateDirty = false;
    bool ok = true;
    ok &= m_header.Write(&m_file, &m_footer);
    ok &= m_footer.Write(&m_file, &m_header);
    ok &= m_file.Flush();
    if (!ok)
        return FPK_Error(Error::PKG_UPDATE);
    return true;
}

bool Package::Merge(const std::string &package)
{
    if (!this->IsValid())
        return FPK_Error(Error::PKG_INVALID);
    
    Package other;
    bool ok = other.Load(package);
    if (!ok)
        return FPK_Error(Error::PKG_OPEN);
    
    ok = this->Merge(&other);
    if (!ok)
        return FPK_Error(Error::PKG_MERGE);
    return ok;
}

bool Package::Merge(Package *pOther)
{
    assert(pOther);
    bool ok = true;
    pOther->m_footer.Traverse([&](Entry *pEntry)->bool{
        
        if (pEntry->m_entry.flag == Entry::State::NORMAL) {
            // read data from other package body
            size_t length = 0;
            void *pBuffer = nullptr;
            ok = pOther->m_body.Read(&pOther->m_file, pEntry, &pBuffer, &length);
            if (!ok)
                return false;
            ok = this->Append(pEntry->m_entry.id, (char*)pBuffer, length);
            Memory::Get().Free(pBuffer);
            if (!ok)
                return false;
        }
        return true;
    });
    return ok;
}

bool Package::Update()
{
    if (!this->IsValid())
        return FPK_Error(Error::PKG_INVALID);
    
    std::string path_tmp = LM::Path::GetTemp();
    std::string path_pkg = m_file.GetPath();

    // build a tmp package
    Package other;
    bool ok = other.Load(path_tmp);
    if (!ok)
        return FPK_Error(Error::PKG_OPEN);
    
    m_footer.Traverse([&](Entry *pEntry) ->bool {
        if (pEntry->m_entry.flag == Entry::State::NORMAL) {
            // read data from body
            size_t length = 0;
            void *pBuffer = nullptr;
            bool ok = m_body.Read(&m_file, pEntry, &pBuffer, &length);
            if (!ok)
                return FPK_Error(Error::PKG_UPDATE);
            
            ok = other.Append(pEntry->m_entry.id, (char*)pBuffer, length);
            Memory::Get().Free(pBuffer);
            if (!ok)
                return FPK_Error(Error::PKG_UPDATE);
        }
        return true;
    });
    
    ok = true;
    ok &= this->Unload();
    ok &= other.Unload();
    if (!ok) return false;

    LM::Path pathobj(path_pkg);
    std::string path_backup = pathobj.GetPath();
    path_backup += ".";
    path_backup += pathobj.GetFilename();

    // move this to backup
    ok &= LM::File::Move(path_pkg, path_backup);
    // move pkg_tmp to this package
    ok &= LM::File::Move(path_tmp, path_pkg);
    if (!ok) return false;

    ok &= this->Load(path_pkg);
    if (!ok) return false;
    
    return true;
}

std::string Package::GetString(const std::string &filepath)
{
    size_t length = 0;
    char* pBuffer = (char*)this->GetBinary(filepath, &length);
    if (!pBuffer)
        return std::string();
    
    std::string result(pBuffer, length);
    Memory::Get().Free(pBuffer);
    return result;
}

unsigned char* Package::GetBinary(const std::string &filepath, size_t *pLength_out)
{
    *pLength_out = 0;
    
    if (filepath.empty())
        return nullptr;
    if (!this->IsValid())
        return nullptr;
    
    // find entry with filepath id
    uint64_t name_id = String::GenID(filepath);
    Entry *pEntry = m_footer.Find(name_id);
    if (!pEntry)
        return nullptr;
    if (pEntry->m_entry.flag != Entry::State::NORMAL)
        return nullptr;

    // read package data with entry
    size_t length = 0;
    void *pBuffer = nullptr;
    bool ok = m_body.Read(&m_file, pEntry, &pBuffer, &length);
    if (!ok) return nullptr;
    
    // data length
    *pLength_out = length;
    return (unsigned char*)pBuffer;
}

bool Package::Exist(const std::string &filepath)
{
    if (filepath.empty())
        return false;
    uint64_t id = String::GenID(filepath);
    Entry *pEntry = m_footer.Find(id);
    if (pEntry) {
        if (pEntry->m_entry.flag == Entry::State::NORMAL)
            return true;
        else
            return false;
    }
    return false;
}

size_t Package::GetSize()
{
    return m_file.GetSize();
}

void Package::Dump()
{
    if (!this->IsValid())
        return;
    m_header.Dump();
    m_footer.Dump();
}

uint32_t Package::GetVersion()
{
    return FPK_VERSION;
}

// [PRIVATE]

bool Package::ResolveConflict(uint64_t id)
{
    uint64_t old_id = id;
    Entry *pEntry = m_footer.Find(old_id);
    if (pEntry) {
        if(pEntry->m_entry.flag == Entry::State::NORMAL) {
            return false;
        }
        else if (pEntry->m_entry.flag == Entry::State::REMOVE) {
            int exit_counter = 0;
            while (exit_counter < 50) {
                exit_counter++;

                uint64_t new_id = old_id + LM::Random::Gen();
                if (!m_footer.Find(new_id)) {
                    pEntry->m_entry.id = new_id;
                    m_footer.Update(old_id);
                }
            }
        }
    }
    return true;
}

bool Package::Append(uint64_t keyid, const char* pBuffer, size_t length)
{
    assert(pBuffer);
    
    if (!this->IsValid())
        return FPK_Error(Error::PKG_INVALID);
    
    // try to resolve name hash-id conflict
    bool ok = this->ResolveConflict(keyid);
    if (!ok)
        return FPK_Error(Error::PKG_CONFLICT);
    
    // init entry
    Entry *pEntry = new Entry;
    pEntry->m_entry.offset = m_header.m_ph.offset;
    pEntry->m_entry.length = length;
    pEntry->m_entry.id = keyid;
    pEntry->m_entry.flag = Entry::State::NORMAL;

#ifdef FPK_CHECK_CRC32
    pEntry->m_entry.crc32 = Hash::CRC32((unsigned char*)pBuffer, length);
#else
    pEntry->m_entry.crc32 = 0x00000000;
#endif
    
    // insert entry to footer
    ok = m_footer.Insert(pEntry);
    if (!ok)
        return FPK_Error(Error::PKG_CONFLICT);
    
    // write package body
    ok = m_body.Write(&m_file, pEntry, pBuffer);
    if (!ok) {
        m_footer.Remove(pEntry->m_entry.id);
        return FPK_Error(Error::PKG_UPDATE);
    }
    
    // write successful move header.offset
    m_header.m_ph.offset = m_header.m_ph.offset + length;
    m_updateDirty = true;
    return true;
}

bool Package::Build(const std::string &package)
{
    if (package.empty())
        return false;
    if (m_file.IsOpen())
        return false;
    
    bool ok = true;
    ok = m_file.Open(package, "wb");
    if (!ok) return false;
    
    // write init package header
    Header header;
    header.Initialize(this->GetVersion());
    ok = header.Write(&m_file, &m_footer);
    if (!ok) return false;
    
    ok = m_file.Close();
    return ok;
}

