//
//  OrderItem.h
//  moon
//
//  Created by Lovells on 13-7-15.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface OrderItem : NSObject

@property (nonatomic, strong, readonly) NSString *username;
@property (nonatomic, strong, readonly) NSString *restaurant;
@property (nonatomic, strong, readonly) NSString *foodName;
@property (nonatomic, readonly) double price;

- (id)initWithUsername:(NSString *)username andRestaurant:(NSString *)restaurant andFoodName:(NSString *)foodName andPrice:(double)price;

@end
