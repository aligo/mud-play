
int _mud_object_try_cast_snprintf(mud_object_t * object, char * ret, size_t n, const char * fmt) {
  switch (object->type) {
    case MUD_OBJ_TYPE_NIL:      return snprintf(ret, n, fmt, 0);
    case MUD_OBJ_TYPE_BOOLEAN:  return snprintf(ret, n, fmt, *(mud_boolean_t *)object->ptr);
    case MUD_OBJ_TYPE_INT:      return snprintf(ret, n, fmt, *(mud_int_t *)object->ptr);
    case MUD_OBJ_TYPE_FLOAT:    return snprintf(ret, n, fmt, *(mud_float_t *)object->ptr);
    default:                    return snprintf(ret, n, fmt, object->ptr);
  }
}

int _mud_object_try_cast_sprintf(mud_object_t * object, char * ret, const char * fmt) {
  switch (object->type) {
    case MUD_OBJ_TYPE_NIL:      return sprintf(ret, fmt, 0);
    case MUD_OBJ_TYPE_BOOLEAN:  return sprintf(ret, fmt, *(mud_boolean_t *)object->ptr);
    case MUD_OBJ_TYPE_INT:      return sprintf(ret, fmt, *(mud_int_t *)object->ptr);
    case MUD_OBJ_TYPE_FLOAT:    return sprintf(ret, fmt, *(mud_float_t *)object->ptr);
    default:                    return sprintf(ret, fmt, object->ptr);
  }
}
