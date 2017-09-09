//
//  ASWindowController.m
//  BatchRename
//
//  Created by Luwei on 14-1-23.
//  Copyright (c) 2014年 fireflysoft. All rights reserved.
//

#import "ASRenameController.h"
#import "ASAppDelegate.h"

@implementation ASRenameController

- (instancetype)init
{
    self = [super init];
    if (self) {
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            self.dragBoxView.delegate = self;
        });
    }
    return self;
}

#pragma mark - 功能

- (NSArray *)filterOutWithPaths:(NSArray *)paths
{
    // 处理文件名，减少干扰项
    _filePaths = [self pretreatmentFilenames:paths];
    _oldPrefix = [self commonPrefixInArray:_filePaths];
    
    // 去除和公共头不符的文件名
    NSMutableArray *removeFilenames = [NSMutableArray array];
    for (NSString *filename in _filePaths) {
        if (![filename hasPrefix:_oldPrefix]) {
            [removeFilenames addObject:filename];
        }
    }
    NSMutableArray *removedArray = [NSMutableArray arrayWithArray:_filePaths];
    [removedArray removeObjectsInArray:removeFilenames];
    _filePaths = removedArray;
    
    return _filePaths;
}

- (void)displayInformationWithArray:(NSArray *)array
{
    if (array.count == 0) {
        self.warnningLabel.stringValue = @"警告：没有符合条件的文件";
        return;
    }
    
    if (array.count == 1) {
        [self.commonPerfix setStringValue:[array objectAtIndex:0]];
        _oldPrefix = array[0];
        return;
    }
    
    // 显示信息
    [self.commonPerfix setStringValue:_oldPrefix];
    [self.fileCount setStringValue:@(array.count).description];
    
    //
    // 获得数字范围
    //
    self.logTextView.string = @"将要修改的文件名";
    NSMutableArray *numberArray = [NSMutableArray array];
    for (NSString *item in array) {
        self.logTextView.string = [NSString stringWithFormat:@"%@\n%@", self.logTextView.string, item];
        NSString *substring = [item substringFromIndex:_oldPrefix.length];
        substring = [substring stringByDeletingPathExtension];
        if (substring.length == 0 || [substring hasPrefix:@"."]) {
            self.warnningLabel.stringValue = [NSString stringWithFormat:@"警告：包含异常文件名(%@)", item];
            continue;
        }
        [numberArray addObject:substring];
    }
    
    NSString *rangeBegin = numberArray[0];
    NSString *rangeEnd = [numberArray lastObject];
    _filenameRange = NSMakeRange(rangeBegin.intValue, rangeEnd.intValue - rangeBegin.intValue + 1);
    [self.fileRangeBegin setStringValue:@(_filenameRange.location).description];
    [self.fileRangeEnd setStringValue:@(_filenameRange.location + _filenameRange.length - 1).description];
    if (_filenameRange.length != array.count) {
        [self.fileRangeEnd setStringValue:@("?")];
        self.warnningLabel.stringValue = @"警告：文件数量存在异常，可能有不包含数字的文件名";
    }
}

- (NSArray *)pretreatmentFilenames:(NSArray *)filenames
{
    // 获得扩展名字典，保存每个扩展名对应的文件个数
    NSMutableDictionary *extensionDictionary = [NSMutableDictionary dictionary];
    for (NSString *filename in filenames) {
        NSString *extension = [filename pathExtension];
        NSNumber *value = extensionDictionary[extension];
        value = (value) ? @(value.intValue + 1) : @(1);
        [extensionDictionary setObject:value forKey:extension];
    }
    
    // 获取要去除的扩展名
    NSMutableArray *removeExtensions = [NSMutableArray array];
    for (NSString *key in extensionDictionary) {
        NSNumber *value = extensionDictionary[key];
        if (value.intValue == 1 || value.intValue == 2) {
            [removeExtensions addObject:key];
        }
    }
    
    // 获得要删除的文件名
    NSMutableArray *removeFilenames = [NSMutableArray array];
    for (NSString *filename in filenames) {
        for (NSString *extension in removeExtensions) {
            if ([[filename pathExtension] isEqualToString:extension]) {
                [removeFilenames addObject:filename];
            }
        }
    }
    
    // 删除文件名
    NSMutableArray *handleFilenames = [NSMutableArray arrayWithArray:filenames];
    [handleFilenames removeObjectsInArray:removeFilenames];
    return handleFilenames;
}

