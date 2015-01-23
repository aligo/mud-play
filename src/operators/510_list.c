/*
  list
    - lreverse:  510
    - lflatten:  511
*/

void _mud_list_object_flatten(mud_list_t * new_list, mud_list_t * cur_list, mud_boolean_t shallow, mud_boolean_t first_level) {
  for ( unsigned i = 0; i < cur_list->count; i++ ) {
    mud_object_t * obj = cur_list->objects[i];
    if ( ( first_level || shallow ) && ( obj->type == MUD_OBJ_TYPE_LIST ) ) {
      _mud_list_object_flatten(new_list, (mud_list_t *)obj->ptr, shallow, false);
    } else {
      mud_list_append(new_list, obj);
    }
  }
}

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

mud_object_t * _mud_op_list_flatten_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 511
  mud_object_t * ret = ME_ARG(0);
  mud_list_t * new_list = mud_list_alloc();
  _mud_list_object_flatten(new_list, (mud_list_t *)ret->ptr, ME_ARG_BOOLEAN(1), true);
  mud_list_free((mud_list_t *)ret->ptr);
  free((mud_list_t *)ret->ptr);
  ret->ptr = new_list;
  return ret;
}