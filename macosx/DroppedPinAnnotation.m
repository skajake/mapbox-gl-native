#import "DroppedPinAnnotation.h"

#import "LocationCoordinate2DTransformer.h"
#import "TimeIntervalTransformer.h"
#import "NSValue+Additions.h"

@implementation DroppedPinAnnotation {
    NSTimer *_timer;
    
    NSValueTransformer *_coordinateTransformer;
    NSValueTransformer *_timeIntervalTransformer;
}

- (instancetype)init {
    if (self = [super init]) {
        _coordinateTransformer = [NSValueTransformer valueTransformerForName:
                                  NSStringFromClass([LocationCoordinate2DTransformer class])];
        _timeIntervalTransformer = [NSValueTransformer valueTransformerForName:
                                    NSStringFromClass([TimeIntervalTransformer class])];
        [self update];
    }
    return self;
}

- (void)dealloc {
    [self pause];
}

- (void)setCoordinate:(CLLocationCoordinate2D)coordinate {
    super.coordinate = coordinate;
    [self update];
}

- (void)resume {
    _timer = [NSTimer scheduledTimerWithTimeInterval:1
                                              target:self
                                            selector:@selector(increment:)
                                            userInfo:nil
                                             repeats:YES];
}

- (void)pause {
    [_timer invalidate];
    _timer = nil;
}

- (void)increment:(NSTimer *)timer {
    self.elapsedShownTime++;
    [self update];
}

- (void)update {
    NSString *coordinate = [_coordinateTransformer transformedValue:
                            [NSValue valueWithCLLocationCoordinate2D:self.coordinate]];
    NSString *elapsedTime = [_timeIntervalTransformer transformedValue:@(self.elapsedShownTime)];
    self.subtitle = [NSString stringWithFormat:@"%@\nSelected for %@", coordinate, elapsedTime];
}

@end
