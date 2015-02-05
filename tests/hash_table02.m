#import "support.h"

int main() {

  NSLog(@"(hteach, (ht, 'a', 1, 'b', 2), (lambda, (*, 2, (sarg, 0)))) should be: { a = 1, b = 2 } == %@", nsMudTestEvaluate(@[@620, @[@600, @"a", @1, @"b", @2], @[@130, @[@202, @2, @[@122, @1]]]]));

  NSLog(@"(htmap, (ht, 'a', 1, 'b', 2), (lambda, (*, 2, (sarg, 0)))) should be: { a = 2, b = 4 } == %@", nsMudTestEvaluate(@[@621, @[@600, @"a", @1, @"b", @2], @[@130, @[@202, @2, @[@122, @1]]]]));

  NSLog(@"(htsort_by, (ht, 'b', 2, 'a', 1)) should be: { a = 1, b = 2 } == %@", nsMudTestEvaluate(@[@625, @[@600, @"b", @2, @"a", @1]]));

  NSLog(@"(htsort_by, (ht, 'c', 8, 'a', 11, 'd', 24, 'b', 2)) should be: { a = 11, b = 2, c = 8, d = 24 } == %@", nsMudTestEvaluate(@[@625, @[@600, @"c", @8, @"a", @11, @"d", @24, @"b", @2], 
    @[@130, @[@204, @[@122, @1], @5]
  ]]));

  NSLog(@"(htpairs, (htsort, (ht, 'c', 3, 'a', 1, 'b', 2), (lambda, (-, (sarg, 1), (sarg, 0))))) should be: ((c, 3), (b, 2), (a, 1)) == %@", nsMudTestEvaluate(
    @[@606, @[@626, @[@600, @"c", @3, @"a", @1, @"b", @2], @[@130, @[@201, @[@122, @1], @[@122, @0]]]]]
  ));

}