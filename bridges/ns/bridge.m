void MudErrorToNSLog(char * formatString, ...) {
  #ifndef MUD_MUTE_ERROR
  va_list args;
  va_start(args, formatString);
  NSString * output = [[NSString alloc] initWithFormat: [NSString stringWithUTF8String: formatString] arguments: args];
  NSLog(@"[Mud Runtime] [Error] %@", output);
  #if !__has_feature(objc_arc)
    [output release];
  #endif
  va_end(args);
  #endif
}

void MudWarningToNSLog(char * formatString, ...) {
  #ifndef MUD_MUTE_WARNING
  va_list args;
  va_start(args, formatString);
  NSString * output = [[NSString alloc] initWithFormat: [NSString stringWithUTF8String: formatString] arguments: args];
  NSLog(@"[Mud Runtime] [Warning] %@", output);
  #if !__has_feature(objc_arc)
  #endif
  va_end(args);
  #endif
}

void MudInfoToNSLog(char * formatString, ...) {
  #ifndef MUD_MUTE_WARNING
  va_list args;
  va_start(args, formatString);
  NSString * output = [[NSString alloc] initWithFormat: [NSString stringWithUTF8String: formatString] arguments: args];
  NSLog(@"[Mud Runtime] [Info] %@", output);
  #if !__has_feature(objc_arc)
  #endif
  va_end(args);
  #endif
}

mud_object_t * initMudObjectWithNSObject(mud_gc_stack_t * stack, NSObject * ns_object) {
  if ( [ns_object isKindOfClass: [NSArray class]] ) {
    NSObject * first_el = [(NSArray *)ns_object objectAtIndex: 0];
    if ( [first_el isKindOfClass: [NSNumber class]] ) {
      return _initMudExprWithNSArray(stack, (NSArray *) ns_object);
    } else {
      return _initMudExprsWithNSArray(stack, (NSArray *) ns_object);
    }
  } else if ( [ns_object isKindOfClass: [NSNumber class]] ) {
    if ( [ns_object class] == [@(YES) class] ) {
      return mud_boolean_init(stack, [(NSNumber*)ns_object boolValue]);
    } else {
      if ( CFNumberIsFloatType((CFNumberRef)(NSNumber*)ns_object) ) {
        return mud_float_init(stack, [(NSNumber*)ns_object doubleValue]);
      } else {
        return mud_int_init(stack, [(NSNumber*)ns_object longValue]);
      }
    }
  } else if ( [ns_object isKindOfClass: [NSString class]] ) {
    return mud_string_init(stack, [(NSString *)ns_object UTF8String]);
  } else if ( [ns_object isKindOfClass: [NSNull class] ]) {
    return mud_nil_init(stack);
  } else if ( [ns_object isKindOfClass: [NSDictionary class]] ) {
    return _initMudHashTableWithNSDictionary(stack, (NSDictionary *)ns_object);
  } else if ( [ns_object isKindOfClass: [NSDate class]] ) {
    return _initMudDateWithNSDate(stack, (NSDate *)ns_object);
  } else {
    // mud_error("Converting an unsupported NSObject %@ '%@' as Number, as mud_nil", [ns_object class], ns_object);
    // return mud_nil_init();
    mud_object_t * object = mud_object_alloc(stack, MUD_OBJ_TYPE_BRIDGE);
    #if __has_feature(objc_arc)
    object->ptr = (__bridge_retained void *)ns_object;
    #else
    object->ptr = (__bridge void *)ns_object;
    CFRetain((CFTypeRef)object->ptr);
    #endif
    return object;
  }
}

id nsWithMudObject(mud_object_t * object) {
  if ( !object ) {
    return nil;
  }
  id ret;
  switch ( object->type ) {
    case MUD_OBJ_TYPE_NIL:
      ret = nil;
      break;
    case MUD_OBJ_TYPE_BOOLEAN:
      ret = *(mud_boolean_t *)object->ptr ? @YES : @NO;
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
    case MUD_OBJ_TYPE_LIST:
      ret = nsArrayWithMudList((mud_list_t *)object->ptr);
      break;
    case MUD_OBJ_TYPE_HASH_TABLE:
      ret = nsDictionaryWithMudHashTable((mud_hash_table_t *)object->ptr);
      break;
    case MUD_OBJ_TYPE_DATE:
      ret = nsDateWithMudDate((mud_date_t *)object->ptr);
      break;
    case MUD_OBJ_TYPE_BRIDGE:
      #if __has_feature(objc_arc)
      ret = (__bridge_transfer NSObject *)object->ptr;
      #else
      ret = (__bridge NSObject *)object->ptr;
      CFRelease((CFTypeRef)ret);
      #endif
      object->ptr = NULL;
      break;
    default:
      mud_error("Unsupported converting Type:%lu to NSObject, return NSNull", object->type);
      ret = nil;
      break;
  }
  return ret;
}

