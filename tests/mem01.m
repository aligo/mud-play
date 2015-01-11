#import <Foundation/Foundation.h>


#import "../src/bridges/NSBridge.h"
#import "../src/mud.c"
#import "../src/bridges/NSBridge.m"

#import "support.m"

int main() {
  NSArray * ns01 = @[
                      @[ @2015.0111, @"expr1"],
                      @[ @[ @2015.0111, @"expr2"], @"expr3"]
                    ];
  mud_object_t * test01;

  int t = 10;
  while ( t <= 1000000 ) {
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
    t *= 10;
  }
}