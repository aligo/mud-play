#import "mud_objects.h"

mud_object_t * mud_object_alloc(mud_object_type_e type) {
  mud_object_t * object = (mud_object_t *)malloc(sizeof(mud_object_t));
  memset(object, 0, sizeof(mud_object_t));
  object->type = type;
  return object;
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

mud_object_t * mud_number_init(mud_number_t value) {
  mud_object_t * object = mud_object_alloc(MUD_OBJ_TYPE_NUMBER);
  object->ptr = malloc(sizeof(mud_number_t));
  * (mud_number_t *)object->ptr = value;
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