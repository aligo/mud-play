#import "support.h"

int main() {

  NSLog(@"(lremove, (list), 0) should be: () == %@", nsMudTestEvaluate(@[@507, @[@500], @0]));

  NSLog(@"(lremove, (list), -1) should be: () == %@", nsMudTestEvaluate(@[@507, @[@500], @-1]));


  NSLog(@"ok");
}