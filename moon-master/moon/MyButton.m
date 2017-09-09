//
//  MyButton.m
//  moon
//
//  Created by Lovells on 13-7-14.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "MyButton.h"

@implementation MyButton

+ (id)buttonWithTitle:(NSString *)title withTarget:(id)target andAction:(SEL)action
{
    UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button setTitle:title forState:UIControlStateNormal];
    [button addTarget:target action:action forControlEvents:UIControlEventTouchDown];
    
    return button;
}

@end
