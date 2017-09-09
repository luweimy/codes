//
//  XMemPool.h
//  Utility
//
//  Created by Luwei on 15/1/28.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __LM_UTILITY_MEMPOOL__
#define __LM_UTILITY_MEMPOOL__
#include <list>
#include "XMemory.h"

namespace LM
{
    /** Fixed size memory pool */
    template<size_t __SZ>
    class MemPool
    {
    public:
        
        MemPool(const MemPool &) = delete;
        MemPool& operator=(const MemPool &) = delete;
        
        MemPool():m_pRoot(nullptr)                                  {
            Chunk *pChunk = this->AllocChunk();
            if (!pChunk)
                return;
            m_chunkList.push_back(pChunk);
            m_pRoot = pChunk->items;
        }
        
        ~MemPool()                                                  {
            this->Clear();
        }
        
        void* Alloc()                                               {
            if (!m_pRoot) {
                Chunk *pChunk = this->AllocChunk();
                if (!pChunk) return nullptr;
                m_chunkList.push_back(pChunk);
                m_pRoot = pChunk->items;
            }
            void *mem = m_pRoot;
            m_pRoot = m_pRoot->next;
            return mem;
        }
        
        void Free(void *mem)                                        {
            if (!mem) return;
            Item *item = static_cast<Item*>(mem);
            item->next = m_pRoot;
            m_pRoot = item;
        }
        
        void Clear()                                                {
            for (Chunk *pChunk : m_chunkList) {
                this->Deallocator(pChunk);
            }
            m_chunkList.clear();
        }
        
        size_t Capacity()                                           {
            return m_chunkList.size() * CHUNK_COUNT * __SZ;
        }
        
    private:
        struct Chunk;
        enum { CHUNK_COUNT = (4*1024)/__SZ };
        
        Chunk* AllocChunk()                                         {
            Chunk *pChunk = (Chunk *)this->Allocator(sizeof(Chunk));
            if (!pChunk)
                return nullptr;
            for (int i = 0; i < CHUNK_COUNT - 1; i++) {
                pChunk->items[i].next = &pChunk->items[i+1];
            }
            pChunk->items[CHUNK_COUNT-1].next = nullptr;
            return pChunk;
        }
        
        void* Allocator(size_t size)                                {
            return Memory::Get().Alloc(size);
        }
        
        void  Deallocator(void* ptr)                                {
            Memory::Get().Free(ptr);
        }
        
    private:
        union Item      {
            Item*   next;
            uint8_t mem[__SZ];
        };
        
        struct Chunk    {
            Item items[CHUNK_COUNT];
        };
        
        Item*               m_pRoot;
        std::list<Chunk *>  m_chunkList;
    };
    
}

#endif /* __LM_UTILITY_MEMPOOL__ */
