//
//  OrderItem.m
//  moon
//
//  Created by Lovells on 13-7-15.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "OrderItem.h"

@implementation OrderItem

- (id)initWithUsername:(NSString *)username
         andRestaurant:(NSString *)restaurant
           andFoodName:(NSString *)foodName
              andPrice:(double)price
{
    if (self = [super init])
    {
        _username = username;
        _restaurant = restaurant;
        _foodName = foodName;
        _price = price;
    }
    return self;
}

@end
