//
//  Body.cpp
//  FilePackage
//
//  Created by Luwei on 15/1/14.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "Body.h"
#include "Footer.h"
#include "Header.h"
#include "Error.h"
#include "Utility/all.h"
#include <assert.h>
using namespace LM;

Body::Body()
{
}

Body::~Body()
{
}

bool Body::Read(const File *pPackageFile,
                const Entry *pEntry,
                void **ppBuffer_out,
                size_t *pLength_out)
{
    assert(pPackageFile);
    assert(pEntry);
    assert(ppBuffer_out);
    assert(pLength_out);
    
    *ppBuffer_out = nullptr;
    *pLength_out = 0;
    
    const Entry::package_entry &entry = pEntry->m_entry;
    
    pPackageFile->SeekSet(entry.offset);
    size_t length = 0;
    void *pBuffer = pPackageFile->GetBinary(&length, entry.length);
    if (!pBuffer)
        return false;
    
#ifdef FPK_SECRET_KEY
    LM::Crypto::LM2::Calc64((unsigned char*)pBuffer, length, FPK_SECRET_KEY);
#endif
    
#ifdef FPK_CHECK_CRC32
    uint32_t crc32 = Hash::CRC32((unsigned char*)pBuffer, entry.length);
    if (entry.crc32 != 0 && crc32 != entry.crc32) {
        LM::Memory::Get().Free(pBuffer);
        return FPK_Error(Error::PKG_CRC32);
    }
#endif
    
    *ppBuffer_out = pBuffer;
    *pLength_out = length;
    
    return true;
}

bool Body::Write(const File *pPackageFile,
                 const Entry *pEntry,
                 const char* pBuffer)
{
    assert(pPackageFile);
    assert(pEntry);
    assert(pBuffer);
    
    const Entry::package_entry &entry = pEntry->m_entry;

    bool ok = pPackageFile->SeekSet(entry.offset);
    if (!ok) return false;
    
#ifdef FPK_SECRET_KEY
    LM::Crypto::LM2::Calc64((unsigned char*)pBuffer, entry.length, FPK_SECRET_KEY);
#endif
    
    size_t count = pPackageFile->Write(pBuffer, sizeof(char), entry.length);
    if (count != entry.length)
        return false;
    
    return true;
}


