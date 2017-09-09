//
//  XDumper.h
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __LM_UTILITY_DUMPER__
#define __LM_UTILITY_DUMPER__

#include <stdint.h>

namespace LM
{
    /* Dump binary data output utility */
    class Dumper
    {
    public:
        template<typename T>
        static void Binary(T x);
        
        static void Binary(uint8_t  x);
        static void Binary(uint16_t x);
        static void Binary(uint32_t x);
        static void Binary(uint64_t x);
        
        static void Binary(int8_t  x);
        static void Binary(int16_t x);
        static void Binary(int32_t x);
        static void Binary(int64_t x);
    };
}

#endif /* __LM_UTILITY_DUMPER__ */
