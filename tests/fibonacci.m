#import "support.h"

int main() {

  NSLog(@"[fibonacci, 1, 1, 20] should be: %@", nsMudTestEvaluate(@[
    @[@121, @"fibonacci", @[@130, @[@500, @"a", @"b", @"n", @"str"],
      @[@111, @[@292, @[@120, @"n"], @0], @[
        @131, @[@120, @"fibonacci"],
          @[@120, @"b"],
          @[@200, @[@120, @"a"], @[@120, @"b"]],
          @[@201, @[@120, @"n"], @1],
          @[@300, @[@120, @"str"], @" ", @[@120, @"a"]]
      ], @[
        @120, @"str"
      ]]
    ]],
    @[@131, @[@120, @"fibonacci"], @1, @1, @20]
  ]));

  NSLog(@"ok");
}