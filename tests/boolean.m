#import "support.m"

int main() {

  NSLog(@"!true should be: 0 == %@", nsMudTestEvaluate(@[@190, @YES]));
  NSLog(@"!false should be: 1 == %@", nsMudTestEvaluate(@[@190, @NO]));

  NSLog(@"!3 should be: 0 == %@", nsMudTestEvaluate(@[@190, @3]));
  NSLog(@"!0 should be: 1 == %@", nsMudTestEvaluate(@[@190, @0]));

  NSLog(@"true && true should be: 1 == %@", nsMudTestEvaluate(@[@191, @YES, @YES]));
  NSLog(@"true && false should be: 0 == %@", nsMudTestEvaluate(@[@191, @YES, @NO]));
  NSLog(@"false && true should be: 0 == %@", nsMudTestEvaluate(@[@191, @NO, @YES]));
  NSLog(@"false && false should be: 0 == %@", nsMudTestEvaluate(@[@191, @NO, @NO]));

  NSLog(@"true || true should be: 1 == %@", nsMudTestEvaluate(@[@192, @YES, @YES]));
  NSLog(@"true || false should be: 1 == %@", nsMudTestEvaluate(@[@192, @YES, @NO]));
  NSLog(@"false || true should be: 1 == %@", nsMudTestEvaluate(@[@192, @NO, @YES]));
  NSLog(@"false || false should be: 0 == %@", nsMudTestEvaluate(@[@192, @NO, @NO]));

  NSLog(@"ok");
}