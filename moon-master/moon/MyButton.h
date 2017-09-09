//
//  MyButton.h
//  moon
//
//  Created by Lovells on 13-7-14.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MyButton : UIButton

+ (id)buttonWithTitle:(NSString *)title withTarget:(id)target andAction:(SEL)action;

@end
