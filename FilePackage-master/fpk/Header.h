//
//  Header.h
//  FilePackage
//
//  Created by Luwei on 15/1/13.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __FPK__HRADER__
#define __FPK__HRADER__

#include <stdio.h>
#include <stdint.h>
#include "define.h"

namespace LM
{
    class File;
    class Footer;
    class Header
    {
    public:
        Header();
        ~Header();
        Header(const Header &) = delete;
        Header& operator=(const Header &) = delete;
        
        bool Read(const File *pPackageFile);
        bool Write(const File *pPackageFile, const Footer *pFooter);
        bool Check() const;
        void Clear();
        
        void Initialize(uint32_t version);

        void Dump() const;
        void Dump16() const;
        void Dump2() const;
        
        static size_t GetSize() {
            return sizeof(uint16_t)+sizeof(uint32_t)+sizeof(uint64_t)*2+sizeof(uint8_t)*16;
        }
        
    public:
        struct package_header {
            uint16_t sign;          /** 包固定标记(用于标示是否为合理数据包) */
            uint32_t version;       /** 资源包的版本 */
            uint64_t offset;        /** 文件尾列表区偏移量 */
            uint64_t length;        /** 文件尾列表区长度 */
            uint8_t  reserved[16];  /** 保留字 */
        } m_ph;
    };
}



#endif /* __FPK__HRADER__ */
