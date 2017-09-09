//
//  ASWindowController.h
//  BatchRename
//
//  Created by Luwei on 14-1-23.
//  Copyright (c) 2014年 fireflysoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ASDropBoxView.h"

@interface ASRenameController : NSViewController<ASDropDelegate>
{
    NSInteger   _browserState;
    NSRange     _filenameRange;
    
    NSString    *_oldPrefix;
    NSArray     *_filePaths;
    NSString    *_backupPath;
}

@property (weak) IBOutlet NSTextField *pathLabel;
@property (weak) IBOutlet NSTextField *commonPerfix;
@property (weak) IBOutlet NSTextField *fileCount;
@property (weak) IBOutlet NSTextField *fileRangeBegin;
@property (weak) IBOutlet NSTextField *fileRangeEnd;
@property (weak) IBOutlet NSTextField *warnningLabel;
@property (weak) IBOutlet NSTextField *successPromptLabel;
@property (unsafe_unretained) IBOutlet NSTextView *logTextView;
@property (weak) IBOutlet ASDropBoxView *dragBoxView;

- (void)setPathLablePath:(NSString*)path;

@end
