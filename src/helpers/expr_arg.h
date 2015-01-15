// const char * mud_expr_evaluator_get_str_format(mud_expr_evaluator_t * evaluator, unsigned i, const char * fmt) {
//   return mud_object_try_cast_str_format(evaluator->pool, _mud_expr_evaluator_get(evaluator, i), fmt);
// }

// const char * mud_expr_evaluator_get_str(mud_expr_evaluator_t * evaluator, unsigned i) {
//   return mud_object_try_cast_str(evaluator->pool, _mud_expr_evaluator_get(evaluator, i));
// }

// mud_boolean_t mud_expr_evaluator_get_boolean(mud_expr_evaluator_t * evaluator, unsigned i) {
//   return mud_object_try_cast_boolean(evaluator->pool, _mud_expr_evaluator_get(evaluator, i));
// }

// mud_int_t mud_expr_evaluator_get_int(mud_expr_evaluator_t * evaluator, unsigned i) {
//   return mud_object_try_cast_int(evaluator->pool, _mud_expr_evaluator_get(evaluator, i));
// }

// mud_float_t mud_expr_evaluator_get_float(mud_expr_evaluator_t * evaluator, unsigned i) {
//   return mud_object_try_cast_float(evaluator->pool, _mud_expr_evaluator_get(evaluator, i));
// }

#define M_ARG_STR_FMT(I, FMT)   mud_object_try_cast_str_format(evaluator->pool, _mud_expr_evaluator_get(evaluator, I), FMT)
#define M_ARG_STR(I)            mud_object_try_cast_str(evaluator->pool, _mud_expr_evaluator_get(evaluator, I))
#define M_ARG_BOOLEAN(I)        mud_object_try_cast_boolean(evaluator->pool, _mud_expr_evaluator_get(evaluator, I))
#define M_ARG_INT(I)            mud_object_try_cast_int(evaluator->pool, _mud_expr_evaluator_get(evaluator, I))
#define M_ARG_FLOAT(I)          mud_object_try_cast_float(evaluator->pool, _mud_expr_evaluator_get(evaluator, I))