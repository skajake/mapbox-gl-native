#import <Foundation/Foundation.h>

#import "MGLTypes.h"

NS_ASSUME_NONNULL_BEGIN

@class MGLMapView;
@class MGLAnnotationImage;
@class MGLPolygon;
@class MGLPolyline;
@class MGLShape;

@protocol MGLMapViewDelegate <NSObject>

@optional

- (void)mapView:(MGLMapView *)mapView regionWillChangeAnimated:(BOOL)animated;
- (void)mapViewRegionIsChanging:(MGLMapView *)mapView;
- (void)mapView:(MGLMapView *)mapView regionDidChangeAnimated:(BOOL)animated;

- (void)mapViewWillStartLoadingMap:(MGLMapView *)mapView;
- (void)mapViewDidFinishLoadingMap:(MGLMapView *)mapView;

- (nullable MGLAnnotationImage *)mapView:(MGLMapView *)mapView imageForAnnotation:(id <MGLAnnotation>)annotation;
- (CGFloat)mapView:(MGLMapView *)mapView alphaForShapeAnnotation:(MGLShape *)annotation;
- (NSColor *)mapView:(MGLMapView *)mapView strokeColorForShapeAnnotation:(MGLShape *)annotation;
- (NSColor *)mapView:(MGLMapView *)mapView fillColorForPolygonAnnotation:(MGLPolygon *)annotation;
- (CGFloat)mapView:(MGLMapView *)mapView lineWidthForPolylineAnnotation:(MGLPolyline *)annotation;

@end

NS_ASSUME_NONNULL_END
