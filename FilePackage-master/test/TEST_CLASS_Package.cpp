//
//  TEST_CLASS_Package.cpp
//  FilePackage
//
//  Created by Guy on 15/1/14.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#include "TEST_CLASS_Package.h"
#include <iostream>
#include <string.h>
#include "../fpk/Package.h"
#include "../fpk/Header.h"
#include "../fpk/Footer.h"

#include <unordered_map>

#include "time.h"

#define __IF_TRUE__(ok,reason) if(!ok){printf("%s\n",reason); return false;}
#define __IF_OK__(ok,reason) if(ok){ printf("测试成功 -- %s \n",reason); } else{ printf("%s 失败！！！\n",reason); }

//CLOCKS_PER_SEC

using namespace std;
using namespace LM;

bool test_Unload_GetSize(char *res_path);
bool test_GetString();
bool test_GetBinary(char *res_path);
bool test_Append_Remove(char *res_path);
bool test_Append_Buffer(char *res_path);
bool test_Remove_Flush(char *res_path);
bool test_Flush(char *res_path);
bool test_Dump_GetVersion(char *res_path);
bool test_Merge_packagePath(char *res_path);
bool test_Merge(char *res_path);
bool test_Remove(char *res_path);
bool test_Remove_update(char *res_path);
bool test_Remove_GetBinary_Appending(char *res_path);

bool TEST_CLASS_Package()
{
    clock_t t_start, t_end;
    double duration;
    bool ok = true;
    
    static char *res_path = "../res/";
    
    t_start = clock();
    
    /**
     *  Test:[Unload][GetSize]
     */
    ok = test_Unload_GetSize(res_path);
    __IF_OK__(ok, "Package_Unload_GetSize")
    
    /**
     *  Test:[GetString]
     */
    ok = test_GetString();
    __IF_OK__(ok, "Package_GetString")
    
    /**
     *  Test:[GetBinary]
     */
    ok = test_GetBinary(res_path);
    __IF_OK__(ok, "Package_GetBinary")
    
    /**
     *  Test:[Append]
     */
    ok = test_Append_Remove(res_path);
    __IF_OK__(ok, "Package_Append_Remove")
    
    /**
     *  Test:[Append]argument is buffer
     */
    ok = test_Append_Buffer(res_path);
    __IF_OK__(ok, "Package_Append_Buffer")
    
    /**
     *  Test:[Dump][GetVersion]
     */
    ok = test_Dump_GetVersion(res_path);
    __IF_OK__(ok, "Package_Dump_GetVersion")
    
    /**
     *  Test:[Merge(package_path)] with a package has the same thing, result will be faild
     */
    ok = test_Merge_packagePath(res_path);
    __IF_OK__(ok, "Package_Merge_packagePath");
    
    /**
     *  Test:[Merge(otherPackage)]
     */
    ok = test_Merge(res_path);
    __IF_OK__(ok, "Package_Merge")
    
    /**
     *  Test:After [Remove] B then [Merge] A to B
     */
    ok = test_Remove(res_path);
    __IF_OK__(ok, "Package_Remove");
    
    /**
     *  Test:After [Remove] then [Update]
     */
    ok = test_Remove_update(res_path);
    __IF_OK__(ok, "Package_Remove_Update");
    
    /**
     *  Test:Redo [Append] after appended files in same folder, result will be faild
     */
    ok = test_Remove_Flush(res_path);
    __IF_OK__(ok, "Package_Remove_Flush")
    
    /**
     *  Test:After [Remove] A then [getBinary] from B then [Appending] to A
     *  Test:[Exist]
     */
    ok = test_Remove_GetBinary_Appending(res_path);
    __IF_OK__(ok, "Package_Remove_GetBinary_Appending");
    
    t_end = clock();

    duration = (double)(t_end - t_start)/CLOCKS_PER_SEC;
    cout<<"second "<<duration<<endl;

    return true;
}

