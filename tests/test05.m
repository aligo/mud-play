#import "support.h"

int main() {

  NSDictionary * json = openAndParseJson(@"fixtures/test05.json");

  // [ht, "a", 1, "b", 2]
  NSLog(@"t01e should be: { a = 1, b = 2 } == %@", nsMudTestEvaluate([json objectForKey: @"01"]));

  // [htinvert, [ht, "a", 1, "b", 2]]
  NSLog(@"t02e should be: { 1 = a, 2 = b } == %@", nsMudTestEvaluate([json objectForKey: @"02"]));

  // [htpairs, [ht, "a", 1, "b", 2]]
  NSLog(@"t03e should be: ((a, 1), (b, 2)) == %@", nsMudTestEvaluate([json objectForKey: @"03"]));

  // [htmerge, [ht, "a", 1, "b", 3], [ht, "c", 3, "b", 2]]
  NSLog(@"t04e should be: { a = 1, b = 2, c = 3 } == %@", nsMudTestEvaluate([json objectForKey: @"04"]));

  // [htvalues, [htsort_by, [ht, "b", 2, "a", 1]]]
  NSLog(@"t05e should be: [1, 2] == %@", nsMudTestEvaluate([json objectForKey: @"05"]));
}