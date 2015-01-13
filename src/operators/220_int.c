/*
  float
    - round: 210
    - floor: 211
    - ceil: 212
*/

mud_object_t * _mud_op_float_round_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 210
  return mud_int_init( 
    round( mud_expr_evaluator_get_float(evaluator, 0) )
  );
}

mud_object_t * _mud_op_float_floor_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 211
  return mud_int_init( 
    floor( mud_expr_evaluator_get_float(evaluator, 0) )
  );
}

mud_object_t * _mud_op_float_ceil_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 212
  return mud_int_init( 
    ceil( mud_expr_evaluator_get_float(evaluator, 0) )
  );
}