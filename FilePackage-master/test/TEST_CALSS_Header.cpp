//
//  TEST_CALSS_Header.cpp
//  FilePackage
//
//  Created by Luwei on 15/1/13.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "TEST_CALSS_Header.h"
#include <iostream>
#include <string.h>
#include "../fpk/Utility/all.h"
#include "../fpk/Header.h"
#include "../fpk/Footer.h"

using namespace std;

bool TEST_CLASS_Header()
{
    cout<< "---------------- TEST-HEADER ----------------\n" <<endl;
    
    const char *path = "/Users/etime/Documents/projects/FilePackage/res/TEST_CLASS_Header";

    int ok = 0;
    
    LM::File f;
    ok = f.Open(path, "wb+");
    if (!ok) perror("open");
    
    cout<< "[FILE-SIZE] # " << f.GetSize() <<endl;
    
    LM::Header header;
    LM::Footer footer;
    
    ok = header.Read(&f);
    if (!ok) puts("header-read");
    
    ok = header.Check();
    if (!ok) puts("header-check");
    
    header.Initialize(1);
    
    ok = header.Write(&f, &footer);
    if (!ok) perror("header-write");
    
    f.SeekSet();
    puts("[FILE-DATA-BIN] #");
    f.Dump16();
    cout<< "[FILE-DATA-STR] # " << f.GetString() <<endl;
    
    header.Dump();
    puts("[HEADER-DATA-BIN] #");
    header.Dump16();
    puts("[HEADER-DATA-BIN] #");
    header.Dump2();
    
    ok = f.Close();
    if (!ok) perror("close");
    
    return true;
}
