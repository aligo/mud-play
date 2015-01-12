#import <Foundation/Foundation.h>
#import "_operators.h"
#import "../../mud_objects.h"

void MudErrorToNSLog(NSString * formatString, ...);

void MudWarningToNSLog(NSString * formatString, ...);

#define mud_error(...)    MudErrorToNSLog(__VA_ARGS__)

#define mud_warning(...)  MudErrorToNSWarning(__VA_ARGS__)

mud_object_t * initMudObjectWithNSObject(NSObject * ns_object);

mud_object_t * _initMudExprWithNSArray(NSArray * expr);
mud_object_t * _initMudExprsWithNSArray(NSArray * ns_exprs);

void mud_object_bridge_free(mud_object_t * object);