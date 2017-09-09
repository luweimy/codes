//
//  JsonParser.h
//  moon
//
//  Created by Lovells on 13-7-13.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface JsonParser : NSObject

+ (NSDictionary *)jsonParserFromFile:(NSString *)fileName ofType:(NSString *)fileType;

@end
