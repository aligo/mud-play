mud_object_casting_pool_t * mud_object_casting_pool_init() {
  mud_object_casting_pool_t * pool = (mud_object_casting_pool_t *)malloc(sizeof(mud_object_casting_pool_t));

  pool->ptr = NULL;
  pool->prev = NULL;

  return pool;
}

void mud_object_casting_pool_free(mud_object_casting_pool_t * pool) {
  if ( pool->ptr ) {
    free(pool->ptr);
  }
  if ( pool->prev ) {
    mud_object_casting_pool_free(pool->prev);
  }
  free(pool);
}

void * _mud_object_casting_pool_malloc(mud_expr_evaluator_t * evaluator, size_t size) {
  mud_object_casting_pool_t * new_pool = mud_object_casting_pool_init();
  new_pool->ptr = malloc(size);
  if ( evaluator-> pool ) {
    new_pool->prev = evaluator->pool;
  }
  evaluator->pool = new_pool;
  return new_pool->ptr;
}

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

const char * mud_object_try_cast_str_format(mud_expr_evaluator_t * evaluator, mud_object_t * object, const char * fmt) {
  size_t len = _mud_object_try_cast_snprintf(object, NULL, 0, fmt);
  char * ret = (char *)_mud_object_casting_pool_malloc(evaluator, (len + 1) * sizeof(char));
  _mud_object_try_cast_sprintf(object, ret, fmt);
  return ret;
}

const char * mud_object_try_cast_str_with_default(mud_expr_evaluator_t * evaluator, mud_object_t * object, const char * _default) {
  switch ( object->type ) {
    case MUD_OBJ_TYPE_STRING:
      return object->ptr;
    case MUD_OBJ_TYPE_INT:
      return mud_object_try_cast_str_format(evaluator, object, "%ld");
    case MUD_OBJ_TYPE_FLOAT:
      return mud_object_try_cast_str_format(evaluator, object, "%lf");
    case MUD_OBJ_TYPE_BOOLEAN:
      return ( *(mud_boolean_t *)object->ptr != 0 ) ? "true" : "false";
    default:
      #ifdef mud_warning
      mud_warning("casting Type:%lu as mud_string", object->type);
      #endif
      return _default;
  }
}

mud_boolean_t mud_object_try_cast_boolean_with_default(mud_expr_evaluator_t * evaluator, mud_object_t * object, mud_boolean_t _default) {
  switch ( object->type ) {
    case MUD_OBJ_TYPE_STRING:
      // if ( strcmp("false", (char *)object->ptr) == 0 ) {
      //   return 0;
      // } else {
        return 1;
      // }
    case MUD_OBJ_TYPE_INT:
      return ( (*(mud_int_t *)object->ptr) != 0 );
    case MUD_OBJ_TYPE_FLOAT:
      return ( (*(mud_float_t *)object->ptr) != 0.0 );
    case MUD_OBJ_TYPE_BOOLEAN:
      return *(mud_boolean_t *)object->ptr;
    case MUD_OBJ_TYPE_NIL:
      return _default;
    case MUD_OBJ_TYPE_LIST:
      return ((mud_list_t *)object->ptr)->count == 0 ? 0 : 1;
    default:
      #ifdef mud_warning
      mud_warning("casting Type:%lu as mud_boolean, return false", object->type);
      #endif
      return _default;
  }
}

mud_int_t mud_object_try_cast_int_with_default(mud_expr_evaluator_t * evaluator, mud_object_t * object, mud_int_t _default) {
  switch ( object->type ) {
    case MUD_OBJ_TYPE_STRING:
      return atol(object->ptr);
    case MUD_OBJ_TYPE_INT:
      return *(mud_int_t *)object->ptr;
    case MUD_OBJ_TYPE_FLOAT:
      return (mud_float_t)(*(mud_float_t *)object->ptr);
    case MUD_OBJ_TYPE_BOOLEAN:
      return (mud_boolean_t)(*(mud_boolean_t *)object->ptr);
    default:
      #ifdef mud_warning
      mud_warning("casting Type:%lu as mud_int, return 0", object->type);
      #endif
      return _default;
  }
}

mud_float_t mud_object_try_cast_float_with_default(mud_expr_evaluator_t * evaluator, mud_object_t * object, mud_float_t _default) {
  switch ( object->type ) {
    case MUD_OBJ_TYPE_STRING:
      return atof(object->ptr);
    case MUD_OBJ_TYPE_INT:
      return (mud_int_t)(*(mud_int_t *)object->ptr);
    case MUD_OBJ_TYPE_FLOAT:
      return *(mud_float_t *)object->ptr;
    case MUD_OBJ_TYPE_BOOLEAN:
      return (mud_boolean_t)(*(mud_boolean_t *)object->ptr);
    default:
      #ifdef mud_warning
      mud_warning("casting Type:%lu as mud_float, return 0.0", object->type);
      #endif
      return _default;
  }
}