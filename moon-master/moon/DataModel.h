//
//  DataModel.h
//  moon
//
//  Created by Lovells on 13-7-18.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@class OrderList;
@class OrderItem;

@interface DataModel : NSObject

// 获得订单列表对象OrderList
- (OrderList *)orderListObject;

// 获得从JSON中解析出来的数据字典
- (NSDictionary *)usersDictionary;
- (NSDictionary *)restaurantDictionary;
- (NSDictionary *)foodsDictionary;

// 获得从字典中解析出来的对应数据数组
- (NSMutableArray *)allUsername;
- (NSMutableArray *)allRestaurant;
- (NSMutableArray *)unOrderedUsersNeedReload:(BOOL)isReload;
- (NSMutableArray *)foodsForSpecifyRestaurant;
- (NSMutableArray *)foodsWithRestaurant:(NSString *)restaurant;

// orderList
- (NSString *)usernameInOrderListAtIndex:(NSUInteger)index;
- (double)priceInOrderListAtIndex:(NSUInteger)index;
- (OrderItem *)itemInOrderListAtIndex:(NSUInteger)index;
- (NSUInteger)orderListCount;
- (double)totalPriceAllOrderList;
- (BOOL)addOrderItemWithUsername:(NSString *)username restaurant:(NSString *)restaurant food:(NSString *)foodName price:(double)price;

// user
- (NSString *)usernameInAllUsernameAtIndex:(NSUInteger)index;
- (NSUInteger)allUsernameCount;
- (NSString *)unOrderedUsernameAtIndex:(NSUInteger)index;
- (NSUInteger)unOrderedUsersCount;

// restaurant
- (NSString *)restaurantInAllRestaurantAtIndex:(NSUInteger)index;
- (NSUInteger)allRestaurantCount;

// foods
- (NSDictionary *)foodForSpecifyRestaurantAtIndex:(NSUInteger)index;
- (NSString *)foodNameForSpecifyRestaurantAtIndex:(NSUInteger)index;
- (double)foodPriceForSpecifyRestaurantAtIndex:(NSUInteger)index;
- (NSUInteger)foodCountForSpecifyRestaurant;
- (double)priceWithFoodName:(NSString *)foodName;

@end
