
#ifdef __OBJC__
#import <Foundation/Foundation.h>

mud_object_t * initMudObjectWithNSObject(NSObject * ns_object);
NSObject * nsWithMudObject(mud_object_t * object);
NSArray * nsArrayWithMudList(mud_list_t * list);
NSDictionary * nsDictionaryWithMudHashTable(mud_hash_table_t * hash_table);
NSDate * nsDateWithMudDate(mud_date_t * date);

mud_object_t * _initMudExprWithNSArray(NSArray * expr);
mud_object_t * _initMudExprsWithNSArray(NSArray * ns_exprs);
mud_object_t * _initMudHashTableWithNSDictionary(NSDictionary * ns_dict);
mud_object_t * _initMudDateWithNSDate(NSDate * ns_date);
#endif

void MudErrorToNSLog(char * formatString, ...);
void MudWarningToNSLog(char * formatString, ...);
void MudInfoToNSLog(char * formatString, ...);

#define mud_error(...)    MudErrorToNSLog(__VA_ARGS__)
#define mud_warning(...)  MudWarningToNSLog(__VA_ARGS__)
#define mud_info(...)  MudInfoToNSLog(__VA_ARGS__)
