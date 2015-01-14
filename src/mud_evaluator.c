#import "mud_evaluator.h"

mud_object_t * mud_evaluate(mud_object_t * object) {
  switch ( object->type ) {
    case MUD_OBJ_TYPE_EXPR:
      return _mud_expr_evaluate(object->ptr);
    case MUD_OBJ_TYPE_EXPRS:
      return _mud_exprs_evaluate(object->ptr);
    default:
      return object;
  }
}

mud_object_t * _mud_exprs_evaluate(mud_exprs_t * exprs) {
  mud_object_t * ret;
  for ( unsigned i = 0; i < exprs->count; i++ ) {
    ret = mud_evaluate(exprs->exprs[i]);
  }
  return ret;
}

mud_expr_evaluator_t * mud_expr_evaluator_init(mud_expr_t * expr) {
  mud_expr_evaluator_t * evaluator = (mud_expr_evaluator_t *)malloc(sizeof(mud_expr_evaluator_t));
  
  evaluator->args = (mud_object_t **)malloc(expr->argc * sizeof(mud_object_t *));
  for (unsigned i = 0; i < expr->argc; i++) {
    evaluator->args[i] = mud_evaluate(expr->args[i]);
  }
  evaluator->argc = expr->argc;

  evaluator->tmp_pool_count = 0;
  evaluator->tmp_pool_size = MUD_EXPR_EVALUATOR_TMP_POOL_ALLOC_SIZE;
  evaluator->tmp_pool = (void **)malloc(evaluator->tmp_pool_size * sizeof(void *));

  return evaluator;
}

void mud_expr_evaluator_free(mud_expr_evaluator_t * evaluator) {
  free(evaluator->args);
  for ( unsigned int i = 0; i < evaluator->tmp_pool_count; i++ ) {
    if ( evaluator->tmp_pool[i] ) {
      free(evaluator->tmp_pool[i]);
    }
  }
  free(evaluator->tmp_pool);

  evaluator->args = NULL;
  evaluator->tmp_pool = NULL;

  evaluator->argc = evaluator->tmp_pool_count = evaluator->tmp_pool_size = 0;
  free(evaluator);
}

void * _mud_expr_evaluator_tmp_pool_alloc(mud_expr_evaluator_t * evaluator, size_t size) {
  void * ptr = malloc(size);
  if (evaluator->tmp_pool_count == evaluator->tmp_pool_size) {
    evaluator->tmp_pool_size *= 2;
    evaluator->tmp_pool = (void **)realloc(evaluator->tmp_pool, evaluator->tmp_pool_size * sizeof(void *));
  }
  evaluator->tmp_pool[evaluator->tmp_pool_count++] = ptr;
  return ptr;
}

int _mud_expr_evaluator_snprintf(mud_expr_evaluator_t * evaluator, unsigned i, char * ret, size_t n, const char * fmt) {
  mud_object_t * arg = evaluator->args[i];
  switch (arg->type) {
    case MUD_OBJ_TYPE_NIL:      return snprintf(ret, n, fmt, 0);
    case MUD_OBJ_TYPE_BOOLEAN:  return snprintf(ret, n, fmt, *(mud_boolean_t *)arg->ptr);
    case MUD_OBJ_TYPE_INT:      return snprintf(ret, n, fmt, *(mud_int_t *)arg->ptr);
    case MUD_OBJ_TYPE_FLOAT:    return snprintf(ret, n, fmt, *(mud_float_t *)arg->ptr);
    default:                    return snprintf(ret, n, fmt, arg->ptr);
  }
}

int _mud_expr_evaluator_sprintf(mud_expr_evaluator_t * evaluator, unsigned i, char * ret, const char * fmt) {
  mud_object_t * arg = evaluator->args[i];
  switch (arg->type) {
    case MUD_OBJ_TYPE_NIL:      return sprintf(ret, fmt, 0);
    case MUD_OBJ_TYPE_BOOLEAN:  return sprintf(ret, fmt, *(mud_boolean_t *)arg->ptr);
    case MUD_OBJ_TYPE_INT:      return sprintf(ret, fmt, *(mud_int_t *)arg->ptr);
    case MUD_OBJ_TYPE_FLOAT:    return sprintf(ret, fmt, *(mud_float_t *)arg->ptr);
    default:                    return sprintf(ret, fmt, arg->ptr);
  }
}

