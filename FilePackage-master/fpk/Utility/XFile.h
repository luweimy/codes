//
//  XFile.h
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __LM_UTILITY_FILE__
#define __LM_UTILITY_FILE__
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace LM
{
    class File
    {
    public:
        typedef enum Where {
            SET = SEEK_SET,
            CUR = SEEK_CUR,
            END = SEEK_END,
        } Where;
        
        File();
        ~File();
        File(const File &) = delete;
        File& operator=(const File&) = delete;
        
        bool Open(const std::string &path, const std::string &mode);
        bool Attach(FILE *pFile);
        bool Close();
        bool Flush();
        bool IsOpen() const;
        const std::string& GetPath() const;
        
        size_t Read(void *pBuffer, size_t size, size_t count) const;
        size_t Write(const void *pBuffer, size_t size, size_t count) const;
        
        long Tell()    const;
        bool SeekSet() const;
        bool SeekEnd() const;
        bool SeekSet(long offset) const;
        bool SeekCur(long offset) const;
        bool SeekEnd(long offset) const;
        bool Seek(long offset, Where whence) const;
        
        /** get file size in bytes */
        long GetSize() const;
        bool Eof()  const;
        
        /** begin of current position
            length is 0 mean to end of file
            [GetBinary] free memory use [Memory::Get().Free()] manually */
        std::string GetString(size_t length = 0) const;
        void* GetBinary(size_t *pLength_out, size_t length_in = 0) const;
        
        /** dump begin of current position
            length is 0 mean dump to end of file */
        void Dump16(size_t length = 0) const;
        void Dump2(size_t length = 0) const;
        
        static bool Exist(const std::string &path);
        static bool Touch(const std::string &path);
        
        static bool Remove(const std::string &path);
        static bool Rename(const std::string &path, const std::string &newname);
        static bool Move(const std::string &srcpath, const std::string &dstpath);
        static bool Copy(const std::string &srcpath, const std::string &dstpath);
        
        static void* GetBinary(const std::string &diskpath, size_t *pLength_out, size_t length_in = 0);
        
    private:
        FILE*       m_pFileStream;
        std::string m_path;
    };

}

#endif /* __LM_UTILITY_FILE__ */
