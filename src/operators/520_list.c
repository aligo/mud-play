/*
  list
    - leach:    520
    - lmap:     521
    - lreduce:  522
*/

mud_object_t * _mud_op_list_each_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 520
  mud_object_t * ret = ME_ARG(0);
  mud_object_t * _tmp;
  mud_list_t * list = (mud_list_t *)ret->ptr;
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t ** args = (mud_object_t **)malloc(2 * sizeof(mud_object_t *));
  for ( unsigned i = 0; i < list->count; i++ ) {
    args[0] = list->objects[i];
    args[1] = mud_int_init(i);
    _tmp = _mud_lambda_object_apply(ME_ARG(1), new_scope, args, 2); 
  }
  mud_scope_free(new_scope);
  free(args);
  return ret;
}

mud_object_t * _mud_op_list_map_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 521
  mud_object_t * org = ME_ARG(0);
  mud_list_t * list = (mud_list_t *)org->ptr;
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
  ret->ptr = mud_list_alloc();
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t ** args = (mud_object_t **)malloc(2 * sizeof(mud_object_t *));
  for ( unsigned i = 0; i < list->count; i++ ) {
    args[0] = list->objects[i];
    args[1] = mud_int_init(i);
    mud_list_append((mud_list_t *)ret->ptr, _mud_lambda_object_apply(ME_ARG(1), new_scope, args, 2)); 
  }
  mud_scope_free(new_scope);
  free(args);
  return ret;
}

mud_object_t * _mud_op_list_reduce_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 522
  mud_object_t * org = ME_ARG(0);
  mud_list_t * list = (mud_list_t *)org->ptr;
  mud_object_t * ret = ME_ARG(1);
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t ** args = (mud_object_t **)malloc(3 * sizeof(mud_object_t *));
  for ( unsigned i = 0; i < list->count; i++ ) {
    args[0] = ret;
    args[1] = list->objects[i];
    args[2] = mud_int_init(i);
    ret = _mud_lambda_object_apply(ME_ARG(2), new_scope, args, 3); 
  }
  mud_scope_free(new_scope);
  free(args);
  return ret;
}