- (NSString *)commonPrefixInArray:(NSArray *)array
{
    // 获得公共文件名头
    NSString *firstPath = [array firstObject];
    NSString *lastPath = [array lastObject];
    NSString *commonPrefix = [firstPath commonPrefixWithString:lastPath options:NSCaseInsensitiveSearch];
    NSMutableString *preCommon = [NSMutableString stringWithString:commonPrefix];
    
    // 从后向前遍历
    for (NSInteger i = preCommon.length - 1; i > 0; i--) {
        // 遍历字符串
        NSString *indexChar = [preCommon substringWithRange:NSMakeRange(i, 1)];

        if ([indexChar intValue] != 0) {
            [preCommon deleteCharactersInRange:NSMakeRange(i, 1)];
        }
        else {
            break;
        }
    }
    
    return preCommon;
}

- (NSArray *)subpathWithFolderPath:(NSString *)folderPath containsFolder:(BOOL)isContains
{
    NSError *error;
    NSArray *filePaths = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:folderPath error:&error];
    if (error) {
        [self alertWithError:error message:@"扫描文件列表异常"];
        return nil;
    }
    
    // 删除文件夹名
    NSMutableArray *removedFolderArray = [NSMutableArray array];
    NSError *pError;
    for (NSString *item in filePaths) {
        NSString *path = [self.pathLabel.stringValue stringByAppendingPathComponent:item];
        NSDictionary *attribute = [[NSFileManager defaultManager] attributesOfItemAtPath:path error:&pError];
        if ([attribute[NSFileType] isEqualToString:NSFileTypeRegular]) {
            [removedFolderArray addObject:item];
        }
    }
    
    // 文件名筛选排序
    NSArray *removedFilenames = [self filterOutWithPaths:removedFolderArray];
    NSArray *sorttedFilenames = [self sortWithFilenames:removedFilenames];

    // 若要包含隐藏文件
    if (isContains) {
        return sorttedFilenames;
    }
    
    // 不包含隐藏文件
    NSMutableArray *removedHiddenFilesArray = [NSMutableArray array];
    for (NSString *path in sorttedFilenames) {
        if (![path hasPrefix:@"."]) {
            [removedHiddenFilesArray addObject:path];
        }
    }
    
    return removedHiddenFilesArray;
}

- (NSArray *)sortWithFilenames:(NSArray *)filenames
{
    filenames = [filenames sortedArrayUsingSelector:@selector(compare:)];
    filenames = [filenames sortedArrayUsingComparator:^NSComparisonResult(id obj1, id obj2) {
        if ([obj1 length] > [obj2 length]) {
            return NSOrderedDescending;
        }
        return NSOrderedSame;
    }];
    return filenames;
}

- (BOOL)backupOldFiles:(NSArray *)fileNames
{
    // 创建备份文件夹
    NSString *dateString = [[NSDate date] description];
    NSString *folderName = [dateString substringToIndex:[dateString rangeOfString:@"+"].location - 1];
    _backupPath = [self.pathLabel.stringValue stringByAppendingPathComponent:folderName];
    NSError *error;
    NSFileManager *fileManager = [NSFileManager defaultManager];
    [fileManager createDirectoryAtPath:_backupPath withIntermediateDirectories:YES attributes:nil error:&error];
    if (error) {
        [self alertWithError:error message:@"创建备份文件夹异常"];
        return NO;
    }
    
    // 将文件拷贝到备份文件夹中
    for (NSString *filename in fileNames) {
        NSString *path = [self.pathLabel.stringValue stringByAppendingPathComponent:filename];
        NSError *error;
        [fileManager copyItemAtPath:path toPath:[_backupPath stringByAppendingPathComponent:filename] error:&error];
        if (error) {
            [self alertWithError:error message:[NSString stringWithFormat:@"备份文件(%@)发生异常", filename]];
            return NO;
        }
    }
    return YES;
}

- (BOOL)renameFilenames:(NSArray *)oldFilenames oldPrefix:(NSString *)oldPrefix newPrefix:(NSString *)newPrefix
{
    NSFileManager *fileManager = [NSFileManager defaultManager];

    // 删除旧的文件
    for (NSString *item in oldFilenames) {
        NSString *filepath = [self.pathLabel.stringValue stringByAppendingPathComponent:item];
        NSError *error;
        [fileManager removeItemAtPath:filepath error:&error];
        if (error) {
            [self alertWithError:error message:@"删除文件发生异常"];
            return NO;
        }
    }
    
    // 重新拷贝回来，并且使用新的文件名
    self.logTextView.string = @"";
    NSInteger index = _filenameRange.location;
    for (NSString *item in oldFilenames) {
        NSString *oldFilepath = [_backupPath stringByAppendingPathComponent:item];
        NSRange oldPrefixRange = [item rangeOfString:oldPrefix];
        NSMutableString *newFilename;
        if ([[item substringWithRange:NSMakeRange(oldPrefixRange.location + oldPrefixRange.length, 1)] isEqualToString:@"."]) {
            newFilename = [NSMutableString stringWithFormat:@"%@.%@", newPrefix, item.pathExtension];
        }
        else {
            newFilename = [NSMutableString stringWithFormat:@"%@%li.%@", newPrefix, index++, item.pathExtension];
        }
        NSString *newFilepath = [self.pathLabel.stringValue stringByAppendingPathComponent:newFilename];
        NSString *logString = [NSString stringWithFormat:@"%@-->%@\n", item.description, newFilename.description];
        self.logTextView.enclosingScrollView.verticalLineScroll = self.logTextView.enclosingScrollView.verticalLineScroll + 1;
        self.logTextView.string = [NSString stringWithFormat:@"%@%@", self.logTextView.string, logString];
        NSError *error;
        [fileManager copyItemAtPath:oldFilepath toPath:newFilepath error:&error];
        if (error) {
            [self alertWithError:error message:@"重命名文件发生异常"];
            return NO;
        }
    }
    
    // 更新文件信息
    [self updateFilenames];
    
    return YES;
}

