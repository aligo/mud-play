/*
  list
    - list: 500
*/


mud_object_t * _mud_op_list_list_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 500
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
  ret->ptr = mud_list_init();
  for ( unsigned i = 0; i < ME_ARGC; i++ ) {
    mud_list_append((mud_list_t *)ret->ptr, (mud_object_t *)ME_ARG(i));
  }
  return ret;
}