bool test_Unload_GetSize(char *res_path)
{
    const char *pkg1_path = "./pkg_merge1.bin";
    LM::File::Remove(pkg1_path);
    LM::Package pkg1;
    bool ok = true;
    
    //load package
    ok = pkg1.Load(pkg1_path);
    __IF_TRUE__(ok, "PKG Load faild");
    ok = pkg1.IsValid();
    __IF_TRUE__(ok, "PKG IsValid no")
    
    LM::Directory dir;
    ok = dir.Open(res_path);
    __IF_TRUE__(ok, "Open not true");
    
    //append package
    LM::File from, to;
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok &= pkg1.Append(path);
            __IF_TRUE__(ok, "PKG1 Append faild")
        }
    }
    
    ok = pkg1.Unload();
    __IF_TRUE__(ok, "PKG Unload faild");
    
    ok = true;
    ok = pkg1.Load(pkg1_path);
    __IF_TRUE__(ok, "PKG Load faild")
    
    size_t sizeOfPackage = pkg1.GetSize();
    pkg1.Unload();
    
    if (sizeOfPackage <= 0) {
        return false;
    }else{
        return true;
    }
    
}

bool test_GetString()
{
    const char *pkg1_path = "./pkg_merge1.bin";
    const char *res_path = "../res/";
    LM::File::Remove(pkg1_path);
    LM::Package pkg1;
    bool ok = true;
    
    //load package
    ok = pkg1.Load(pkg1_path);
    __IF_TRUE__(ok, "PKG Load faild")
    ok = pkg1.IsValid();
    if (!ok) puts("PKG IsValid no");
    
    LM::Directory dir;
    ok = dir.Open(res_path);
    if (!ok) puts("Open not ok");
    
    //append package
    LM::File from, to;
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok &= pkg1.Append(path);
            __IF_TRUE__(ok, "PKG1 Append faild");
        }
    }
    
    dir.Reset();
    LM::File packageTo;
    LM::File fileFrom;
    fileFrom.Close();
    packageTo.Close();
    while (dir.Next()) {
        if(dir.IsFile()){
            string path = dir.GetPath();
            string content = pkg1.GetString(path);
            
            char fromContent[3072] = "";
            ok = fileFrom.Open(path, "rb+");
            __IF_TRUE__(ok, "Open file faild");
            fileFrom.Read(&fromContent, sizeof(char), 3072);
            int strResult = strcmp(content.c_str(), fromContent);
            if (strResult != 0) {
                return false;
            }
            
            ok = packageTo.Open(path + ".tmp", "wb+");
            __IF_TRUE__(ok, "Open file faild");
            packageTo.Write(content.c_str(), sizeof(char), content.length());
            fileFrom.Close();
            packageTo.Close();
        }
        
    }
    pkg1.Unload();
    return true;
}

bool test_GetBinary(char *res_path)
{
    LM::Memory &mem = LM::Memory::Get();
    const char *pkg1_path = "./pkg_merge1.bin";
    LM::File::Remove(pkg1_path);
    LM::Package pkg1;
    bool ok = true;
    
    //load package
    ok = pkg1.Load(pkg1_path);
    __IF_TRUE__(ok, "PKG Load faild");
    ok = pkg1.IsValid();
    __IF_TRUE__(ok, "PKG IsValid no");
    
    LM::Directory dir;
    ok = dir.Open(res_path);
    __IF_TRUE__(ok, "Open not ok");
    
    //append package
    LM::File from, to;
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok &= pkg1.Append(path);
            __IF_TRUE__(ok, "PKG1 Append faild");
        }
    }
    
    string toPath = "../res/";
    dir.Reset();
    LM::File packageTo;
    while (dir.Next()) {
        if(dir.IsFile()){
            string path = dir.GetPath();
            size_t length;
            char* content = (char*)pkg1.GetBinary(path, &length);
            
            int lastPos = path.length() - 1;
            int index = path.find_last_of("/", lastPos);
            string child;
            child = path.substr(index, lastPos);
            toPath = toPath + child;
            
            ok = packageTo.Open(toPath, "wb+");
            __IF_TRUE__(ok, "Open file faild");
            
            packageTo.Write(content, sizeof(char), length);
            packageTo.Close();
            mem.Free(content);
        }
    }
    pkg1.Unload();
    return true;
}

