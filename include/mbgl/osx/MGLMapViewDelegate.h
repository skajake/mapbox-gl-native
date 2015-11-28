#import <Foundation/Foundation.h>

#import "MGLTypes.h"

NS_ASSUME_NONNULL_BEGIN

@class MGLMapView;

@protocol MGLMapViewDelegate <NSObject>

@optional

- (void)mapView:(MGLMapView *)mapView regionWillChangeAnimated:(BOOL)animated;
- (void)mapViewRegionIsChanging:(MGLMapView *)mapView;
- (void)mapView:(MGLMapView *)mapView regionDidChangeAnimated:(BOOL)animated;

- (void)mapViewWillStartLoadingMap:(MGLMapView *)mapView;
- (void)mapViewDidFinishLoadingMap:(MGLMapView *)mapView;

@end

NS_ASSUME_NONNULL_END
