//
//  HelpOrderFormViewController.h
//  moon
//
//  Created by Lovells on 13-7-12.
//  Copyright (c) 2013年 Luwei. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MyNavigateControllerDelegate.h"

@class DataModel;

@interface HelpOrderFormViewController : UIViewController <UITextFieldDelegate, MyNavigateControllerDelegate>

- (id)initWithDataModel:(DataModel *)dataModel;

@end
