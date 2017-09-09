//
//  MyTextField.m
//  moon
//
//  Created by Lovells on 13-7-14.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "MyTextField.h"

@implementation MyTextField

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.borderStyle = UITextBorderStyleRoundedRect;
        self.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
        self.enabled = NO;
    }
    return self;
}

@end
