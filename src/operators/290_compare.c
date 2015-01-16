/*
  compare
    - ==: 290
    - !=: 291
    - >:  292
    - <:  293
    - >=: 294
    - <=: 295
*/

mud_boolean_t _mud_boolean_compare_eq_to_evaluate(mud_expr_evaluator_t * evaluator) {
  switch ( ME_ARG(0)->type ) {
    case MUD_OBJ_TYPE_INT:
      return ( ME_ARG_INT(0) == ME_ARG_INT(1) );
    case MUD_OBJ_TYPE_FLOAT:
      return ( ME_ARG_FLOAT(0) == ME_ARG_FLOAT(1) );
    case MUD_OBJ_TYPE_STRING:
    default:
      return ( strcmp( ME_ARG_STR(0), ME_ARG_STR(1) ) == 0 );
  }
}

mud_object_t * _mud_op_compare_eq_to_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 290
  return mud_boolean_init(_mud_boolean_compare_eq_to_evaluate(evaluator));
}

mud_object_t * _mud_op_compare_not_eq_to_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 291
  return mud_boolean_init(!_mud_boolean_compare_eq_to_evaluate(evaluator));
}

mud_object_t * _mud_op_compare_gt_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 292
  switch ( ME_ARG(0)->type ) {
    case MUD_OBJ_TYPE_INT:
      return mud_boolean_init( ME_ARG_INT(0) > ME_ARG_INT(1) );
    case MUD_OBJ_TYPE_FLOAT:
      return mud_boolean_init( ME_ARG_FLOAT(0) > ME_ARG_FLOAT(1) );
    case MUD_OBJ_TYPE_STRING:
    default:
      return mud_boolean_init( strcmp( ME_ARG_STR(0), ME_ARG_STR(1) ) > 0 );
  }
}

mud_object_t * _mud_op_compare_lt_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 293
  switch ( ME_ARG(0)->type ) {
    case MUD_OBJ_TYPE_INT:
      return mud_boolean_init( ME_ARG_INT(0) < ME_ARG_INT(1) );
    case MUD_OBJ_TYPE_FLOAT:
      return mud_boolean_init( ME_ARG_FLOAT(0) < ME_ARG_FLOAT(1) );
    case MUD_OBJ_TYPE_STRING:
    default:
      return mud_boolean_init( strcmp( ME_ARG_STR(0), ME_ARG_STR(1) ) < 0 );
  }
}

mud_object_t * _mud_op_compare_gt_or_eq_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 294
  switch ( ME_ARG(0)->type ) {
    case MUD_OBJ_TYPE_INT:
      return mud_boolean_init( ME_ARG_INT(0) >= ME_ARG_INT(1) );
    case MUD_OBJ_TYPE_FLOAT:
      return mud_boolean_init( ME_ARG_FLOAT(0) >= ME_ARG_FLOAT(1) );
    case MUD_OBJ_TYPE_STRING:
    default:
      return mud_boolean_init( strcmp( ME_ARG_STR(0), ME_ARG_STR(1) ) >= 0 );
  }
}

mud_object_t * _mud_op_compare_lt_or_eq_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 295
  switch ( ME_ARG(0)->type ) {
    case MUD_OBJ_TYPE_INT:
      return mud_boolean_init( ME_ARG_INT(0) <= ME_ARG_INT(1) );
    case MUD_OBJ_TYPE_FLOAT:
      return mud_boolean_init( ME_ARG_FLOAT(0) <= ME_ARG_FLOAT(1) );
    case MUD_OBJ_TYPE_STRING:
    default:
      return mud_boolean_init( strcmp( ME_ARG_STR(0), ME_ARG_STR(1) ) <= 0 );
  }
}
