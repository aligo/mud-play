mud_expr_evaluator_t * mud_expr_evaluator_init(mud_expr_t * expr) {
  mud_expr_evaluator_t * evaluator = (mud_expr_evaluator_t *)malloc(sizeof(mud_expr_evaluator_t));
  
  evaluator->args = (mud_object_t **)malloc(expr->argc * sizeof(mud_object_t *));
  for (unsigned i = 0; i < expr->argc; i++) {
    evaluator->args[i] = mud_evaluate(expr->args[i]);
  }
  evaluator->argc = expr->argc;

  evaluator->pool = mud_object_casting_pool_init();
  return evaluator;
}

void mud_expr_evaluator_free(mud_expr_evaluator_t * evaluator) {
  free(evaluator->args);
  evaluator->args = NULL;
  mud_object_casting_pool_free(evaluator->pool);
  evaluator->pool = NULL;
  evaluator->argc = 0;
  free(evaluator);
}

mud_object_t * _mud_expr_evaluator_get(mud_expr_evaluator_t * evaluator, unsigned i) {
  if ( evaluator->argc > i ) {
    return evaluator->args[i];
  } else {
    return mud_nil_init();
  }
}

const char * mud_expr_evaluator_get_str_format(mud_expr_evaluator_t * evaluator, unsigned i, const char * fmt) {
  mud_object_t * arg = _mud_expr_evaluator_get(evaluator, i);
  size_t len = _mud_object_try_cast_snprintf(arg, NULL, 0, fmt);
  char * ret = (char *)_mud_object_casting_pool_malloc(evaluator->pool, (len + 1) * sizeof(char));
  _mud_object_try_cast_sprintf(arg, ret, fmt);
  return ret;
}

const char * mud_expr_evaluator_get_str(mud_expr_evaluator_t * evaluator, unsigned i) {
  mud_object_t * arg = _mud_expr_evaluator_get(evaluator, i);
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
  mud_object_t * arg = _mud_expr_evaluator_get(evaluator, i);
  switch ( arg->type ) {
    case MUD_OBJ_TYPE_STRING:
      return 1;
    case MUD_OBJ_TYPE_INT:
      return ( (*(mud_int_t *)arg->ptr) != 0 );
    case MUD_OBJ_TYPE_FLOAT:
      return ( (*(mud_float_t *)arg->ptr) != 0.0 );
    case MUD_OBJ_TYPE_BOOLEAN:
      return *(mud_boolean_t *)arg->ptr;
    case MUD_OBJ_TYPE_NIL:
      return 0;
    default:
      mud_warning("casting Type:%lu as mud_boolean, return false", arg->type);
      return 0;
  }
}

mud_int_t mud_expr_evaluator_get_int(mud_expr_evaluator_t * evaluator, unsigned i) {
  mud_object_t * arg = _mud_expr_evaluator_get(evaluator, i);
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
  mud_object_t * arg = _mud_expr_evaluator_get(evaluator, i);
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