#import "support.m"

int main() {

  NSArray * ns_expr1 = @[@300, @"He", @"llo", @" ", @"World", @"!", @"你好世界"];
  NSArray * ns_expr2 = @[@301,  @"%s %s %lf 你好", @"PI", @"is", @3.1415926535];
  // mud_object_t * mud_expr = _initMudExprWithNSArray(ns_expr1);

  mud_object_t * mud_exprs = initMudObjectWithNSObject(@[ns_expr1, ns_expr2]);

  int ft = 1000;
  int t = ft;
  while ( t <= ( 1024 * ft ) ) {
    NSLog(@"%d units", t);
    reportMemory();
    for (int i = 0; i < t; i++ ) {
      mud_gc_stack_start();
      mud_evaluate(mud_exprs);
      mud_gc_stack_finish();
    }
    reportMemory();
    t *= 2;
  }
}