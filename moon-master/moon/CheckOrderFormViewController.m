//
//  CheckOrderFormViewController.m
//  moon
//
//  Created by Lovells on 13-7-12.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "CheckOrderFormViewController.h"
#import "SelectPeopleViewController.h"
#import "CheckOrderFormTableView.h"
#import "DataModel.h"
#import "OrderItem.h"
#import "data.h"

@interface CheckOrderFormViewController ()
{
    DataModel *_dataModel;
}

@end

@implementation CheckOrderFormViewController

- (void)loadView
{
    CheckOrderFormTableView *tableView = [[CheckOrderFormTableView alloc] initWithFrame:[UIScreen mainScreen].applicationFrame andDataModel:_dataModel];
    
    [tableView createOrderInfoLabelInTabBar:self.tabBarController.tabBar];
    [tableView setDelegate:self];
    [tableView setDataSource:self];
    self.tableView = tableView;
    self.title = CH_SHOW_ORDER;
}

- (void)viewWillAppear:(BOOL)animated
{    
    [UIView animateWithDuration:NU_ANIMATE_TIME animations:^{
        self.tabBarController.tabBar.alpha = 1.f;
    }];
    
    [_dataModel unOrderedUsersNeedReload:YES];
    [(CheckOrderFormTableView *)self.view refreshOrderInfoLabel];
}

- (id)initWithDataModel:(DataModel *)dataModel
{
    if (self = [super init])
    {
        _dataModel = dataModel;
    }
    return self;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return NU_SECTION_SUM;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0.f, 0.f, NU_SCREEN_WIDTH, 0.f)];
    label.backgroundColor = [UIColor colorWithRed:0.269f green:0.433f blue:0.606f alpha:1.f];
    label.textColor = [UIColor whiteColor];
    label.font = [UIFont boldSystemFontOfSize:NU_FONT_SIZE];
    
    if (NU_SECTION_ONE == section)
    {
        label.text = [NSString stringWithFormat:@"%i人已定", [_dataModel orderListCount]];
    }
    else if (NU_SECTION_TWO == section)
    {
        label.text = [NSString stringWithFormat:@"%i人未定", [_dataModel unOrderedUsersCount]];
    }
    
    return label;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (NU_SECTION_ONE == section)
    {
        return [_dataModel orderListCount];
    }
    else if (NU_SECTION_TWO == section)
    {
        return [_dataModel unOrderedUsersCount];
    }
    return NU_DEFAULT;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return NU_TABLE_ROW_HEIGHT;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self.tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier: EN_CHECK];
    if (!cell)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:EN_CHECK];
    }
    
    // 设置tableViewCell
    [self setTableCell:cell withIndexPath:indexPath];
    
    return cell;
}

- (BOOL)setTableCell:(UITableViewCell *)tableCell withIndexPath:(NSIndexPath *)indexPath
{
    if (NU_SECTION_ONE == indexPath.section)
    {
        tableCell.textLabel.text =  [_dataModel usernameInOrderListAtIndex:indexPath.row];
        tableCell.detailTextLabel.text = [self detailTextWithOrderItem:[_dataModel itemInOrderListAtIndex:indexPath.row]];
        [tableCell.contentView addSubview:[self createPriceLabelAtIndexPath:indexPath]];
    }
    else if (NU_SECTION_TWO == indexPath.section)
    {
        tableCell.textLabel.text = [_dataModel unOrderedUsernameAtIndex:indexPath.row];
    }
    return YES;
}

- (UILabel *)createPriceLabelAtIndexPath:(NSIndexPath *)indexPath;
{
    UILabel *priceLabel = [[UILabel alloc]initWithFrame:CGRectMake(255.f, 15.f, 60.f, 30.f)];
    OrderItem *item = [_dataModel itemInOrderListAtIndex:indexPath.row];
    
    priceLabel.text = [self getPriceWithOrderItem:item];
    
    if (item.price > NU_RED_PRICE_LIMIT)
    {
        priceLabel.textColor = [UIColor redColor];
    }
    
    return priceLabel;
}

- (NSString *)getPriceWithOrderItem:(OrderItem *)item
{
    if (item.price)
    {
        return [NSString stringWithFormat:@"￥%.1f", item.price];
    }
    
    return STR_EMPTY;
}

- (NSString *)detailTextWithOrderItem:(OrderItem *)item
{
    NSString *detail = STR_EMPTY;
    
    if (item.restaurant)
    {
        detail = [detail stringByAppendingString:item.restaurant];
    }
    
    if (item.foodName)
    {
        detail = [detail stringByAppendingFormat:@" %@", item.foodName];
    }
    
    return detail;
}

@end
