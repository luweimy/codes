//
//  XDumper.cpp
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "XDumper.h"
#include <stdio.h>
using namespace LM;

// [Dumper]

template<typename T>
void Dumper::Binary(T x)
{
    unsigned char *ptr = (unsigned char*)(&x);
    for (int i = 0; i < sizeof(T); i++) {
        unsigned char uc = ptr[i];
        unsigned char index = 0x80;
        while (index > 0) {
            putchar(uc & index ? '1' : '0');
            index >>= 1;
        }
        putchar(' ');
    }
}

void Dumper::Binary(uint8_t x)
{
    Dumper::Binary<uint8_t>(x);
}

void Dumper::Binary(uint16_t x)
{
    Dumper::Binary<uint16_t>(x);
}

void Dumper::Binary(uint32_t x)
{
    Dumper::Binary<uint32_t>(x);
}

void Dumper::Binary(uint64_t x)
{
    Dumper::Binary<uint64_t>(x);
}

void Dumper::Binary(int8_t  x)
{
    Dumper::Binary<int8_t>(x);
}

void Dumper::Binary(int16_t x)
{
    Dumper::Binary<int16_t>(x);
}

void Dumper::Binary(int32_t x)
{
    Dumper::Binary<int32_t>(x);
}

void Dumper::Binary(int64_t x)
{
    Dumper::Binary<int64_t>(x);
}

