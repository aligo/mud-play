#import "support.m"

int main() {

  NSDictionary * json = openAndParseJson(@"fixtures/test03.json");

  // [concat, "Hell", "o", " world! ", 2014]
  NSLog(@"t01e should: Hello world! 2014 = %@", nsMudTestEvaluate([json objectForKey: @"01"]));

  // [format, "%s %s %lf", "PI", "is", 3.1415926535]
  NSLog(@"t02e should: PI is 3.14159275 你好 = %@", nsMudTestEvaluate([json objectForKey: @"02"]));

  // [format, "%s %s %lf", "PI", "is", 3.1415926535]
  NSLog(@"t03e should: %@", nsMudTestEvaluate([json objectForKey: @"03"]));

  // [format, "format with no arguments"]
  NSLog(@"t04e should: %@", nsMudTestEvaluate([json objectForKey: @"04"]));

  // [format, 1024]
  NSLog(@"t05e should: 1024 = %@", nsMudTestEvaluate([json objectForKey: @"05"]));

  NSLog(@"ok");
}