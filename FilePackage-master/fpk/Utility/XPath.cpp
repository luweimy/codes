//
//  XPath.cpp
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "XPath.h"
using namespace LM;

// [Path]

Path::Path(const std::string& path)
{
    m_origin = path;
    std::string str = path;
    for (size_t i = 0; i < str.size(); ++i)
    {
#ifdef _WIN32
        if (str[i] == '/')
            str[i] = '\\';
#else
        if (str[i] == '\\')
            str[i] = '/';
#endif
    }
    
    size_t x = 0;
    for (size_t i = 0; i < str.size(); ++i)
        if (str[i] == '/' || str[i] == '\\')
            x = i + 1;
    
    m_path      = str.substr(0, x);
    m_filename  = str.substr(x);
    
    for (size_t i = 0; i < m_filename.size(); ++i)
        if (m_filename[i] == '.')
            m_extension = m_filename.substr(i + 1);
}

const Path::StringVector& Path::GetComponents()
{
    if (m_components.size() != 0)
        return m_components;
    
    std::string path = m_origin;
    std::string sep(1, Path::GetSeparator());
    m_components = String::Split(path, sep);
    return m_components;
}

std::string Path::Append(const std::string &path, const std::string &component)
{
    std::string r = path;
    char sep = Path::GetSeparator();
    std::string sep_str(1, sep);
    if (String::HasSuffix(r, sep_str))
        return r + component;
    else
        return r + sep_str + component;
}

std::string Path::GetTemp()
{
    return ::tmpnam(nullptr);
}

char Path::GetSeparator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

