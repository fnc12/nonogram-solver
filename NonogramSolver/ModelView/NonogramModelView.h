//
//  NonogramModelView.h
//  NonogramSolver
//
//  Created by John Zakharov on 05.01.2018.
//  Copyright © 2018 John Zakharov. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol NonogramModelViewDelegate;

@interface NonogramModelView : NSObject

@property NSFont *font;
@property (readonly) BOOL isSolvingNonogram;
@property (weak) id<NonogramModelViewDelegate> delegate;

- (instancetype)init;

- (void)draw:(CGRect)rect;

- (void)loadNonogramFromFile:(NSString*)filepath;
- (void)startSolvingNonogram;

@end

@protocol NonogramModelViewDelegate

- (void)nonogramModelViewDidUpdateNonogramSolution:(NonogramModelView*)sender;
- (void)nonogramModelViewDidFinishNonogramSolving:(NonogramModelView*)sender;

@end
