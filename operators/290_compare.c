/*
  compare
    - ==: 290
    - !=: 291
    - >:  292
    - <:  293
    - >=: 294
    - <=: 295
*/

mud_object_t * _mud_op_compare_eq_to_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 290
  return mud_boolean_init(evaluator->stack, mud_object_compare(evaluator, ME_ARG(0), ME_ARG(1)) == 0);
}

mud_object_t * _mud_op_compare_not_eq_to_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 291
  return mud_boolean_init(evaluator->stack, mud_object_compare(evaluator, ME_ARG(0), ME_ARG(1)) != 0);
}

mud_object_t * _mud_op_compare_gt_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 292
  return mud_boolean_init(evaluator->stack, mud_object_compare(evaluator, ME_ARG(0), ME_ARG(1)) > 0);
}

mud_object_t * _mud_op_compare_lt_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 293
  return mud_boolean_init(evaluator->stack, mud_object_compare(evaluator, ME_ARG(0), ME_ARG(1)) < 0);
}

mud_object_t * _mud_op_compare_gt_or_eq_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 294
  return mud_boolean_init(evaluator->stack, mud_object_compare(evaluator, ME_ARG(0), ME_ARG(1)) >= 0);
}

mud_object_t * _mud_op_compare_lt_or_eq_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 295
  return mud_boolean_init(evaluator->stack, mud_object_compare(evaluator, ME_ARG(0), ME_ARG(1)) <= 0);
}
