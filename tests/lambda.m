#import "support.h"

int main() {

  NSLog(@"(apply, (lambda, (+, 1, 1))) should be: 2 == %@", nsMudTestEvaluate(@[@131, @[@130, @[@200, @1, @1]]]));

  NSLog(@"(apply, (lambda, 1, (+, 1, 1))) should be: 2 == %@", nsMudTestEvaluate(@[@131, @[@130, @1, @[@200, @1, @1]]]));

  NSLog(@"ok");
}