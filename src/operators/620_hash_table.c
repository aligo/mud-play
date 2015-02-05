/*
  hash_table
    - hteach:     620
    - htmap:      621
    - htsort_by:  625
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

mud_object_t * _mud_op_hash_table_sort_by_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 625
  mud_object_t * ret = ME_ARG(0);
  mud_hash_table_t * org_ht = (mud_hash_table_t *)ret->ptr;
  size_t org_ht_count = HASH_COUNT(org_ht);
  mud_list_sort_by_t ** sort_bies = (mud_list_sort_by_t **)malloc(org_ht_count * sizeof(mud_list_sort_by_t *));
  mud_object_type_e sort_by_type;
  mud_object_t * sort_by_object;
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t ** args = (mud_object_t **)malloc(2 * sizeof(mud_object_t *));

  mud_hash_table_t * tmp, * cur_hash = NULL;
  size_t i = 0;
  HASH_ITER(hh, org_ht, cur_hash, tmp) {
    if ( ME_ARGC > 1 ) {
      args[0] = mud_string_init(cur_hash->key);
      args[1] = cur_hash->value;
      sort_by_object = _mud_lambda_object_apply(ME_ARG(1), new_scope, args, 2);
    } else {
      sort_by_object = cur_hash->value;
    }
    if ( i == 0 ) {
      sort_by_type = sort_by_object->type;
    }
    sort_bies[i] = (mud_list_sort_by_t *)mud_list_sort_by_alloc(sort_by_object, evaluator->pool, sort_by_type);
    sort_bies[i]->object = (void *)cur_hash;
    i++;
  }

  mud_list_sort_bies_sort(sort_bies, org_ht_count, sort_by_type);

  ret->ptr = mud_hash_table_alloc();
  for ( unsigned i = 0; i <  org_ht_count; i++ ) {
    cur_hash = (mud_hash_table_t *)sort_bies[i]->object;
    ret->ptr = mud_hash_table_set(ret->ptr, cur_hash->key, cur_hash->value);
    free(sort_bies[i]);
  }
  mud_hash_table_free(org_ht);
  free(sort_bies);
  mud_scope_free(new_scope);
  free(args);
  return ret;
}