#import "bridge.h"

void MudErrorToNSLog(char * formatString, ...) {
  #ifndef MUD_MUTE_ERROR
  va_list args;
  va_start(args, formatString);
  NSString * output = [[NSString alloc] initWithFormat: [NSString stringWithUTF8String: formatString] arguments: args];
  NSLog(@"[Mud Runtime] [Error] %@", output);
  [output release];
  va_end(args);
  #endif
}

void MudWarningToNSLog(char * formatString, ...) {
  #ifndef MUD_MUTE_WARNING
  va_list args;
  va_start(args, formatString);
  NSString * output = [[NSString alloc] initWithFormat: [NSString stringWithUTF8String: formatString] arguments: args];
  NSLog(@"[Mud Runtime] [Warning] %@", output);
  [output release];
  va_end(args);
  #endif
}

mud_object_t * initMudObjectWithNSObject(NSObject * ns_object) {
  mud_object_t * ret;
  if ( [ns_object isKindOfClass: [NSArray class]] ) {
    NSObject * first_el = [(NSArray *)ns_object objectAtIndex: 0];
    if ( [first_el isKindOfClass: [NSNumber class]] ) {
      return _initMudExprWithNSArray((NSArray *) ns_object);
    } else {
      return _initMudExprsWithNSArray((NSArray *) ns_object);
    }
  } else if ( [ns_object isKindOfClass: [NSNumber class]] ) {
    if ( [ns_object class] == [@(YES) class] ) {
      ret = mud_boolean_init([(NSNumber*)ns_object boolValue]);
    } else {
      if ( CFNumberIsFloatType((CFNumberRef)ns_object) ) {
        ret = mud_float_init([(NSNumber*)ns_object doubleValue]);
      } else {
        ret = mud_int_init([(NSNumber*)ns_object longValue]);
      }
    }
  } else if ( [ns_object isKindOfClass: [NSString class]] ) {
    ret = mud_string_init([(NSString *)ns_object UTF8String]);
  } else if ( [ns_object isKindOfClass: [NSNull class] ]) {
    ret = mud_nil_init(); 
  } else {
    mud_error("Converting an unsupported NSObject %@ '%@' as Number, as mud_nil", [ns_object class], ns_object);
    ret = mud_nil_init();
  }
  return ret;
}

NSObject * nsWithMudObject(mud_object_t * object) {
  NSObject * ret;
  switch ( object->type ) {
    case MUD_OBJ_TYPE_NIL:
      ret = [NSNull null];
      break;
    case MUD_OBJ_TYPE_INT:
      ret = [NSNumber numberWithLong: *(mud_int_t *)object->ptr];
      break;
    case MUD_OBJ_TYPE_FLOAT:
      ret = [NSNumber numberWithDouble: *(mud_float_t *)object->ptr];
      break;
    case MUD_OBJ_TYPE_STRING:
      ret = [NSString stringWithUTF8String: (char *)object->ptr];
      break;
    default:
      mud_error("Unsupported converting Type:%lu to NSObject, return NSNull", object->type);
      ret = [NSNull null];
      break;
  }
  return ret;
}

mud_object_t * _initMudExprWithNSArray(NSArray * ns_expr) {
  NSNumber * oper = (NSNumber *)[(NSArray *)ns_expr objectAtIndex: 0];
  NSUInteger args_count = [ns_expr count] - 1;
  mud_object_t ** args = malloc(args_count * sizeof(mud_object_t *));
  for (NSUInteger i = 0; i < args_count; i++ ) {
    args[i] = initMudObjectWithNSObject([ns_expr objectAtIndex: i + 1]);
  }
  return mud_expr_init((mud_operator_e)[oper unsignedIntegerValue], args, args_count);
}

mud_object_t * _initMudExprsWithNSArray(NSArray * ns_exprs) {
  NSUInteger exprs_count = [ns_exprs count];
  mud_object_t ** exprs = malloc(exprs_count * sizeof(mud_object_t *));
  for (NSUInteger i = 0; i < exprs_count; i++ ) {
    exprs[i] = initMudObjectWithNSObject([ns_exprs objectAtIndex: i]);
  }
  return mud_exprs_init(exprs, exprs_count);
}

void mud_object_bridge_free(mud_object_t * object) {
}