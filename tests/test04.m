#import "support.h"

int main() {

  NSDictionary * json = openAndParseJson(@"fixtures/test04.json");

  // [list, "a", "b", "c"]
  NSLog(@"t01e should be: ('a', 'b', 'c') == %@", nsMudTestEvaluate([json objectForKey: @"01"]));

  // [sset, "list", [list, 1, 2, 3] ], [ +, [lcount, [sget, "list"]], [lnth, [sget, "list"], 1]
  NSLog(@"t02e should be: 4 == %@", nsMudTestEvaluate([json objectForKey: @"02"]));

  // [join, ",", [eargs, [list, "a", "b", "c", "d"]]]
  NSLog(@"t03e should be: a,b,c,d == %@", nsMudTestEvaluate([json objectForKey: @"03"]));

  // [lprepend, [lappend, [list, 2, 3], 4], 1]
  NSLog(@"t04e should be: (1,2,3,4) == %@", nsMudTestEvaluate([json objectForKey: @"04"]));

  // [lreverse, [lpush, [list, 4, 2, 1], 3, 1]]
  NSLog(@"t05e should be: (1,2,3,4) == %@", nsMudTestEvaluate([json objectForKey: @"05"]));

  // [lremove, [lreplace, [list, 4, 2, 1], 3, 1], 2]
  NSLog(@"t06e should be: (3, 2) == %@", nsMudTestEvaluate([json objectForKey: @"06"]));

  // [lmap, [list, 0, 1, 2, 3], [lambda, [list, 'el', 'i'], [*, [sget, 'el'], [sget, 'i']]]]
  NSLog(@"t07e should be: (0, 1, 4, 9) == %@", nsMudTestEvaluate([json objectForKey: @"07"]));

  // [lreduce, [list, 1, 2, 3, 4], 1, [lambda, [list, 'res', 'el'], [*, [sget, 'res'], [sget, 'el']]]]
  NSLog(@"t08e should be: 24 == %@", nsMudTestEvaluate([json objectForKey: @"08"]));

  // [lfilter, [list, -1, 1, -2, 2], [lambda, [list, "el"], [>, [sget, "el"], 0]]]
  NSLog(@"t09e should be: (1, 2) == %@", nsMudTestEvaluate([json objectForKey: @"09"]));

  // [lflatten, [list, "a", [list, "b", [list, "c", "d"]]], true]
  NSLog(@"t10e should be: ('a', 'b', 'c', 'd') == %@", nsMudTestEvaluate([json objectForKey: @"10"]));

  // [lfind, [list, "a", "b", "c"], "b"]
  NSLog(@"t11e should be: 1 == %@", nsMudTestEvaluate([json objectForKey: @"11"]));

  // [lmap, [list, 1, 2, 3], [lambda [*, 3, [sarg, 0]]]]
  NSLog(@"t12e should be: (3, 6, 9) == %@", nsMudTestEvaluate([json objectForKey: @"12"]));

  // [lsort_by, [list, 8, 11, 24, 2], [lambda, [list, "el"], [%, [sget, "el"], 5]]]
  NSLog(@"t13e should be: (11, 2, 8, 24) == %@", nsMudTestEvaluate([json objectForKey: @"13"]));

  // [lsort, [list, 0.1, 0.3, 0.7, 0.5], [lambda, [-, [sarg, 1], [sarg, 0]]]]
  NSLog(@"t14e should be: (0.7, 0.5, 0.3, 0.1) == %@", nsMudTestEvaluate([json objectForKey: @"14"]));

  // [lall, [list, 1, 2, 3, -1], [lambda, [>, [sarg, 0], 0]]]
  NSLog(@"t15e should be: 0 == %@", nsMudTestEvaluate([json objectForKey: @"15"])); 

  // [lany, [list, 1, 2, 3, -1], [lambda, [>, [sarg, 0], 0]]]
  NSLog(@"t16e should be: 1 == %@", nsMudTestEvaluate([json objectForKey: @"16"])); 

  NSLog(@"ok");
}