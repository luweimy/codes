//
//  HelpOrderFormView.h
//  moon
//
//  Created by Lovells on 13-7-16.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface HelpOrderFormView : UIControl
{
    @private
    UITextField *_usernameTextField;
    UITextField *_restaurantTextField;
    UITextField *_foodTextField;
}

- (id)initWithFrame:(CGRect)frame andTarget:(id)target;
- (id)usernameTextField;
- (id)restaurantTextField;
- (id)foodTextField;

- (BOOL)setUsernameTextFieldText:(NSString *)text;
- (BOOL)setFoodTextFieldText:(NSString *)text;
- (BOOL)setRestaurantTextFieldText:(NSString *)text;

@end
