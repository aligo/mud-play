#import "support.h"

int main() {

  NSArray * ns_expr1 = @[@300, @"He", @"llo", @" ", @"World", @"!", @"你好世界"];

  mud_gc_stack_t * stack1 = mud_gc_stack_init();

  mud_object_t * mud_exprs = _initMudExprWithNSArray(stack1, ns_expr1);

  // NSArray * ns_expr2 = @[@301,  @"%s %s %lf 你好", @"PI", @"is", @3.1415926535];
  // mud_object_t * mud_exprs = initMudObjectWithNSObject(@[ns_expr1, ns_expr2]);

  int ft = 1000;
  int t = ft;
  while ( t <= ( 1024 * ft ) ) {
    NSLog(@"%d units", t);
    reportMemory();
    mud_scope_t * scope = mud_scope_init();
    for (int i = 0; i < t; i++ ) {
      mud_gc_stack_t * stack2 = mud_gc_stack_init();
      mud_evaluate(mud_exprs, scope, stack2);
      mud_gc_stack_free(stack2);
    }
    mud_scope_free(scope);
    reportMemory();
    t *= 2;
  }

  mud_gc_stack_free(stack1);
}