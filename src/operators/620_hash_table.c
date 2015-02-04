/*
  hash_table
    - hteach:     620
    - htmap:      621
*/


mud_object_t * _mud_op_hash_table_each_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 620
  mud_object_t * ret = ME_ARG(0);
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t ** args = (mud_object_t **)malloc(2 * sizeof(mud_object_t *));
  mud_hash_table_t * tmp, * cur_hash = NULL;
  HASH_ITER(hh, (mud_hash_table_t *)ret->ptr, cur_hash, tmp) {
    args[0] = mud_string_init(cur_hash->key);
    args[1] = cur_hash->value;
    _mud_lambda_object_apply(ME_ARG(1), new_scope, args, 2);
  }
  mud_scope_free(new_scope);
  free(args);
  return ret;
}

mud_object_t * _mud_op_hash_table_map_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 621
  mud_object_t * org = ME_ARG(0);
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_HASH_TABLE);
  ret->ptr = mud_hash_table_alloc();
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t ** args = (mud_object_t **)malloc(2 * sizeof(mud_object_t *));
  mud_hash_table_t * tmp, * cur_hash = NULL;
  HASH_ITER(hh, (mud_hash_table_t *)org->ptr, cur_hash, tmp) {
    args[0] = mud_string_init(cur_hash->key);
    args[1] = cur_hash->value;
    ret->ptr = mud_hash_table_set(ret->ptr, cur_hash->key, _mud_lambda_object_apply(ME_ARG(1), new_scope, args, 2));
  }
  mud_scope_free(new_scope);
  free(args);
  return ret;
}
