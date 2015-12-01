#import <TargetConditionals.h>
#if TARGET_OS_IPHONE
    #import <UIKit/UIKit.h>
#else
    #import <AppKit/AppKit.h>
#endif

#import "MGLTypes.h"

NS_ASSUME_NONNULL_BEGIN

/** The MGLAnnotationImage class is responsible for presenting point-based annotations visually on a map view. Annotation image objects wrap `UIImage` objects and may be recycled later and put into a reuse queue that is maintained by the map view. */
@interface MGLAnnotationImage : NSObject

/** @name Initializing and Preparing the Image Object */

/** Initializes and returns a new annotation image object.
*   @param image The image to be displayed for the annotation.
*   @param reuseIdentifier The string that identifies that this annotation image is reusable.
*   @return The initialized annotation image object or `nil` if there was a problem initializing the object. */
#if TARGET_OS_IPHONE
+ (instancetype)annotationImageWithImage:(UIImage *)image reuseIdentifier:(NSString *)reuseIdentifier;
#else
+ (instancetype)annotationImageWithImage:(NSImage *)image reuseIdentifier:(NSString *)reuseIdentifier;
#endif

/** @name Getting and Setting Attributes */

/** The image to be displayed for the annotation. */
#if TARGET_OS_IPHONE
@property (nonatomic, readonly) UIImage *image;
#else
@property (nonatomic, readonly) NSImage *image;
#endif

/** The string that identifies that this annotation image is reusable. (read-only)
*
*   You specify the reuse identifier when you create the image object. You use this type later to retrieve an annotation image object that was created previously but which is currently unused because its annotation is not on screen.
*
*   If you define distinctly different types of annotations (with distinctly different annotation images to go with them), you can differentiate between the annotation types by specifying different reuse identifiers for each one. */
@property (nonatomic, readonly) NSString *reuseIdentifier;

/** A Boolean value indicating whether the annotation is enabled.
*
*   The default value of this property is `YES`. If the value of this property is `NO`, the annotation image ignores touch events and cannot be selected. */
#if TARGET_OS_IPHONE
@property (nonatomic, getter=isEnabled) BOOL enabled;
#else
@property (nonatomic, getter=isSelectable) BOOL selectable;
#endif

@end

NS_ASSUME_NONNULL_END
