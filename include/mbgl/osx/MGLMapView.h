#import <Cocoa/Cocoa.h>
#import <CoreLocation/CoreLocation.h>

#import "MGLGeometry.h"

NS_ASSUME_NONNULL_BEGIN

/** Options for enabling debugging features in an MGLMapView instance. */
typedef NS_OPTIONS(NSUInteger, MGLMapDebugMaskOptions) {
    /** Edges of tile boundaries are shown as thick, red lines to help diagnose
        tile clipping issues. */
    MGLMapDebugTileBoundariesMask = 1 << 1,
    
    /** Each tile shows its tile coordinate (x/y/z) in the upper-left corner. */
    MGLMapDebugTileInfoMask = 1 << 2,
    
    /** Each tile shows a timestamp indicating when it was loaded. */
    MGLMapDebugTimestampsMask = 1 << 3,
    
    /** Edges of glyphs and symbols are shown as faint, green lines to help
        diagnose collision and label placement issues. */
    MGLMapDebugCollisionBoxesMask = 1 << 4,
};

@class MGLAnnotationImage;

@protocol MGLAnnotation;
@protocol MGLMapViewDelegate;
@protocol MGLOverlay;

/** An interactive, customizable map view with an interface similar to the one
    provided by Apple’s MapKit.
 
    Using MGLMapView, you can embed the map inside the view, allow users to
    manipulate it with standard gestures, animate the map between different
    viewpoints, and present information in the form of annotations and overlays.
    
    The map view loads scalable vector tiles that conform to the
    [Mapbox Vector Tile Specification](https://github.com/mapbox/vector-tile-spec).
    It styles them with a style that conforms to the
    [Mapbox GL style specification](https://www.mapbox.com/mapbox-gl-style-spec/).
    Such styles can be designed in [Mapbox Studio](https://www.mapbox.com/studio/)
    and hosted on mapbox.com.
    
    A collection of Mapbox-hosted styles is available through the MGLStyle
    class. These basic styles use
    [Mapbox Streets](https://www.mapbox.com/developers/vector-tiles/mapbox-streets)
    or [Mapbox Satellite](https://www.mapbox.com/satellite/) data sources, but
    you can specify a custom style that makes use of your own data.
    
    Mapbox-hosted vector tiles and styles require an API access token, which you
    can obtain from the
    [Mapbox account page](https://www.mapbox.com/studio/account/tokens/). Access
    tokens help to deter other developers from hotlinking your styles.
    
    @note You are responsible for getting permission to use the map data and for
        ensuring that your use adheres to the relevant terms of use. */
IB_DESIGNABLE
@interface MGLMapView : NSView

#pragma mark Creating Instances
/** @name Creating Instances */

/** Initializes and returns a newly allocated map view with the specified frame
    and the default style.
 
    @param frame The frame for the view, measured in points.
    @return An initialized map view. */
- (instancetype)initWithFrame:(CGRect)frame;

/** Initializes and returns a newly allocated map view with the specified frame
    and style URL.
 
    @param frame The frame for the view, measured in points.
    @param styleURL URL of the map style to display. The URL may be a full HTTP
        or HTTPS URL, a Mapbox URL indicating the style’s map ID
        (`mapbox://styles/<user>/<style>`), or a path to a local file relative
        to the application’s resource path. Specify `nil` for the default style.
    @return An initialized map view. */
- (instancetype)initWithFrame:(CGRect)frame styleURL:(nullable NSURL *)styleURL;

#pragma mark Accessing the Delegate
/** @name Accessing the Delegate */

/** The receiver’s delegate.
    
    A map view sends messages to its delegate to notify it of changes to its
    contents or the viewpoint. The delegate also provides information about
    annotations displayed on the map, such as the styles to apply to individual
    annotations. */
@property (nonatomic, weak, nullable) IBOutlet id <MGLMapViewDelegate> delegate;

#pragma mark Configuring the Map’s Appearance
/** @name Configuring the Map’s Appearance */


/** URL of the style currently displayed in the receiver.
 
    The URL may be a full HTTP or HTTPS URL, a Mapbox URL indicating the style’s
    map ID (`mapbox://styles/<user>/<style>`), or a path to a local file
    relative to the application’s resource path.
 
    If you set this property to `nil`, the receiver will use the default style
    and this property will automatically be set to that style’s URL. */
@property (nonatomic, null_resettable) NSURL *styleURL;

/** Reloads the style.
 
    You do not normally need to call this method. The map view automatically
    responds to changes in network connectivity by reloading the style. You may
    need to call this method if you change the access token after a style has
    loaded but before loading a style associated with a different Mapbox
    account. */
- (IBAction)reloadStyle:(id)sender;

/** A control for zooming in and out, positioned in the lower-right corner. */
@property (nonatomic, readonly) NSSegmentedControl *zoomControls;

/** A control indicating the map’s direction and allowing the user to manipulate
    the direction, positioned above the zoom controls in the lower-right corner.
 */
@property (nonatomic, readonly) NSSlider *compass;

/** The Mapbox logo, positioned in the lower-left corner.
    
    @note The Mapbox terms of service, which governs the use of Mapbox-hosted
        vector tiles and styles,
        [requires](https://www.mapbox.com/help/mapbox-logo/) most Mapbox
        customers to display the Mapbox logo. If this applies to you, do not
        hide this view or change its contents. */
@property (nonatomic, readonly) NSImageView *logoView;

