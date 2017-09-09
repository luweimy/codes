//
//  TEST_CLASS_File.cpp
//  FilePackage
//
//  Created by Luwei on 15/1/13.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "TEST_CLASS_File.h"
#include <iostream>
#include <string.h>
#include "../fpk/Utility/all.h"
using namespace std;

bool TEST_CLASS_File()
{
    cout<< "---------------- TEST-FILE ----------------\n" <<endl;

    const char *path = "/Users/etime/Documents/projects/FilePackage/res/TEST_CLASS_File";
    bool ok = false;
    
    LM::File f;
    
    ok = f.IsOpen();
    if (!ok) puts("file is not open");
    
    ok = f.Exist(path);
    if (ok) puts("file exist");
    
    ok = f.Touch(string(path) + "_tmp");
    if (!ok) puts("file exist or create failed");
    
    ok = f.Copy(string(path), string(path) + "_tmp1");
    if (!ok) puts("copy failed");
    
    ok = f.Rename(string(path) + "_tmp1", "_tmp2");
    if (!ok) puts("rename failed");

    ok = f.Copy(string(path), string(path) + "_tmp1");
    if (!ok) puts("copy failed");

    ok = f.Move(string(path) + "_tmp1", string(path) + "_tmp3");
    if (!ok) puts("move failed");

    ok = f.Remove(string(path) + "_tmp");
    if (!ok) puts("remove failed");
    
    ok = f.Open(path, "rb");
    if (!ok) perror("open");
    
    cout<< "<FILE-SIZE> # " << f.GetSize() <<endl;
    cout<< "<FILE-DATA> # " << f.GetString() <<endl;
    cout<< "<FILE-DATA> # " << f.GetString(1) <<endl;
    printf("<FILE-DATA> # %s\n", f.GetString(10).c_str());
    
    f.Dump16();
    f.Dump2();
    
    ok = f.SeekEnd();
    if (!ok) perror("seek");
    
    const char *str = "hello world";
    ok = f.Write(str, sizeof(char), strlen(str));
    if (!ok) perror("write");
    
    ok = f.IsOpen();
    if (ok) puts("file is open");
    
    ok = f.Close();
    if (!ok) perror("close");
    
    ok = f.IsOpen();
    if (!ok) puts("file is not open");

    
    return true;
}
