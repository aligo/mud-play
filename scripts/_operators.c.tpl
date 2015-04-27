
mud_object_t * _mud_expr_evaluate(mud_expr_t * expr, mud_scope_t * scope, mud_gc_stack_t * stack) {
  mud_object_t * ret;
  mud_expr_evaluator_t * evaluator = mud_expr_evaluator_init(expr, scope, stack);
  
  switch (expr->oper) {
// auto-generated: switch - begin
// auto-generated: switch - end
    default:
      mud_error("Unknown operator: %lu", expr->oper);
      ret = mud_nil_init(stack);
      break;
  }

  mud_expr_evaluator_free(evaluator);
  return ret;
}
