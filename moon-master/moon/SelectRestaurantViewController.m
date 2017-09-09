//
//  SelectRestaurantViewController.m
//  moon
//
//  Created by Lovells on 13-7-13.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "SelectRestaurantViewController.h"
#import "DataModel.h"
#import "data.h"

@interface SelectRestaurantViewController ()
{
    DataModel *_dataModel;
    id<MyNavigateControllerDelegate> _delegate;
}

@end


@implementation SelectRestaurantViewController

- (void)loadView
{
    UITableView *tableView = [[UITableView alloc] initWithFrame:[UIScreen mainScreen].applicationFrame];
    [tableView setDelegate:self];
    [tableView setDataSource:self];
    self.view = tableView;
    self.title = CH_SELECT_RESTAURANT;
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

#pragma mark - tableView delegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [_dataModel allRestaurantCount];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [_delegate delegateSetRestaurantTextFieldText:[_dataModel restaurantInAllRestaurantAtIndex:indexPath.row]];
    [self.tableView deselectRowAtIndexPath:indexPath animated:YES];
    [self.navigationController popViewControllerAnimated:YES];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:EN_RESTAURANTS];
    if (!cell)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:EN_RESTAURANTS];
    }
    
    cell.textLabel.text = [_dataModel restaurantInAllRestaurantAtIndex:indexPath.row];
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    return cell;
}

@end
