#import <Foundation/Foundation.h>


#import "../src/bridges/NSBridge.h"
#import "../src/mud.c"
#import "../src/bridges/NSBridge.m"

#import "support.m"

int main() {

  // NSDictionary * json = openAndParseJson(@"fixtures/test03.json");

  // NSLog(@"%@", json);

  mud_object_t * object_nil = initMudObjectWithNSObject([NSNull null]);
  NSLog(@"object_nil should be mud_nil: 1 == %d", object_nil->type == MUD_OBJ_TYPE_NIL);
  
  mud_object_t * object_number = initMudObjectWithNSObject([NSNumber numberWithInt: 100]);
  NSLog(@"object_number should be mud_number: 1 == %d", object_number->type == MUD_OBJ_TYPE_NUMBER);
  NSLog(@"object_number value should be: 100 == %@", NSDecimalString((NSDecimal *)object_number->ptr, nil));
  
  mud_object_t * object_string = initMudObjectWithNSObject(@"hello world! 你好世界！");
  NSLog(@"object_string should be mud_string: 1 == %d", object_string->type == MUD_OBJ_TYPE_STRING);
  NSLog(@"object_string value should be: %@", [NSString stringWithUTF8String: (char *)object_string->ptr]);


  NSLog(@"ok");
}