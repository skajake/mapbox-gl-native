#import <mbgl/osx/MGLMapView.h>

@interface MGLMapView (Private)

@property (nonatomic, readonly, getter=isDormant) BOOL dormant;

- (void)renderSync;

@end
