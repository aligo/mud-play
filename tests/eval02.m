#import "support.h"

int main() {
  
  NSLog(@"tu should be logged out Unsupported converting Type:");
  NSLog(@"(quote, (+, 1,1)) should be: (200, 1, 1) == %@", nsMudTestEvaluate(@[@100, @[@200, @1, @1]]));

  NSLog(@"(eval, (quote, (+, 1, 1))) should be: 2 == %@", nsMudTestEvaluate(@[@101, @[@100, @[@200, @1, @1]]]));

  NSLog(@"(expr, +, 1, 1) should be: 2 == %@", nsMudTestEvaluate(@[@102, @200, @1, @1]));

  // NSLog(@"(expr, +, quote, (list, 1, 1), 1 ) should be: 3 == %@", nsMudTestEvaluate(@[@102, @200, @100, @[@500, @1, @1], @1]));

  // NSLog(@"(expr, concat, quote, (list, 'Hello ', 'world'), '!' ) should be: Hello world! == %@", nsMudTestEvaluate(@[@102, @300, @100, @[@500, @"Hello ", @"world"], @"!"]));

  NSLog(@"(expr, +, ( eargs, ( list, 2, ( eargs, 2 ) ) ), 2 ) should be: 6 == %@", nsMudTestEvaluate(@[@102, @200, @[@103, @[@500, @2, @[@103, @2]]], @2]));
}