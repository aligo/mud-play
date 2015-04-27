#import "support.h"

int main() {
  mud_gc_stack_t * stack = mud_gc_stack_init();

  mud_scope_t * scope = mud_scope_init();

  NSArray * ns_expr = @[@300, @"He", @"llo", @" ", @"World", @"! ", @2014, @"-", @3.1415926535, @" ", @"你好世界"];
  mud_object_t * mud_expr = _initMudExprWithNSArray(stack, ns_expr);

  mud_object_t * mud_ret = _mud_expr_evaluate(mud_expr->ptr, scope, stack);
  NSLog(@"mud_ret should be mud_string: 1 == %d", mud_ret->type == MUD_OBJ_TYPE_STRING);
  NSLog(@"mud_ret value should be: %@", [NSString stringWithUTF8String: (char *)mud_ret->ptr]);

  mud_ret = mud_evaluate(mud_expr, scope, stack);
  NSLog(@"mud_ret should be mud_string: 1 == %d", mud_ret->type == MUD_OBJ_TYPE_STRING);
  NSLog(@"mud_ret value should be: %@", [NSString stringWithUTF8String: (char *)mud_ret->ptr]);
  NSLog(@"mud_ret length should be: %zu == %zu", strlen("Hello World! 2014-3.141593 你好世界"),  strlen((char *)mud_ret->ptr));

  mud_gc_stack_free(stack);
}