//
//  CheckOrderFormTableView.m
//  moon
//
//  Created by Lovells on 13-7-18.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "CheckOrderFormTableView.h"
#import "DataModel.h"
#import "OrderList.h"
#import "OrderItem.h"
#import "data.h"

@implementation CheckOrderFormTableView

- (id)initWithFrame:(CGRect)frame andDataModel:(DataModel *)dataModel
{
    self = [super initWithFrame:frame];
    if (self)
    {
        _dataModel = dataModel;
        [self setSectionHeaderHeight:30.f];
    }
    return self;
}

- (BOOL)createOrderInfoLabelInTabBar:(UITabBar *)tabBar
{
    _orderInfoLabel = [[UILabel alloc] initWithFrame:CGRectMake(0.f, 0.f, tabBar.frame.size.width, tabBar.frame.size.height)];
    _orderInfoLabel.backgroundColor = [UIColor colorWithWhite:0.088 alpha:1.f];
    _orderInfoLabel.textColor = [UIColor whiteColor];
    _orderInfoLabel.textAlignment = NSTextAlignmentCenter;
    _orderInfoLabel.font = [UIFont boldSystemFontOfSize:NU_FONT_SIZE];
    _orderInfoLabel.text =
    [NSString stringWithFormat:@"%i人已定 %i人未定 共%.1f元钱", [_dataModel orderListCount], [_dataModel unOrderedUsersCount], [_dataModel totalPriceAllOrderList]];
    [tabBar addSubview:_orderInfoLabel];
    return YES;
}

- (BOOL)refreshOrderInfoLabel
{
    _orderInfoLabel.text =
    [NSString stringWithFormat:@"%i人已定 %i人未定 共%.1f元钱", [_dataModel orderListCount], [_dataModel unOrderedUsersCount], [_dataModel totalPriceAllOrderList]];

    return YES;
}

@end
