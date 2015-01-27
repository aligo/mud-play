/*
  list
    - lreverse:           510
    - lflatten:           511
    - luniq:              512
    - lintersection:      513
    - ldifference:        514
    - lconcat:            515
    - lunion:             516
    - lhead:              517
    - ltail:              518
    - lslice:             519
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

mud_object_t * _mud_op_list_flatten_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 511
  mud_object_t * ret = ME_ARG(0);
  mud_list_t * new_list = mud_list_alloc();
  mud_list_flatten_to(new_list, (mud_list_t *)ret->ptr, ME_ARG_BOOLEAN(1), true);
  mud_list_free((mud_list_t *)ret->ptr);
  free((mud_list_t *)ret->ptr);
  ret->ptr = new_list;
  return ret;
}

mud_object_t * _mud_op_list_uniq_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 512
  mud_object_t * obj = ME_ARG(0);
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
  ret->ptr = mud_list_alloc_uniq((mud_list_t *)obj->ptr, evaluator->pool);
  return ret;
}

mud_object_t * _mud_op_list_intersection_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 513
  mud_object_t * a_obj = ME_ARG(0);
  mud_object_t * b_obj = ME_ARG(1);
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
  ret->ptr = mud_list_alloc_intersection((mud_list_t *)a_obj->ptr, (mud_list_t *)b_obj->ptr, evaluator->pool);
  return ret;
}

mud_object_t * _mud_op_list_difference_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 514
  mud_object_t * a_obj = ME_ARG(0);
  mud_object_t * b_obj = ME_ARG(1);
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
  ret->ptr = mud_list_alloc_difference((mud_list_t *)a_obj->ptr, (mud_list_t *)b_obj->ptr, evaluator->pool);
  return ret;
}

mud_object_t * _mud_op_list_concat_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 515
  mud_object_t * a_obj = ME_ARG(0);
  mud_object_t * b_obj = ME_ARG(1);
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
  ret->ptr = mud_list_alloc_concat((mud_list_t *)a_obj->ptr, (mud_list_t *)b_obj->ptr, evaluator->pool);
  return ret;
}

mud_object_t * _mud_op_list_union_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 516
  mud_object_t * a_obj = ME_ARG(0);
  mud_object_t * b_obj = ME_ARG(1);
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
  ret->ptr = mud_list_alloc_union((mud_list_t *)a_obj->ptr, (mud_list_t *)b_obj->ptr, evaluator->pool);
  return ret;
}

mud_object_t * _mud_op_list_head_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 517
  mud_object_t * org = ME_ARG(0);
  mud_list_t * list = (mud_list_t *)org->ptr;
  mud_int_t limit = ME_ARG_INT(1);

  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
  ret->ptr = mud_list_alloc();
  for ( unsigned i = 0; i < limit; i++) {
    mud_list_append((mud_list_t *)ret->ptr, list->objects[i]);
  }
  return ret;
}

mud_object_t * _mud_op_list_tail_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 518
  mud_object_t * org = ME_ARG(0);
  mud_list_t * list = (mud_list_t *)org->ptr;
  mud_int_t limit = ME_ARG_INT(1);

  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
  ret->ptr = mud_list_alloc();
  for ( unsigned i = list->count - limit; i < list->count; i++) {
    mud_list_append((mud_list_t *)ret->ptr, list->objects[i]);
  }
  return ret;
}

mud_object_t * _mud_op_list_slice_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 519
  mud_object_t * org = ME_ARG(0);
  mud_list_t * list = (mud_list_t *)org->ptr;
  mud_int_t start = ME_ARG_INT(1);
  mud_int_t end = ( ME_ARGC > 2 ) ? ME_ARG_INT(2) : list->count;
  
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
  ret->ptr = mud_list_alloc();
  for ( unsigned i = start; i < end; i++) {
    mud_list_append((mud_list_t *)ret->ptr, list->objects[i]);
  }
  return ret;
}