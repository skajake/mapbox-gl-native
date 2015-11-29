{
  'targets': [
    { 'target_name': 'platform-osx',
      'product_name': 'mbgl-platform-osx',
      'type': 'static_library',
      'standalone_static_library': 1,
      'hard_dependency': 1,
      'dependencies': [
        'version',
      ],

      'sources': [
        '../platform/darwin/log_nslog.mm',
        '../platform/darwin/string_nsstring.mm',
        '../platform/darwin/application_root.mm',
        '../platform/darwin/asset_root.mm',
        '../platform/darwin/image.mm',
        '../platform/darwin/nsthread.mm',
        '../platform/darwin/reachability.m',
        '../platform/darwin/NSException+MGLAdditions.h',
        '../platform/darwin/NSString+MGLAdditions.h',
        '../platform/darwin/NSString+MGLAdditions.m',
        '../include/mbgl/darwin/MGLTypes.h',
        '../platform/darwin/MGLTypes.m',
        '../include/mbgl/darwin/MGLStyle.h',
        '../platform/darwin/MGLStyle.mm',
        '../include/mbgl/darwin/MGLGeometry.h',
        '../platform/darwin/MGLGeometry.m',
        '../include/mbgl/darwin/MGLAnnotation.h',
        '../include/mbgl/darwin/MGLShape.h',
        '../platform/darwin/MGLShape.m',
        '../include/mbgl/darwin/MGLMultiPoint.h',
        '../platform/darwin/MGLMultiPoint_Private.h',
        '../platform/darwin/MGLMultiPoint.mm',
        '../include/mbgl/darwin/MGLOverlay.h',
        '../include/mbgl/darwin/MGLPointAnnotation.h',
        '../platform/darwin/MGLPointAnnotation.m',
        '../include/mbgl/darwin/MGLPolyline.h',
        '../platform/darwin/MGLPolyline.mm',
        '../include/mbgl/darwin/MGLPolygon.h',
        '../platform/darwin/MGLPolygon.mm',
        '../include/mbgl/osx/Mapbox.h',
        '../include/mbgl/osx/MGLAccountManager.h',
        '../platform/osx/MGLAccountManager_Private.h',
        '../platform/osx/MGLAccountManager.m',
        '../include/mbgl/osx/MGLMapView.h',
        '../platform/osx/MGLMapView_Private.h',
        '../platform/osx/MGLMapView.mm',
        '../include/mbgl/osx/MGLMapViewDelegate.h',
        '../platform/osx/MGLOpenGLLayer.h',
        '../platform/osx/MGLOpenGLLayer.mm',
        '../include/mbgl/osx/MGLAnnotationImage.h',
        '../platform/osx/MGLAnnotationImage.m',
        '../platform/osx/NSBundle+MGLAdditions.h',
        '../platform/osx/NSBundle+MGLAdditions.m',
        '../platform/osx/resources/',
      ],

      'variables': {
        'cflags_cc': [
          '<@(libuv_cflags)',
          '<@(boost_cflags)',
          '<@(variant_cflags)',
        ],
        'libraries': [
          '<@(libuv_static_libs)',
        ],
        'ldflags': [
          '-framework Cocoa',
          '-framework CoreLocation',
          '-framework OpenGL',
          '-framework QuartzCore',
          '-framework SystemConfiguration',
        ],
      },

      'include_dirs': [
        '../include/mbgl/osx',
        '../include/mbgl/darwin',
        '../include',
      ],

      'xcode_settings': {
        'OTHER_CPLUSPLUSFLAGS': [ '<@(cflags_cc)' ],
        'CLANG_ENABLE_OBJC_ARC': 'YES',
        'CLANG_ENABLE_MODULES': 'YES',
      },

      'link_settings': {
        'libraries': [ '<@(libraries)' ],
        'xcode_settings': {
          'OTHER_LDFLAGS': [ '<@(ldflags)' ],
        },
      },

      'direct_dependent_settings': {
        'include_dirs': [
          '../include/mbgl/osx',
          '../include/mbgl/darwin',
          '../include',
        ],
        'mac_bundle_resources': [
          '<!@(find ../platform/osx/resources -type f \! -name "README")',
        ],
      },
    },
  ],
}
