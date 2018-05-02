#import "support.h"

int main() {

  NSLog(@"(lremove, (list), 0) should be: () == %@", nsMudTestEvaluate(@[@507, @[@500], @0]));

  NSLog(@"(lremove, (list), -1) should be: () == %@", nsMudTestEvaluate(@[@507, @[@500], @-1]));

  NSLog(@"(lpush, (list), 1) should be: (1) == %@", nsMudTestEvaluate(@[@505, @[@500], @1]));

  NSLog(@"(lpush, (list), 1, 2) should be: () == %@", nsMudTestEvaluate(@[@505, @[@500], @1, @2]));

  NSLog(@"(lreplace, (list), 1, 2) should be: () == %@", nsMudTestEvaluate(@[@506, @[@500], @1, @2]));

  NSLog(@"ok");
}