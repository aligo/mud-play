#import "support.m"

int main() {

  NSArray * ns_expr = @[@300, @"He", @"llo", @" ", @"World", @"!", @"你好世界"];
  mud_object_t * mud_expr = _initMudExprWithNSArray(ns_expr);
  
  int ft = 1000;
  int t = ft;
  while ( t <= ( 1024 * ft ) ) {
    NSLog(@"%d units", t);
    reportMemory();
    @autoreleasepool {
      for (int i = 0; i < t; i++ ) {
        mud_gc_stack_start();
        _mud_expr_evaluate(mud_expr->ptr);
        mud_gc_stack_finish();
      }
    }
    reportMemory();
    t *= 2;
  }
}