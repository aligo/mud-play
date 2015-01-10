#import "NSBridge.h"

void MudErrorToNSLog(NSString * formatString, ...) {
  #ifndef MUD_MUTE_ERROR
  va_list args;
  va_start(args, formatString);
  NSString * output = [[NSString alloc] initWithFormat: formatString arguments: args];
  NSLog(@"[Mud Runtime] [Error] %@", output);
  [output release];
  va_end(args);
  #endif
}

void MudWarningToNSLog(NSString * formatString, ...) {
  #ifndef MUD_MUTE_WARNING
  va_list args;
  va_start(args, formatString);
  NSString * output = [[NSString alloc] initWithFormat: formatString arguments: args];
  NSLog(@"[Mud Runtime] [Warning] %@", output);
  [output release];
  va_end(args);
  #endif
}

mud_object_t * initMudObjectWithNSObject(NSObject * ns_object) {
  mud_object_t * ret;
  if ( [ns_object isKindOfClass: [NSNumber class]] ) {
    ret = mud_number_init([(NSNumber*)ns_object decimalValue]);
  } else if ( [ns_object isKindOfClass: [NSString class]] ) {
    ret = mud_string_init([(NSString *)ns_object UTF8String]);
  } else if ( [ns_object isKindOfClass: [NSNull class] ]) {
    ret = mud_nil_init(); 
  } else {
    mud_error(@"Converting an unsupported NSObject %@ '%@' as Number, as mud_nil", [ns_object class], ns_object);
    ret = mud_nil_init();
  }
  return ret;
}