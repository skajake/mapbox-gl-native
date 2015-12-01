#import "MGLAnnotationImage.h"

@interface MGLAnnotationImage ()

#if TARGET_OS_IPHONE
@property (nonatomic) UIImage *image;
#else
@property (nonatomic) NSImage *image;
#endif
@property (nonatomic) NSString *reuseIdentifier;

@end

@implementation MGLAnnotationImage

#if TARGET_OS_IPHONE
+ (instancetype)annotationImageWithImage:(UIImage *)image reuseIdentifier:(NSString *)reuseIdentifier
#else
+ (instancetype)annotationImageWithImage:(NSImage *)image reuseIdentifier:(NSString *)reuseIdentifier
#endif
{
    return [[self alloc] initWithImage:image reuseIdentifier:reuseIdentifier];
}

#if TARGET_OS_IPHONE
- (instancetype)initWithImage:(UIImage *)image reuseIdentifier:(NSString *)reuseIdentifier
#else
- (instancetype)initWithImage:(NSImage *)image reuseIdentifier:(NSString *)reuseIdentifier
#endif
{
    self = [super init];

    if (self)
    {
        _image = image;
        _reuseIdentifier = [reuseIdentifier copy];
#if TARGET_OS_IPHONE
        _enabled = YES;
#else
        _selectable = YES;
#endif
    }

    return self;
}

@end
