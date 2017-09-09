//
//  OrderList.h
//  moon
//
//  Created by Lovells on 13-7-14.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@class OrderItem;

@interface OrderList : NSObject

- (BOOL)addOrderWithUsername:(NSString *)username restaurant:(NSString *)restaurant foodName:(NSString *)foodname price:(double)price;
- (OrderItem *)objectAtIndex:(NSUInteger)index;
- (NSInteger)itemCount;
- (NSArray *)orderListArray;

@end
