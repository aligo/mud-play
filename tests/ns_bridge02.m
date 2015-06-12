#import "support.h"

int main() {

  NSLog(@"(list, 1, 2, nil) should be: (1, 2) == %@", nsMudTestEvaluate(@[@500, @1, @2, @[@120, @"unknown"]]));

  NSLog(@"(ht, 1, 'a', 2, nil) should be: { 1 = a } == %@", nsMudTestEvaluate(@[@600, @1, @"a", @2, @[@120, @"unknown"]]));

  
}