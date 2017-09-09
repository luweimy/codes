//
//  XHash.h
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __LM_UTILITY_HASH__
#define __LM_UTILITY_HASH__

#include <stdlib.h>
#include <string>

namespace LM
{
    /** Hash: CRC32 / FNV / BKDR / FNV & BKDR */
    class Hash
    {
    public:
        static uint32_t CRC32(const unsigned char *buf, size_t length);
        
        static uint32_t FNV(const unsigned char* buf, size_t length);
        static uint32_t BKDR(const unsigned char* buf, size_t length);
        static uint64_t BKDR_FNV(const unsigned char *buf, size_t length);
        
        static std::string ToString(uint32_t hash);
        static std::string ToString(uint64_t hash);
    };

}

#endif /* __LM_UTILITY_HASH__ */
