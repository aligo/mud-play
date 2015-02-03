/*
  float
    - **: 205
    - abs: 206
    - log: 207
    - exp: 208

    - cos: 220
    - sin: 221
    - tan: 222
    - acos: 223
    - asin: 224
    - atan: 225
    - atan2: 226
    - log10: 227
    - log1p: 228
    - log2: 229
*/

mud_object_t * _mud_op_float_pow_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 205
  return mud_float_init( 
    pow( ME_ARG_FLOAT(0), ME_ARG_FLOAT(1) )
  );
}

mud_object_t * _mud_op_float_abs_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 206
  return mud_float_init( 
    fabs( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_float_log_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 207
  return mud_float_init( 
    log( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_float_exp_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 208
  return mud_float_init( 
    exp( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_float_cos_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 220
  return mud_float_init( 
    cos( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_float_sin_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 221
  return mud_float_init( 
    sin( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_float_tan_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 222
  return mud_float_init( 
    tan( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_float_acos_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 223
  return mud_float_init( 
    acos( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_float_asin_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 224
  return mud_float_init( 
    asin( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_float_atan_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 225
  return mud_float_init( 
    atan( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_float_atan2_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 226
  return mud_float_init( 
    atan2( ME_ARG_FLOAT(0), ME_ARG_FLOAT(1) )
  );
}

mud_object_t * _mud_op_float_log10_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 227
  return mud_float_init( 
    log10( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_float_log1p_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 228
  return mud_float_init( 
    log1p( ME_ARG_FLOAT(0) )
  );
}

mud_object_t * _mud_op_float_log2_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 229
  return mud_float_init( 
    log2( ME_ARG_FLOAT(0) )
  );
}

