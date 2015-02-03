/*
  int
    - round:  210
    - floor:  211
    - ceil:   212
    - rand:   213
*/

mud_object_t * _mud_op_int_round_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 210
  return mud_int_init( 
    round( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_int_floor_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 211
  return mud_int_init( 
    floor( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_int_ceil_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 212
  return mud_int_init( 
    ceil( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_int_rand_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 213
  srand(time(NULL));
  if ( ME_ARGC > 0 ) {
    return mud_int_init( rand() % ME_ARG_INT(0) );
  } else {
    return mud_float_init( (mud_float_t)rand() / (mud_float_t)RAND_MAX );
  }
}