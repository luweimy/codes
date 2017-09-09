//
//  Entry.cpp
//  FilePackage
//
//  Created by Luwei on 15/1/13.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "Entry.h"
#include "Utility/all.h"
#include <memory.h>
#include <assert.h>
using namespace LM;

Entry::Entry()
{
    LM::Memory::Get().Insert(this, sizeof(Entry));
}

Entry::~Entry()
{
    LM::Memory::Get().Remove(this);
}

bool Entry::Read(const File *pPackageFile)
{
    assert(pPackageFile);

    this->Clear();
    
    size_t count = 0;
    count = pPackageFile->Read(&m_entry.offset, sizeof(m_entry.offset), 1)  &
            pPackageFile->Read(&m_entry.length, sizeof(m_entry.length), 1)  &
            pPackageFile->Read(&m_entry.id,     sizeof(m_entry.id), 1)      &
            pPackageFile->Read(&m_entry.crc32,  sizeof(m_entry.crc32), 1)   &
            pPackageFile->Read(&m_entry.flag,   sizeof(m_entry.flag), 1)    ;
    if (count != 1)
        return false;
    
    m_entry.offset  = Endian::ToHost(m_entry.offset);
    m_entry.length  = Endian::ToHost(m_entry.length);
    m_entry.id      = Endian::ToHost(m_entry.id);
    m_entry.crc32   = Endian::ToHost(m_entry.crc32);
    m_entry.flag    = Endian::ToHost(m_entry.flag);
    
    return true;
}

bool Entry::Write(const File *pPackageFile)
{
    assert(pPackageFile);
    
    auto offset = Endian::ToNet(m_entry.offset);
    auto length = Endian::ToNet(m_entry.length);
    auto id     = Endian::ToNet(m_entry.id);
    auto crc32  = Endian::ToNet(m_entry.crc32);
    auto flag   = Endian::ToNet(m_entry.flag);
    
    size_t count = 0;
    count = pPackageFile->Write(&offset, sizeof(m_entry.offset), 1)  &
            pPackageFile->Write(&length, sizeof(m_entry.length), 1)  &
            pPackageFile->Write(&id,    sizeof(m_entry.id), 1)       &
            pPackageFile->Write(&crc32, sizeof(m_entry.crc32), 1)    &
            pPackageFile->Write(&flag,  sizeof(m_entry.flag), 1)     ;
    if (count != 1)
        return false;
    return true;
}

void Entry::Clear()
{
    memset(&m_entry, 0, sizeof(Entry::package_entry));
}

void Entry::Dump() const
{
    printf("----------------- Entry -----------------\n");
    printf("[Entry.offset] -> %llu\n", m_entry.offset);
    printf("[Entry.length] -> %llu\n", m_entry.length);
    printf("[Entry.id    ] -> %llu\n", m_entry.id);
    printf("[Entry.crc32 ] -> %u\n", m_entry.crc32);
    printf("[Entry.flag  ] -> %d\n", m_entry.flag);
}

void Entry::Dump16() const
{
    unsigned char *ucptr = (unsigned char*)(&m_entry);
    for (int i = 0; i < (int)sizeof(Entry::package_entry); i++) {
        unsigned char uc = ucptr[i];
        printf("%02X", uc);
        if ((i+1) % 2 == 0)
            putchar(' ');
    }
    putchar('\n');
}

void Entry::Dump2() const
{
    unsigned char *ucptr = (unsigned char*)(&m_entry);
    for (int i = 0; i < (int)sizeof(Entry::package_entry); i++) {
        unsigned char uc = ucptr[i];
        Dumper::Binary(uc);
        putchar(' ');
    }
    putchar('\n');
}

