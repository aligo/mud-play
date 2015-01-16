#import "support.m"

int main() {

  NSLog(@"(==, 1, 1) should be: 1 == %@", nsMudTestEvaluate(@[@290, @1, @1]));
  NSLog(@"(==, 1, 0) should be: 0 == %@", nsMudTestEvaluate(@[@290, @1, @0]));

  NSLog(@"(==, 1.1, 1.1) should be: 1 == %@", nsMudTestEvaluate(@[@290, @1.1, @1.1]));
  NSLog(@"(==, 1.1, 2.1) should be: 0 == %@", nsMudTestEvaluate(@[@290, @1.1, @2.1]));

  NSLog(@"(==, 'same', 'same') should be: 1 == %@", nsMudTestEvaluate(@[@290, @"same", @"same"]));
  NSLog(@"(==, 'same', 'diff') should be: 0 == %@", nsMudTestEvaluate(@[@290, @"same", @"diff"]));

  NSLog(@"(!=, 1, 1) should be: 0 == %@", nsMudTestEvaluate(@[@291, @1, @1]));

  NSLog(@"(>, 2, 1) should be: 1 == %@", nsMudTestEvaluate(@[@292, @2, @1]));
  NSLog(@"(>, 2.1, 3) should be: 0 == %@", nsMudTestEvaluate(@[@292, @2.1, @3]));

  NSLog(@"(<, 3.2, 1) should be: 0 == %@", nsMudTestEvaluate(@[@293, @3.2, @1]));
  NSLog(@"(<, 0, 3) should be: 1 == %@", nsMudTestEvaluate(@[@293, @0, @3]));

  NSLog(@"(>=, 20, 20) should be: 1 == %@", nsMudTestEvaluate(@[@294, @20, @20]));
  NSLog(@"(>=, 3.0, 2.9) should be: 1 == %@", nsMudTestEvaluate(@[@294, @3.0, @2.9]));

  NSLog(@"(<=, 20, 20) should be: 1 == %@", nsMudTestEvaluate(@[@295, @20, @20]));
  NSLog(@"(<=, 3.0, 2.9) should be: 0 == %@", nsMudTestEvaluate(@[@295, @3.0, @2.9]));

  NSLog(@"ok");
}