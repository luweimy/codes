//
//  Error.h
//  FilePackage
//
//  Created by Luwei on 15/1/15.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __FPK__ERROR__
#define __FPK__ERROR__

#include <stdio.h>

namespace LM
{
    
    class Error
    {
    public:
        
        static const char* FILE_PATH_EMPTY;
        static const char* FILE_READ;
        static const char* PKG_ALREADY_OPEN;
        static const char* PKG_OPEN;
        static const char* PKG_BUILD;
        static const char* PKG_INVALID;
        static const char* PKG_UPDATE;
        static const char* PKG_MERGE;
        static const char* PKG_CLOSE;
        static const char* PKG_CONFLICT;
        static const char* PKG_CRC32;
        
        static Error& Get();
        bool Put(const char *format, ...);
        
    private:
        Error();
        ~Error();
        Error(const Error&) = delete;
        Error& operator=(const Error&) = delete;

    private:
        static Error* m_instance;
    };
}

#endif /* __FPK__ERROR__ */
