/*
  scope
    - sget:   120
    - sset:   121
    - sarg:   122
    - aargc:  123
*/

mud_object_t * _mud_op_scope_get_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 120
  return mud_scope_get(evaluator->scope, evaluator->stack, (char *)ME_ARG_STR(0));
}

mud_object_t * _mud_op_scope_set_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 121
  mud_scope_set(evaluator->scope, (char *)ME_ARG_STR(0), ME_ARG(1));
  return ME_ARG(1);
}

mud_object_t * _mud_op_scope_arg_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 122
  return mud_scope_arg(evaluator->scope, evaluator->stack, ME_ARG_INT(0));
}
mud_object_t * _mud_op_scope_argc_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 123
  return mud_int_init(evaluator->stack, evaluator->scope->argc);
}