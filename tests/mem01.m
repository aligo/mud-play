#import "support.m"

int main() {
  NSArray * ns01 = @[
                      @[ @2015.0111, @"expr1"],
                      @[ @[ @2015, @"expr2"], @"expr3"]
                    ];
  mud_object_t * test01;

  int ft = 1000;
  int t = ft;
  while ( t <= ( 1024 * ft ) ) {
    NSLog(@"%d units", t);
    reportMemory();
    @autoreleasepool {
      for (int i = 0; i < t; i++ ) {
        mud_gc_stack_start();
        test01 = _initMudExprsWithNSArray(ns01);
        mud_gc_stack_finish();
      }
    }
    reportMemory();
    t *= 2;
  }
}