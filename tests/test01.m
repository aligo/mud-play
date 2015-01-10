#import <Foundation/Foundation.h>

#import "../src/mud.c"
#import "../src/bridges/NSBridge.m"

#import "support.m"

int main() {

  NSDictionary * json = openAndParseJson(@"fixtures/test03.json");

  NSLog(@"%@", json);

  NSLog(@"ok");
}