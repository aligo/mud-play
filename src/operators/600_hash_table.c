/*
  hash_table
    - ht:       600
    - htcount:  601
    - htget:    602
    - htset:    603
*/

mud_object_t * _mud_op_hash_table_ht_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 600
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_HASH_TABLE);
  ret->ptr = mud_hash_table_alloc();
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

mud_object_t * _mud_op_hash_table_count_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 601
  mud_object_t * org = ME_ARG(0);
  return mud_int_init( HASH_COUNT((mud_hash_table_t *)org->ptr) );
}

mud_object_t * _mud_op_hash_table_get_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 602
  mud_object_t * org = ME_ARG(0);
  return mud_hash_table_get((mud_hash_table_t *)org->ptr, ME_ARG_STR(1));
}

mud_object_t * _mud_op_hash_table_set_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 603
  mud_object_t * org = ME_ARG(0);
  org->ptr = mud_hash_table_set((mud_hash_table_t *)org->ptr, ME_ARG_STR(1), ME_ARG(2));
  return org;
}