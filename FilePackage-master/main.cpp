//
//  main.cpp
//  FilePackage
//
//  Created by Luwei on 15/1/10.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include <stdlib.h>
#include "fpk/Package.h"
#include "test/TEST_CLASS_Package.h"
#include "test/TEST_CLASS_Utility.h"
#include <iostream>
using namespace std;

void Package_demo()
{
 LM::Memory &mem = LM::Memory::Get();
    const char *pkg1_path = "./pkg1.bin";
    const char *pkg2_path = "./pkg2.bin";
#ifdef __linux__
    const char *res_path = "./../res/";
#else
    const char *res_path = "/Users/mac/Documents/work/FilePackage/fpk";
#endif

    LM::File::Remove(pkg1_path);
    LM::File::Remove(pkg2_path);

    LM::Package pkg1; 
    LM::Package pkg2; 

    bool ok = true;

    ///////// Load/Unload ///////////

    ok &= pkg1.Load(pkg1_path);
    ok &= pkg2.Load(pkg2_path);
    if (!ok) puts("PKG Load failed");

    ok &= pkg1.IsValid();
    ok &= pkg2.IsValid();
    if (!ok) puts("PKG is invalid");

    ok &= pkg1.Unload();
    ok &= pkg2.Unload();
    if (!ok) puts("PKG Unload failed");

    /////////// Append/Rmove ///////////
    
    ok &= pkg1.Load(pkg1_path);
    ok &= pkg2.Load(pkg2_path);
    if (!ok) puts("PKG Load failed");
    
    LM::Directory dir;    
    ok &= dir.Open(res_path);
    if (!ok) puts("Dir open failed");

    int index = 0;
    std::string path;
    while (dir.Next()) {

        if (dir.IsFolder())
            continue;
        
        path = dir.GetPath();
        printf("[APPEND-PKG]: %s\n", path.c_str());

        ok &= pkg1.Append(path);
        ok &= pkg2.Append(path);

        if (++index%2==0)
            ok &= pkg1.Remove(path);
        else
            ok &= pkg2.Remove(path);
        
    }
    if (!ok) puts("PKG Append failed");
    
    printf("[PATH] # %s\n", path.c_str());
    for (int i = 0; i < 100; i++) {
        ok = pkg1.Remove(path);
        if (!ok) puts("remove failed");
        ok = pkg1.Append(path);
        if (!ok) puts("append failed");
    }

    /////////// Update ///////////
    
    // 进行完所有的删除后，update一次即可
    ok = true;
    ok &= pkg1.Update();
    ok &= pkg2.Update(); 
    if (!ok) puts("PKG update failed");

    ok = true;
    ok &= pkg1.IsValid();
    ok &= pkg2.IsValid();
    if (!ok) puts("PKG is invalid");

    /////////// GetString/GetBindry ///////////
    
    dir.Reset();
    index = 0;
    while (dir.Next()) {
        std::string path = dir.GetPath();
        if (dir.IsFolder()) 
            continue;
        if (index++%2==0) {
            size_t length = 0;
            char *pBuffer = (char*)pkg1.GetBinary(path, &length);
            std::string str(pBuffer, length);
            /** !IMPORTANT */
            mem.Free(pBuffer);
            printf("[PKG1-DATA]: (%s) | %s\n", path.c_str(), str.c_str());
        }
        else
            printf("[PKG2-DATA]: (%s) | %s\n", path.c_str(), pkg2.GetString(path).c_str());
    }
    
    /////////// Merge/Flush ///////////
    
    // 内部自动调用了Flush, 也可以手动调用，仍然只会刷新一次缓冲区
//    pkg2.Unload();
    
    // Merge小心重名文件造成失败
    ok = true;
    ok &= pkg1.Merge(&pkg2);
    if (!ok) puts("PKG1 Merge failed");

    pkg1.Dump();
    
    // free memory
    pkg1.Unload();
    pkg2.Unload();

    /////////// Memory-Leak ///////////
    
    // 内存泄露会在Dumper中打印出来
    mem.Alloc(1);
    
    puts("Successfully ...");
    
    puts("-------<mem-leak>---------");
    mem.Dump();
}

/********* <PACKAGE TOOL> ************/
vector<string>& walk_directory(vector<string> &list, const std::string &dirpath) {
    LM::Directory dir;
    dir.Open(dirpath);
    while (dir.Next()) {
        
        // 去掉以'.'开头的文件
        std::string filename = dir.GetName();
        if (LM::String::HasPrefix(filename, "."))
            continue;
        
        std::string path = dir.GetPath();
        
        // 递归文件夹
        if (dir.IsFolder())
            walk_directory(list, path);
        else
            list.push_back(path);
    }
    return list;
}

int Package_Tool(int argc, const char * argv[]) {
    //    std::string script_path = "/data/muse/game-01/trunk/musegame/code";
    //    std::string to_path = "/data/muse/game-01/trunk/musegame/res/musegame";
    
    LM::Argument arg(argc, argv);
    arg.AddCommand("-h", [](const std::string& argv){
        printf("-----------------------\n"
               "[PACKAGE TOOL] v.1.0.1\n"
               "[1st PARAM] FROM PATH(the path of the resources folder)\n"
               "[2st PARAM]   TO PATH(the path of the package file to generate)\n"
               "-----------------------\n");
    });
    
    arg.DoCommand();
    
    std::string script_path = arg.GetFreeArgv(1);
    std::string to_path = arg.GetFreeArgv(2);
    
    if (script_path.size()==0 || to_path.size()==0)
        return 0;
    
    printf("[FROM] %s\n", script_path.c_str());
    printf("  [TO] %s\n", to_path.c_str());
    
    vector<string> list;
    
    // 获得所有的文件
    walk_directory(list, script_path);
    // 删掉原来的数据包，否则会追加文件
    LM::File::Remove(to_path);
    //
    LM::Package pkg;
    LM::File f;
    pkg.Load(to_path);
    for (auto path : list) {
        std::string key = "src/"+path.substr(script_path.length()+1);
        size_t length = 0;
        char *pBuffer = (char*)LM::File::GetBinary(path, &length);
        pkg.Append(key, pBuffer, length);
        printf("[KEY-PATH] %s\n", key.c_str());
    }
    
    return 0;
}


int main(int argc, const char * argv[]) 
{
//    Package_demo();
    Package_Tool(argc, argv);
//    TEST_CLASS_Utility();
    // TEST_CLASS_Package();
    return 0;
}
