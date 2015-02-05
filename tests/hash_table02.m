#import "support.h"

int main() {

  NSLog(@"(hteach, (ht, 'a', 1, 'b', 2), (lambda, (*, 2, (sarg, 0)))) should be: { a = 1, b = 2 } == %@", nsMudTestEvaluate(@[@620, @[@600, @"a", @1, @"b", @2], @[@130, @[@202, @2, @[@122, @1]]]]));

  NSLog(@"(htmap, (ht, 'a', 1, 'b', 2), (lambda, (*, 2, (sarg, 0)))) should be: { a = 2, b = 4 } == %@", nsMudTestEvaluate(@[@621, @[@600, @"a", @1, @"b", @2], @[@130, @[@202, @2, @[@122, @1]]]]));

  NSLog(@"(htsort_by, (ht, 'b', 2, 'a', 1)) should be: { a = 1, b = 2 } == %@", nsMudTestEvaluate(@[@625, @[@600, @"b", @2, @"a", @1]]));

  NSLog(@"(htsort_by, (ht, 3, 8, 1, 11, 4, 24, 2, 2)) should be: { 1 = 11, 2 = 2, 3 = 8, 4 = 24 } == %@", nsMudTestEvaluate(@[@625, @[@600, @3, @8, @1, @11, @4, @24, @2, @2], 
    @[@130, @[@500, @"el"], @[@204, @[@120, @"el"], @5]
  ]]));

}