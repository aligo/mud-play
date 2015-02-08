#import "support.h"

int main() {

  mud_object_t * date = initMudObjectWithNSObject([NSDate date]);

  NSLog(@"Date should be: %@ == %@", [NSDate date], nsWithMudObject(date));
}