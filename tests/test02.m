#import "support.m"

int main() {

  NSDictionary * json = openAndParseJson(@"fixtures/test02.json");

  // [+, 0.9, "49.1", [+, 10, 25, 15]]
  NSLog(@"t01e should be: 100 ==  %@", nsMudTestEvaluate([json objectForKey: @"01"]));

  // [-, "100", 200, -50, [-, 51]]
  NSLog(@"t02e should: 1 == %@", nsMudTestEvaluate([json objectForKey: @"02"]));

   // [*, 1, 100, "0.01"]
  NSLog(@"t03e should: 1 == %@", nsMudTestEvaluate([json objectForKey: @"03"]));

  // [/, 4000, 4, "5"]
  NSLog(@"t04e should: 200 == %@", nsMudTestEvaluate([json objectForKey: @"04"]));

  // [/, 2.0, 3, 2]
  NSLog(@"t05e should: 0.333...3 == %@", nsMudTestEvaluate([json objectForKey: @"05"]));

  // [/, 1, 0]
  NSLog(@"t06e should be logged out 'dividing by zero':");
  NSLog(@"t06e should: 1 == %@", nsMudTestEvaluate([json objectForKey: @"06"]));

  // [%, 200, 11]
  NSLog(@"t07e should: 2 == %@", nsMudTestEvaluate([json objectForKey: @"07"]));

  // [**, 2, 10]
  NSLog(@"t08e should: 1024 == %@", nsMudTestEvaluate([json objectForKey: @"08"]));

  // [log, 1000]
  NSLog(@"t09e should: 2.302585093 =~ %@", nsMudTestEvaluate([json objectForKey: @"09"]));

  NSLog(@"ok");
}