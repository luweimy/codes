//
//  ASAppDelegate.h
//  BatchRename
//
//  Created by Luwei on 14-1-23.
//  Copyright (c) 2014年 fireflysoft. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ASAppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;

@property (readonly, strong, nonatomic) NSPersistentStoreCoordinator *persistentStoreCoordinator;
@property (readonly, strong, nonatomic) NSManagedObjectModel *managedObjectModel;
@property (readonly, strong, nonatomic) NSManagedObjectContext *managedObjectContext;

- (IBAction)saveAction:(id)sender;
@property (unsafe_unretained) IBOutlet NSTextView *logTextView;

@end
