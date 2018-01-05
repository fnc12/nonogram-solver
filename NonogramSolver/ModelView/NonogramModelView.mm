//
//  NonogramModelView.m
//  NonogramSolver
//
//  Created by John Zakharov on 05.01.2018.
//  Copyright © 2018 John Zakharov. All rights reserved.
//

#import "NonogramModelView.h"
#include "Nonogram.hpp"

#import <Quartz/Quartz.h>
#include <algorithm>

using namespace DataModel;

static struct {
    int width = 10;
    int height = 10;
} start;

static const NSSize cellSize{30, 30};

@interface NonogramModelView () {
    Nonogram nonogram;
}

@end

@implementation NonogramModelView

- (instancetype)init {
    self = [super init];
    if(self){
        for(auto i = 0; i < start.width; ++i) {
            nonogram.vertical.emplace_back();
        }
        for(auto i = 0; i < start.height; ++i) {
            nonogram.horizontal.emplace_back();
        }
        _font = [NSFont systemFontOfSize:[NSFont systemFontSize]];
    }
    return self;
}

- (void)draw:(CGRect)rect {
//    NSLog(@"%@ %@", NSStringFromSelector(_cmd), NSStringFromRect(rect));
    NSPoint center{CGRectGetMidX(rect), CGRectGetMidY(rect)};
    auto nonogramWidth = int(nonogram.vertical.size());
    auto nonogramHeight = int(nonogram.horizontal.size());
    auto ctx = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
    
    CGPoint o;
    CGSize s;
    
    auto verticalNumbersMaxIt = std::max_element(nonogram.vertical.begin(), nonogram.vertical.end(), [](auto &lhs, auto &rhs) {
        return lhs.size() < rhs.size();
    });
    auto verticalNumbersMax = 0;
    if(verticalNumbersMaxIt != nonogram.vertical.end()) {
        verticalNumbersMax = int(verticalNumbersMaxIt->size());
    }
    if(verticalNumbersMax == 0) {
        verticalNumbersMax = 1;
    }
    auto verticalCellsCount = nonogramHeight + verticalNumbersMax;
    
    auto horizontalNumbersMaxIt = std::max_element(nonogram.horizontal.begin(), nonogram.horizontal.end(), [](auto &lhs, auto &rhs) {
        return lhs.size() < rhs.size();
    });
    auto horizontalNumbersMax = 0;
    if(horizontalNumbersMaxIt != nonogram.horizontal.end()) {
        horizontalNumbersMax = int(horizontalNumbersMaxIt->size());
    }
    if(horizontalNumbersMax == 0) {
        horizontalNumbersMax = 1;
    }
    auto horizontalCellsCount = nonogramWidth + horizontalNumbersMax;
    
    NSSize nonogramSize{
        (cellSize.width + 0) * CGFloat(nonogramWidth),
        (cellSize.height + 0) * CGFloat(nonogramHeight),
    };
    NSSize fieldSize{
        cellSize.width * CGFloat(nonogramWidth + verticalNumbersMax),
        cellSize.height * CGFloat(nonogramHeight + horizontalNumbersMax),
    };
    
    //  fill field with white color
    s = fieldSize;
    auto fieldOrigin = o = {center.x - s.width / 2, center.y - s.height / 2};
    CGRect fieldRect{o, s};
    [[NSColor whiteColor] setFill];
    CGContextFillRect(ctx, fieldRect);
    
    //  fill horizontal numbers with light gray color
    s = {
        cellSize.width * CGFloat(horizontalNumbersMax),
        nonogramSize.height,
    };
    o = fieldRect.origin;
    [[NSColor lightGrayColor] setFill];
    CGContextFillRect(ctx, {o, s});
    
    //  fill vertical numbers with light gray color
    s = {
        nonogramSize.width,
        cellSize.height * CGFloat(verticalNumbersMax),
    };
    o = {
        fieldRect.origin.x + cellSize.width * CGFloat(horizontalNumbersMax),
        fieldRect.origin.y + nonogramSize.height,
    };
    CGContextFillRect(ctx, {o, s});
    
    //  draw vertical lines..
    [[NSColor blackColor] setFill];
    for(auto x = 0; x < horizontalCellsCount; ++x) {
        s.width = 1;
        if(x >= horizontalNumbersMax) {
            s.height = fieldSize.height;
            if((x - horizontalNumbersMax) % 5 == 0) {
                s.width = 3;
            }
        }else{
            s.height = nonogramSize.height;
        }
        o = {fieldOrigin.x + cellSize.width * CGFloat(x) - s.width / 2, fieldOrigin.y};
        CGContextFillRect(ctx, {o, s});
    }
    
    //  draw horizontal lines..
    for(auto y = 0; y < verticalCellsCount; ++y) {
        s.height = 1;
        if(y <= nonogramHeight) {
            o.x = fieldOrigin.x;
            s.width = fieldSize.width;
            if(y % 5 == 0) {
                s.height = 3;
            }
        }else{
            s.width = nonogramSize.width;
            o.x = fieldOrigin.x + CGFloat(horizontalNumbersMax * cellSize.width);
        }
        o.y = fieldOrigin.y + cellSize.height * CGFloat(y) - s.height / 2;
        CGContextFillRect(ctx, {o, s});
    }
    
    //  draw vertical numbers..
    auto attributes = @{NSFontAttributeName: self.font, NSForegroundColorAttributeName: [NSColor blackColor]};
    for(size_t lineIndex = 0; lineIndex < nonogram.vertical.size(); ++lineIndex) {
        auto &line = nonogram.vertical[lineIndex];
        for(size_t numberIndex = 0; numberIndex < line.size(); ++numberIndex) {
            auto number = line[line.size() - numberIndex - 1];
            auto text = [NSString stringWithFormat:@"%d", number];
            s = [text sizeWithAttributes:@{NSFontAttributeName: self.font}];
            CGPoint cellCenter{
                fieldOrigin.x + CGFloat(horizontalNumbersMax + lineIndex + 0.5) * cellSize.width,
                fieldOrigin.y + nonogramSize.height + cellSize.height * CGFloat(numberIndex + 0.5),
            };
            o = {
                cellCenter.x - s.width / 2,
                cellCenter.y - s.height / 2,
            };
            [text drawInRect:{o, s} withAttributes:attributes];
        }
    }
    
    //  draw horizontal numbers..
    for(size_t lineIndex = 0; lineIndex < nonogram.horizontal.size(); ++lineIndex) {
        auto &line = nonogram.horizontal[lineIndex];
        for(size_t numberIndex = 0; numberIndex < line.size(); ++numberIndex) {
            auto number = line[numberIndex];
            auto text = [NSString stringWithFormat:@"%d", number];
            s = [text sizeWithAttributes:@{NSFontAttributeName: self.font}];
            CGPoint cellCenter{
                fieldOrigin.x + cellSize.width * CGFloat(horizontalNumbersMax - line.size() + 0.5 + numberIndex),
                fieldOrigin.y + nonogramSize.height - cellSize.height * CGFloat(lineIndex + 0.5),
            };
            o = {
                cellCenter.x - s.width / 2,
                cellCenter.y - s.height / 2,
            };
            [text drawInRect:{o, s} withAttributes:attributes];
        }
    }
}

- (void)loadNonogramFromFile:(NSString*)filepath {
    if(auto data = [NSData dataWithContentsOfFile:filepath]) {
        if(auto jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]) {
            using nlohmann::json;
            try{
                nonogram = json::parse(jsonString.UTF8String);
            }catch(...){
                NSLog(@"%s error parsing Nonogram", sel_getName(_cmd));
            }
        }else{
            NSLog(@"%s jsonString is nil", sel_getName(_cmd));
        }
    }else{
        NSLog(@"%s data is nil", sel_getName(_cmd));
    }
}

@end
