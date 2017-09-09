//
//  Error.cpp
//  FilePackage
//
//  Created by Luwei on 15/1/15.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "Error.h"
#include <string.h>
#include <stdarg.h>
#include <assert.h>

using namespace LM;

const char* Error::FILE_PATH_EMPTY  = "File path is empty";
const char* Error::FILE_READ        = "File read failed";
const char* Error::PKG_ALREADY_OPEN = "Package already open";
const char* Error::PKG_OPEN         = "Package open failed";
const char* Error::PKG_BUILD        = "Build package failed";
const char* Error::PKG_INVALID      = "Package is invalid";
const char* Error::PKG_UPDATE       = "Package update failed";
const char* Error::PKG_MERGE        = "Package merge failed";
const char* Error::PKG_CLOSE        = "Package close failed";
const char* Error::PKG_CONFLICT     = "Package have conflict name";
const char* Error::PKG_CRC32        = "Package entry crc32 detection failed";

Error* Error::m_instance = nullptr;

Error& Error::Get()
{
    if (!m_instance)
        m_instance = new Error();
    return *m_instance;
}

bool Error::Put(const char *format, ...)
{
    char pBuffer[128];
    memset(&pBuffer, 0, sizeof(pBuffer));
    
    va_list ap;
    va_start(ap, format);
    vsnprintf(pBuffer, sizeof(pBuffer), format, ap);
    va_end(ap);
    
    printf("[FPK-ERROR] # %s\n", pBuffer);
    return false;
}

Error::Error()
{
}

Error::~Error()
{
}
