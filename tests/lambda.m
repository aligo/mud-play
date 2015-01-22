#import "support.h"

int main() {

  NSLog(@"(lambda, (+, 1, 1)) should be: (2) == %@", nsMudTestEvaluate(@[@130, @[@200, @1, @1]]));

  NSLog(@"ok");
}