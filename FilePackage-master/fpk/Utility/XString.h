//
//  XString.h
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __LM_UTILITY_STRING__
#define __LM_UTILITY_STRING__

#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include "XHash.h"

namespace LM
{
    class String
    {
    public:
        typedef std::vector<std::string> StringVector;
        
        static uint64_t GenID(const std::string &str)                                   {
            return LM::Hash::BKDR_FNV((unsigned char*)str.c_str(), str.length());
        }
        
        static std::string ToUpper(const std::string &str)                              {
            std::string tmp = str;
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), toupper);
            return tmp;
        }
        
        static std::string ToLower(const std::string &str)                              {
            std::string tmp = str;
            std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
            return tmp;
        }
        
        template<typename T>
        static std::string ToString(const T &var);
        
        static double      ToDouble(const std::string &str)                             {
            return ::atof(str.c_str());
        }
        
        static int         ToInteger(const std::string &str)                            {
            return ::atoi(str.c_str());
        }
        
        static std::string Trim(const std::string &str)                                 {
            return String::TrimR(String::TrimL(str));
        }
        
        static std::string TrimL(const std::string &str)                                {
            std::string tmp = str;
            auto fptr = std::not1(std::ptr_fun(isspace));
            auto it = std::find_if(tmp.begin(), tmp.end(), fptr);
            tmp.erase(tmp.begin(), it);
            return tmp;
        }
        
        static std::string TrimR(const std::string &str)                                {
            std::string tmp = str;
            auto fptr = std::not1(std::ptr_fun(isspace));
            auto it = std::find_if(tmp.rbegin(), tmp.rend(), fptr);
            tmp.erase(it.base(), tmp.end());
            return tmp;
        }
        
        static bool HasPrefix(const std::string &str, const std::string &prefix)        {
            size_t pre_len = prefix.length();
            return str.compare(0, pre_len, prefix) == 0;
        }
        
        static bool HasSuffix(const std::string &str, const std::string &suffix)        {
            size_t str_len = str.length();
            size_t pre_len = suffix.length();
            return str.compare(str_len-pre_len, pre_len, suffix) == 0;
        }
        
        static StringVector Split(const std::string &str, const std::string &pattern);
    };
}

#endif /* __LM_UTILITY_STRING__ */