/** A view showing legally required copyright notices, positioned along the
    bottom of the map view, to the left of the Mapbox logo.
    
    @note The Mapbox terms of service, which governs the use of Mapbox-hosted
        vector tiles and styles,
        [requires](https://www.mapbox.com/help/attribution/) these copyright
        notices to accompany any map that features Mapbox-designed styles,
        OpenStreetMap data, or other Mapbox data such as satellite or terrain
        data. If that applies to this map view, do not hide this view or remove
        any notices from it. */
@property (nonatomic, readonly) NSView *attributionView;

#pragma mark Manipulating the Viewpoint
/** @name Manipulating the Viewpoint */

/** The coordinate at the center of the map view.
    
    Changing the value of this property centers the map on the new coordinate
    without changing the current zoom level.
 
    Changing the value of this property updates the map view immediately. If you
    want to animate the change, use the -setCenterCoordinate:animated: method
    instead. */
@property (nonatomic) CLLocationCoordinate2D centerCoordinate;

/** Changes the center coordinate of the map and optionally animates the change.
    
    Changing the center coordinate centers the map on the new coordinate without
    changing the current zoom level.
    
    @param coordinate The new center coordinate for the map.
    @param animated Specify `YES` if you want the map view to scroll to the new
        location or `NO` if you want the map to display the new location
        immediately. */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;

/** The zoom level of the receiver.
    
    In addition to affecting the visual size and detail of features on the map,
    the zoom level affects the size of the vector tiles that are loaded. At zoom
    level 0, each tile covers the entire world map; at zoom level 1, it covers ¼
    of the world; at zoom level 2, <sup>1</sup>⁄<sub>16</sub> of the world, and
    so on.
    
    Changing the value of this property updates the map view immediately. If you
    want to animate the change, use the -setZoomLevel:animated: method instead.
 */
@property (nonatomic) double zoomLevel;

/** The minimum zoom level that can be displayed by the receiver using the
    current style. */
@property (nonatomic, readonly) double maximumZoomLevel;

/** The maximum zoom level that can be displayed by the receiver using the
    current style. */
@property (nonatomic, readonly) double minimumZoomLevel;

/** Changes the zoom level of the map and optionally animates the change.
    
    Changing the zoom level scales the map without changing the current center
    coordinate.
    
    @param zoomLevel The new zoom level for the map.
    @param animated Specify `YES` if you want the map view to animate the change
        to the new zoom level or `NO` if you want the map to display the new
        zoom level immediately. */
- (void)setZoomLevel:(double)zoomLevel animated:(BOOL)animated;

/** The heading of the map, measured in degrees clockwise from true north.
    
    The value `0` means that the top edge of the map view corresponds to true
    north. The value `90` means the top of the map is pointing due east. The
    value `180` means the top of the map points due south, and so on.
    
    Changing the value of this property updates the map view immediately. If you
    want to animate the change, use the -setDirection:animated: method instead.
 */
@property (nonatomic) CLLocationDirection direction;

/** Changes the heading of the map and optionally animates the change.
    
    @param direction The heading of the map, measured in degrees clockwise from
        true north.
    @param animated Specify `YES` if you want the map view to animate the change
        to the new heading or `NO` if you want the map to display the new
        heading immediately.
    
    Changing the heading rotates the map without changing the current center
    coordinate or zoom level. */
- (void)setDirection:(CLLocationDirection)direction animated:(BOOL)animated;

@property (nonatomic) MGLCoordinateBounds visibleCoordinateBounds;

@property (nonatomic, getter=isScrollEnabled) BOOL scrollEnabled;
@property (nonatomic, getter=isZoomEnabled) BOOL zoomEnabled;
@property (nonatomic, getter=isRotateEnabled) BOOL rotateEnabled;
@property (nonatomic, getter=isPitchEnabled) BOOL pitchEnabled;

@property (nonatomic, readonly, nullable) NS_ARRAY_OF(id <MGLAnnotation>) *annotations;

- (void)addAnnotation:(id <MGLAnnotation>)annotation;
- (void)addAnnotations:(NS_ARRAY_OF(id <MGLAnnotation>) *)annotations;
- (void)removeAnnotation:(id <MGLAnnotation>)annotation;
- (void)removeAnnotations:(NS_ARRAY_OF(id <MGLAnnotation>) *)annotations;

- (nullable MGLAnnotationImage *)dequeueReusableAnnotationImageWithIdentifier:(NSString *)identifier;

@property (nonatomic, copy) NS_ARRAY_OF(id <MGLAnnotation>) *selectedAnnotations;

- (void)selectAnnotation:(id <MGLAnnotation>)annotation animated:(BOOL)animated;
- (void)deselectAnnotation:(id <MGLAnnotation>)annotation animated:(BOOL)animated;

- (id <MGLAnnotation>)annotationAtPoint:(NSPoint)point;

- (void)addOverlay:(id <MGLOverlay>)overlay;
- (void)addOverlays:(NS_ARRAY_OF(id <MGLOverlay>) *)overlays;
- (void)removeOverlay:(id <MGLOverlay>)overlay;
- (void)removeOverlays:(NS_ARRAY_OF(id <MGLOverlay>) *)overlays;

- (CLLocationCoordinate2D)convertPoint:(NSPoint)point toCoordinateFromView:(nullable NSView *)view;
- (NSPoint)convertCoordinate:(CLLocationCoordinate2D)coordinate toPointToView:(nullable NSView *)view;
- (MGLCoordinateBounds)convertRectToCoordinateBounds:(NSRect)rect;
- (CLLocationDistance)metersPerPointAtLatitude:(CLLocationDegrees)latitude;

@property (nonatomic) MGLMapDebugMaskOptions debugMask;

@end

NS_ASSUME_NONNULL_END