bool test_Append_Remove(char *res_path)
{
    const char *pkg1_path = "./pkg_merge1.bin";
    LM::File::Remove(pkg1_path);
    LM::Package pkg1;
    bool ok = true;
    
    //load package
    ok = pkg1.Load(pkg1_path);
    __IF_TRUE__(ok, "PKG Load faild");
    ok = pkg1.IsValid();
    __IF_TRUE__(ok, "PKG IsValid no");
    
    LM::Directory dir;
    ok = dir.Open(res_path);
    __IF_TRUE__(ok, "Open ok");
    
    //append package
    LM::File from, to;
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok &= pkg1.Append(path);
            __IF_TRUE__(ok, "PKG1 Append faild");
        }
    }
    
    //Append
    string againPath = "/Users/etime/Desktop/mp3/to";
    ok = dir.Open(againPath);
    dir.Reset();
    while (dir.Next()) {
        if (dir.IsFile()) {
            string path = dir.GetPath();
            ok = pkg1.Append(path);
            __IF_TRUE__(ok, "PKG Append faild");
        }
    }
    pkg1.Flush();
    
    //Remove
    dir.Reset();
    while (dir.Next()) {
        if (dir.IsFile()) {
            string path = dir.GetPath();
            ok = pkg1.Remove(path);
            __IF_TRUE__(ok, "PKG Remove faild");
        }
    }
    
    pkg1.Unload();

    return true;
}

bool test_Append_Buffer(char *res_path)
{
    const char *pkg1_path = "./pkg_merge1.bin";
    LM::File::Remove(pkg1_path);
    LM::Package pkg1;
    bool ok = true;
    
    //load package
    ok = pkg1.Load(pkg1_path);
    __IF_TRUE__(ok, "PKG Load faild");
    ok = pkg1.IsValid();
    __IF_TRUE__(ok, "PKG IsValid no");
    
    LM::Directory dir;
    ok = dir.Open(res_path);
    __IF_TRUE__(ok, "Open ok");
    
    //append package
    LM::File from, to;
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok &= pkg1.Append(path);
            __IF_TRUE__(ok, "PKG1 Append faild");
        }
    }
    pkg1.Flush();
    
    //Append
    ok = true;
    string bufferPath = "/Users/etime/Desktop/mp3/buffer.lua";
    char buffer[50] = "hellow world";
    ok = pkg1.Append(bufferPath, buffer, 50);
    __IF_TRUE__(ok, "PKG Append buffer not OK");
    
    pkg1.Flush();
    
    //Exist
    ok = pkg1.Exist(bufferPath);
    __IF_TRUE__(ok, "PKG Exist not OK, Append Buffer not OK");
    
    pkg1.Unload();
    
    return true;
}

bool test_Remove_Flush(char *res_path)
{
    const char *pkg1_path = "./pkg_merge1.bin";
    const char *pkg2_path = "./pkg_merge2.bin";
    LM::File::Remove(pkg1_path);
    LM::File::Remove(pkg2_path);
    LM::Package pkg1;
    LM::Package pkg2;
    bool ok = true;
    
    //load package
    ok = pkg1.Load(pkg1_path);
    ok = pkg2.Load(pkg2_path);
    __IF_TRUE__(ok, "PKG Load faild");
    ok = pkg1.IsValid();
    ok = pkg2.IsValid();
    __IF_TRUE__(ok, "PKG IsValid no");
    
    LM::Directory dir;
    ok = dir.Open(res_path);
    __IF_TRUE__(ok, "Open not ok");
    
    //append package
    LM::File from, to;
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok &= pkg1.Append(path);
            __IF_TRUE__(ok, "PKG1 Append faild");
            ok &= pkg2.Append(path);
            __IF_TRUE__(ok, "PKG2 Append faild");
        }
    }
    
    //Append
    dir.Reset();
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok = pkg1.Remove(path);
            pkg1.Flush();
            ok = pkg1.Append(path);
            __IF_TRUE__(ok, "pkg1 append faild");
        }
    }
    
    pkg1.Unload();
    pkg2.Unload();
    return true;
}

