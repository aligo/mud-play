mud_object_t * mud_evaluate(mud_object_t * object, mud_scope_t * scope, mud_gc_stack_t * stack) {
  switch ( object->type ) {
    case MUD_OBJ_TYPE_EXPR:
      if (_mud_expr_evaluate == NULL) {
        return mud_nil_init(stack);
      }
      return _mud_expr_evaluate(object->ptr, scope, stack);
    case MUD_OBJ_TYPE_EXPRS:
      return _mud_exprs_evaluate(object->ptr, scope, stack);
    default:
      return object;
  }
}

mud_object_t * _mud_exprs_evaluate(mud_exprs_t * exprs, mud_scope_t * scope, mud_gc_stack_t * stack) {
  mud_object_t * ret = mud_nil_init(stack);
  for ( unsigned i = 0; i < exprs->count; i++ ) {
    ret = mud_evaluate(exprs->exprs[i], scope, stack);
  }
  return ret;
}

#ifndef MUD_AUTO_INIT
  mud_object_t * (* _mud_expr_evaluate)(mud_expr_t * expr, mud_scope_t * scope, mud_gc_stack_t * stack) = NULL;
#endif