#import "MGLPointAnnotation.h"

@interface DroppedPinAnnotation : MGLPointAnnotation

@property (nonatomic) NSTimeInterval elapsedShownTime;

- (void)resume;
- (void)pause;

@end
