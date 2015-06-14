#import "support.h"

int main() {

  NSLog(@"(list, 1, 2, nil) should be: (1, 2) == %@", nsMudTestEvaluate(@[@500, @1, @2, @[@120, @"unknown"]]));

  NSLog(@"(ht, 1, 'a', 2, nil) should be: { 1 = a } == %@", nsMudTestEvaluate(@[@600, @1, @"a", @2, @[@120, @"unknown"]]));

  NSLog(@"(quote, (+, 1, 1)) should be: (200, 1, 1) == %@", nsMudTestEvaluate(@[@100, @[@200, @1, @1]]));

  NSLog(@"(quote, (+, 1, (+, 1, 1))) should be: (200, 1, (200, 1, 1)) == %@", nsMudTestEvaluate(@[@100, @[@200, @1, @[@200, @1, @1]]]));

  NSLog(@"(quote, ((+, 1, 1) (+, 1, 1))) should be: ((200, 1, 1), (200, 1, 1)) == %@", nsMudTestEvaluate(@[@100, @[@[@200, @1, @1], @[@200, @1, @1]]]));

  NSLog(@"(quote, (+, 1, 1) (+, 1, 1)) should be: ((200, 1, 1), (200, 1, 1)) == %@", nsMudTestEvaluate(@[@100, @[@200, @1, @1], @[@200, @1, @1]]));

  NSLog(@"(quote, (+, 1, null)) should be: (200, 1, null) == %@", nsMudTestEvaluate(@[@100, @[@200, @1, [NSNull null]]]));

  NSLog(@"nsMudTestEvaluate (quote, (+, 1, null)) should be: 1 == %@", nsMudTestEvaluate(nsMudTestEvaluate(@[@100, @[@200, @1, [NSNull null]]])));

}