- (void)updateFilenames
{
    _filePaths = [self subpathWithFolderPath:self.pathLabel.stringValue containsFolder:(NSOnState == _browserState)];
    _oldPrefix = self.commonPerfix.stringValue;
    self.successPromptLabel.stringValue = @"";
    self.warnningLabel.stringValue = @"";
}

#pragma mark - 事件回调

- (IBAction)browserPressed:(NSButton *)sender {
    
    NSOpenPanel *openPanel = [NSOpenPanel openPanel];
    openPanel.canChooseDirectories = YES;
    openPanel.canChooseFiles = NO;
    openPanel.canCreateDirectories = YES;
    openPanel.message = @"请选择文件夹(可以对文件夹内的文件重命名)";
    
    if (NSOnState == _browserState) {
        openPanel.showsHiddenFiles = YES;
    }
    
    ASAppDelegate *delegate = [NSApplication sharedApplication].delegate;
    [openPanel beginSheetModalForWindow:delegate.window completionHandler:^(NSInteger result) {
        if (NSOKButton == result) {
            NSString *path = [[[openPanel URLs] objectAtIndex:0] relativePath];
            [self setPathLablePath:path];
        }
    }];
}

- (void)setPathLablePath:(NSString*)path{
    self.pathLabel.stringValue = path;
    _filePaths = [self subpathWithFolderPath:path containsFolder:(NSOnState == _browserState)];
    [self displayInformationWithArray:_filePaths];
}

- (IBAction)checkButtonPressed:(NSButton *)sender {
    _browserState = sender.state;
}

- (IBAction)renameButtonPressed:(NSButton *)sender {
    
    [self.commonPerfix becomeFirstResponder];
    
    // 若没有选择文件夹
    if (!_filePaths || _filePaths.count == 0) {
        NSInteger ret = NSRunAlertPanel(@"警告", @"您还没有选择文件夹", @"YES", @"Cancel", nil);
        if (ret == NSOKButton) {
            // 打开文件浏览panel
            [self browserPressed:nil];
        }
    }
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        // 备份原来的文件们
        if ([self backupOldFiles:_filePaths]) {
            // 重命名所有文件
            BOOL ret = [self renameFilenames:_filePaths oldPrefix:_oldPrefix newPrefix:self.commonPerfix.stringValue];
            if (ret) {
                self.successPromptLabel.stringValue = [NSString stringWithFormat:@"成功修改文件%@个", self.fileCount.stringValue];
            }
            else {
                self.successPromptLabel.stringValue = @"修改文件名失败";
            }
        }
    });
}

- (IBAction)filenameRangeChanged:(NSTextField *)sender {
    _filenameRange = NSMakeRange(sender.stringValue.intValue, _filenameRange.length);
    self.fileRangeEnd.stringValue = @(_filenameRange.location + _filenameRange.length - 1).description;
}

- (IBAction)updateFilenamesInfomation:(NSButton *)sender {
    if ([self.pathLabel.stringValue isEqualToString:@""]) {
        return;
    }
    [self updateFilenames];
    self.commonPerfix.stringValue = [self commonPrefixInArray:_filePaths];
    _oldPrefix = self.commonPerfix.stringValue;
    [self displayInformationWithArray:_filePaths];
}

- (IBAction)openFinder:(NSButton *)sender {
    NSString *commond = [NSString stringWithFormat:@"open '%@'", self.pathLabel.stringValue];
    system(commond.UTF8String);
}

- (void)alertWithError:(NSError *)error message:(NSString *)message
{
    NSAlert *alert = [NSAlert alertWithError:error];
    alert.informativeText = message;
    [alert runModal];
}

@end
