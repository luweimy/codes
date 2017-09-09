//
//  HelpOrderFormView.m
//  moon
//
//  Created by Lovells on 13-7-16.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "HelpOrderFormView.h"
#import "MyButton.h"
#import "MyTextField.h"
#import "data.h"

@implementation HelpOrderFormView

- (id)initWithFrame:(CGRect)frame andTarget:(id)target
{
    self = [super initWithFrame:frame];
    if (self)
    {
        [self addTarget:target
                 action:@selector(backgroundTapControlTouchDown)
       forControlEvents:UIControlEventTouchDown];
        
        // 初始化控件
        [self selectPeopleInitWithTarget:target];
        [self selectRestaurantInitWithTarget:target];
        [self selectFoodInitWithTarget:target];
        [self confirmButtonInitWithTarget:target];
    }
    return self;
}

#pragma mark - initialization

- (BOOL)confirmButtonInitWithTarget:(id)target
{
    MyButton *button = [MyButton buttonWithTitle:CH_CONFIRM
                                      withTarget:target
                                       andAction:@selector(confirmButtonTouchDown)];
    button.frame = CGRectMake(NU_CONTROL_X, 330.0f, NU_WIDTH, NU_HEIGHT);
    [self addSubview:button];
    
    return YES;
}

- (BOOL)selectPeopleInitWithTarget:(id)target
{
    const CGFloat marginTop = 0.f;
    
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(NU_CONTROL_X, marginTop, NU_WIDTH, NU_LABEL_HEIGHT)];
    label.text = CH_PEOPLE;
    [self addSubview:label];
    
    _usernameTextField = [[MyTextField alloc] initWithFrame:CGRectMake(NU_CONTROL_X, marginTop + NU_LABEL_HEIGHT, NU_WIDTH, NU_LABEL_HEIGHT)];
    _usernameTextField.delegate = target;
    [self addSubview:_usernameTextField];
    
    MyButton *button = [MyButton buttonWithTitle:CH_SELECT_PEOPLE
                                      withTarget:target
                                       andAction:@selector(selectPeopleButtonTouchDown)];
    button.frame = CGRectMake(NU_CONTROL_X, marginTop + NU_HEIGHT * 2, NU_WIDTH, NU_HEIGHT);
    [self addSubview:button];
    
    return YES;
}

- (BOOL)selectRestaurantInitWithTarget:(id)target
{
    const CGFloat marginTop = 105.f;
    
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(NU_CONTROL_X, marginTop, NU_WIDTH, NU_LABEL_HEIGHT)];
    label.text = CH_RESTAURANT;
    [self addSubview:label];
    
    _restaurantTextField = [[MyTextField alloc] initWithFrame:CGRectMake(NU_CONTROL_X, marginTop + NU_LABEL_HEIGHT, NU_WIDTH, NU_LABEL_HEIGHT)];
    _restaurantTextField.delegate = target;
    [self addSubview:_restaurantTextField];
    
    MyButton *button = [MyButton buttonWithTitle:CH_SELECT_RESTAURANT
                                      withTarget:target
                                       andAction:@selector(selectRestaurantButtonTouchDown)];
    button.frame = CGRectMake(NU_CONTROL_X, marginTop + NU_HEIGHT * 2, NU_WIDTH, NU_HEIGHT);
    [self addSubview:button];
    
    return YES;
}

- (BOOL)selectFoodInitWithTarget:(id)target
{
    const CGFloat marginTop = 210.f;
    
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(NU_CONTROL_X, marginTop, NU_WIDTH, NU_LABEL_HEIGHT)];
    label.text = CH_FOOD;
    [self addSubview:label];
    
    _foodTextField = [[MyTextField alloc] initWithFrame:CGRectMake(NU_CONTROL_X, marginTop + NU_LABEL_HEIGHT, NU_WIDTH, NU_LABEL_HEIGHT)];
    _foodTextField.delegate = target;
    [self addSubview:_foodTextField];
    
    MyButton *button = [MyButton buttonWithTitle:CH_SELECT_FOOD
                                      withTarget:target
                                       andAction:@selector(selectFoodButtonTouchDown)];
    button.frame = CGRectMake(NU_CONTROL_X, marginTop + NU_HEIGHT * 2, NU_WIDTH, NU_HEIGHT);
    [self addSubview:button];
    
    return YES;
}

#pragma mark - get textField

- (id)usernameTextField
{
    return _usernameTextField;
}

- (id)restaurantTextField
{
    return _restaurantTextField;
}

- (id)foodTextField
{
    return _foodTextField;
}

#pragma mark - set textField text

- (BOOL)setUsernameTextFieldText:(NSString *)text
{
    _usernameTextField.text = text;
    return YES;
}

- (BOOL)setFoodTextFieldText:(NSString *)text
{
    _foodTextField.text = text;
    return YES;
}

- (BOOL)setRestaurantTextFieldText:(NSString *)text
{
    _restaurantTextField.text = text;
    return YES;
}

@end
