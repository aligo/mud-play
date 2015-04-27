/*
  boolean
    - !: 190
    - &&: 191
    - ||: 192
*/

mud_object_t * _mud_op_boolean_not_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 190
  return mud_boolean_init(evaluator->stack, 
    ! ME_ARG_BOOLEAN(0)
  );
}

mud_object_t * _mud_op_boolean_and_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 191
  return mud_boolean_init(evaluator->stack, 
    ME_ARG_BOOLEAN(0) && ME_ARG_BOOLEAN(1)
  );
}

mud_object_t * _mud_op_boolean_or_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 192
  return mud_boolean_init(evaluator->stack, 
    ME_ARG_BOOLEAN(0) || ME_ARG_BOOLEAN(1)
  );
}