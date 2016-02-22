
#ifdef __OBJC__
#import <Foundation/Foundation.h>

mud_object_t * initMudScriptWithNSObject(mud_gc_stack_t * stack, NSObject * ns_object);
mud_object_t * initMudObjectWithNSObject(mud_gc_stack_t * stack, id ns_object);
id nsWithMudObject(mud_object_t * object);
NSArray * nsArrayWithMudList(mud_list_t * list);
NSArray * nsArrayWithMudExpr(mud_expr_t * expr);
NSArray * nsArrayWithMudExprs(mud_exprs_t * exprs);
NSDictionary * nsDictionaryWithMudHashTable(mud_hash_table_t * hash_table);
NSDate * nsDateWithMudDate(mud_date_t * date);

mud_object_t * _initMudExprWithNSArray(mud_gc_stack_t * stack, NSArray * expr);
mud_object_t * _initMudExprsWithNSArray(mud_gc_stack_t * stack, NSArray * ns_exprs);
mud_object_t * _initMudStringWithNSString(mud_gc_stack_t * stack, NSString * ns_str);
mud_object_t * _initMudListWithNSArray(mud_gc_stack_t * stack, NSArray * ns_array);
mud_object_t * _initMudHashTableWithNSDictionary(mud_gc_stack_t * stack, NSDictionary * ns_dict);
mud_object_t * _initMudDateWithNSDate(mud_gc_stack_t * stack, NSDate * ns_date);
#endif

void MudErrorToNSLog(char * formatString, ...);
void MudWarningToNSLog(char * formatString, ...);
void MudInfoToNSLog(char * formatString, ...);

#define mud_error(...)    MudErrorToNSLog(__VA_ARGS__)
#define mud_warning(...)  MudWarningToNSLog(__VA_ARGS__)
#define mud_info(...)  MudInfoToNSLog(__VA_ARGS__)
