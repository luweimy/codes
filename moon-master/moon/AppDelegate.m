//
//  AppDelegate.m
//  moon
//
//  Created by Lovells on 13-7-12.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import "AppDelegate.h"
#import "MainViewController.h"
#import "data.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
        
    UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:[[MainViewController alloc] init]];
    navController.navigationBar.tintColor = [UIColor blackColor];
    UITabBarController *tabBarController = [[UITabBarController alloc] init];
    tabBarController.viewControllers = [NSArray arrayWithObject:navController];
    self.window.rootViewController = tabBarController;
    [self setBackButtonItem];
    self.window.backgroundColor = [UIColor whiteColor];
    
    [self.window makeKeyAndVisible];
    
    return YES;
}

- (BOOL)setBackButtonItem
{
    UIBarButtonItem *backButtonItem = [[UIBarButtonItem alloc] init];
    backButtonItem.title = EN_BACK;
    self.window.rootViewController.navigationItem.backBarButtonItem = backButtonItem;
    return YES;
}

@end
