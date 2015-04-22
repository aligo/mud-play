mud_object_t * mud_evaluate(mud_object_t * object, mud_scope_t * scope) {
  switch ( object->type ) {
    case MUD_OBJ_TYPE_EXPR:
      return _mud_expr_evaluate(object->ptr, scope);
    case MUD_OBJ_TYPE_EXPRS:
      return _mud_exprs_evaluate(object->ptr, scope);
    default:
      return object;
  }
}

mud_object_t * _mud_exprs_evaluate(mud_exprs_t * exprs, mud_scope_t * scope) {
  mud_object_t * ret = mud_nil_init();
  for ( unsigned i = 0; i < exprs->count; i++ ) {
    ret = mud_evaluate(exprs->exprs[i], scope);
  }
  return ret;
}

