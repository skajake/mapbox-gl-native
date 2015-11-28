#import <Cocoa/Cocoa.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    MGLMapDebugTileBoundariesMask = 1 << 1,
    MGLMapDebugParsingStatusMask = 1 << 2,
    MGLMapDebugTimestampsMask = 1 << 3,
    MGLMapDebugCollisionBoxesMask = 1 << 4,
    MGLMapDebugAllMask = 0xffffffff,
} MGLMapDebugMaskOptions;

@interface MGLMapView : NSView

- (instancetype)initWithFrame:(CGRect)frame styleURL:(nullable NSURL *)styleURL;

@property (nonatomic, null_resettable) NSURL *styleURL;

- (IBAction)reloadStyle:(id)sender;

@property (nonatomic, readonly) NSSegmentedControl *zoomControls;
@property (nonatomic, readonly) NSSlider *compass;
@property (nonatomic, readonly) NSImageView *logoView;
@property (nonatomic, readonly) NSView *attributionView;

@property (nonatomic) CLLocationCoordinate2D centerCoordinate;

- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;

@property (nonatomic) double zoomLevel;
@property (nonatomic, readonly) double maximumZoomLevel;
@property (nonatomic, readonly) double minimumZoomLevel;

- (void)setZoomLevel:(double)zoomLevel animated:(BOOL)animated;

@property (nonatomic) CLLocationDirection direction;

- (void)setDirection:(CLLocationDirection)direction animated:(BOOL)animated;

@property (nonatomic, getter=isScrollEnabled) BOOL scrollEnabled;
@property (nonatomic, getter=isZoomEnabled) BOOL zoomEnabled;
@property (nonatomic, getter=isRotateEnabled) BOOL rotateEnabled;
@property (nonatomic, getter=isPitchEnabled) BOOL pitchEnabled;

@property (nonatomic) NSUInteger debugMask;

@end

NS_ASSUME_NONNULL_END
