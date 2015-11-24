#import "MGLAccountManager_Private.h"

#import "MGLMapView.h"

#import "NSString+MGLAdditions.h"

@interface MGLAccountManager ()

@property (atomic) NSString *accessToken;

@end

@implementation MGLAccountManager

#pragma mark - Internal

+ (void)load {
    [MGLMapView restorableStateKeyPaths];
    
    // Read the initial configuration from Info.plist.
    NSString *accessToken = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"MGLMapboxAccessToken"];
    if (accessToken.length) {
        self.accessToken = accessToken;
    }
}

// Can be called from any thread.
//
+ (instancetype)sharedManager {
    mgl_linkStringCategory();
    
    static dispatch_once_t onceToken;
    static MGLAccountManager *_sharedManager;
    void (^setupBlock)() = ^{
        dispatch_once(&onceToken, ^{
            _sharedManager = [[self alloc] init];
        });
    };
    if (![[NSThread currentThread] isMainThread]) {
        dispatch_sync(dispatch_get_main_queue(), ^{
            setupBlock();
        });
    }
    else {
        setupBlock();
    }
    return _sharedManager;
}

+ (void)setAccessToken:(NSString *)accessToken {
    accessToken = [accessToken stringByTrimmingCharactersInSet:
                   [NSCharacterSet whitespaceAndNewlineCharacterSet]];
    if (![accessToken length]) return;
    
    [MGLAccountManager sharedManager].accessToken = accessToken;
}

+ (NSString *)accessToken {
    return [MGLAccountManager sharedManager].accessToken;
}

@end
