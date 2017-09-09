//
//  XCrypto.h
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __LM_UTILITY_CRYPTO__
#define __LM_UTILITY_CRYPTO__
#include <stdlib.h>
#include <stdint.h>

namespace LM
{
    class Crypto
    {
    public:
        // LM1 Encryption algorithm
        class LM1 {
        public:
            static void Enc64(unsigned char*ptr, size_t length, uint64_t key);
            static void Dec64(unsigned char*ptr, size_t length, uint64_t key);
            
            static void Enc32(unsigned char*ptr, size_t length, uint32_t key);
            static void Dec32(unsigned char*ptr, size_t length, uint32_t key);
            
            static void Enc16(unsigned char*ptr, size_t length, uint16_t key);
            static void Dec16(unsigned char*ptr, size_t length, uint16_t key);
        };
        
        // LM2 Encryption algorithm
        class LM2 {
        public:
            static void Calc64(unsigned char*ptr, size_t length, uint64_t key);
            static void Calc32(unsigned char*ptr, size_t length, uint32_t key);
            static void Calc16(unsigned char*ptr, size_t length, uint16_t key);
        };
    };
}

#endif /* __LM_UTILITY_CRYPTO__ */
