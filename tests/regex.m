#import "support.h"

int main() {

  NSLog(@"(regex, 'a') should be: mud_regex(Type:135) == %@", nsMudTestEvaluate(@[@310, @"a"]));

  NSLog(@"(rmatch, (regex, 'a'), 'b') should be: 0 == %@", nsMudTestEvaluate(@[@311, @[@310, @"a"], @"b"]));

  NSLog(@"(rmatch, (regex, 'a'), 'a') should be: 1 == %@", nsMudTestEvaluate(@[@311, @[@310, @"a"], @"a"]));

  NSLog(@"(rmatch, (regex, 'ab?'), 'a') should be: 1 == %@", nsMudTestEvaluate(@[@311, @[@310, @"ab?"], @"a"]));

  NSLog(@"(rmatch, (regex, 'a(b?)'), 'ab') should be: (ab, b) == %@", nsMudTestEvaluate(@[@312, @[@310, @"a(b?)"], @"ab"]));

  NSLog(@"(rmatch, (regex, 'abc'), '111abc111') should be: (abc) == %@", nsMudTestEvaluate(@[@312, @[@310, @"abc"], @"111abc111"]));

  NSLog(@"(rmatch_all, (regex, '(ab|bc)'), 'abcbcab') should be: (ab, bc, ab) == %@", nsMudTestEvaluate(@[@313, @[@310, @"(ab|bc)"], @"abcbcab"]));

  NSLog(@"(rmatch_all, (regex, '(ab|bc)(\\d{2})', true), 'ab12bc13ab14') should be: ( (ab12, ab, 12), (bc13, bc, 13), (ab14, ab, 14) ) == %@", nsMudTestEvaluate(@[@313, @[@310, @"(ab|bc)([0-9]{2})"], @"ab12bc13ab14", @YES]));
  
  NSLog(@"(rrep_all, (regex, '(ab|bc)(\\d{2})', 'ab12-bc13中文ab14', 'xx')) should be: ? == %@", nsMudTestEvaluate(@[@314, @[@310, @"(ab|bc)([0-9]{2})"], @"ab12-bc13中文ab14", @"xx"]));
  
  NSLog(@"(rrep_all, (regex, '(ab|bc)(\\d{2})', 'ab12-bc13中文ab14', (lambda, (concat, (sarg, 1), ',', (*, 100, (sarg, 2)))))) should be: ab,1200-bc,1300中文ab,1400 == %@", nsMudTestEvaluate(@[
    @314, @[@310, @"(ab|bc)([0-9]{2})"], @"ab12-bc13中文ab14", @[
      @130, @[@300, @[@122, @1], @",", @[@202, @100, @[@122, @2]]]
    ]
  ]));
}