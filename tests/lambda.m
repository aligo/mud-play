#import "support.h"

int main() {

  NSLog(@"(apply, (lambda, (+, 1, 1))) should be: 2 == %@", nsMudTestEvaluate(@[@131, @[@130, @[@200, @1, @1]]]));

  NSLog(@"should be logged out 'Lambda arguments list is not a list.':");
  NSLog(@"(apply, (lambda, 1, (+, 1, 1))) should be: 2 == %@", nsMudTestEvaluate(@[@131, @[@130, @1, @[@200, @1, @1]]]));


  NSLog(@"(apply, (lambda, [list, 'a'], (+, 1, 1))) should be: 2 == %@", nsMudTestEvaluate(@[@131, @[@130, @[@500, @"a"], @[@200, @1, @1]]]));

  NSLog(@"ok");
}