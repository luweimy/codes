//
//  ASDropBoxView.h
//  BatchRename
//
//  Created by etime on 14-9-4.
//  Copyright (c) 2014年 fireflysoft. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@protocol ASDropDelegate <NSObject>

- (void)setPathLablePath:(NSString*)path;

@end

@interface ASDropBoxView : NSBox<NSDraggingDestination>
{
    BOOL highlight;
}

@property(assign)id <ASDropDelegate>delegate;

- (id)initWithCoder:(NSCoder *)coder;

@end
