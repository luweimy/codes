//
//  MainView.m
//  moon
//
//  Created by Lovells on 13-7-16.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "MainView.h"
#import "MyButton.h"
#import "data.h"

@implementation MainView

- (id)initWithFrame:(CGRect)frame andTarget:(id)target
{
    self = [super initWithFrame:frame];
    if (self)
    {
        // 初始化按钮
        [self buttonsInitWithTarget:target];
    }
    return self;
}

- (BOOL)buttonsInitWithTarget:(id)target
{
    // 添加帮订餐按钮
    MyButton *helpOrderButton = [MyButton buttonWithTitle:CH_SELECT_FOOD
                                               withTarget:target
                                                andAction:@selector(helpOrderButtonTouchDown)];
    helpOrderButton.frame = CGRectMake(NU_CONTROL_X, NU_MARGIN_TOP, NU_WIDTH, NU_HEIGHT);
    [self addSubview:helpOrderButton];
    
    // 添加看订单按钮
    MyButton *checkOrderButton = [MyButton buttonWithTitle:CH_CHECK_ORDER
                                                withTarget:target
                                                 andAction:@selector(checkOrderButtonTouchDown)];
    checkOrderButton.frame = CGRectMake(NU_CONTROL_X, NU_MARGIN_TOP + NU_HEIGHT + NU_SPACE, NU_WIDTH, NU_HEIGHT);
    [self addSubview:checkOrderButton];
        
    return YES;
}

@end
