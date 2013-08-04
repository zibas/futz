//
//  ifutzAppDelegate.h
//  ifutz
//
//  Created by Ziba Scott on 5/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ifutzViewController;

@interface ifutzAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    ifutzViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet ifutzViewController *viewController;

@end

