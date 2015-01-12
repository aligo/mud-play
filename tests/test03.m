#import "support.m"

int main() {

  NSDictionary * json = openAndParseJson(@"fixtures/test03.json");

  NSLog(@"t01e should: Hello world! 2014 = %@", nsMudTestEvaluate([json objectForKey: @"01"]));

  NSLog(@"ok");
}