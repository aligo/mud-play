#import "support.h"

NSDictionary * openAndParseJson(NSString * path) {
  NSError * error;

  NSData * data  = [NSData dataWithContentsOfFile: path];
  NSDictionary * json = [NSJSONSerialization JSONObjectWithData: data options: NSJSONReadingMutableContainers error: &error];
  
  return json;
}

NSObject * nsMudTestEvaluate(NSObject * input) {
  mud_gc_stack_t * stack = mud_gc_stack_init();
  mud_object_t * code = initMudObjectWithNSObject(stack, input);
  mud_scope_t * scope = mud_scope_init();
  mud_object_t * result = mud_evaluate(code, scope, stack);
  mud_scope_free(scope);
  NSObject * ret = nsWithMudObject(result);
  mud_gc_stack_free(stack);
  return ret;
}

void reportMemory() {
  struct task_basic_info info;
  mach_msg_type_number_t size = sizeof(info);
  kern_return_t kerr = task_info(mach_task_self(),
                                 TASK_BASIC_INFO,
                                 (task_info_t)&info,
                                 &size);
  if( kerr == KERN_SUCCESS ) {
    NSLog(@"Memory in use (in bytes): %lu", info.resident_size);
  } else {
    NSLog(@"Error with task_info(): %s", mach_error_string(kerr));
  }
}