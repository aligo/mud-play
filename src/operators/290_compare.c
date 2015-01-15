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
  mud_object_t * arg_0 = ME_ARG(0);
  mud_object_t * ret = mud_boolean_init(true);
  switch ( arg_0->type ) {
    case MUD_OBJ_TYPE_INT:
      *(mud_boolean_t *)ret->ptr = ( ME_ARG_INT(0) == ME_ARG_INT(1) );
      break;
    case MUD_OBJ_TYPE_FLOAT:
      *(mud_boolean_t *)ret->ptr = ( ME_ARG_FLOAT(0) == ME_ARG_FLOAT(1) );
      break;
    case MUD_OBJ_TYPE_STRING:
    default:
      *(mud_boolean_t *)ret->ptr = ( strcmp( ME_ARG_STR(0), ME_ARG_STR(1) ) == 0 );
      break;
  }
  return ret;
}
