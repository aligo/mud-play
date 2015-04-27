#define MUD_MUTE_ERROR    TRUE
#define MUD_MUTE_WARNING  TRUE

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

  mud_gc_stack_t * stack1 = mud_gc_stack_init();

  mud_object_t * code = initMudObjectWithNSObject(stack1, _code);

  int ft = 100;
  int t = ft;
  while ( t <= ( 512 * ft ) ) {
    NSLog(@"%d units", t);
    reportMemory();
    mud_scope_t * scope = mud_scope_init();
    for (int i = 0; i < t; i++ ) {
      mud_gc_stack_t * stack2 = mud_gc_stack_init();
      mud_evaluate(code, scope, stack2);
      mud_gc_stack_free(stack2);
    }
    mud_scope_free(scope);
    reportMemory();
    t *= 2;
  }

  mud_gc_stack_free(stack1);
}