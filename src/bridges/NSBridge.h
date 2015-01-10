#import <Foundation/Foundation.h>

typedef NSDecimal mud_number_t;

void MudErrorToNSLog(NSString * formatString, ...);

void MudWarningToNSLog(NSString * formatString, ...);

#define mud_error(...)    MudErrorToNSLog(__VA_ARGS__)

#define mud_warning(...)  MudErrorToNSWarning(__VA_ARGS__)

#import "../mud.h"

mud_object_t * initMudObjectWithNSObject(NSObject * ns_object);