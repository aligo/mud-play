/*
  hash_table
    - ht:       600
    - htcount:  601
    - htget:    602
    - htset:    603
    - htkeys:   604
    - htvalues: 605
    - htpairs:  606
    - htmerge:  607
    - htinvert: 608
*/

mud_object_t * _mud_op_hash_table_ht_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 600
  mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_HASH_TABLE);
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
      key = mud_object_try_cast_str(evaluator->pool, arg);
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
  if ( _mud_hash_table_check(org) ) {
    return mud_int_init(evaluator->stack, HASH_COUNT((mud_hash_table_t *)org->ptr) );
  } else {
    return mud_int_init(evaluator->stack, 0);
  }
}

mud_object_t * _mud_op_hash_table_get_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 602
  mud_object_t * org = ME_ARG(0);
  if ( _mud_hash_table_check(org) ) {
    return mud_hash_table_get((mud_hash_table_t *)org->ptr, evaluator->stack, ME_ARG_STR(1));
  } else {
    return mud_nil_init(evaluator->stack);
  }
}

mud_object_t * _mud_op_hash_table_set_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 603
  mud_object_t * org = ME_ARG(0);
  if ( _mud_hash_table_check(org) ) {
    org->ptr = mud_hash_table_set((mud_hash_table_t *)org->ptr, ME_ARG_STR(1), ME_ARG(2));
    return org;
  } else {
    return mud_nil_init(evaluator->stack);
  }
}

mud_object_t * _mud_op_hash_table_keys_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 604
  mud_object_t * org = ME_ARG(0);
  if ( _mud_hash_table_check(org) ) {
    mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_LIST);
    ret->ptr = mud_list_alloc();
    mud_hash_table_t * tmp, * cur_hash = NULL;
    HASH_ITER(hh, (mud_hash_table_t *)org->ptr, cur_hash, tmp) {
      mud_list_append((mud_list_t *)ret->ptr, mud_string_init(evaluator->stack, cur_hash->key));
    }
    return ret;
  } else {
    return mud_nil_init(evaluator->stack);
  }
}

mud_object_t * _mud_op_hash_table_values_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 605
  mud_object_t * org = ME_ARG(0);
  if ( _mud_hash_table_check(org) ) {
    mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_LIST);
    ret->ptr = mud_list_alloc();
    mud_hash_table_t * tmp, * cur_hash = NULL;
    HASH_ITER(hh, (mud_hash_table_t *)org->ptr, cur_hash, tmp) {
      mud_list_append((mud_list_t *)ret->ptr, cur_hash->value);
    }
    return ret;
  } else {
    return mud_nil_init(evaluator->stack);
  }
}

mud_object_t * _mud_op_hash_table_pairs_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 606
  mud_object_t * org = ME_ARG(0);
  if ( _mud_hash_table_check(org) ) {
    mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_LIST);
    ret->ptr = mud_list_alloc();
    mud_hash_table_t * tmp, * cur_hash = NULL;
    HASH_ITER(hh, (mud_hash_table_t *)org->ptr, cur_hash, tmp) {
      mud_object_t * pair = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_LIST);
      pair->ptr = mud_list_alloc();
      mud_list_append((mud_list_t *)pair->ptr, mud_string_init(evaluator->stack, cur_hash->key));
      mud_list_append((mud_list_t *)pair->ptr, cur_hash->value);
      mud_list_append((mud_list_t *)ret->ptr, pair);
    }
    return ret;
  } else {
    return mud_nil_init(evaluator->stack);
  }
}

mud_object_t * _mud_op_hash_table_merge_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 607
  mud_object_t * ret = ME_ARG(0);
  if ( _mud_hash_table_check(ret) ) {
    for ( unsigned i = 1; i < ME_ARGC; i++ ) {
      mud_hash_table_t * tmp, * cur_hash = NULL;
      mud_object_t * org = ME_ARG(i);
      HASH_ITER(hh, (mud_hash_table_t *)org->ptr, cur_hash, tmp) {
        ret->ptr = mud_hash_table_set(ret->ptr, cur_hash->key, cur_hash->value);
      }
    }
  }
  return ret;
}

mud_object_t * _mud_op_hash_table_invert_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 608
  mud_object_t * org = ME_ARG(0);
  if ( _mud_hash_table_check(org) ) {
    mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_HASH_TABLE);
    ret->ptr = mud_hash_table_alloc();
    mud_hash_table_t * tmp, * cur_hash = NULL;
    HASH_ITER(hh, (mud_hash_table_t *)org->ptr, cur_hash, tmp) {
      ret->ptr = mud_hash_table_set(ret->ptr, mud_object_try_cast_str(evaluator->pool, cur_hash->value), mud_string_init(evaluator->stack, cur_hash->key));
    }
    return ret;
  } else {
    return mud_nil_init(evaluator->stack);
  }
}
