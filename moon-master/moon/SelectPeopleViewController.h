//
//  SelectPeopleViewController.h
//  moon
//
//  Created by Lovells on 13-7-13.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MyNavigateControllerDelegate.h"

@class DataModel;

@interface SelectPeopleViewController : UITableViewController

- (id)initWithDataModel:(DataModel *)dataModel andDelegate:(id)delegate;

@end
