//
//  OrderList.m
//  moon
//
//  Created by Lovells on 13-7-14.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "OrderList.h"
#import "OrderItem.h"

@interface OrderList ()
{
    NSMutableArray *_orderList;
}

@end

@implementation OrderList

-(id)init
{
    if (self = [super init])
    {
        _orderList = [[NSMutableArray alloc] init];
    }
    return self;
}

- (BOOL)addOrderWithUsername:(NSString *)username
                  restaurant:(NSString *)restaurant
                    foodName:(NSString *)foodname
                       price:(double)price
{
    // 若用户已存在则删除
    [self removeOrderItemWithUsername:username];
    
    // 添加新订单项
    OrderItem *item = [[OrderItem alloc] initWithUsername:username
                                            andRestaurant:restaurant
                                              andFoodName:foodname
                                                 andPrice:price];
    [_orderList addObject:item];
    return YES;
}

- (OrderItem *)objectAtIndex:(NSUInteger)index
{
    return [_orderList objectAtIndex:index];
}

- (NSInteger)itemCount
{
    return _orderList.count;
}

- (BOOL)isUsernameExists:(NSString *)username
{    
    for (OrderItem *item in _orderList)
    {
        if ([username isEqualToString:item.username])
        {
            return YES;
        }
    }
    return NO;
}

- (BOOL)removeOrderItemWithUsername:(NSString *)username
{
    for (int i = 0; i < _orderList.count; ++i)
    {
        if ([username isEqualToString:[[_orderList objectAtIndex:i] username]])
        {
            [_orderList removeObjectAtIndex:i--];
        }
    }
    return YES;
}

- (NSArray *)orderListArray
{
    return _orderList;
}

@end
