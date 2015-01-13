#import "support.m"

int main() {
  NSArray * ns_expr = @[@300, @"He", @"llo", @" ", @"World", @"! ", @2014, @"-", @3.1415926535, @" ", @"你好世界"];
  mud_object_t * mud_expr = _initMudExprWithNSArray(ns_expr);

  mud_object_t * mud_ret = _mud_expr_evaluate(mud_expr->ptr);
  NSLog(@"mud_ret should be mud_string: 1 == %d", mud_ret->type == MUD_OBJ_TYPE_STRING);
  NSLog(@"mud_ret value should be: %@", [NSString stringWithUTF8String: (char *)mud_ret->ptr]);

  mud_ret = mud_evaluate(mud_expr);
  NSLog(@"mud_ret should be mud_string: 1 == %d", mud_ret->type == MUD_OBJ_TYPE_STRING);
  NSLog(@"mud_ret value should be: %@", [NSString stringWithUTF8String: (char *)mud_ret->ptr]);
}