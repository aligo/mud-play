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

  NSLog(@"ok");
}