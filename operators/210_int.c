/*
  int
    - round:  210
    - floor:  211
    - ceil:   212
    - rand:   213
    - srand:  214
*/

mud_object_t * _mud_op_int_round_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 210
  return mud_int_init(evaluator->stack, 
    round( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_int_floor_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 211
  return mud_int_init(evaluator->stack, 
    floor( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_int_ceil_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 212
  return mud_int_init(evaluator->stack, 
    ceil( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_int_rand_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 213
  if ( ME_ARGC > 0 ) {
    return mud_int_init(evaluator->stack, rand() % ME_ARG_INT(0) );
  } else {
    return mud_float_init(evaluator->stack, (mud_float_t)rand() / (mud_float_t)RAND_MAX );
  }
}

mud_object_t * _mud_op_int_srand_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 214
  srand((int)time(NULL));
  return _mud_op_int_rand_evaluate(evaluator);
}