bool test_Dump_GetVersion(char *res_path)
{
    const char *pkg1_path = "./pkg_merge1.bin";
    LM::File::Remove(pkg1_path);
    LM::Package pkg1;
    bool ok = true;
    
    //load package
    ok = pkg1.Load(pkg1_path);
    __IF_TRUE__(ok, "PKG Load faild");
    ok = pkg1.IsValid();
    __IF_TRUE__(ok, "PKG IsValid no")
    
    LM::Directory dir;
    ok = dir.Open(res_path);
    if (!ok) puts("Open ok");
    
    //append package
    LM::File from, to;
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok = pkg1.Append(path);
            __IF_TRUE__(ok, "PKG1 Append faild");
        }
    }
    
    uint32_t version = pkg1.GetVersion();
    __IF_TRUE__(version != 0, "PKG GetVersion faild");
    
    pkg1.Unload();
    return true;
}

bool test_Merge_packagePath(char *res_path)
{
    const char *pkg1_path = "./pkg_merge1.bin";
    const char *pkg2_path = "./pkg_merge2.bin";
//    const char *res_path = "/Users/etime/Desktop/mp3/17.4";
    LM::File::Remove(pkg1_path);
    LM::File::Remove(pkg2_path);
    LM::Package pkg1;
    LM::Package pkg2;
    bool ok = true;
    
    //load package
    ok = pkg1.Load(pkg1_path);
    ok = pkg2.Load(pkg2_path);
    __IF_TRUE__(ok, "PKG Load faild");
    ok = pkg1.IsValid();
    ok = pkg2.IsValid();
    __IF_TRUE__(ok, "PKG Not IsValid");
    
    LM::Directory dir;
    ok = dir.Open(res_path);
    __IF_TRUE__(ok, "Open not ok");
    
    //append package
    LM::File from, to;
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok &= pkg2.Append(path);
            __IF_TRUE__(ok, "PKG2 Append faild");
        }
    }
    pkg1.Flush();
    pkg2.Flush();
    
    ok = pkg1.Merge(pkg2_path);
    if (!ok) {
        puts("PKG1 Merge faild");
        return !ok;
    }else{
        return ok;
    }
    
}

bool test_Merge(char *res_path)
{
    const char *pkg1_path = "./pkg_merge1.bin";
    const char *pkg2_path = "./pkg_merge2.bin";
    LM::File::Remove(pkg1_path);
    LM::File::Remove(pkg2_path);
    LM::Package pkg1;
    LM::Package pkg2;
    bool ok = true;
    
    //load package
    ok = pkg1.Load(pkg1_path);
    ok = pkg2.Load(pkg2_path);
    __IF_TRUE__(ok, "PKG Load faild");
    ok = pkg1.IsValid();
    ok = pkg2.IsValid();
    __IF_TRUE__(ok, "PKG Not IsValid");
    
    LM::Directory dir;
    ok = dir.Open(res_path);
    __IF_TRUE__(ok, "Open ok");
    
    //append package
    LM::File from, to;
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok &= pkg2.Append(path);
            __IF_TRUE__(ok, "PKG2 Append faild");
            }
    }
    
    pkg2.Flush();
    
    ok = pkg1.Merge(&pkg2);
    __IF_TRUE__(ok, "PKG1 Merge faild");
    
    
    pkg1.Unload();
    pkg2.Unload();
    
    if (!ok) {
        puts("PKG1 Merge faild");
        return !ok;
    }else{
        return ok;
    }
}

bool test_Remove(char *res_path)
{
    const char *pkg1_path = "./pkg_remove.bin";
    LM::File::Remove(pkg1_path);
    LM::Package pkg1;
    bool ok = true;

    //load package
    ok = pkg1.Load(pkg1_path);
    __IF_TRUE__(ok, "PKG Load faild");
    ok = pkg1.IsValid();
    __IF_TRUE__(ok, "PKG Not IsValid");
    
    LM::Directory dir;
    ok = dir.Open(res_path);
    __IF_TRUE__(ok, "Open ok");
    
    //append package
    LM::File from, to;
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok &= pkg1.Append(path);
            __IF_TRUE__(ok, "PKG Append faild");
        }
    }
    
    //remove package
    dir.Reset();
    while (dir.Next()) {
        if (dir.IsFile()) {
            string path = dir.GetPath();
            ok = pkg1.Remove(path);
            __IF_TRUE__(ok, "PKG Remove faild");
        }
    }
    pkg1.Flush();
    
    //after remove, isExist
    dir.Reset();
    while (dir.Next()) {
        if (dir.IsFile()) {
            string path = dir.GetPath();
            ok = pkg1.Exist(path);
            __IF_TRUE__(!ok, "PKG Remove faild, Exist");
        }
    }

    pkg1.Unload();
    return true;
}

