/*
  base
    - quote: 100
    - eval: 101
*/

mud_object_t * _mud_op_base_quote_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 100
  return _ME_ORG(0);
}

mud_object_t * _mud_op_base_eval_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 101
  return mud_evaluate(ME_ARG(0));
}
