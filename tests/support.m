#import <mach/mach.h>

NSDictionary * openAndParseJson(NSString * path) {
  NSError * error;

  NSData * data  = [NSData dataWithContentsOfFile: path];
  NSDictionary * json = [NSJSONSerialization JSONObjectWithData: data options: NSJSONReadingMutableContainers error: &error];
  
  return json;
}

// NSObject * MudTestEvaluate(NSObject * input) {
//   MudEvaluator * evaluator = [[MudEvaluator alloc] init];
//   NSObject * ret = [evaluator evaluate: input];
//   [evaluator release];
//   return ret;
// }

void reportMemory(void) {
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