NSArray * nsArrayWithMudList(mud_list_t * list) {
  NSMutableArray * ns_arr = [NSMutableArray arrayWithCapacity: list->count];
  for ( unsigned i = 0; i < list->count; i++ ) {
    id ns_obj = nsWithMudObject(list->objects[i]);
    if ( ns_obj != nil ) {
      [ns_arr insertObject: ns_obj atIndex: i];
    }
  }
  return ns_arr;
}

NSDictionary * nsDictionaryWithMudHashTable(mud_hash_table_t * hash_table) {
  NSMutableDictionary * ns_dict = [NSMutableDictionary new];
  mud_hash_table_t * tmp, * cur_hash = NULL;
  HASH_ITER(hh, hash_table, cur_hash, tmp) {
    id ns_obj = nsWithMudObject(cur_hash->value);
    if ( ns_obj != nil ) {
      [ns_dict setValue: ns_obj forKey: [NSString stringWithUTF8String: cur_hash->key]];
    }
  }
  return ns_dict;
}

NSDate * nsDateWithMudDate(mud_date_t * date) {
  NSString * calendar_type = NSCalendarIdentifierGregorian;
  NSCalendar * calendar = [[NSCalendar alloc] initWithCalendarIdentifier: calendar_type];
  NSDateComponents * components = [[NSDateComponents alloc] init];
  [components setYear:    date->year];
  [components setMonth:   date->mon];
  [components setDay:     date->mday];
  [components setHour:    date->hour];
  [components setMinute:  date->sec / 60];
  [components setSecond:  date->sec % 60];
  [components setTimeZone: [NSTimeZone timeZoneForSecondsFromGMT: 0]];
  NSDate * ns_date = [calendar dateFromComponents: components];
  #if !__has_feature(objc_arc)
    [components release];
    [calendar release];
  #endif
  return ns_date;
}

mud_object_t * _initMudExprWithNSArray(mud_gc_stack_t * stack, NSArray * ns_expr) {
  NSNumber * oper = (NSNumber *)[(NSArray *)ns_expr objectAtIndex: 0];
  NSUInteger args_count = [ns_expr count] - 1;
  mud_object_t ** args = malloc(args_count * sizeof(mud_object_t *));
  for (NSUInteger i = 0; i < args_count; i++ ) {
    args[i] = initMudObjectWithNSObject(stack, [ns_expr objectAtIndex: i + 1]);
  }
  return mud_expr_init(stack, (mud_operator_e)[oper unsignedIntegerValue], args, args_count);
}

mud_object_t * _initMudExprsWithNSArray(mud_gc_stack_t * stack, NSArray * ns_exprs) {
  NSUInteger exprs_count = [ns_exprs count];
  mud_object_t ** exprs = malloc(exprs_count * sizeof(mud_object_t *));
  for (NSUInteger i = 0; i < exprs_count; i++ ) {
    exprs[i] = initMudObjectWithNSObject(stack, [ns_exprs objectAtIndex: i]);
  }
  return mud_exprs_init(stack, exprs, exprs_count);
}

mud_object_t * _initMudHashTableWithNSDictionary(mud_gc_stack_t * stack, NSDictionary * ns_dict) {
  mud_object_t * ret = mud_object_alloc(stack, MUD_OBJ_TYPE_HASH_TABLE);
  ret->ptr = mud_hash_table_alloc();
  for ( NSString * key in ns_dict) {
    ret->ptr = mud_hash_table_set(ret->ptr, [key UTF8String], initMudObjectWithNSObject(stack, [ns_dict objectForKey:key]));
  }
  return ret;
}

mud_object_t * _initMudDateWithNSDate(mud_gc_stack_t * stack, NSDate * ns_date) {
  mud_object_t * ret = mud_object_alloc(stack, MUD_OBJ_TYPE_DATE);
  mud_date_t * date = mud_date_alloc_from_timestamp([ns_date timeIntervalSince1970]);
  date->off = [[NSTimeZone localTimeZone] secondsFromGMT];
  ret->ptr = date;
  return ret;
}

void mud_object_bridge_free(mud_object_t * object) {
  if ( object->ptr ) {
  //   #if __has_feature(objc_arc)
  //   (__bridge_transfer NSObject *)object->ptr;
  //   #else
    CFRelease((CFTypeRef)object->ptr);
  //   #endif
  }
  object->ptr = NULL;
}