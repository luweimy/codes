//
//  XDirectory.h
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __LM_UTILITY_DIRECTORY__
#define __LM_UTILITY_DIRECTORY__
#include <dirent.h>
#include <string>

namespace LM
{
    class Directory
    {
    public:
        Directory();
        ~Directory();
        Directory(const Directory&) = delete;
        Directory& operator=(const Directory&) = delete;
        
        bool Open(const std::string &path);
        void Reset();
        bool IsOpen();
        bool Close();
        bool Next();
        bool IsFile();
        bool IsFolder();
        const char* GetName();
        std::string GetPath();
        
        static bool Make(const std::string &path);
        static bool MakeDeep(const std::string &path);
        
    private:
        dirent*     m_pDirent;
        DIR*        m_pDirectory;
        std::string m_path;
    };
}

#endif /* __LM_UTILITY_DIRECTORY__ */
