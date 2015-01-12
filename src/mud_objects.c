#import "mud_objects.h"
#import "mud_gc.h"

mud_object_t * mud_object_alloc(mud_object_type_e type) {
  mud_object_t * object = (mud_object_t *)malloc(sizeof(mud_object_t));
  memset(object, 0, sizeof(mud_object_t));
  object->type = type;
  mud_gc_stack_cur_push(object);
  return object;
}

void mud_object_free(mud_object_t * object) {
  if ( object->type == MUD_OBJ_TYPE_EXPR ) {
    mud_expr_t * expr = (mud_expr_t *)object->ptr;
    free(expr->args);
    expr->args = NULL;
    expr->oper = 0;
  } else if ( object-> type >= MUD_OBJ_TYPE_BRIDGE ) {
    mud_object_bridge_free(object);
  }
  free(object->ptr);
  object->ptr = NULL;
  object->type = 0;
  free(object);
}

mud_object_t * mud_nil_init() {
  return mud_object_alloc(MUD_OBJ_TYPE_NIL);
}

mud_object_t * mud_boolean_init(mud_boolean_t value) {
  mud_object_t * object = mud_object_alloc(MUD_OBJ_TYPE_BOOLEAN);
  object->ptr = malloc(sizeof(mud_boolean_t));
  * (mud_boolean_t *)object->ptr = value;
  return object;
}

mud_object_t * mud_int_init(mud_int_t value) {
  mud_object_t * object = mud_object_alloc(MUD_OBJ_TYPE_INT);
  object->ptr = malloc(sizeof(mud_int_t));
  * (mud_int_t *)object->ptr = value;
  return object;
}
mud_object_t * mud_float_init(mud_float_t value){
  mud_object_t * object = mud_object_alloc(MUD_OBJ_TYPE_FLOAT);
  object->ptr = malloc(sizeof(mud_float_t));
  * (mud_float_t *)object->ptr = value;
  return object;
}

mud_object_t * mud_string_init(const char * value) {
  mud_object_t * object = mud_object_alloc(MUD_OBJ_TYPE_STRING);
  object->ptr = strdup(value);
  return object; 
}

mud_object_t * mud_expr_init(mud_operator_e oper, mud_object_t ** args) {
  mud_object_t * object = mud_object_alloc(MUD_OBJ_TYPE_EXPR);
  object->ptr = malloc(sizeof(mud_expr_t));
  mud_expr_t * expr = (mud_expr_t *)object->ptr;
  expr->oper = oper;
  expr->args = args;
  return object;
}

mud_object_t * mud_exprs_init(mud_object_t ** exprs) {
  mud_object_t * object = mud_object_alloc(MUD_OBJ_TYPE_EXPRS);
  object->ptr = exprs;
  return object;
}