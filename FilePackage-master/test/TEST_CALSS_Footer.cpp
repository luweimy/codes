//
//  TEST_CALSS_Footer.cpp
//  FilePackage
//
//  Created by Luwei on 15/1/13.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "TEST_CALSS_Footer.h"
#include <iostream>
#include <string.h>
#include "../fpk/Header.h"
#include "../fpk/Footer.h"
#include "../fpk/Utility/all.h"
#include <assert.h>

#include <unordered_map>

using namespace std;

bool TEST_CLASS_Footer()
{
    cout<< "---------------- TEST-FOOTER ----------------\n" <<endl;
    
    const char *path = "/Users/etime/Documents/projects/FilePackage/res/TEST_CLASS_Footer";
    
    int ok = 0;
    
    LM::File f;
    ok = f.Open(path, "rb+");
    if (!ok) perror("open");
    
    cout<< "[FILE-SIZE] # " << f.GetSize() <<endl;
    
    LM::Header header;
    ok = header.Read(&f);
    if (!ok) puts("header-read");
    
    ok = header.Check();
    if (!ok) puts("header-check");
    
    LM::Footer footer;
//    ok = footer.write(&f, &header);
//    if (!ok) puts("footer-write");

    char pBuffer[20];
    cout<< "[BUFFER-SIZE] # " << sizeof(pBuffer) <<endl;
    
#if (0)
    
    // insert & write
    for (int i = 0; i < 100; i++) {
        LM::Entry *pEntry;
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "f_%03d.txt", i);
        printf("[FILENAME] # %s\n", pBuffer);
        
        pEntry->m_entry.id = LM::String::GenID(pBuffer);
        pEntry->m_entry.crc32 = i;
        
        footer.Insert(pEntry);
    }
    footer.Dump();
    header.Dump();
    printf("[FOOTER-COUNT] # %zu\n", footer.Count());

    header.Initialize(1);
    ok = footer.Write(&f, header);
    if (!ok) puts("footer-write");
    
    // write header
    header.write(&f);
#else
    
    // read & dump
    ok = footer.Read(&f, &header);
    if (!ok) puts("footer-read");
    
    printf("[FOOTER-COUNT] # %zu\n", footer.Count());
    
    for (int i = 0; i < (int)footer.Count(); i++) {
        memset(pBuffer, 0, sizeof(pBuffer));
        sprintf(pBuffer, "f_%03d.txt", i);
        
        uint64_t id = LM::String::GenID(pBuffer);
        uint32_t crc32 = i;
        
        LM::Entry *p = footer.Find(id);
        assert(p);
        assert(p->m_entry.crc32 == crc32);
        footer.Dump(id);
        printf("[FILENAME-CHECK] # %s\n", pBuffer);
    }

#endif
    
    std::unordered_map<std::string, int> map;
    map.insert(std::make_pair("*1", 1));
    map.insert(std::make_pair("*2", 2));
    auto pair = std::make_pair("*3", 3);
    auto r = map.insert(pair);
    
    std::cout<< (r.second);

//    cout<< map["*2"] <<endl;
//    cout<< map["*3"] <<endl;
//    auto iter = map["*3"];
//    cout<< iter <<endl;
//    
    for (auto pair : map) {
        cout<< pair.first << " -- " << pair.second <<endl;
    }
    return true;
}
