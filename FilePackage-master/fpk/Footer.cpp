//
//  Footer.cpp
//  FilePackage
//
//  Created by Luwei on 15/1/13.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "Footer.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Utility/all.h"
#include "Entry.h"
#include "Header.h"

using namespace LM;

Footer::Footer()
{
}

Footer::~Footer()
{
    this->Clear();
}

bool Footer::Read(const File *pPackageFile, const Header *pHeader)
{
    assert(pPackageFile);
    assert(pHeader);
    
    this->Clear();
    const Header::package_header &ph = pHeader->m_ph;
    
    if (ph.offset == 0 || ph.length == 0)
        return true;
    
    // ensure divide exactly
    if ( (ph.length % Entry::GetSize()) != 0 )
        return false;
    
    bool ok = pPackageFile->SeekSet(ph.offset);
    if (!ok) return false;
    
    long count = ph.length / Entry::GetSize();
    ok = true;
    for (long i = 0; i < count; i++) {
        Entry *pEntry = new Entry;
        ok = pEntry->Read(pPackageFile);
        if (!ok) {
            delete pEntry;
            return false;
        }
        auto r = m_entryMap.insert(EntryPair(pEntry->m_entry.id, pEntry));
        if (!r.second) {
            delete pEntry;
            return false;
        }
    }
    
    if (!ok)
        this->Clear();
    return ok;
}

bool Footer::Write(const File *pPackageFile, const Header *pHeader)
{
    assert(pPackageFile);
    assert(pHeader);
    
    const Header::package_header &ph = pHeader->m_ph;
    
    assert(ph.offset != 0);
    bool ok = pPackageFile->SeekSet(ph.offset);
    if (!ok) return false;

    for (auto& pair : m_entryMap) {
        LM::Entry *pEntry = pair.second;
        ok = pEntry->Write(pPackageFile);
        if (!ok) break;
    }
    
    return ok;
}

bool Footer::Insert(Entry *pEntry)
{
    assert(pEntry);
    // pair.second is insert result
    auto pair = m_entryMap.insert(EntryPair(pEntry->m_entry.id, pEntry));
    return pair.second;
}

bool Footer::Remove(uint64_t entry_id)
{
    Entry *pEntry = this->Find(entry_id);
    if (pEntry) {
        delete pEntry;
        return (m_entryMap.erase(entry_id) == 1);
    }
    return false;
}

bool Footer::Update(uint64_t old_id)
{
    bool ok = false;
    Entry *pEntry = this->Find(old_id);
    if (pEntry) {
        ok = true;
        ok &= (m_entryMap.erase(old_id) == 1);
        ok &= this->Insert(pEntry);
    }
    return ok;
}

Entry* Footer::Find(uint64_t entry_id)
{
    auto iter = m_entryMap.find(entry_id);
    if (iter == m_entryMap.end())
        return nullptr;
    
    return (iter->second);
}

bool Footer::IsExist(uint64_t entry_id) const
{
    // not found
    if (m_entryMap.find(entry_id) == m_entryMap.end())
        return false;
    return true;
}

bool Footer::IsEmpty() const
{
    return (m_entryMap.size() == 0);
}

void Footer::Clear()
{
    for (auto pair : m_entryMap) {
        Entry *pEntry = pair.second;
        delete pEntry;
    }
    m_entryMap.clear();
}

size_t Footer::Count() const
{
    return m_entryMap.size();
}

void Footer::Traverse(TraverseCallback callback)
{
    for (auto pair : m_entryMap) {
        if (!callback(pair.second))
            break;
    }
}

void Footer::Dump(uint64_t entry_id) const
{
    if (0 == entry_id) {
        int counter = 0;
        for (auto & pair : m_entryMap) {
            Entry *pEntry = pair.second;
            counter += (pEntry->m_entry.flag == Entry::State::NORMAL) ? 1 : 0;
            pEntry->Dump();
        }
        printf("================= Footer =================\n");
        printf("[Entry-Count ]: %d\n\n", counter);
    }
    else {
        auto iter = m_entryMap.find(entry_id);
        if (iter != m_entryMap.end())
            iter->second->Dump();
    }
}

