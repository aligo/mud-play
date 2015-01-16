#import "support.m"

int main() {

  NSLog(@"(if, true, 2, 3) should be: 2 == %@", nsMudTestEvaluate(@[@111, @YES, @2, @3]));
  NSLog(@"(if, false, 2, 3) should be: 3 == %@", nsMudTestEvaluate(@[@111, @NO, @2, @3]));


  NSLog(@"should be logged out Unknown operator 404:");
  NSLog(@"(if, true, (unknown-404), 1) should be: 0 == %@", nsMudTestEvaluate(@[@111, @YES, @[@404], @1]));
  NSLog(@"(if, true, 1, (unknown-404)) should be: 1 == %@", nsMudTestEvaluate(@[@111, @YES, @1, @[@404]]));

  NSLog(@"should be logged out Unknown operator 404:");
  NSLog(@"(if, false, 1, (unknown-404)) should be: 0 == %@", nsMudTestEvaluate(@[@111, @NO, @1, @[@404]]));
  NSLog(@"(if, false, (unknown-404), 1) should be: 1 == %@", nsMudTestEvaluate(@[@111, @NO, @[@404], @1]));

  NSLog(@"(when, true, 2, 3) should be: 2 == %@", nsMudTestEvaluate(@[@112, @YES, @2, @3]));
  NSLog(@"(when, false, 2, 3) should be: 3 == %@", nsMudTestEvaluate(@[@112, @NO, @2, @3]));

  NSLog(@"(unless, true, 2, 3) should be: 3 == %@", nsMudTestEvaluate(@[@113, @YES, @2, @3]));
  NSLog(@"(unless, false, 2, 3) should be: 2 == %@", nsMudTestEvaluate(@[@113, @NO, @2, @3]));

  NSLog(@"ok");
}