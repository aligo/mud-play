#import "mud_evaluator.h"

mud_object_t * mud_evaluate(mud_object_t * object) {
  switch ( object->type ) {
    case MUD_OBJ_TYPE_EXPR:
      return _mud_expr_evaluate(object->ptr);
      break;
    case MUD_OBJ_TYPE_EXPRS:
      return _mud_exprs_evaluate(object->ptr);
      break;
    default:
      return object;
      break;
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
  void * ptr = malloc(size);
  if (evaluator->tmp_pool_count == evaluator->tmp_pool_size) {
    evaluator->tmp_pool_size *= 2;
    evaluator->tmp_pool = (void **)realloc(evaluator->tmp_pool, evaluator->tmp_pool_size * sizeof(void *));
  }
  evaluator->tmp_pool[evaluator->tmp_pool_count++] = ptr;
  return ptr;
}

const char * mud_expr_evaluator_get_str(mud_expr_evaluator_t * evaluator, unsigned i) {
  char * _str = "";
  mud_object_t * arg = evaluator->args[i];
  size_t _len;
  switch ( arg->type ) {
    case MUD_OBJ_TYPE_STRING:
      _str = arg->ptr;
      break;
    case MUD_OBJ_TYPE_INT:
      _len = (size_t)snprintf(NULL, 0, "%ld", *(mud_int_t *)arg->ptr);
      _str = mud_expr_evaluator_tmp_pool_alloc(evaluator, _len);
      sprintf(_str, "%ld", *(mud_int_t *)arg->ptr);
      break;
    case MUD_OBJ_TYPE_FLOAT:
      _len = (size_t)snprintf(NULL, 0, "%lf", *(mud_float_t *)arg->ptr);
      _str = mud_expr_evaluator_tmp_pool_alloc(evaluator, _len);
      sprintf(_str, "%lf", *(mud_float_t *)arg->ptr);
      break;
    default:
      mud_warning(@"casting Type:%lu as mud_string", arg->type);
      break;
  }
  return _str;
}