//
//  RootViewController.m
//  moon
//
//  Created by Lovells on 13-7-12.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "MainViewController.h"
#import "HelpOrderFormViewController.h"
#import "CheckOrderFormViewController.h"
#import "MainView.h"
#import "DataModel.h"
#import "data.h"

@interface MainViewController ()
{
    DataModel *_dataModel;
}

@end

@implementation MainViewController

- (void)loadView
{
    // 创建UIView
    MainView *view = [[MainView alloc] initWithFrame:[UIScreen mainScreen].applicationFrame andTarget:self];
    self.view = view;
    self.title = CH_ORDER_FORM;
}

- (void)viewWillAppear:(BOOL)animated
{
    [UIView animateWithDuration:NU_ANIMATE_TIME animations:^{
        self.tabBarController.tabBar.alpha = 0.f;
    }];
}

#pragma mark - getter

- (DataModel *)dataModel
{
    if (!_dataModel)
    {
        _dataModel = [[DataModel alloc] init];
    }
    return _dataModel;
}

#pragma mark - actions

- (BOOL)helpOrderButtonTouchDown
{
    HelpOrderFormViewController *orderViewController = [[HelpOrderFormViewController alloc] initWithDataModel:[self dataModel]];
    [[self navigationController] pushViewController:orderViewController animated:YES];
    
    return YES;
}

- (BOOL)checkOrderButtonTouchDown
{
    CheckOrderFormViewController *checkViewController = [[CheckOrderFormViewController alloc] initWithDataModel:[self dataModel]];
    [[self navigationController] pushViewController:checkViewController animated:YES];
    
    return YES;
}


@end
