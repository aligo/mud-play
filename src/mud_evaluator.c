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

void * mud_expr_evaluator_tmp_pool_alloc(mud_expr_evaluator_t * evaluator, size_t size) {
  void * ptr = malloc_empty(size);
  if (evaluator->tmp_pool_count == evaluator->tmp_pool_size) {
    evaluator->tmp_pool_size *= 2;
    evaluator->tmp_pool = (void **)realloc(evaluator->tmp_pool, evaluator->tmp_pool_size * sizeof(void *));
  }
  evaluator->tmp_pool[evaluator->tmp_pool_count++] = ptr;
  return ptr;
}

const char * mud_expr_evaluator_sprintf(mud_expr_evaluator_t * evaluator, const char * fmt, unsigned i) {
  char * ret = NULL;
  size_t len;
  mud_object_t * arg = evaluator->args[i];
  switch (arg->type) {
    case MUD_OBJ_TYPE_NIL:      len = (size_t)snprintf(NULL, 0, fmt, 0); break;
    case MUD_OBJ_TYPE_BOOLEAN:  len = (size_t)snprintf(NULL, 0, fmt, *(mud_boolean_t *)arg->ptr); break;
    case MUD_OBJ_TYPE_INT:      len = (size_t)snprintf(NULL, 0, fmt, *(mud_int_t *)arg->ptr); break;
    case MUD_OBJ_TYPE_FLOAT:    len = (size_t)snprintf(NULL, 0, fmt, *(mud_float_t *)arg->ptr); break;
    default:                    len = (size_t)snprintf(NULL, 0, fmt, arg->ptr); break;
  }
  ret = (char *)mud_expr_evaluator_tmp_pool_alloc(evaluator, len);
  switch (arg->type) {
    case MUD_OBJ_TYPE_NIL:      sprintf(ret, fmt, 0); break;
    case MUD_OBJ_TYPE_BOOLEAN:  sprintf(ret, fmt, *(mud_boolean_t *)arg->ptr); break;
    case MUD_OBJ_TYPE_INT:      sprintf(ret, fmt, *(mud_int_t *)arg->ptr); break;
    case MUD_OBJ_TYPE_FLOAT:    sprintf(ret, fmt, *(mud_float_t *)arg->ptr); break;
    default:                    sprintf(ret, fmt, arg->ptr); break;
  }
  return ret;
}

const char * mud_expr_evaluator_get_str(mud_expr_evaluator_t * evaluator, unsigned i) {
  mud_object_t * arg = evaluator->args[i];
  switch ( arg->type ) {
    case MUD_OBJ_TYPE_STRING:
      return arg->ptr;
    case MUD_OBJ_TYPE_INT:
      return mud_expr_evaluator_sprintf(evaluator, "%ld", i);
    case MUD_OBJ_TYPE_FLOAT:
      return mud_expr_evaluator_sprintf(evaluator, "%lf", i);
    default:
      mud_warning(@"casting Type:%lu as mud_string", arg->type);
      return "";
  }
}