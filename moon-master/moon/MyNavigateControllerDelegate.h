//
//  MyNavigateControllerDelegate.h
//  moon
//
//  Created by Lovells on 13-7-16.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MyNavigateControllerDelegate <NSObject>

- (BOOL)delegateSetUsernameTextFieldText:(NSString *)username;
- (BOOL)delegateSetRestaurantTextFieldText:(NSString *)restaurant;
- (BOOL)delegateSetFoodNameTextFieldText:(NSString *)foodName andPrice:(double)price;

@end
