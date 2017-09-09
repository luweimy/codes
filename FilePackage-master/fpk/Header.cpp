//
//  Header.cpp
//  FilePackage
//
//  Created by Luwei on 15/1/13.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "Header.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Utility/all.h"
#include "Footer.h"
#include "Entry.h"
#include "define.h"

using namespace LM;

Header::Header()
{
    this->Clear();
}

Header::~Header()
{
}

bool Header::Read(const File *pPackageFile)
{
    assert(pPackageFile);
    this->Clear();
    
    pPackageFile->SeekSet();
    size_t count = 0;
    count = pPackageFile->Read(&m_ph.sign, sizeof(m_ph.sign), 1)        &
            pPackageFile->Read(&m_ph.version, sizeof(m_ph.version), 1)  &
            pPackageFile->Read(&m_ph.offset, sizeof(m_ph.offset), 1)    &
            pPackageFile->Read(&m_ph.length, sizeof(m_ph.length), 1)    ;
    if (count != 1)
        return false;
    
    m_ph.sign = Endian::ToHost(m_ph.sign);
    m_ph.version = Endian::ToHost(m_ph.version);
    m_ph.offset = Endian::ToHost(m_ph.offset);
    m_ph.length = Endian::ToHost(m_ph.length);
    return true;
}

bool Header::Write(const File *pPackageFile, const Footer *pFooter)
{
    assert(pPackageFile);
    assert(pFooter);
    
    m_ph.length = pFooter->Count() * Entry::GetSize();

    pPackageFile->SeekSet();
    
    auto sign = Endian::ToNet(m_ph.sign);
    auto version = Endian::ToNet(m_ph.version);
    auto offset = Endian::ToNet(m_ph.offset);
    auto length = Endian::ToNet(m_ph.length);
    
    size_t count = 0;
    count = pPackageFile->Write(&sign, sizeof(m_ph.sign), 1)        &
            pPackageFile->Write(&version, sizeof(m_ph.version), 1)  &
            pPackageFile->Write(&offset, sizeof(m_ph.offset), 1)    &
            pPackageFile->Write(&length, sizeof(m_ph.length), 1)    &
            pPackageFile->Write(&m_ph.reserved, sizeof(m_ph.reserved), 1);
    
    if (count != 1)
        return false;
    return true;
}

bool Header::Check() const
{
    if (m_ph.sign != FPK_CODE_SIGN ||
        m_ph.version == 0 ||
        m_ph.offset == 0  )
        return false;
    return true;
}

void Header::Clear()
{
    memset(&m_ph, 0, sizeof(Header::package_header));
}

void Header::Initialize(uint32_t version)
{
    this->Clear();
    m_ph.sign = FPK_CODE_SIGN;
    m_ph.version = version;
    m_ph.offset = Header::GetSize();
}

void Header::Dump() const
{
    printf("----------------- Header -----------------\n");
    printf("[Header.sign   ] -> 0x%0x\n", m_ph.sign);
    printf("[Header.version] -> %u\n", m_ph.version);
    printf("[Header.offset ] -> %llu\n", m_ph.offset);
    printf("[Header.length ] -> %llu\n", m_ph.length);
}

void Header::Dump16() const
{
    unsigned char *ucptr = (unsigned char*)(&m_ph);
    for (int i = 0; i < (int)sizeof(Header::package_header); i++) {
        unsigned char uc = ucptr[i];
        printf("%02X", uc);
        if ((i+1) % 2 == 0)
            putchar(' ');
    }
    putchar('\n');
}

void Header::Dump2() const
{
    unsigned char *ucptr = (unsigned char*)(&m_ph);
    for (int i = 0; i < (int)sizeof(Header::package_header); i++) {
        unsigned char uc = ucptr[i];
        Dumper::Binary(uc);
        putchar(' ');
    }
    putchar('\n');
}
