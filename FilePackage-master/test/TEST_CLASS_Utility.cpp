//
//  TEST_CLASS_Utility.cpp
//  FilePackage
//
//  Created by Guy on 15/2/5.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "TEST_CLASS_Utility.h"
#include <iostream>
#include <string.h>
#include <vector>
#include "../fpk/Utility/all.h"
using namespace std;

#define __IF_OK__(ok,reason) if(!ok){printf("%s\n",reason); return false;}
#define __IF_TRUE__(ok,reason) if(ok){ printf("测试成功 -- %s \n",reason); } else{ printf("%s 失败！！！\n",reason); }

bool test_Hash();
bool test_Random();
bool test_String();
bool test_Crypto();

bool TEST_CLASS_Utility()
{
    cout<<"----------------- TEST-Utility ----------------------\n"<<endl;
    bool ret = true;
    
//    test_Hash();
    
    ret = test_Random();
    __IF_TRUE__(ret, "Random() ")
    
    ret = test_String();
    __IF_TRUE__(ret, "test_String()");
    
    ret = test_Crypto();
    __IF_TRUE__(ret, "test_Crypto()");
    
    return true;
}

bool test_Hash()
{
    const char *buf = "我又一只小毛驴呀咿呀咿呀哟";
    unsigned char *buffStr = (unsigned char*)(const_cast<char*>(buf));
    uint32_t crc32 = LM::Hash::CRC32(buffStr, 40);
    
    string hashValue = LM::Hash::ToString(crc32);
    printf("hashValue is %s\n",hashValue.c_str());
    
    return true;
}

bool test_Random()
{
    int ran = 0;
    int min = 2147483646;
    bool ok = true;
    for(int i = 0; i < 50; i++)
    {
        ran = LM::Random::Gen(min);
        ok = ran >= min;
        __IF_OK__(ok, "random value has bigger than min");
    }
    return true;
}

bool test_String()
{
    bool ok = true;
    char* a = "123545";
    double aDouble = LM::String::ToDouble(a);
//    printf("aStr -> %lf\n", aDouble);
    
    int aInt = LM::String::ToInteger(a);
//    printf("aStr -> %d\n", aInt);
    
    string hasSpace = " 你好，hello \n";
    string noSpace = LM::String::Trim(hasSpace);
//    printf("noSpace -> a%sa\n",noSpace.c_str());
    
    string prefix = " 你";
    ok = LM::String::HasPrefix(hasSpace, prefix);
    __IF_OK__(ok, "LM::String::HasPrefix No!");
    
    string suffix = "o \n";
    ok = LM::String::HasSuffix(hasSpace, suffix);
    __IF_OK__(ok, "LM::String::HasSuffix No!");
    
    LM::String::StringVector vector = LM::String::Split(hasSpace, "，");
    __IF_OK__((vector[0] != ""), "LM::String::Split()");
    
    return true;
}

bool test_Crypto()
{
    bool ok = true;
    char from[30] = "wo you yi zhi 小毛驴哈哈";
    char to[30];
    for (int i = 0; i<30; i++) {
        to[i] = from[i];
    }
    unsigned char *unsignFrom = (unsigned char*)to;
    //LM1 64
    uint64_t key64 = 123456;
    LM::Crypto::LM1::Enc64(unsignFrom, strlen((const char*)unsignFrom), key64);
    LM::Crypto::LM1::Dec64(unsignFrom, strlen((const char*)unsignFrom), key64);
    ok = strcmp(from, to);
    __IF_OK__(!ok, "LM::Crypto::LM1::Enc64()、Dec32(), not ok");
    //LM1 32
    uint32_t key32 = 123456;
    LM::Crypto::LM1::Enc32(unsignFrom, strlen((const char*)unsignFrom), key32);
    LM::Crypto::LM1::Dec32(unsignFrom, strlen((const char*)unsignFrom), key32);
    ok = strcmp(from, to);
    __IF_OK__(!ok, "LM::Crypto::LM1::Enc32()、Dec32(), not ok");
    //LM1 16
    uint32_t key16 = 123456;
    LM::Crypto::LM1::Enc16(unsignFrom, strlen((const char*)unsignFrom), key16);
    LM::Crypto::LM1::Dec16(unsignFrom, strlen((const char*)unsignFrom), key16);
    ok = strcmp(from, to);
    __IF_OK__(!ok, "LM::Crypto::LM1::Enc16()、Dec16(), not ok");
    
    //LM2 64
    LM::Crypto::LM2::Calc64(unsignFrom, strlen((const char*)unsignFrom), key64);
    LM::Crypto::LM2::Calc64(unsignFrom, strlen((const char*)unsignFrom), key64);
    ok = strcmp(from, to);
    __IF_OK__(!ok, "LM::Crypto::LM1::Calc64()、Calc64(), not ok");
    //LM2 32
    LM::Crypto::LM2::Calc32(unsignFrom, strlen((const char*)unsignFrom), key32);
    LM::Crypto::LM2::Calc32(unsignFrom, strlen((const char*)unsignFrom), key32);
    ok = strcmp(from, to);
    __IF_OK__(!ok, "LM::Crypto::LM1::Calc32()、Calc32(), not ok");
    //LM2 16
    LM::Crypto::LM2::Calc16(unsignFrom, strlen((const char*)unsignFrom), key16);
    LM::Crypto::LM2::Calc16(unsignFrom, strlen((const char*)unsignFrom), key16);
    ok = strcmp(from, to);
    __IF_OK__(!ok, "LM::Crypto::LM1::Calc16()、Calc16(), not ok");
    
    return true;
}

