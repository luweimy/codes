//
//  define.h
//  FilePackage
//
//  Created by Luwei on 15/1/14.
//  Copyright (c) 2015年 Luwei. All rights reserved.
//

#ifndef __FPK__DEFINE__
#define __FPK__DEFINE__

#include "Error.h"
#include <stdlib.h>

/** 数据包标记字段，位于数据包前2个字节，用于标记是否为数据包 */
#define FPK_CODE_SIGN   0xAA99

/** 如果定义FPK_CHECK_CRC32，则使用CRC32进行数据校验
    只有打包时和解包时同时打开校验才能成功进行校验 */
#define FPK_CHECK_CRC32

/** 如果定义秘钥(FPK_SECRET_KEY)，则会对存储的数据进行加密处理
    注意：必须在构造包时和取包中数据时秘钥完全一致才能正确取出数据 */
#define FPK_SECRET_KEY  0xFACD00FA00224FF8

/** 定义版本号 */
#define FPK_VERSION     0x00010002

#define FPK_Error(__ERR) LM::Error::Get().Put("%s (%s: %d)", (__ERR), __FILE__, __LINE__)

#endif /* __FPK__DEFINE__ */
