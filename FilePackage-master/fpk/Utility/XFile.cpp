//
//  XFile.cpp
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "XFile.h"
#include "XPath.h"
#include "XMemory.h"
#include <unistd.h>
#include <assert.h>
using namespace LM;

// [File]

File::File()
:m_pFileStream(nullptr)
{
}

File::~File()
{
    this->Close();
}

bool File::Open(const std::string &path, const std::string &mode)
{
    if (m_pFileStream)
        return false;
    if (path.empty())
        return false;
    if (mode.empty())
        return false;
    
    m_pFileStream = fopen(path.c_str(), mode.c_str());
    if (!m_pFileStream)
        return false;
    m_path = path;
    return true;
}

bool File::Attach(FILE *pFile)
{
    assert(pFile);
    bool ret = this->Close();
    if (ret)
        m_pFileStream = pFile;
    return ret;
}

bool File::Close()
{
    if (!this->IsOpen())
        return true;
    
    int c = fclose(m_pFileStream);
    if (c != 0)
        return false;
    m_pFileStream = nullptr;
    m_path = "";
    return true;
}

bool File::Flush()
{
    if (!this->IsOpen())
        return false;
    return fflush(m_pFileStream) == 0;
}

bool File::IsOpen() const
{
    return (m_pFileStream != nullptr);
}

const std::string& File::GetPath() const
{
    return m_path;
}

size_t File::Read(void *pBuffer, size_t size, size_t count) const
{
    if (!this->IsOpen())
        return 0;
    return fread(pBuffer, size, count, m_pFileStream);
}

size_t File::Write(const void *pBuffer, size_t size, size_t count) const
{
    if (!this->IsOpen())
        return 0;
    return fwrite(pBuffer, size, count, m_pFileStream);
}

long File::Tell() const
{
    if (!this->IsOpen())
        return -1;
    return ftell(m_pFileStream);
}

bool File::SeekSet() const
{
    return this->Seek(0L, Where::SET);
}

bool File::SeekEnd() const
{
    return this->Seek(0L, Where::END);
}

bool File::SeekSet(long offset) const
{
    return this->Seek(offset, Where::SET);
}

bool File::SeekCur(long offset) const
{
    return this->Seek(offset, Where::CUR);
}

bool File::SeekEnd(long offset) const
{
    return this->Seek(offset, Where::END);
}

bool File::Seek(long offset, Where whence) const
{
    if (!this->IsOpen())
        return false;
    int res = fseek(m_pFileStream, offset, (int)whence);
    if (res != 0)
        return false;
    return true;
}

long File::GetSize() const
{
    if (!this->IsOpen())
        return false;
    long old_pos = this->Tell();
    this->SeekEnd();
    long fsize = this->Tell();
    this->SeekSet(old_pos);
    return fsize;
}

bool File::Eof() const
{
    if (!this->IsOpen())
        return true;
    if (feof(m_pFileStream))
        return true;
    return false;
}

std::string File::GetString(size_t length) const
{
    if (!this->IsOpen())
        return std::string();
    
    size_t length_out = 0;
    char* pBuffer = (char*)this->GetBinary(&length_out, length);
    if (!pBuffer)
        return std::string();
    
    std::string str(pBuffer, length_out);
    
    Memory::Get().Free(pBuffer);
    
    return str;
}

void* File::GetBinary(size_t *pLength_out, size_t length_in ) const
{
    assert(pLength_out);
    *pLength_out = 0;
    
    if (!this->IsOpen())
        return nullptr;
    
    long cur_offset = this->Tell();
    if (length_in == 0)
        length_in = this->GetSize() - cur_offset;
    
    size_t alloc_size = sizeof(char) * length_in;
    char *pBuffer = (char *) Memory::Get().Alloc(alloc_size);
    if (!pBuffer) {
        return nullptr;
    }
    memset(pBuffer, 0, alloc_size);
    
    // return really bytes had read
    *pLength_out = this->Read(pBuffer, sizeof(char), length_in);
    
    this->SeekSet(cur_offset);
    
    return pBuffer;
}

void File::Dump16(size_t length) const
{
    if (!this->IsOpen())
        return;
    
    size_t length_out = 0;
    unsigned char* pBuffer = (unsigned char*)this->GetBinary(&length_out, length);
    
    for (size_t i = 0; i < length_out; i++) {
        unsigned char uc = pBuffer[i];
        printf("%02X", uc);
        if ((i+1) % 2 == 0)
            putchar(' ');
    }
    putchar('\n');
    Memory::Get().Free(pBuffer);
}

void File::Dump2(size_t length) const
{
    if (!this->IsOpen())
        return;
    
    size_t length_out = 0;
    unsigned char* pBuffer = (unsigned char*)this->GetBinary(&length_out, length);
    
    for (size_t i = 0; i < length_out; i++) {
        unsigned char uc = pBuffer[i];
        unsigned char index = 0x80;
        while (index > 0) {
            putchar(uc & index ? '1' : '0');
            index >>= 1;
        }
        putchar(' ');
    }
    putchar('\n');
    Memory::Get().Free(pBuffer);
}

bool File::Exist(const std::string &path)
{
    return (access(path.c_str(), F_OK) == 0);
}

bool File::Touch(const std::string &path)
{
    bool ok = false;
    File stream;
    
    // file exist
    ok = stream.Exist(path);
    if (ok) return false;
    
    // create empty file
    ok = stream.Open(path, "wb");
    if (!ok) return false;
    ok = stream.Close();
    if (!ok) return false;
    
    return true;
}

bool File::Remove(const std::string &path)
{
    return (::remove(path.c_str()) == 0);
}

bool File::Rename(const std::string &path, const std::string &newname)
{
    std::string new_path = Path(path).GetPath();
    new_path += newname;
    return File::Move(path, new_path);
}

bool File::Move(const std::string &srcpath, const std::string &dstpath)
{
    return (::rename(srcpath.c_str(), dstpath.c_str()) == 0);
}

bool File::Copy(const std::string &srcpath, const std::string &dstpath)
{
    bool ok = true;
    
    File fsrc, fdst;
    ok &= fsrc.Open(srcpath, "rb");
    ok &= fdst.Open(dstpath, "wb");
    if (!ok) return false;
    
    // copy ...
    char pBuffer[800];
    while (!fsrc.Eof()) {
        // read --> write
        size_t count = fsrc.Read(pBuffer, sizeof(char), sizeof(pBuffer));
        fdst.Write(pBuffer, sizeof(char), count);
    }
    
    return true;
}

void* File::GetBinary(const std::string &diskpath, size_t *pLength_out, size_t length_in)
{
    assert(pLength_out);
    *pLength_out = 0;
    
    bool ok = true;
    
    // read data from disk
    File fstream;
    ok = fstream.Open(diskpath, "rb");
    if (!ok) return nullptr;
    
    size_t length = 0;
    char* pBuffer = (char*)fstream.GetBinary(&length, length_in);
    fstream.Close();
    
    *pLength_out = length;
    return pBuffer;
}
