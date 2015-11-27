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
        '../include/mbgl/osx/Mapbox.h',
        '../include/mbgl/osx/MGLAccountManager.h',
        '../platform/osx/MGLAccountManager_Private.h',
        '../platform/osx/MGLAccountManager.m',
        '../include/mbgl/osx/MGLMapView.h',
        '../platform/osx/MGLMapView.mm',
        '../include/mbgl/osx/MGLTypes.h',
        '../platform/osx/MGLTypes.m',
        '../include/mbgl/osx/MGLStyle.h',
        '../platform/osx/MGLStyle.mm',
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
          '-framework CoreFoundation',
          '-framework CoreLocation',
          '-framework CoreVideo',
          '-framework GLKit',
          '-framework Foundation',
          '-framework ImageIO',
          '-framework CoreServices',
          '-framework OpenGL',
          '-framework ApplicationServices',
          '-framework SystemConfiguration',
          '-framework QuartzCore',
        ],
      },

      'include_dirs': [
        '../include',
      ],

      'xcode_settings': {
        'OTHER_CPLUSPLUSFLAGS': [ '<@(cflags_cc)' ],
        'CLANG_ENABLE_OBJC_ARC': 'YES',
        'CLANG_ENABLE_MODULES': 'YES',
        'USER_HEADER_SEARCH_PATHS': '../include/mbgl/osx',
      },

      'link_settings': {
        'libraries': [ '<@(libraries)' ],
        'xcode_settings': {
          'OTHER_LDFLAGS': [ '<@(ldflags)' ],
        },
      },

      'direct_dependent_settings': {
        'include_dirs': [
          '../include',
        ],
        'mac_bundle_resources': [
          '<!@(find ../platform/osx/resources -type f \! -name "README")',
        ],
      },
    },
  ],
}
