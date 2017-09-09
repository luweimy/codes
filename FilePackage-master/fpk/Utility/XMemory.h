//
//  XMemory.h
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __LM_UTILITY_MEMORY__
#define __LM_UTILITY_MEMORY__
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <unordered_map>

/* mem-leak check */
#define LM_MEM_LEAK_CHECK

namespace LM
{
    /** Memory class use detected memory-leak */
    class Memory
    {
    public:
        static Memory& Get()                                                    {
            if (!m_instance)
                m_instance = new Memory();
            return *m_instance;
        }
        static void Destroy()                                                   {
            if (m_instance)
                delete m_instance;
            m_instance = nullptr;
        }
        
        void* Alloc(size_t size)                                                {
            void *ptr = ::malloc(size);
#ifdef LM_MEM_LEAK_CHECK
            auto pair = m_pointerMap.insert(std::make_pair(ptr, size));
            assert(pair.second);
#endif
            return ptr;
        }
        void* Calloc(size_t n, size_t size)                                     {
            void *ptr = ::calloc(n, size);
#ifdef LM_MEM_LEAK_CHECK
            auto pair = m_pointerMap.insert(std::make_pair(ptr, size));
            assert(pair.second);
#endif
            return ptr;
        }
        void* Realloc(void *ptr, size_t size)                                   {
            void *ptr_new = ::realloc(ptr, size);
#ifdef LM_MEM_LEAK_CHECK
            size_t count = m_pointerMap.erase(ptr);
            auto pair = m_pointerMap.insert(std::make_pair(ptr_new, size));
            assert(count == 1);
            assert(pair.second);
#endif
            return ptr_new;
        }
        void  Free(void *ptr)                                                   {
            ::free(ptr);
#ifdef LM_MEM_LEAK_CHECK
            m_pointerMap.erase(ptr);
#endif
        }
        
        /** use to record memory alloc other way */
        void Insert(void *ptr, size_t size)                                     {
#ifdef LM_MEM_LEAK_CHECK
            auto pair = m_pointerMap.insert(std::make_pair(ptr, size));
            assert(pair.second);
#endif
        }
        void Remove(void *ptr)                                                  {
#ifdef LM_MEM_LEAK_CHECK
            m_pointerMap.erase(ptr);
#endif
        }
        
        /** dump memory-leak */
        void  Dump();

        
        static void  Clear(void *ptr, size_t size)                              {
            ::memset(ptr, 0, size);
        }
        static void* Copy(void *dst, void *src, size_t size)                    {
            return ::memcpy(dst, src, size);
        }
        static void* Move(void *dst, void *src, size_t size)                    {
            return ::memmove(dst, src, size);
        }
        static int   Compare(void *p1, void *p2, size_t size)                   {
            return ::memcmp(p1, p2, size);
        }
        
    private:
        Memory();
        ~Memory();
        Memory(const Memory&) = delete;
        Memory& operator=(const Memory&) = delete;
        
    private:
        static Memory* m_instance;
        std::unordered_map<void*, size_t> m_pointerMap;
    };

}

#endif /* __LM_UTILITY_MEMORY__ */
