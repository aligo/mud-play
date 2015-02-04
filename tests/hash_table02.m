#import "support.h"

int main() {

  NSLog(@"(hteach, (ht, 'a', 1, 'b', 2), (lambda, (*, 2, (sarg, 0)))) should be: { a = 1, b = 2 } == %@", nsMudTestEvaluate(@[@620, @[@600, @"a", @1, @"b", @2], @[@130, @[@202, @2, @[@122, @1]]]]));

  NSLog(@"(htmap, (ht, 'a', 1, 'b', 2), (lambda, (*, 2, (sarg, 0)))) should be: { a = 2, b = 4 } == %@", nsMudTestEvaluate(@[@621, @[@600, @"a", @1, @"b", @2], @[@130, @[@202, @2, @[@122, @1]]]]));

}