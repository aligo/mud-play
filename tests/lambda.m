#import "support.h"

int main() {

  NSLog(@"(apply, (lambda, (+, 1, 1))) should be: 2 == %@", nsMudTestEvaluate(@[@131, @[@130, @[@200, @1, @1]]]));

  NSLog(@"should be logged out 'Lambda arguments list is not a list.':");
  NSLog(@"(apply, (lambda, 1, (+, 1, 1))) should be: 2 == %@", nsMudTestEvaluate(@[@131, @[@130, @1, @[@200, @1, @1]]]));


  NSLog(@"(apply, (lambda, [list, 'a'], (+, 1, 1))) should be: 2 == %@", nsMudTestEvaluate(@[@131, @[@130, @[@500, @"a"], @[@200, @1, @1]]]));

  NSLog(@"(apply, (lambda, [list, 'a'], (+, 1, 1, (sget, 'a'))), 2) should be: 4 == %@", nsMudTestEvaluate(@[@131, @[@130, @[@500, @"a"], @[@200, @1, @1, @[@120, @"a"]]], @2]));

  NSLog(@"(apply,"
          " (lambda, [list, 'a', 'b, 'c'],"
            " (+, 1, 1, (sget, 'a'), (sget, 'b'), (sget, 'c'))"
          " ),"
        " 2, 2"
      " ) should be: 6 == %@", nsMudTestEvaluate(@[@131, 
            @[@130, @[@500, @"a", @"b", @"c"], 
              @[@200, @1, @1, @[@120, @"a"], @[@120, @"b"], @[@120, @"c"]]
            ], 
          @2, @2
        ]));

    NSLog(@"(apply,"
          " (lambda, [list, 'arg1', 'arg2'],"
            " (concat, 'a', (sget, 'arg1'), ( apply,"
              " ( lambda, [list, 'arg1'],"
                " (concat, (sget, 'arg1'), 'd')"
              " )"
            " , (sget, 'arg1') )"
            " )"
          " ),"
        " 'b', 'c'"
      " ) should be: abcd == %@", nsMudTestEvaluate(@[@131, 
            @[@130, @[@500, @"arg1", @"arg2"], 
              @[@300, @"a", @[@120, @"arg1"], @[@131, 
                @[@130, @[@500, @"arg1"], 
                  @[@300, @[@120, @"arg1"], @"d"]
                ]
              , @[@120, @"arg2"]]
              ]
            ],
          @"b", @"c"
        ]));

  NSLog(@"ok");
}