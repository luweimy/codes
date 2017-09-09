//
//  Entry.h
//  FilePackage
//
//  Created by Luwei on 15/1/13.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __FPK__ENTRY__
#define __FPK__ENTRY__

#include <stdio.h>
#include <stdint.h>
#include "define.h"

namespace LM
{
    class File;
    class Entry
    {
    public:
        
        Entry();
        ~Entry();
        Entry(const Entry &) = delete;
        Entry& operator=(const Entry &) = delete;
        
        bool Read(const File *pPackageFile);
        bool Write(const File *pPackageFile);
        void Clear();
        
        void Dump() const;
        void Dump16() const;
        void Dump2() const;
        
        static size_t GetSize() {
            return sizeof(uint64_t) * 3 + sizeof(uint32_t) + sizeof(uint8_t);
        }

    public:
        struct package_entry {
            uint64_t offset;        /** 文件内容偏移量 */
            uint64_t length;        /** 文件内容长度 */
            uint64_t id;            /** 文件名id */
            uint32_t crc32;         /** 文件crc32校验码 */
            uint8_t  flag;          /** 文件状态(State) */
        } m_entry;
        
        enum State {
            NORMAL,                 /** 文件正常状态(默认) */
            REMOVE,                 /** 文件标记为删除 */
        };
    };
}

#endif /* __FPK__ENTRY__ */
