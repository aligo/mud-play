/*
  cond
    - cond:   110
    - if:     111
    - when:   112
    - unless: 113
*/

mud_object_t * _mud_op_cond_if_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 111
  if ( ME_ARG_BOOLEAN(0) ){
    return ME_ARG(1);
  } else {
    return ME_ARG(2);
  }
}

mud_object_t * _mud_op_cond_when_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 112
  return _mud_op_cond_if_evaluate(evaluator);
}

mud_object_t * _mud_op_cond_unless_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 113
  if ( ! ME_ARG_BOOLEAN(0) ){
    return ME_ARG(1);
  } else {
    return ME_ARG(2);
  }
}
