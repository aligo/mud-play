/*
  scope
    - sget: 120
    - sset: 121
*/

mud_object_t * _mud_op_scope_get_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 120
  return mud_scope_get(evaluator->scope, (char *)ME_ARG_STR(0));
}

mud_object_t * _mud_op_scope_set_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 121
  mud_scope_set(evaluator->scope, (char *)ME_ARG_STR(0), ME_ARG(1));
  return ME_ARG(1);
}
