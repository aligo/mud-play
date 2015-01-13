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

    // [round, 10.4]
  NSLog(@"t10e should: 10 = %@", nsMudTestEvaluate([json objectForKey: @"10"]));

  // [round, 9.5]
  NSLog(@"t11e should: 10 = %@", nsMudTestEvaluate([json objectForKey: @"11"]));

  // [floor, 10.9]
  NSLog(@"t12e should: 10 = %@", nsMudTestEvaluate([json objectForKey: @"12"]));

  // [ceil, 9.1]
  NSLog(@"t13e should: 10 = %@", nsMudTestEvaluate([json objectForKey: @"13"]));


  // [abs, -123456789.87654321]
  NSLog(@"t14e should: 123456789.87654321 = %@", nsMudTestEvaluate([json objectForKey: @"14"]));

  // [abs, 123456789.87654321]
  NSLog(@"t15e should: 123456789.87654321 = %@", nsMudTestEvaluate([json objectForKey: @"15"]));

  NSLog(@"ok");
}