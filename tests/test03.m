#import <Foundation/Foundation.h>

#import "../src/bridges/ns/bridge.h"
#import "../src/mud.c"
#import "../src/bridges/ns/bridge.m"

#import "support.m"

int main() {

  NSDictionary * json = openAndParseJson(@"fixtures/test03.json");

  NSLog(@"%@", json);

  NSLog(@"ok");
}