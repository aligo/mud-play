#import "support.m"

int main() {

  NSLog(@"(==, 1, 1) should be: 1 == %@", nsMudTestEvaluate(@[@290, @1, @1]));
  NSLog(@"(==, 1, 0) should be: 0 == %@", nsMudTestEvaluate(@[@290, @1, @0]));

  NSLog(@"(==, 1.1, 1.1) should be: 1 == %@", nsMudTestEvaluate(@[@290, @1.1, @1.1]));
  NSLog(@"(==, 1.1, 2.1) should be: 0 == %@", nsMudTestEvaluate(@[@290, @1.1, @2.1]));

  NSLog(@"(==, 'same', 'same') should be: 1 == %@", nsMudTestEvaluate(@[@290, @"same", @"same"]));
  NSLog(@"(==, 'same', 'diff') should be: 0 == %@", nsMudTestEvaluate(@[@290, @"same", @"diff"]));

  NSLog(@"ok");
}