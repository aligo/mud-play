#import "support.h"

int main() {

  // [sget, 'unknown']
  NSLog(@"t01e should be: null == %@", nsMudTestEvaluate(@[@120, @"unknown"]));

  // [[sset, 'hello', 'Hello World'], [sget, 'hello']
  NSLog(@"t02e should be: Hello World == %@", nsMudTestEvaluate(@[@[@121, @"hello", @"Hello World"], @[@120, @"hello"]]));

  NSLog(@"ok");
}