bool test_Remove_update(char *res_path)
{
    const char *pkg1_path = "./pkg_remove.bin";
    LM::File::Remove(pkg1_path);
    LM::Package pkg1;
    bool ok = true;
    
    //load package
    ok = pkg1.Load(pkg1_path);
    __IF_TRUE__(ok, "PKG Load faild");
    ok = pkg1.IsValid();
    __IF_TRUE__(ok, "PKG IsValid no");
    
    LM::Directory dir;
    ok = dir.Open(res_path);
    __IF_TRUE__(ok, "Open ok");
    
    //append package
    LM::File from, to;
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok &= pkg1.Append(path);
            __IF_TRUE__(ok, "PKG1 Append faild");
        }
    }
    
    //Remove
    dir.Reset();
    while (dir.Next()) {
        if (dir.IsFile()) {
            string path = dir.GetPath();
            ok = pkg1.Remove(path);
            __IF_TRUE__(ok, "PKG Remove faild");
        }
    }
    
    pkg1.Update();
    
    //isExist
    dir.Reset();
    while (dir.Next()) {
        if (dir.IsFile()) {
            string path = dir.GetPath();
            ok = pkg1.Exist(path);
            __IF_TRUE__(!ok, "PKG Remove faild, after update, exist");
        }
    }
    
    pkg1.Unload();
    
    return true;
}

bool test_Remove_GetBinary_Appending(char *res_path)
{
    LM::Memory &mem = LM::Memory::Get();
    const char *pkg1_path = "./pkg_merge1.bin";
    const char *pkg2_path = "./pkg_merge2.bin";
//    const char *res_path = "/Users/etime/Desktop/mp3/17.4";
    LM::File::Remove(pkg1_path);
    LM::File::Remove(pkg2_path);
    LM::Package pkg1;
    LM::Package pkg2;
    bool ok = true;
    
    //load package
    ok = pkg1.Load(pkg1_path);
    ok = pkg2.Load(pkg2_path);
    __IF_TRUE__(ok, "PKG Load faild");
    ok = pkg1.IsValid();
    ok = pkg2.IsValid();
    __IF_TRUE__(ok, "PKG IsValid no");
    
    LM::Directory dir;
    ok = dir.Open(res_path);
    __IF_TRUE__(ok, "Open not ok");
    
    //append package
    LM::File from, to;
    while (dir.Next()) {
        string path = dir.GetPath();
        if (dir.IsFile()) {
            ok &= pkg1.Append(path);
            __IF_TRUE__(ok, "PKG1 Append faild");
            ok &= pkg2.Append(path);
            __IF_TRUE__(ok, "PKG2 Append faild");
        }
    }
    
    dir.Reset();
    ok = true;
    while (dir.Next()) {
        if (dir.IsFile()) {
            string path = dir.GetPath();
            ok = pkg1.Exist(path);
            __IF_TRUE__(ok, "pkg1 not exist file at path");
            ok = pkg2.Exist(path);
            __IF_TRUE__(ok, "pkg2 not exist file at path");
            
            ok &= pkg1.Remove(path);
            __IF_TRUE__(ok, "PKG Remove faild");
            pkg1.Flush();
            
            size_t length;
            char *binary = (char*)pkg2.GetBinary(path, &length);
            ok = pkg1.Append(path, binary, length);
            mem.Free(binary);
            __IF_TRUE__(ok, "PKG1 Append faild");
        }
    }
    pkg1.Unload();
    pkg2.Unload();
    return true;
}
