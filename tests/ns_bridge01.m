#import "support.m"

int main() {

  // NSDictionary * json = openAndParseJson(@"fixtures/test03.json");

  mud_object_t * object_nil = initMudObjectWithNSObject([NSNull null]);
  NSLog(@"object_nil should be mud_nil: 1 == %d", object_nil->type == MUD_OBJ_TYPE_NIL);
  

  mud_object_t * object_boolean = initMudObjectWithNSObject(@(YES));
  NSLog(@"object_boolean should be mud_boolean: 1 == %d", object_boolean->type == MUD_OBJ_TYPE_BOOLEAN);
  NSLog(@"object_boolean value should be: 1 == %d", *(BOOL *)object_boolean->ptr);

  mud_object_t * object_int = initMudObjectWithNSObject([NSNumber numberWithInt: 100]);
  NSLog(@"object_int should be mud_int: 1 == %d", object_int->type == MUD_OBJ_TYPE_INT);
  NSLog(@"object_int value should be: 100 == %ld", *(mud_int_t *)object_int->ptr);
  NSLog(@"object_int to nsWithMudObject should be: 100 == %@", nsWithMudObject(object_int));
  

  mud_object_t * object_float = initMudObjectWithNSObject([NSNumber numberWithDouble: 2015.0112]);
  NSLog(@"object_float should be mud_float: 1 == %d", object_float->type == MUD_OBJ_TYPE_FLOAT);
  NSLog(@"object_float value should be: 2015.0112 == %lf", *(mud_float_t *)object_float->ptr);
  NSLog(@"object_float to nsWithMudObject should be: 2015.0112 == %@", nsWithMudObject(object_float));
  
  mud_object_t * object_string = initMudObjectWithNSObject(@"hello world! 你好世界！");
  NSLog(@"object_string should be mud_string: 1 == %d", object_string->type == MUD_OBJ_TYPE_STRING);
  NSLog(@"object_string value should be: %@", [NSString stringWithUTF8String: (char *)object_string->ptr]);
  NSLog(@"object_string to nsWithMudObject should be: %@", nsWithMudObject(object_string));

  mud_object_t * object_expr1 = _initMudExprWithNSArray(@[@2015, @"test", @"test2"]);
  NSLog(@"object_expr1 should be mud_expr: 1 == %d", object_expr1->type == MUD_OBJ_TYPE_EXPR);
  mud_expr_t * expr1 = object_expr1->ptr;
  NSLog(@"object_expr1 operator should be: 2015 == %d", expr1->oper);
  NSLog(@"object_expr1 argument 1 should be: test == %s", (char *)expr1->args[0]->ptr);
  NSLog(@"object_expr1 argument 1 should be: test2 == %s", (char *)expr1->args[1]->ptr);

  mud_object_t * object_expr2 = _initMudExprWithNSArray(@[@2014]);
  NSLog(@"object_expr2 should be mud_expr: 1 == %d", object_expr2->type == MUD_OBJ_TYPE_EXPR);
  mud_expr_t * expr2 = object_expr2->ptr;
  NSLog(@"object_expr2 operator should be: 2014 == %d", expr2->oper);

  NSArray * ns_exprs1 = @[
                            @[@2015, @"expr1"],
                            @"expr2"
                        ];
  mud_object_t * object_exprs1 = _initMudExprsWithNSArray(ns_exprs1);
  NSLog(@"object_exprs1 should be mud_exprs: 1 == %d", object_exprs1->type == MUD_OBJ_TYPE_EXPRS);
  mud_exprs_t * exprs1 = object_exprs1->ptr;
  mud_object_t * exprs1_0 = exprs1->exprs[0];
  NSLog(@"exprs1_0 should be mud_expr: 1 == %d", exprs1_0->type == MUD_OBJ_TYPE_EXPR);
  mud_expr_t * exprs1_expr0 = exprs1_0->ptr;
  NSLog(@"exprs1_expr0 operator should be: 2015 == %d", exprs1_expr0->oper);
  NSLog(@"exprs1_expr0 argument 1 should be: expr1 == %s", (char *)exprs1_expr0->args[0]->ptr);

  mud_object_t * exprs1_1 = exprs1->exprs[1];
  NSLog(@"exprs1_1 should be mud_expr: 1 == %d", exprs1_1->type == MUD_OBJ_TYPE_STRING);
  NSLog(@"exprs1_1 should be: expr2 == %s", (char *)exprs1_1->ptr);

  NSLog(@"ok");
}