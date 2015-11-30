#import "MGLCompassCell.h"

@implementation MGLCompassCell

- (void)drawKnob:(NSRect)knobRect {
    NSBezierPath *trianglePath = [NSBezierPath bezierPath];
    [trianglePath moveToPoint:NSMakePoint(NSMinX(knobRect), NSMaxY(knobRect))];
    [trianglePath lineToPoint:NSMakePoint(NSMaxX(knobRect), NSMaxY(knobRect))];
    [trianglePath lineToPoint:NSMakePoint(NSMidX(knobRect), NSMinY(knobRect))];
    [trianglePath closePath];
    NSAffineTransform *transform = [NSAffineTransform transform];
    [transform translateXBy:NSMidX(knobRect) yBy:NSMidY(knobRect)];
    [transform scaleBy:0.8];
    [transform rotateByDegrees:self.doubleValue];
    [transform translateXBy:-NSMidX(knobRect) yBy:-NSMidY(knobRect)];
    [trianglePath transformUsingAffineTransform:transform];
    [[NSColor redColor] setFill];
    [trianglePath fill];
}

@end
