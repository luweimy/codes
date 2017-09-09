//
//  Package.h
//  FilePackage
//
//  Created by Luwei on 15/1/13.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __FPK__PACKAGE__
#define __FPK__PACKAGE__

#include <stdio.h>
#include <string>
#include "define.h"
#include "Utility/all.h"
#include "Header.h"
#include "Body.h"
#include "Footer.h"

namespace LM
{
    class Package
    {
    public:
        Package();
        ~Package();
        Package(const Package &) = delete;
        Package& operator=(const Package &) = delete;
        
        /** [Load]加载数据包，同时只能打开一个
            [Unload]卸载数据包，必须先[Unload]才能再次[Load]
            [IsValid]数据包是否有效 */
        bool Load(const std::string &package);
        bool Unload();
        bool IsValid();
        
        /** [Append]将文件追加到数据包种，如果存在重名则失败
            [Remove]不会真实删除数据，仅仅将其标记为`REMOVE` 
            [NOTE] 如果想插入重名的文件，则应该先[Remove], 然后[Append] */
        bool Append(const std::string &diskfile);
        bool Append(const std::string &keypath, const char*pBuffer, size_t length);
        bool Remove(const std::string &filepath);
        
        /** 会将数据头和数据尾更新到数据包中, 但不会删除数据包中的数据
            会在数据包卸载时自动调用 */
        bool Flush();
        
        /** [Merge]将另一个数据包合并到当前数据包中，不会修改另一个数据包
            若存在重名现象，则停止合并 */
        bool Merge(const std::string &package);
        bool Merge(Package *pOther);

        /** 此操作配合[Remove]操作使用
            将标记为REMOVE的数据删除出数据包，此操作比较费时，谨慎使用 */
        bool Update();

        /** [GetString] 获取字符串
            [GetBinary] 获取二进制数据，必须手动释放[Memory::Get().Free()] */
        std::string GetString(const std::string &filepath);
        unsigned char* GetBinary(const std::string &filepath, size_t *pLength_out);
        
        /** 检测文件是否在资源包中 */
        bool Exist(const std::string &filepath);
        
        /** 获得资源包的大小(单位：字节) */
        size_t GetSize();
        
        void Dump();
        uint32_t GetVersion();
        
    private:
        bool ResolveConflict(uint64_t id);
        bool Append(uint64_t keyid, const char* pBuffer, size_t length);
        bool Build(const std::string &package);
        
    private:
        File        m_file;
        Header      m_header;
        Body        m_body;
        Footer      m_footer;
        
        bool        m_updateDirty;
    };
}
#endif /* __FPK__PACKAGE__ */
