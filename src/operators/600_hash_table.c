/*
  hash_table
    - ht:       600
*/

mud_object_t * _mud_op_hash_table_ht_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 600
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_HASH_TABLE);
  ret->ptr = NULL;
  for ( unsigned i = 0; i < ME_ARGC; i++ ) {
    mud_object_t * arg = ME_ARG(i);
    const char * key;
    mud_object_t * value;
    if ( arg->type == MUD_OBJ_TYPE_NIL ) {
      continue;
    } else if ( arg->type == MUD_OBJ_TYPE_LIST ) {
      mud_list_t * list = (mud_list_t *)arg->ptr;
      key = mud_object_try_cast_str(evaluator->pool, list->objects[0]);
      value = list->objects[1];
    } else {
      key = ME_ARG_STR(i);
      value = ME_ARG(i + 1);
      i += 1;
    }
    ret->ptr = mud_hash_table_set(ret->ptr, key, value);
  }
  return ret;
}