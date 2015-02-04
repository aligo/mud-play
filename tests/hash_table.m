#import "support.h"

int main() {

  NSLog(@"(ht, 1, 'a', 2, 'b') should be: { 1 = 'a', 2 = 'b' } == %@", nsMudTestEvaluate(@[@600, @1, @"a", @2, @"b"]));

  NSLog(@"(ht, (list, 1, 'a'), (list, 2, 'b')) should be: { 1 = 'a', 2 = 'b' } == %@", nsMudTestEvaluate(@[@600, @[@500, @1, @"a"], @[@500, @2, @"b"]]));
}