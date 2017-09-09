//
//  DataModel.m
//  moon
//
//  Created by Lovells on 13-7-18.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "DataModel.h"
#import "OrderList.h"
#import "JsonParser.h"
#import "OrderList.h"
#import "OrderItem.h"
#import "data.h"

@interface DataModel ()
{
    OrderList *_orderList;
    
    NSDictionary *_usersDictionary;
    NSDictionary *_restaurantDictionary;
    NSDictionary *_foodsDictionary;
    
    NSMutableArray *_allUsername;
    NSMutableArray *_allRestaurant;
    NSMutableArray *_foodsForRestaurant;
    
    // 未订餐的人们
    NSMutableArray *_unOrderedUsers;
}

@end

@implementation DataModel

#pragma mark - getter

- (OrderList *)orderListObject
{
    if (!_orderList)
    {
        _orderList = [[OrderList alloc] init];
    }
    return _orderList;
}

- (NSDictionary *)usersDictionary
{
    if (!_usersDictionary)
    {
        _usersDictionary = [JsonParser jsonParserFromFile:EN_USERS ofType:EN_JSON];
    }
    return _usersDictionary;
}

- (NSDictionary *)restaurantDictionary
{
    if (!_restaurantDictionary)
    {
        _restaurantDictionary = [JsonParser jsonParserFromFile:EN_RESTAURANTS ofType:EN_JSON];
    }
    return _restaurantDictionary;
}

- (NSDictionary *)foodsDictionary
{
    if (!_foodsDictionary)
    {
        _foodsDictionary = [JsonParser jsonParserFromFile:EN_FOOD ofType:EN_JSON];
    }
    return _foodsDictionary;
}

- (NSMutableArray *)allUsername
{
    if (!_allUsername)
    {
        _allUsername = [[NSMutableArray alloc] initWithCapacity:[self usersDictionary].count];
        
        for (NSDictionary *item in [self usersDictionary])
        {
            [_allUsername addObject:[item objectForKey:EN_NAME]];
        }
    }
    return _allUsername;
}

- (NSMutableArray *)allRestaurant
{
    if (!_allRestaurant)
    {
        _allRestaurant = [[NSMutableArray alloc] initWithCapacity:[self restaurantDictionary].count];
        
        for (NSDictionary *item in [self restaurantDictionary])
        {
            [_allRestaurant addObject:[item objectForKey:EN_NAME]];
        }
    }
    return _allRestaurant;
}

- (NSMutableArray *)unOrderedUsersNeedReload:(BOOL)isReload;
{
    if (nil == _unOrderedUsers || YES == isReload)
    {
        _unOrderedUsers = [[NSMutableArray alloc] initWithArray:[self allUsername]];
        
        for (OrderItem *item in [[self orderListObject] orderListArray])
        {
            // 删除 _unOrderedUsers 中指定的 item.username 的 OrderItem
            [self removeSpecifyUsername:item.username inUsernameArray:_unOrderedUsers];
        }
    }
    return _unOrderedUsers;
}

- (BOOL)removeSpecifyUsername:(NSString *)username inUsernameArray:(NSMutableArray *)usernameArray
{
    for (int i = 0; i < usernameArray.count; ++i)
    {
        if ([[usernameArray objectAtIndex:i] isEqualToString:username])
        {
            [usernameArray removeObjectAtIndex:i--];
        }
    }
    return YES;
}

- (NSMutableArray *)foodsForSpecifyRestaurant
{
    if (!_foodsForRestaurant)
    {
        [self foodsWithRestaurant:[[self allRestaurant] objectAtIndex:0]];
    }
    return _foodsForRestaurant;
}

- (NSMutableArray *)foodsWithRestaurant:(NSString *)restaurant
{
    NSDictionary *foodsDictionary = [[self foodsDictionary] objectForKey:restaurant];
    _foodsForRestaurant = [[NSMutableArray alloc] initWithCapacity:foodsDictionary.count];
    
    for (NSDictionary *item in foodsDictionary)
    {
        [_foodsForRestaurant addObject:item];
    }
    
    return _foodsForRestaurant;
}

#pragma mark - order list method

- (NSString *)usernameInOrderListAtIndex:(NSUInteger)index
{
    return [[self orderListObject] objectAtIndex:index].username;
}

- (double)priceInOrderListAtIndex:(NSUInteger)index
{
    return [[self orderListObject] objectAtIndex:index].price;
}

- (OrderItem *)itemInOrderListAtIndex:(NSUInteger)index
{
    return [[self orderListObject] objectAtIndex:index];
}

- (NSUInteger)orderListCount
{
    return [[self orderListObject] itemCount];
}

- (double)totalPriceAllOrderList
{
    double sum = 0.f;
    
    for (OrderItem *item in [[self orderListObject] orderListArray])
    {
        sum += item.price;
    }
    
    return sum;
}

- (BOOL)addOrderItemWithUsername:(NSString *)username
                      restaurant:(NSString *)restaurant
                            food:(NSString *)foodName
                           price:(double)price
{
    [[self orderListObject] addOrderWithUsername:username
                                      restaurant:restaurant
                                        foodName:foodName
                                           price:price];
    return YES;
}

#pragma mark - users

- (NSString *)usernameInAllUsernameAtIndex:(NSUInteger)index
{
    return [[self allUsername] objectAtIndex:index];
}

- (NSUInteger)allUsernameCount
{
    return [self allUsername].count;
}

- (NSString *)unOrderedUsernameAtIndex:(NSUInteger)index
{
    return [[self unOrderedUsersNeedReload:NO] objectAtIndex:index];
}

- (NSUInteger)unOrderedUsersCount
{
    return [self unOrderedUsersNeedReload:NO].count;
}

#pragma mark - restaurant

- (NSString *)restaurantInAllRestaurantAtIndex:(NSUInteger)index
{
    return [[self allRestaurant] objectAtIndex:index];
}

- (NSUInteger)allRestaurantCount
{
    return [self allRestaurant].count;
}

#pragma mark - foods

- (NSString *)foodForSpecifyRestaurantAtIndex:(NSUInteger)index
{
    return [[self foodsForSpecifyRestaurant] objectAtIndex:index];
}

- (NSString *)foodNameForSpecifyRestaurantAtIndex:(NSUInteger)index
{
    return [[self foodForSpecifyRestaurantAtIndex:index] objectForKey:EN_NAME];
}

- (double)foodPriceForSpecifyRestaurantAtIndex:(NSUInteger)index
{
    return [[[self foodForSpecifyRestaurantAtIndex:index] objectForKey:EN_PRICE] doubleValue];
}

- (NSUInteger)foodCountForSpecifyRestaurant
{
    return [self foodsForSpecifyRestaurant].count;
}

- (double)priceWithFoodName:(NSString *)foodName
{
    for (NSDictionary *item in [self foodsForSpecifyRestaurant])
    {
        if ([foodName isEqualToString:[item objectForKey:EN_NAME]])
        {
            return [[item objectForKey:EN_PRICE] doubleValue];
        }
    }
    return 0.f;
}

@end
