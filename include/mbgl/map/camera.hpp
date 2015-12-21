#ifndef MBGL_MAP_CAMERA
#define MBGL_MAP_CAMERA

#include <mapbox/optional.hpp>

#include <mbgl/util/geo.hpp>
#include <mbgl/util/chrono.hpp>
#include <mbgl/util/unitbezier.hpp>

#include <functional>

namespace mbgl {

/** Various options for describing the viewpoint of a map, along with parameters
    for transitioning to the viewpoint with animation. All fields are optional;
    the default values of transition options depend on how this struct is used.
 */
struct CameraOptions {
    // Viewpoint options
    
    /** Coordinate at the center of the map. */
    mapbox::util::optional<LatLng> center;
    
    /** Zero-based zoom level. Constrained to the minimum and maximum zoom
        levels. */
    mapbox::util::optional<double> zoom;
    
    /** Bearing, measured in radians counterclockwise from true north. Wrapped
        to [−π rad, π rad). */
    mapbox::util::optional<double> angle;
    
    /** Pitch toward the horizon measured in radians, with 0 rad resulting in a
        two-dimensional map. */
    mapbox::util::optional<double> pitch;
    
    // Transition options
    
    /** Time to animate to the viewpoint defined herein. */
    mapbox::util::optional<Duration> duration;
    
    /** Average velocity of a flyTo() transition, measured in screenfuls per
        second, assuming a linear timing curve.
        
        A <i>screenful</i> is the visible span in pixels. It does not correspond
        to a fixed physical distance but rather varies by zoom level. */
    mapbox::util::optional<double> velocity;
    
    /** Zero-based zoom level at the peak of the flyTo() transition’s flight
        path. */
    mapbox::util::optional<double> minZoom;
    
    /** The easing timing curve of the transition. */
    mapbox::util::optional<mbgl::util::UnitBezier> easing;
    
    /** A function that is called on each frame of the transition, just before a
        screen update, except on the last frame. The first parameter indicates
        the elapsed time as a percentage of the duration. */
    std::function<void(double)> transitionFrameFn;
    
    /** A function that is called once on the last frame of the transition, just
        before the corresponding screen update. */
    std::function<void()> transitionFinishFn;
};

} // namespace mbgl

#endif /* MBGL_MAP_CAMERA */
