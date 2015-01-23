/*
  list
    - lreverse:  510
*/

mud_object_t * _mud_op_list_reverse_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 510
  mud_object_t * ret = ME_ARG(0);
  mud_list_t * old_list = (mud_list_t *)ret->ptr;
  mud_list_t * new_list = mud_list_alloc();
  for ( unsigned i = old_list->count; i > 0; ) {
    mud_list_append(new_list, old_list->objects[--i]);
  }
  mud_list_free(old_list);
  free(old_list);
  ret->ptr = new_list;
  return ret;
}

