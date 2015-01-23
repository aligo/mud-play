#import "support.h"

int main() {

  NSLog(@"(list, 1, 2, 3) should be: (1, 2, 3) == %@", nsMudTestEvaluate(@[@500, @1, @2, @3]));

  NSLog(@"(lcount, (list, 1, 2, nil, 3)) should be: 3 == %@", nsMudTestEvaluate(@[@501, @[@500, @1, @2, @[@120, @"unknown"], @3]]));

  NSLog(@"(lnth, (list, 1, 2, 3), 0) should be: 1 == %@", nsMudTestEvaluate(@[@502, @[@500, @1, @2, @3], @0]));
  NSLog(@"(lnth, (list, 1, 2, 3), 1) should be: 2 == %@", nsMudTestEvaluate(@[@502, @[@500, @1, @2, @3], @1]));

  NSLog(@"(lappend, (list, 1, 2, 3), 4, nil, 5, 6) should be: (1, 2, 3, 4, 5, 6) == %@", nsMudTestEvaluate(@[@503, @[@500, @1, @2, @3], @4, @[@120, @"ud"], @5, @6]));

  NSLog(@"(lprepend, (list, 4, 5, 6), 1, nil, 2, 3) should be: (1, 2, 3, 4, 5, 6) == %@", nsMudTestEvaluate(@[@504, @[@500, @4, @5, @6], @1, @[@120, @"ud"], @2, @3]));

  NSLog(@"(lpush, (list, 1, 2, 3), 4) should be: (1, 2, 3, 4) == %@", nsMudTestEvaluate(@[@505, @[@500, @1, @2, @3], @4]));

  NSLog(@"(lpush, (list, 1, 2, 3), 1.5, 1) should be: (1, 1.5, 2, 3) == %@", nsMudTestEvaluate(@[@505, @[@500, @1, @2, @3], @1.5, @1]));

  NSLog(@"(lpush, (list, 1, 2, 3), 0, 0) should be: (0, 1, 2, 3) == %@", nsMudTestEvaluate(@[@505, @[@500, @1, @2, @3], @0, @0]));

  NSLog(@"(lreplace, (list, 3, 2, 3), 1, 0) should be: (1, 2, 3) == %@", nsMudTestEvaluate(@[@506, @[@500, @3, @2, @3], @1, @0]));

  NSLog(@"(lreplace, (list, 1, 2, 3), 'all') should be: (all, all, all) == %@", nsMudTestEvaluate(@[@506, @[@500, @3, @2, @3], @"all"]));

  NSLog(@"(lremove, (list, 1, 1, 2, 3), 0) should be: (1, 2, 3) == %@", nsMudTestEvaluate(@[@507, @[@500, @1, @1, @2, @3], @0]));

  NSLog(@"(lfind, (list, 1, 2, 3), 2) should be: 1 == %@", nsMudTestEvaluate(@[@508, @[@500, @1, @2, @3], @2]));

  NSLog(@"(lreverse, (list, 1, 2, 3)) should be: (3, 2, 1) == %@", nsMudTestEvaluate(@[@510, @[@500, @1, @2, @3]]));

  NSLog(@"("
    " (sset, 'ret', ''), "
    " (leach, (list, 1, 2, 3), "
      " (lambda, (list, 'el', 'i'), ( "
        " (sset, 'ret', (concat, (sget, 'ret'), (sget, 'i'), ':', (sget, 'el'), '. ' )) "
      " )) "
    " ), "
    " (sget, 'ret') "
  ") should be:  0:a. 1:b. 2:c. == %@", nsMudTestEvaluate(@[
    @[@121, @"ret", @""],
    @[@520, @[@500, @"a", @"b", @"c"],
      @[@130, @[@500, @"el", @"i"], @[@121, @"ret", @[@300, @[@120, @"ret"], @[@120, @"i"], @":", @[@120, @"el"], @". "]]]
    ],
    @[@120, @"ret"]
  ]));

  NSLog(@"(lmap, (list, 1, 2, 3), (lambda, (list, 'el'), (*, (sget, 'el'), 2))) should be: (2, 4, 6) == %@", nsMudTestEvaluate(
    @[@521, @[@500, @1, @2, @3],
      @[@130, @[@500, @"el"], @[@202, @[@120, @"el"], @2]]
    ]
  ));

  NSLog(@"(lreduce, (list, 1, 2, 3), 0, (lambda, (list, 'sum', 'el'), (+, (sget, 'sum'), (sget, 'el')))) should be: 6 == %@", nsMudTestEvaluate(@[
    @522,
    @[@500, @1, @2, @3],
    @0,
    @[@130, @[@500, @"sum", @"el"], @[@200, @[@120, @"sum"], @[@120, @"el"]]]
  ]));

  NSLog(@"(lfilter, (list, 1, 2, 3), (lambda, (list, 'el'), (%%, (sget, 'el'), 2))) should be: (1, 3) == %@", nsMudTestEvaluate(
    @[@523, @[@500, @1, @2, @3],
      @[@130, @[@500, @"el"], @[@204, @[@120, @"el"], @2]]
    ]
  ));

  NSLog(@"(lflatten, (list, 1, (list 2, 3))) should be: (1, 2, 3) == %@", nsMudTestEvaluate(@[@511, @[@500, @1, @[@500, @2, @3]]]));

  NSLog(@"(lflatten, (list, 1, (list 2, (list, 3, 4)))) should be: (1, 2, (3, 4)) == %@", nsMudTestEvaluate(@[@511, @[@500, @1, @[@500, @2, @[@500, @3, @4]]]]));

  NSLog(@"(lflatten, (list, 1, (list 2, (list, 3, 4))), true) should be: (1, 2, 3, 4) == %@", nsMudTestEvaluate(@[@511, @[@500, @1, @[@500, @2, @[@500, @3, @4]]], @YES]));

  NSLog(@"(luniq, (list, 1, 1, 2, 2, 3, 2, 0, 3) should be: (1, 2, 3, 0) == %@", nsMudTestEvaluate(@[@512, @[@500, @1, @1, @2, @2, @3, @2, @0, @3]]));

  NSLog(@"ok");
}