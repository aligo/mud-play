#define MUD_MUTE_ERROR    1
#define MUD_MUTE_WARNING  1

#import "support.h"

int main() {
  NSMutableArray * _code = [[NSMutableArray alloc] init];

  for (int i = 1; i < 6; i++) {
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
  while ( t <= ( 512 * ft ) ) {
    NSLog(@"%d units", t);
    reportMemory();
    mud_scope_t * scope = mud_scope_init();
    for (int i = 0; i < t; i++ ) {
      mud_gc_stack_start();
      mud_evaluate(code, scope);
      mud_gc_stack_finish();
    }
    mud_scope_free(scope);
    reportMemory();
    t *= 2;
  }

}