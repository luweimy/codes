//
//  JsonParser.m
//  moon
//
//  Created by Lovells on 13-7-13.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "JsonParser.h"

@implementation JsonParser

+ (NSDictionary *)jsonParserFromFile:(NSString *)fileName ofType:(NSString *)fileType
{
    NSData *jsonData = [[NSData alloc] initWithContentsOfFile:[[NSBundle mainBundle]
                                                               pathForResource:fileName ofType:fileType]];
    NSError *error;
    NSDictionary *json = [NSJSONSerialization JSONObjectWithData:jsonData options:kNilOptions error:&error];
    if (!json)
    {
        NSLog(@"%@.json parsing failed.\n%@", fileName, error);
    }
    
    return json;
}

@end
