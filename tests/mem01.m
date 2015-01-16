#import "support.h"

int main() {
  NSArray * ns01 = @[
                      @[ @2015.0111, @"expr1"],
                      @[ @[ @2015, @"expr2"], @"expr3"]
                    ];
  mud_object_t * test01;

  int ft = 100;
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

  printf("\n========================\n\n");

  mud_object_t * test02 = mud_string_init("Wow, such leaking and slow!");
  NSObject * ns02;

  t = ft;
  while ( t <= ( 1024 * ft ) ) {
    NSLog(@"%d units", t);
    reportMemory();
    @autoreleasepool {
      for (int i = 0; i < t; i++ ) {
        ns02 = nsWithMudObject(test02);
      }
    }
    reportMemory();
    t *= 2;
  }

  printf("\n========================\n\n");

  mud_object_t * test03 = mud_string_init("Wow, such good!");
  NSObject * ns03;

  t = ft;
  while ( t <= ( 1024 * ft ) ) {
    NSLog(@"%d units", t);
    reportMemory();
    for (int i = 0; i < t; i++ ) {
      @autoreleasepool {
        ns03 = nsWithMudObject(test03);
      }
    }
    reportMemory();
    t *= 2;
  }

}