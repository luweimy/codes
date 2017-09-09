//
//  XCompressor.h
//  Utility
//
//  Created by Luwei on 15/2/2.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __LM_UTILITY_COMPRESSOR__
#define __LM_UTILITY_COMPRESSOR__

#include "libs/bzip2/bzlib.h"

namespace LM {
    class Compressor {
    public:
        static bool Compress(char* dst, unsigned *dstlen, char* src, unsigned srclen)   {
            int c = BZ2_bzBuffToBuffCompress(dst, dstlen, src, srclen, 1, 0, 0);
            if (c != BZ_OK)
                printf("[BZip2:Compress] error code: %d", c);
            return c == BZ_OK;
        }
        
        static bool Decompress(char* dst, unsigned *dstlen, char* src, unsigned srclen) {
            int c = BZ2_bzBuffToBuffDecompress(dst, dstlen, src, srclen, 0, 0);
            if (c != BZ_OK)
                printf("[BZip2:Decompress] error code: %d", c);
            return c == BZ_OK;
        }
    };

}

#endif /* __LM_UTILITY_COMPRESSOR__ */
