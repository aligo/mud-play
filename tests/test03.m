#import "support.h"

int main() {

  NSDictionary * json = openAndParseJson(@"fixtures/test03.json");

  // [concat, "Hell", "o", " world! ", 2014]
  NSLog(@"t01e should be: Hello world! 2014 = %@", nsMudTestEvaluate([json objectForKey: @"01"]));

  // [format, "%s %s %lf", "PI", "is", 3.1415926535]
  NSLog(@"t02e should be: PI is 3.14159275 你好 = %@", nsMudTestEvaluate([json objectForKey: @"02"]));

  // [format, "%s %s %lf", "PI", "is", 3.1415926535]
  NSLog(@"t03e should be: %@", nsMudTestEvaluate([json objectForKey: @"03"]));

  // [format, "format with no arguments"]
  NSLog(@"t04e should be: %@", nsMudTestEvaluate([json objectForKey: @"04"]));

  // [format, 1024]
  NSLog(@"t05e should: 1024 = %@", nsMudTestEvaluate([json objectForKey: @"05"]));

  // [strlen_byte, "Hello world! 你好世界！"]
  NSLog(@"t06e should: 28 = %@", nsMudTestEvaluate([json objectForKey: @"06"]));

  // [strstr_byte, "Hello world! 你好世界！", "world"]
  NSLog(@"t07e should: 6 = %@", nsMudTestEvaluate([json objectForKey: @"07"]));

  // [strstr_byte, "Hello world! 你好世界！", "世界"]
  NSLog(@"t08e should: 19 = %@", nsMudTestEvaluate([json objectForKey: @"08"]));

  // [strstr_byte, "Hello world! 你好世界！", "404"]
  NSLog(@"t09e should: <null> = %@", nsMudTestEvaluate([json objectForKey: @"09"]));

  // [substr_byte, "Hello world! 你好世界！", 0, 5]
  NSLog(@"t10e should: Hello = %@", nsMudTestEvaluate([json objectForKey: @"10"]));

  // [strlen, [concat, "Hello", " world! 你好世界！"]]
  NSLog(@"t11e should: 18 = %@", nsMudTestEvaluate([json objectForKey: @"11"]));

  // [strstr, "Hello world! 你好世界！", "世界"]
  NSLog(@"t12e should: 15 = %@", nsMudTestEvaluate([json objectForKey: @"12"]));

  // [substr, "Hello world! 你好世界！", 0, 5]
  NSLog(@"t13e should: Hello = %@", nsMudTestEvaluate([json objectForKey: @"13"]));

  // [substr, "Hello world! 你好世界！", 15, 2]
  NSLog(@"t14e should: 世界 = %@", nsMudTestEvaluate([json objectForKey: @"14"]));

  // [substr, "Hello world! 你好世界！", 6, 11]
  NSLog(@"t15e should: world! 你好世界 = %@", nsMudTestEvaluate([json objectForKey: @"15"]));

  // [subrep, "你好世界！", "世界", " aligo"]
  NSLog(@"t16e should: 你好 aligo！ = %@", nsMudTestEvaluate([json objectForKey: @"16"]));

  // [subrep, "a1 a2 a3 a4", "a", "aligo", true]
  NSLog(@"t17e should: aligo1 aligo2 aligo3 aligo4 = %@", nsMudTestEvaluate([json objectForKey: @"17"]));

  // [join, ".", "a", "b", "c", "d", 2014]
  NSLog(@"t18e should be: a.b.c.d.2014 = %@", nsMudTestEvaluate([json objectForKey: @"18"]));

  NSLog(@"ok");
}