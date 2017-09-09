//
//  XCrypto.cpp
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "XCrypto.h"
#include <stdio.h>
using namespace LM;

// [LM1]

void Crypto::LM1::Enc64(unsigned char*ptr, size_t length, uint64_t key)
{
    for (size_t i = 0; i < length; i++) {
        unsigned char c = ptr[i];
        c ^= key;
        c ^= key >> 8;
        c ^= key >> 16;
        c ^= key >> 24;
        c ^= key >> 32;
        c ^= key >> 40;
        c ^= key >> 48;
        c ^= key >> 56;
        ptr[i] = c;
    }
}

void Crypto::LM1::Dec64(unsigned char*ptr, size_t length, uint64_t key)
{
    for (size_t i = 0; i < length; i++) {
        unsigned char c = ptr[i];
        c ^= key >> 56;
        c ^= key >> 48;
        c ^= key >> 40;
        c ^= key >> 32;
        c ^= key >> 24;
        c ^= key >> 16;
        c ^= key >> 8;
        c ^= key;
        ptr[i] = c;
    }
}

void Crypto::LM1::Enc32(unsigned char *ptr, size_t length, uint32_t key)
{
    for (size_t i = 0; i < length; i++) {
        unsigned char c = ptr[i];
        c ^= key;
        c ^= key >> 8;
        c ^= key >> 16;
        c ^= key >> 24;
        ptr[i] = c;
    }
}

void Crypto::LM1::Dec32(unsigned char *ptr, size_t length, uint32_t key)
{
    for (size_t i = 0; i < length; i++) {
        unsigned char c = ptr[i];
        c ^= key >> 24;
        c ^= key >> 16;
        c ^= key >> 8;
        c ^= key;
        ptr[i] = c;
    }
}

void Crypto::LM1::Enc16(unsigned char*ptr, size_t length, uint16_t key)
{
    for (size_t i = 0; i < length; i++) {
        unsigned char c = ptr[i];
        c ^= key;
        c ^= key >> 8;
        ptr[i] = c;
    }
}

void Crypto::LM1::Dec16(unsigned char*ptr, size_t length, uint16_t key)
{
    for (size_t i = 0; i < length; i++) {
        unsigned char c = ptr[i];
        c ^= key >> 8;
        c ^= key;
        ptr[i] = c;
    }
}

// [LM2]

void Crypto::LM2::Calc64(unsigned char*ptr, size_t length, uint64_t key)
{
    const int key_len = 8;
    size_t enc_len = length - length % key_len;
    
    for (size_t i = 0; i < enc_len; i += key_len) {
        *(uint64_t*)(ptr + i) ^= key;
    }
    
    for (int i = 0; i < length % key_len; i++) {
        ptr[enc_len+i] ^= key >> i*key_len;
    }
}

void Crypto::LM2::Calc32(unsigned char*ptr, size_t length, uint32_t key)
{
    const int key_len = 4;
    size_t enc_len = length - length % key_len;
    
    for (size_t i = 0; i < enc_len; i += key_len) {
        *(uint32_t*)(ptr + i) ^= key;
    }
    
    for (int i = 0; i < length % key_len; i++) {
        ptr[enc_len+i] ^= key >> i*key_len;
    }
}

void Crypto::LM2::Calc16(unsigned char*ptr, size_t length, uint16_t key)
{
    const int key_len = 2;
    size_t enc_len = length - length % key_len;
    
    for (size_t i = 0; i < enc_len; i += key_len) {
        *(uint16_t*)(ptr + i) ^= key;
    }
    
    for (int i = 0; i < length % key_len; i++) {
        ptr[enc_len+i] ^= key >> i*key_len;
    }
}

