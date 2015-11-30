#import "MGLAttributionButton.h"

@implementation MGLAttributionButton {
    NSTrackingRectTag _trackingAreaTag;
}

- (instancetype)initWithTitle:(NSString *)title URL:(NSURL *)url {
    if (self = [super initWithFrame:NSZeroRect]) {
        self.bordered = NO;
        self.bezelStyle = NSRegularSquareBezelStyle;
        
        NSMutableAttributedString *attributedTitle = [[NSMutableAttributedString alloc] initWithString:@"© "
                                                                                            attributes:@{
            NSFontAttributeName: [NSFont systemFontOfSize:[NSFont systemFontSizeForControlSize:NSMiniControlSize]],
        }];
        [attributedTitle appendAttributedString:
         [[NSAttributedString alloc] initWithString:title
                                         attributes:@{
            NSFontAttributeName: [NSFont systemFontOfSize:[NSFont systemFontSizeForControlSize:NSMiniControlSize]],
            NSUnderlineStyleAttributeName: @(NSUnderlineStyleSingle),
        }]];
        self.attributedTitle = attributedTitle;
        [self sizeToFit];
        
        _URL = url;
        self.toolTip = _URL.absoluteString;
        
        self.target = self;
        self.action = @selector(openURL:);
    }
    return self;
}

- (void)viewDidMoveToWindow {
    [self removeTrackingRect:_trackingAreaTag];
    _trackingAreaTag = [self addTrackingRect:self.bounds owner:self userData:NULL assumeInside:NO];
}

- (BOOL)wantsLayer {
    return YES;
}

- (void)mouseEntered:(__unused NSEvent *)event {
    [[NSCursor pointingHandCursor] push];
}

- (void)mouseExited:(__unused NSEvent *)event {
    [[NSCursor pointingHandCursor] pop];
}

- (IBAction)openURL:(__unused id)sender {
    [[NSWorkspace sharedWorkspace] openURL:self.URL];
}

@end
