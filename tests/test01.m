#import <Foundation/Foundation.h>


#import "../src/bridges/NSBridge.h"
#import "../src/mud.c"
#import "../src/bridges/NSBridge.m"

#import "support.m"

int main() {

  // NSDictionary * json = openAndParseJson(@"fixtures/test03.json");

  mud_object_t * object_nil = initMudObjectWithNSObject([NSNull null]);
  NSLog(@"object_nil should be mud_nil: 1 == %d", object_nil->type == MUD_OBJ_TYPE_NIL);
  

  mud_object_t * object_boolean = initMudObjectWithNSObject(@(YES));
  NSLog(@"object_boolean should be mud_boolean: 1 == %d", object_boolean->type == MUD_OBJ_TYPE_BOOLEAN);
  NSLog(@"object_boolean value should be: 1 == %d", *(BOOL *)object_boolean->ptr);

  mud_object_t * object_number = initMudObjectWithNSObject([NSNumber numberWithInt: 100]);
  NSLog(@"object_number should be mud_number: 1 == %d", object_number->type == MUD_OBJ_TYPE_NUMBER);
  NSLog(@"object_number value should be: 100 == %@", NSDecimalString((NSDecimal *)object_number->ptr, nil));
  
  mud_object_t * object_string = initMudObjectWithNSObject(@"hello world! 你好世界！");
  NSLog(@"object_string should be mud_string: 1 == %d", object_string->type == MUD_OBJ_TYPE_STRING);
  NSLog(@"object_string value should be: %@", [NSString stringWithUTF8String: (char *)object_string->ptr]);

  mud_object_t * object_expr1 = initMudExprWithNSArray(@[@2015, @"test", @"test2"]);
  NSLog(@"object_expr1 should be mud_expr: 1 == %d", object_expr1->type == MUD_OBJ_TYPE_EXPR);
  mud_expr_t * expr1 = object_expr1->ptr;
  NSLog(@"object_expr1 operator should be: 2015 == %d", expr1->oper);
  NSLog(@"object_expr1 argument 1 should be: test == %s", (char *)expr1->args[0]->ptr);
  NSLog(@"object_expr1 argument 1 should be: test2 == %s", (char *)expr1->args[1]->ptr);

  mud_object_t * object_expr2 = initMudExprWithNSArray(@[@2014]);
  NSLog(@"object_expr2 should be mud_expr: 1 == %d", object_expr2->type == MUD_OBJ_TYPE_EXPR);
  mud_expr_t * expr2 = object_expr2->ptr;
  NSLog(@"object_expr2 operator should be: 2014 == %d", expr2->oper);

  NSLog(@"ok");
}