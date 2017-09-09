//
//  CheckOrderFormTableView.h
//  moon
//
//  Created by Lovells on 13-7-18.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DataModel;

@interface CheckOrderFormTableView : UITableView <UITableViewDelegate, UITableViewDataSource>
{
    DataModel *_dataModel;
    UILabel *_orderInfoLabel;
}

- (id)initWithFrame:(CGRect)frame andDataModel:(DataModel *)dataModel;
- (BOOL)createOrderInfoLabelInTabBar:(UITabBar *)tabBar;
- (BOOL)refreshOrderInfoLabel;

@end
