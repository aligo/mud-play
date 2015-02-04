#import "support.h"

int main() {

  NSLog(@"(ht, 1, 'a', 2, 'b') should be: { 1 = a, 2 = b } == %@", nsMudTestEvaluate(@[@600, @1, @"a", @2, @"b"]));

  NSLog(@"(ht, (list, 1, 'a'), (list, 2, 'b')) should be: { 1 = a, 2 = b } == %@", nsMudTestEvaluate(@[@600, @[@500, @1, @"a"], @[@500, @2, @"b"]]));

  NSLog(@"(htcount, (ht, 'hello', 'world')) should be: 1 == %@", nsMudTestEvaluate(@[@601, @[@600, @"hello", @"world"]]));

  NSLog(@"(htget, (ht, 'hello', 'world'), 'hello') should be: world == %@", nsMudTestEvaluate(@[@602, @[@600, @"hello", @"world"], @"hello"]));
  
  NSLog(@"(htget, (htset, (ht, 'hello', 'world'), 'hello', 'changed'), 'hello') should be: changed == %@", nsMudTestEvaluate(@[@602, @[@603, @[@600, @"hello", @"world"], @"hello", @"changed"], @"hello"]));

  NSLog(@"(htkeys, (ht, 1, 'a', 2, 'b')) should be: (1, 2) == %@", nsMudTestEvaluate(@[@604, @[@600, @1, @"a", @2, @"b"]]));

  NSLog(@"(htvalues, (ht, 1, 'a', 2, 'b')) should be: ('a', b') == %@", nsMudTestEvaluate(@[@605, @[@600, @1, @"a", @2, @"b"]]));

  NSLog(@"(htpairs, (ht, 1, 'a', 2, 'b')) should be: (('1', 'a') ('2', b')) == %@", nsMudTestEvaluate(@[@606, @[@600, @1, @"a", @2, @"b"]]));

  NSLog(@"(htmerge, (ht, 1, 'a', 2, 'c'), (h1, 2, 'b', 3, 'c')) should be: { 1 = a, 2 = b, 3 = c }  == %@", nsMudTestEvaluate(@[@607, @[@600, @1, @"a", @2, @"c"], @[@600, @2, @"b", @3, @"c"]]));

  NSLog(@"(htinvert, (ht, 1, 'a', 2, 'b')) should be:  { a = 1, b = 2 } == %@", nsMudTestEvaluate(@[@608, @[@600, @1, @"a", @2, @"b"]]));
}