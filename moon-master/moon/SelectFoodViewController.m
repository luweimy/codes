//
//  SelectFoodViewController.m
//  moon
//
//  Created by Lovells on 13-7-13.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "SelectFoodViewController.h"
#import "DataModel.h"
#import "data.h"

@interface SelectFoodViewController ()
{
    DataModel *_dataModel;
    id<MyNavigateControllerDelegate> _delegate;
}

@end

@implementation SelectFoodViewController

- (void)loadView
{
    UITableView *tableView = [[UITableView alloc] initWithFrame:[UIScreen alloc].applicationFrame];
    [tableView setDelegate:self];
    [tableView setDataSource:self];
    self.tableView = tableView;
    self.title = CH_SELECT_FOOD;
}

- (id)initWithDataModel:(DataModel *)dataModel andDelegate:(id)delegate
{
    if (self = [super init])
    {
        _dataModel = dataModel;
        _delegate = delegate;
    }
    return self;
}

- (BOOL)setCurrentRestaurant:(NSString *)restaurant
{
    if (restaurant)
    {
        [_dataModel foodsWithRestaurant:restaurant];
    }
        
    return YES;
}

#pragma mark - tableView delegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [_dataModel foodCountForSpecifyRestaurant];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [_delegate delegateSetFoodNameTextFieldText:[_dataModel foodNameForSpecifyRestaurantAtIndex:indexPath.row]
                                       andPrice:[_dataModel foodPriceForSpecifyRestaurantAtIndex:indexPath.row]];
    [self.tableView deselectRowAtIndexPath:indexPath animated:YES];
    [self.navigationController popViewControllerAnimated:YES];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CH_FOOD];
    if (!cell)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CH_FOOD];
    }
        
    cell.textLabel.text = [_dataModel foodNameForSpecifyRestaurantAtIndex:indexPath.row];
    cell.detailTextLabel.text = [NSString stringWithFormat:@"￥%.1f", [_dataModel foodPriceForSpecifyRestaurantAtIndex:indexPath.row]];
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    return cell;
}

@end
