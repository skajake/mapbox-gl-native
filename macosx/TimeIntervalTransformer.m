#import "TimeIntervalTransformer.h"

#import "NSValue+Additions.h"

@implementation TimeIntervalTransformer

+ (Class)transformedValueClass {
    return [NSString class];
}

+ (BOOL)allowsReverseTransformation {
    return NO;
}

NSString *NumberAndUnitString(double quantity, NSString *singular, NSString *plural) {
    return [NSString stringWithFormat:@"%.0f %@", quantity, quantity == 1 ? singular : plural];
}

- (id)transformedValue:(id)value {
    if (![value isKindOfClass:[NSValue class]]) {
        return nil;
    }
    
    NSTimeInterval timeInterval = [value doubleValue];
    double seconds = timeInterval;
    double minutes = seconds / 60;
    seconds -= trunc(minutes) * 60;
    double hours = minutes / 60;
    minutes -= trunc(hours) * 60;
    double days = hours / 24;
    hours -= trunc(days) * 24;
    double weeks = days / 7;
    days -= trunc(weeks) * 7;
    
    NSMutableArray *components = [NSMutableArray array];
    if (trunc(seconds) || timeInterval < 60) {
        [components addObject:NumberAndUnitString(seconds, @"second", @"seconds")];
    }
    if (trunc(minutes)) {
        [components insertObject:NumberAndUnitString(minutes, @"minute", @"minutes") atIndex:0];
    }
    if (trunc(hours)) {
        [components insertObject:NumberAndUnitString(hours, @"hour", @"hours") atIndex:0];
    }
    if (trunc(days)) {
        [components insertObject:NumberAndUnitString(days, @"day", @"days") atIndex:0];
    }
    if (trunc(weeks)) {
        [components insertObject:NumberAndUnitString(weeks, @"week", @"weeks") atIndex:0];
    }
    
    return [components componentsJoinedByString:@", "];
}

@end
