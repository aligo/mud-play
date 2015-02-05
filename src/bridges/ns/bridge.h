#import <Foundation/Foundation.h>

void MudErrorToNSLog(char * formatString, ...);
void MudWarningToNSLog(char * formatString, ...);
void MudInfoToNSLog(char * formatString, ...);

#define mud_error(...)    MudErrorToNSLog(__VA_ARGS__)
#define mud_warning(...)  MudWarningToNSLog(__VA_ARGS__)
#define mud_info(...)  MudInfoToNSLog(__VA_ARGS__)

#import "_operators.h"
#import "../../mud_objects.h"

mud_object_t * initMudObjectWithNSObject(NSObject * ns_object);
NSObject * nsWithMudObject(mud_object_t * object);
NSArray * nsArrayWithMudList(mud_list_t * list);
NSDictionary * nsDictionaryWithMudHashTable(mud_hash_table_t * hash_table);

#import "../../mud_evaluator.h"
#import "_operators.c"



mud_object_t * _initMudExprWithNSArray(NSArray * expr);
mud_object_t * _initMudExprsWithNSArray(NSArray * ns_exprs);
mud_object_t * _initMudHashTableWithNSDictionary(NSDictionary * ns_dict);

void mud_object_bridge_free(mud_object_t * object);