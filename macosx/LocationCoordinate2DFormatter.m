#import "LocationCoordinate2DFormatter.h"

#import "NSValue+Additions.h"

NSString *StringFromDegrees(CLLocationDegrees degrees, char positiveDirection, char negativeDirection) {
    double minutes = (degrees - floor(degrees)) / 60;
    double seconds = (minutes - floor(minutes)) / 60;
    
    NSMutableString *string = [NSMutableString stringWithFormat:@"%.0f°", fabs(degrees)];
    if (floor(minutes) || floor(seconds)) {
        [string appendFormat:@"%.0f′", minutes];
    }
    if (floor(seconds)) {
        [string appendFormat:@"%.0f″", seconds];
    }
    if (degrees) {
        [string appendFormat:@"%c", degrees > 0 ? positiveDirection : negativeDirection];
    }
    return string;
}

@implementation LocationCoordinate2DFormatter

- (NSString *)stringForObjectValue:(id)obj {
    if (![obj isKindOfClass:[NSValue class]]) {
        return nil;
    }
    CLLocationCoordinate2D coordinate = [obj CLLocationCoordinate2DValue];
    return [NSString stringWithFormat:@"%@, %@",
            StringFromDegrees(coordinate.latitude, 'N', 'S'),
            StringFromDegrees(coordinate.longitude, 'E', 'W')];
}

- (BOOL)getObjectValue:(out id _Nullable __autoreleasing *)obj forString:(NSString *)string errorDescription:(out NSString *__autoreleasing _Nullable *)error {
    NSAssert(NO, @"Not implemented.");
}

@end
