//
//  XPath.h
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __LM_UTILITY_PATH__
#define __LM_UTILITY_PATH__
#include <string>
#include "XString.h"

namespace LM
{
    class Path
    {
    public:
        typedef LM::String::StringVector StringVector;
        Path(const std::string& path);
        
        const std::string&  GetOrigin()         {
            return m_origin;
        }
        const std::string&  GetExtension()      {
            return m_extension;
        }
        const std::string&  GetFilename()       {
            return m_filename;
        }
        const std::string&  GetPath()           {
            return m_path;
        }
        const StringVector& GetComponents();
        
        static std::string Append(const std::string &path, const std::string &component);
        static std::string GetTemp();
        static char        GetSeparator();
        
    private:
        std::string m_origin;
        std::string m_extension;
        std::string m_filename;
        std::string m_path;
        
        StringVector m_components;
    };
    
}

#endif /* __LM_UTILITY_PATH__ */
