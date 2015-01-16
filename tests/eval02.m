#import "support.h"

int main() {
  
  NSLog(@"tu should be logged out Unsupported converting Type:");
  NSLog(@"(quote, (+, 1,1)) should be: null == %@", nsMudTestEvaluate(@[@100, @[@200, @1, @1]]));

  NSLog(@"(eval, (quote, (+, 1, 1))) should be: 2 == %@", nsMudTestEvaluate(@[@101, @[@100, @[@200, @1, @1]]]));

}