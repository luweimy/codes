//
//  SelectPeopleViewController.m
//  moon
//
//  Created by Lovells on 13-7-13.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "SelectPeopleViewController.h"
#import "DataModel.h"
#import "data.h"

@interface SelectPeopleViewController ()
{    
    DataModel *_dataModel;
    id<MyNavigateControllerDelegate> _delegate;
}

@end

@implementation SelectPeopleViewController

- (void)loadView
{
    UITableView *tableView = [[UITableView alloc] initWithFrame:[UIScreen mainScreen].applicationFrame];
    [tableView setDelegate:self];
    [tableView setDataSource:self];
    self.view = tableView;
    self.title = CH_SELECT_PEOPLE;
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
    return [_dataModel allUsernameCount];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:EN_USERS];
    if (!cell)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:EN_USERS];
    }
    
    cell.textLabel.text = [_dataModel usernameInAllUsernameAtIndex:indexPath.row];
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [_delegate delegateSetUsernameTextFieldText:[_dataModel usernameInAllUsernameAtIndex:indexPath.row]];
    [self.tableView deselectRowAtIndexPath:indexPath animated:YES];
    [self.navigationController popViewControllerAnimated:YES];
}

@end
