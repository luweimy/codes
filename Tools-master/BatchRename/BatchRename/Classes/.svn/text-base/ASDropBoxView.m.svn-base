//
//  ASDropBoxView.m
//  BatchRename
//
//  Created by etime on 14-9-4.
//  Copyright (c) 2014年 fireflysoft. All rights reserved.
//

#import "ASDropBoxView.h"
#import "ASRenameController.h"

@implementation ASDropBoxView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
        [self registerForDraggedTypes:[NSArray arrayWithObjects:NSFilenamesPboardType, nil]];
    }
    return self;
}

- (id)initWithCoder:(NSCoder *)coder
{
    self=[super initWithCoder:coder];
    if ( self ) {
        [self registerForDraggedTypes:[NSArray arrayWithObjects:NSFilenamesPboardType, nil]];
    }
    return self;
}


- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
    
    // Drawing code here.
    if ( highlight ) {
        //highlight by overlaying a gray border
        [[NSColor redColor] set];
        [NSBezierPath setDefaultLineWidth: 5];
        [NSBezierPath setDefaultFlatness:10];
        [NSBezierPath strokeRect: dirtyRect];
//        [[NSBezierPath bezierPathWithRoundedRect:dirtyRect xRadius:10 yRadius:10] stroke];
    }
}

#pragma mark - Destination Operations

- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender
{
    highlight = YES;
    [self setNeedsDisplay:YES];
    return NSDragOperationCopy;
}

- (void)draggingExited:(id <NSDraggingInfo>)sender
{
    /*------------------------------------------------------
     method called whenever a drag exits our drop zone
     --------------------------------------------------------*/
    //remove highlight of the drop zone
    highlight=NO;
    
    [self setNeedsDisplay: YES];
}

- (BOOL)prepareForDragOperation:(id <NSDraggingInfo>)sender
{
    /*------------------------------------------------------
     method to determine if we can accept the drop
     --------------------------------------------------------*/
    //finished with the drag so remove any highlighting
    highlight=NO;
    
    [self setNeedsDisplay: YES];
    
    //check to see if we can accept the data
    return YES;//[NSImage canInitWithPasteboard: [sender draggingPasteboard]];
}

- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender
{
    /*------------------------------------------------------
     method that should handle the drop data
     --------------------------------------------------------*/
    if ( [sender draggingSource] != self ) {
        NSURL* fileURL;
        
        //if the drag comes from a file, set the window title to the filename
        fileURL=[NSURL URLFromPasteboard: [sender draggingPasteboard]];
        NSString *path = [fileURL relativePath];
        [self.delegate setPathLablePath:path];
    }
    return YES;
}


@end
