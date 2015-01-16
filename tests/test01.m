#import "support.h"

int main() {

  NSDictionary * json = openAndParseJson(@"fixtures/test01.json");

  // Unknown Operator 404
  NSLog(@"tu should be logged out Unknown operator 404:");
  NSLog(@"tu should be: null ==  %@", nsMudTestEvaluate([json objectForKey: @"unknown"]));

  // [!, [and, false, [ or, true, false]]]
  NSLog(@"t01e should: 1 == %@", nsMudTestEvaluate([json objectForKey: @"01"]));


  NSLog(@"ok");
}