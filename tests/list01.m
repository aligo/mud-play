#import "support.h"

int main() {

  NSLog(@"(list, 1, 2, 3) should be: (1, 2, 3) == %@", nsMudTestEvaluate(@[@500, @1, @2, @3]));

  NSLog(@"(lcount, (list, 1, 2, nil, 3)) should be: 3 == %@", nsMudTestEvaluate(@[@501, @[@500, @1, @2, @[@120, @"unknown"], @3]]));

  NSLog(@"(lnth, (list, 1, 2, 3), 0) should be: 1 == %@", nsMudTestEvaluate(@[@502, @[@500, @1, @2, @3], @0]));
  NSLog(@"(lnth, (list, 1, 2, 3), 1) should be: 2 == %@", nsMudTestEvaluate(@[@502, @[@500, @1, @2, @3], @1]));
  NSLog(@"(lnth, (list, 1, 2, 3), 3) should be: <null> == %@", nsMudTestEvaluate(@[@502, @[@500, @1, @2, @3], @3]));
  NSLog(@"(lnth, (list, 1, 2, 3), -1) should be: 3 == %@", nsMudTestEvaluate(@[@502, @[@500, @1, @2, @3], @-1]));

  NSLog(@"(lappend, (list, 1, 2, 3), 4, nil, 5, 6) should be: (1, 2, 3, 4, 5, 6) == %@", nsMudTestEvaluate(@[@503, @[@500, @1, @2, @3], @4, @[@120, @"ud"], @5, @6]));

  NSLog(@"(lprepend, (list, 4, 5, 6), 1, nil, 2, 3) should be: (1, 2, 3, 4, 5, 6) == %@", nsMudTestEvaluate(@[@504, @[@500, @4, @5, @6], @1, @[@120, @"ud"], @2, @3]));

  NSLog(@"(lpush, (list, 1, 2, 3), 4) should be: (1, 2, 3, 4) == %@", nsMudTestEvaluate(@[@505, @[@500, @1, @2, @3], @4]));

  NSLog(@"(lpush, (list, 1, 2, 3), 1.5, 1) should be: (1, 1.5, 2, 3) == %@", nsMudTestEvaluate(@[@505, @[@500, @1, @2, @3], @1.5, @1]));

  NSLog(@"(lpush, (list, 1, 2, 3), 0, 0) should be: (0, 1, 2, 3) == %@", nsMudTestEvaluate(@[@505, @[@500, @1, @2, @3], @0, @0]));

  NSLog(@"(lreplace, (list, 3, 2, 3), 1, 0) should be: (1, 2, 3) == %@", nsMudTestEvaluate(@[@506, @[@500, @3, @2, @3], @1, @0]));

  NSLog(@"(lreplace, (list, 1, 2, 3), 'all') should be: (all, all, all) == %@", nsMudTestEvaluate(@[@506, @[@500, @3, @2, @3], @"all"]));

  NSLog(@"(lremove, (list, 1, 1, 2, 3), 0) should be: (1, 2, 3) == %@", nsMudTestEvaluate(@[@507, @[@500, @1, @1, @2, @3], @0]));

  NSLog(@"(lremove, (list, 1, 2, 3, 3), -1) should be: (1, 2, 3) == %@", nsMudTestEvaluate(@[@507, @[@500, @1, @2, @3, @3], @-1]));

  NSLog(@"(lfind, (list, 1, 2, 3), 2) should be: 1 == %@", nsMudTestEvaluate(@[@508, @[@500, @1, @2, @3], @2]));

  NSLog(@"(lreverse, (list, 1, 2, 3)) should be: (3, 2, 1) == %@", nsMudTestEvaluate(@[@510, @[@500, @1, @2, @3]]));

  NSLog(@"(lflatten, (list, 1, (list 2, 3))) should be: (1, 2, 3) == %@", nsMudTestEvaluate(@[@511, @[@500, @1, @[@500, @2, @3]]]));

  NSLog(@"(lflatten, (list, 1, (list 2, (list, 3, 4)))) should be: (1, 2, (3, 4)) == %@", nsMudTestEvaluate(@[@511, @[@500, @1, @[@500, @2, @[@500, @3, @4]]]]));

  NSLog(@"(lflatten, (list, 1, (list 2, (list, 3, 4))), true) should be: (1, 2, 3, 4) == %@", nsMudTestEvaluate(@[@511, @[@500, @1, @[@500, @2, @[@500, @3, @4]]], @YES]));

  NSLog(@"(luniq, (list, 1, 1, 2, 2, 3, 2, 0, 3) should be: (1, 2, 3, 0) == %@", nsMudTestEvaluate(@[@512, @[@500, @1, @1, @2, @2, @3, @2, @0, @3]]));

  NSLog(@"(lintersection, (list, 1, 2), (list, 2, 3)) should be: (2) == %@", nsMudTestEvaluate(@[@513, @[@500, @1, @2], @[@500, @2, @3]]));

  NSLog(@"(ldifference, (list, 1, 2), (list, 2, 3)) should be: (1, 3) == %@", nsMudTestEvaluate(@[@514, @[@500, @1, @2], @[@500, @2, @3]]));

  NSLog(@"(lconcat, (list, 1, 2), (list, 2, 3)) should be: (1, 2, 2, 3) == %@", nsMudTestEvaluate(@[@515, @[@500, @1, @2], @[@500, @2, @3]]));

  NSLog(@"(lunion, (list, 1, 2), (list, 2, 3)) should be: (1, 2, 3) == %@", nsMudTestEvaluate(@[@516, @[@500, @1, @2], @[@500, @2, @3]]));

  NSLog(@"(lhead, (list, 1, 2, 3), 2) should be: (1, 2) == %@", nsMudTestEvaluate(@[@517, @[@500, @1, @2, @3], @2]));

  NSLog(@"(ltail, (list, 1, 2, 3), 2) should be: (2, 3) == %@", nsMudTestEvaluate(@[@518, @[@500, @1, @2, @3], @2]));

  NSLog(@"(lslice, (list, 1, 2, 3), 1) should be: (2, 3) == %@", nsMudTestEvaluate(@[@519, @[@500, @1, @2, @3], @1]));

  NSLog(@"(lslice, (list, 1, 2, 3), 1, 2) should be: (2) == %@", nsMudTestEvaluate(@[@519, @[@500, @1, @2, @3], @1, @2]));

  NSLog(@"ok");
}