#import "support.m"

int main() {

  NSDictionary * json = openAndParseJson(@"fixtures/test03.json");

  NSLog(@"%@", json);

  NSLog(@"ok");
}