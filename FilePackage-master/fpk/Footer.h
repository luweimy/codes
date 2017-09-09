//
//  Footer.h
//  FilePackage
//
//  Created by Luwei on 15/1/13.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __FPK__FOOTER__
#define __FPK__FOOTER__

#include <stdio.h>
#include <stdint.h>
#include <unordered_map>
#include <functional>
#include "Entry.h"
#include "define.h"

namespace LM
{
    typedef std::unordered_map<uint64_t, Entry*> EntryMap;
    typedef std::pair<uint64_t, Entry*>          EntryPair;
    typedef std::function<bool(Entry*)>          TraverseCallback;
    
    class File;
    class Header;
    class Footer
    {
    public:
        Footer();
        ~Footer();
        Footer(const Footer &) = delete;
        Footer& operator=(const Footer &) = delete;
        
        bool Read(const File *pPackageFile, const Header *pHeader);
        bool Write(const File *pPackageFile, const Header *pHeader);
        
        bool Insert(Entry *entry);
        bool Remove(uint64_t entry_id);
        bool Update(uint64_t old_id);
        Entry* Find(uint64_t entry_id);
        
        bool   IsExist(uint64_t entry_id) const;
        bool   IsEmpty() const;
        void   Clear();
        size_t Count() const;
        
        void Traverse(TraverseCallback callback);
        
        void Dump(uint64_t entry_id = 0) const;
        
    private:
        EntryMap    m_entryMap;
    };
}

#endif /* __FPK__FOOTER__ */
