#import <Mapbox/Mapbox.h>

#import "../../platform/darwin/NSString+MGLAdditions.h"
#import "../../platform/osx/NSBundle+MGLAdditions.h"
#import "../../platform/osx/NSProcessInfo+MGLAdditions.h"

__attribute__((constructor))
static void InitializeMapbox() {
    static int initialized = 0;
    if (initialized) {
        return;
    }
    
    mgl_linkBundleCategory();
    mgl_linkStringCategory();
    mgl_linkProcessInfoCategory();
    
    [MGLAccountManager class];
    [MGLAnnotationImage class];
    [MGLMapView class];
    [MGLMultiPoint class];
    [MGLPointAnnotation class];
    [MGLPolygon class];
    [MGLPolyline class];
    [MGLShape class];
    [MGLStyle class];
}
