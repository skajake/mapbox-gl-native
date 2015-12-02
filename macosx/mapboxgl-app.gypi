{
  'includes': [
    '../gyp/common.gypi',
  ],
  'targets': [
    {
      'target_name': 'osxsdk',
      'product_name': 'Mapbox',
      'type': 'shared_library',
      'mac_bundle': 1,
      
      'dependencies': [
        'mbgl.gyp:core',
        'mbgl.gyp:platform-<(platform_lib)',
        'mbgl.gyp:http-<(http_lib)',
        'mbgl.gyp:asset-<(asset_lib)',
        'mbgl.gyp:cache-<(cache_lib)',
      ],

      'xcode_settings': {
        'SDKROOT': 'macosx',
        'SUPPORTED_PLATFORMS':'macosx',
        'OTHER_LDFLAGS': [ '-stdlib=libc++', '-lstdc++' ],
        'INSTALL_PATH': '@executable_path/../Frameworks',
        'INFOPLIST_FILE': '../macosx/framework/Info.plist',
        'CLANG_ENABLE_OBJC_ARC': 'YES',
        'PRODUCT_BUNDLE_IDENTIFIER': 'com.mapbox.MapboxGL',
      },
      
      'mac_framework_headers': [
        'framework/Mapbox.h',
        '<!@(find ../include/mbgl/{darwin,osx} -type f \! -name \'.*\')',
      ],
      
      'sources': [
        'framework/Mapbox.h',
        'framework/Mapbox.m',
      ],
      
      'direct_dependent_settings': {
        'libraries': [
          '$(SDKROOT)/System/Library/Frameworks/Cocoa.framework',
          '$(SDKROOT)/System/Library/Frameworks/CoreLocation.framework',
        ],
      },
    },
    
    {
      'target_name': 'osxapp',
      'product_name': 'Mapbox GL',
      'type': 'executable',
      'product_extension': 'app',
      'mac_bundle': 1,
      'mac_bundle_resources': [
        'Credits.rtf',
        'Icon.icns',
        'MainMenu.xib',
      ],

      'dependencies': [
        'osxsdk',
      ],

      'sources': [
        './AppDelegate.h',
        './AppDelegate.m',
        './DroppedPinAnnotation.h',
        './DroppedPinAnnotation.m',
        './LocationCoordinate2DTransformer.h',
        './LocationCoordinate2DTransformer.m',
        './TimeIntervalTransformer.h',
        './TimeIntervalTransformer.m',
        './NSValue+Additions.h',
        './NSValue+Additions.m',
        './main.m',
      ],

      'xcode_settings': {
        'SDKROOT': 'macosx',
        'SUPPORTED_PLATFORMS':'macosx',
        'INFOPLIST_FILE': '../macosx/Info.plist',
        'CLANG_ENABLE_OBJC_ARC': 'YES',
        'PRODUCT_BUNDLE_IDENTIFIER': 'com.mapbox.MapboxGL',
      },
    },
  ]
}
