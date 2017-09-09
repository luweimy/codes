//
//  XString.cpp
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "XString.h"
#include <sstream>
using namespace LM;

// [String]

template<typename T>
std::string String::ToString(const T &var)
{
    std::ostringstream osstream;
    osstream<< var;
    return osstream.str();
}

std::vector<std::string> String::Split(const std::string &str, const std::string &pattern)
{
    std::string content = str;
    content += pattern;
    
    std::string::size_type x;
    std::vector<std::string> r;
    
    for(size_t i = 0; i < content.size(); i++) {
        x = content.find(pattern, i);
        if(x < content.size()) {
            std::string s = content.substr(i, x - i);
            r.push_back(s);
            i = x + pattern.size() - 1;
        }
    }
    return r;
}

