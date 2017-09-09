//
//  XDirectory.cpp
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "XDirectory.h"
#include "XPath.h"
#include "XFile.h"
#include <sys/stat.h>
#include <assert.h>
using namespace LM;

// [Directory]

Directory::Directory()
:m_pDirectory(nullptr)
,m_pDirent(nullptr)
{
}

Directory::~Directory()
{
    this->Close();
}

bool Directory::Open(const std::string &path)
{
    this->Close();
    m_pDirectory = ::opendir(path.c_str());
    if (!m_pDirectory)
        return false;
    m_path = path;
    return true;
}

void Directory::Reset()
{
    assert(m_pDirectory);
    ::rewinddir(m_pDirectory);
}

bool Directory::IsOpen()
{
    return (m_pDirectory != nullptr);
}

bool Directory::Close()
{
    if (m_pDirectory == nullptr) {
        m_pDirent = nullptr;
        return true;
    }
    int ok = closedir(m_pDirectory);
    if (ok != 0)
        return false;
    m_pDirectory = nullptr;
    m_pDirent = nullptr;
    m_path = "";
    return true;
}

bool Directory::Next()
{
    assert(m_pDirectory);
    m_pDirent = readdir(m_pDirectory);
    return (m_pDirent != nullptr);
}

bool Directory::IsFile()
{
    assert(m_pDirectory);
    assert(m_pDirent);
    return (m_pDirent->d_type == DT_REG);
}

bool Directory::IsFolder()
{
    assert(m_pDirectory);
    assert(m_pDirent);
    return (m_pDirent->d_type == DT_DIR);
}

const char* Directory::GetName()
{
    assert(m_pDirectory);
    assert(m_pDirent);
    return m_pDirent->d_name;
}

std::string Directory::GetPath()
{
    return Path::Append(m_path, this->GetName());
}

bool Directory::Make(const std::string &path)
{
    return (::mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0);
}

bool Directory::MakeDeep(const std::string &path)
{
    Path pathobj(path);
    const Path::StringVector& components = pathobj.GetComponents();
    
    char sep = Path::GetSeparator();
    std::string chdir_path(1, sep);
    for (auto com : components) {
        if (com.empty())
            continue;
        chdir_path += com + sep;
        if (File::Exist(chdir_path))
            continue;
        if (!Directory::Make(chdir_path))
            return false;
    }
    return true;
}

