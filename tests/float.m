#import "support.m"

int main() {

  NSLog(@"cos(10) should be: %@ == %lf", nsMudTestEvaluate(@[@220, @10]), cos(10));

  NSLog(@"sin(10) should be: %@ == %lf", nsMudTestEvaluate(@[@221, @10]), sin(10));

  NSLog(@"tan(10) should be: %@ == %lf", nsMudTestEvaluate(@[@222, @10]), tan(10));

  NSLog(@"acos(1) should be: %@ == %lf", nsMudTestEvaluate(@[@223, @1]), acos(1));

  NSLog(@"asin(1) should be: %@ == %lf", nsMudTestEvaluate(@[@224, @1]), asin(1));

  NSLog(@"atan(10) should be: %@ == %lf", nsMudTestEvaluate(@[@225, @10]), atan(10));

  NSLog(@"atan2(10, 10) should be: %@ == %lf", nsMudTestEvaluate(@[@226, @10, @10]), atan2(10, 10));

  NSLog(@"log10(10) should be: %@ == %lf", nsMudTestEvaluate(@[@227, @10]), log10(10));

  NSLog(@"log1p(0.3) should be: %@ == %lf", nsMudTestEvaluate(@[@228, @0.3]), log1p(0.3));

  NSLog(@"log2(1024) should be: %@ == %lf", nsMudTestEvaluate(@[@229, @1024]), log2(1024));

  NSLog(@"ok");
}