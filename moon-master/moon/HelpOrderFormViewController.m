//
//  HelpOrderFormViewController.m
//  moon
//
//  Created by Lovells on 13-7-12.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "MainViewController.h"
#import "HelpOrderFormViewController.h"
#import "SelectPeopleViewController.h"
#import "SelectRestaurantViewController.h"
#import "SelectFoodViewController.h"
#import "HelpOrderFormView.h"
#import "DataModel.h"
#import "MyTextField.h"
#import "OrderList.h"
#import "data.h"

@interface HelpOrderFormViewController ()
{
    DataModel *_dataModel;
}

@end

@implementation HelpOrderFormViewController

- (void)loadView
{
    HelpOrderFormView *view = [[HelpOrderFormView alloc] initWithFrame:[UIScreen mainScreen].applicationFrame andTarget:self];
    self.view = view;
    self.title = CH_ORDER_FORM;
}

- (id)initWithDataModel:(DataModel *)dataModel
{
    if (self = [super init])
    {
        _dataModel = dataModel;
    }
    return self;
}

#pragma mark - actions

- (BOOL)selectPeopleButtonTouchDown
{
    SelectPeopleViewController *usernameViewController = [[SelectPeopleViewController alloc] initWithDataModel:_dataModel andDelegate:self];
    [self.navigationController pushViewController:usernameViewController animated:YES];
    
    return YES;
}

- (BOOL)selectRestaurantButtonTouchDown
{
    SelectRestaurantViewController *restaurantViewController = [[SelectRestaurantViewController alloc] initWithDataModel:_dataModel andDelegate:self];
    [(HelpOrderFormView *)self.view setFoodTextFieldText:nil];
    [self.navigationController pushViewController:restaurantViewController animated:YES];
    
    return YES;
}

- (BOOL)selectFoodButtonTouchDown
{
    SelectFoodViewController *foodViewController = [[SelectFoodViewController alloc] initWithDataModel:_dataModel andDelegate:self];
    [foodViewController setCurrentRestaurant:[[(HelpOrderFormView *)self.view restaurantTextField] text]];
    [self.navigationController pushViewController:foodViewController animated:YES];
    
    return YES;
}

- (BOOL)confirmButtonTouchDown
{
    if ([self canSubmitOrder])
    {
        HelpOrderFormView *view = (HelpOrderFormView *)self.view;
        
        [_dataModel addOrderItemWithUsername:[[view usernameTextField] text]
                                  restaurant:[[view restaurantTextField] text]
                                        food:[[view foodTextField] text]
                                       price:[_dataModel priceWithFoodName:[[view usernameTextField] text]]];
        
        [view setUsernameTextFieldText:nil];
        [view setFoodTextFieldText:nil];
        [self.navigationController popToRootViewControllerAnimated:YES];
    }
    return YES;
}

- (BOOL)canSubmitOrder
{
    NSString *usernameText = [[(HelpOrderFormView *)self.view usernameTextField] text];
    
    if (!usernameText)
    {
        return NO;
    }
    if ([[usernameText stringByTrimmingCharactersInSet:
           [NSCharacterSet whitespaceAndNewlineCharacterSet]] isEqualToString:STR_EMPTY])
    {
        return NO;
    }
    
    return YES;
}

- (BOOL)backgroundTapControlTouchDown
{
    HelpOrderFormView *view = (HelpOrderFormView *)self.view;
    
    [[view usernameTextField] resignFirstResponder];
    [[view restaurantTextField] resignFirstResponder];
    [[view foodTextField] resignFirstResponder];
    
    return YES;
}

#pragma mark - delegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

- (BOOL)delegateSetUsernameTextFieldText:(NSString *)username
{
    [(HelpOrderFormView *)self.view setUsernameTextFieldText:username];
    return YES;
}

- (BOOL)delegateSetRestaurantTextFieldText:(NSString *)restaurant
{
    [(HelpOrderFormView *)self.view setRestaurantTextFieldText:restaurant];
    return YES;
}

- (BOOL)delegateSetFoodNameTextFieldText:(NSString *)foodName andPrice:(double)price;
{
    [(HelpOrderFormView *)self.view setFoodTextFieldText:foodName];
    return YES;
}

@end
