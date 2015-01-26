#import "support.h"

int main() {

  NSLog(@"(sget, 'unknown') should be: null == %@", nsMudTestEvaluate(@[@120, @"unknown"]));

  NSLog(@"((sset, 'hello', 'Hello World'), (sget, 'hello')) should be: Hello World == %@", nsMudTestEvaluate(@[@[@121, @"hello", @"Hello World"], @[@120, @"hello"]]));

  NSLog(@"(apply, (lambda, (+, 1, 1, (sarg, 0))), 2) should be: 4 == %@", nsMudTestEvaluate(@[@131, @[@130, @[@200, @1, @1, @[@122, @0]]], @2]));

  NSLog(@"(apply, (lambda, (+, 1, 1, (sargc))), 0, 0) should be: 4 == %@", nsMudTestEvaluate(@[@131, @[@130, @[@200, @1, @1, @[@123]]], @0, @0]));

  NSLog(@"ok");
}