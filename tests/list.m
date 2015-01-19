#import "support.h"

int main() {

  NSLog(@"(list, 1, 2, 3) should be: (1, 2, 3) == %@", nsMudTestEvaluate(@[@500, @1, @2, @3]));


  NSLog(@"ok");
}