const char * mud_expr_evaluator_get_str_format(mud_expr_evaluator_t * evaluator, unsigned i, const char * fmt) {
  size_t len = _mud_expr_evaluator_snprintf(evaluator, i, NULL, 0, fmt);
  char * ret = (char *)_mud_expr_evaluator_tmp_pool_alloc(evaluator, len);
  _mud_expr_evaluator_sprintf(evaluator, i, ret, fmt);
  return ret;
}

const char * mud_expr_evaluator_get_str(mud_expr_evaluator_t * evaluator, unsigned i) {
  mud_object_t * arg = evaluator->args[i];
  switch ( arg->type ) {
    case MUD_OBJ_TYPE_STRING:
      return arg->ptr;
    case MUD_OBJ_TYPE_INT:
      return mud_expr_evaluator_get_str_format(evaluator, i, "%ld");
    case MUD_OBJ_TYPE_FLOAT:
      return mud_expr_evaluator_get_str_format(evaluator, i, "%lf");
    case MUD_OBJ_TYPE_BOOLEAN:
      return ( *(mud_boolean_t *)arg->ptr != 0 ) ? "true" : "false";
    default:
      mud_warning("casting Type:%lu as mud_string", arg->type);
      return "";
  }
}

mud_boolean_t mud_expr_evaluator_get_boolean(mud_expr_evaluator_t * evaluator, unsigned i) {
  mud_object_t * arg = evaluator->args[i];
  switch ( arg->type ) {
    case MUD_OBJ_TYPE_STRING:
      return 1;
    case MUD_OBJ_TYPE_INT:
      return ( (*(mud_int_t *)arg->ptr) != 0 );
    case MUD_OBJ_TYPE_FLOAT:
      return ( (*(mud_float_t *)arg->ptr) != 0.0 );
    case MUD_OBJ_TYPE_BOOLEAN:
      return *(mud_boolean_t *)arg->ptr;
    default:
      mud_warning("casting Type:%lu as mud_int, return false", arg->type);
      return 0;
  }
}

mud_int_t mud_expr_evaluator_get_int(mud_expr_evaluator_t * evaluator, unsigned i) {
  mud_object_t * arg = evaluator->args[i];
  switch ( arg->type ) {
    case MUD_OBJ_TYPE_STRING:
      return atol(arg->ptr);
    case MUD_OBJ_TYPE_INT:
      return *(mud_int_t *)arg->ptr;
    case MUD_OBJ_TYPE_FLOAT:
      return (mud_float_t)(*(mud_float_t *)arg->ptr);
    case MUD_OBJ_TYPE_BOOLEAN:
      return (mud_boolean_t)(*(mud_boolean_t *)arg->ptr);
    default:
      mud_warning("casting Type:%lu as mud_int, return 0", arg->type);
      return 0;
  }
}

mud_float_t mud_expr_evaluator_get_float(mud_expr_evaluator_t * evaluator, unsigned i) {
  mud_object_t * arg = evaluator->args[i];
  switch ( arg->type ) {
    case MUD_OBJ_TYPE_STRING:
      return atof(arg->ptr);
    case MUD_OBJ_TYPE_INT:
      return (mud_int_t)(*(mud_int_t *)arg->ptr);
    case MUD_OBJ_TYPE_FLOAT:
      return *(mud_float_t *)arg->ptr;
    case MUD_OBJ_TYPE_BOOLEAN:
      return (mud_boolean_t)(*(mud_boolean_t *)arg->ptr);
    default:
      mud_warning("casting Type:%lu as mud_float, return 0.0", arg->type);
      return 0.0;
  }
}