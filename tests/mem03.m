#define MUD_MUTE_ERROR    1
#define MUD_MUTE_WARNING  1

#import "support.m"

int main() {
  NSMutableArray * _code = [[NSMutableArray alloc] init];

  for (int i = 1; i < 4; i++) {
    NSDictionary * json = openAndParseJson([NSString stringWithFormat: @"fixtures/test0%d.json", i]);
    for ( NSArray * test in [json allValues] ) {
      for ( NSArray * expr in test ) {
        [_code addObject: expr];
      }
    }
  }

  mud_object_t * code = initMudObjectWithNSObject(_code);

  int ft = 100;
  int t = ft;
  while ( t <= ( 1024 * ft ) ) {
    NSLog(@"%d units", t);
    reportMemory();
    for (int i = 0; i < t; i++ ) {
      mud_gc_stack_start();
      mud_evaluate(code);
      mud_gc_stack_finish();
    }
    reportMemory();
    t *= 2;
  }

}