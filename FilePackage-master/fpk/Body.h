//
//  Body.h
//  FilePackage
//
//  Created by Luwei on 15/1/14.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __FPK__BODY__
#define __FPK__BODY__

#include <stdio.h>
#include <string>
#include "Entry.h"
#include "define.h"

namespace LM
{
    class File;
    class Body
    {
    public:
        Body();
        ~Body();
        Body(const Body &) = delete;
        Body& operator=(const Body &) = delete;
        
        // v2
        
        bool Read(const File *pPackageFile,
                  const Entry *pEntry,
                  void **ppBuffer_out,
                  size_t *pLength_out);
        
        bool Write(const File *pPackageFile,
                   const Entry *pEntry,
                   const char* pBuffer);
    };
}


#endif /* __FPK__BODY__ */
