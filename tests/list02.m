#import "support.h"

int main() {

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

    NSLog(@"(lpluck, (list, 1, 2, 3), -, 1) should be: (0, 1, 2) == %@", nsMudTestEvaluate(
    @[@524, @[@500, @1, @2, @3], @201, @1]
  ));

  NSLog(@"ok");
}