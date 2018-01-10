//
//  NonogramModelView.h
//  NonogramSolver
//
//  Created by John Zakharov on 05.01.2018.
//  Copyright © 2018 John Zakharov. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NonogramModelView : NSObject

@property NSFont *font;
@property (readonly) BOOL isSolvingNonogram;

- (instancetype)init;

- (void)draw:(CGRect)rect;

- (void)loadNonogramFromFile:(NSString*)filepath;
- (void)startSolvingNonogram;

@end
