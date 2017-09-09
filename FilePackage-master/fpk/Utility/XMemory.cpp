//
//  XMemory.cpp
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "XMemory.h"
#include <memory.h>
#include <assert.h>
using namespace LM;

// [Memory]

Memory* Memory::m_instance = nullptr;

void Memory::Dump()
{
    for (auto pair : m_pointerMap) {
        printf(" > %16p \t size:%lu\n", pair.first, pair.second);
    }
}

Memory::Memory()
{
}
Memory::~Memory()
{
    m_pointerMap.clear();
}

