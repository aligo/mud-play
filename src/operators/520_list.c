/*
  list
    - leach:    520
    - lmap:     521
    - lreduce:  522
    - lfilter:  523
    - lreject:  524
    - lsort_by: 525
    - lsort:    526
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

mud_object_t * _mud_op_list_filter_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 523
  mud_object_t * org = ME_ARG(0);
  mud_list_t * list = (mud_list_t *)org->ptr;
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
  ret->ptr = mud_list_alloc();
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t ** args = (mud_object_t **)malloc(2 * sizeof(mud_object_t *));
  for ( unsigned i = 0; i < list->count; i++ ) {
    args[0] = list->objects[i];
    args[1] = mud_int_init(i);
    if ( mud_object_try_cast_boolean(evaluator->pool, _mud_lambda_object_apply(ME_ARG(1), new_scope, args, 2)) ) {
      mud_list_append((mud_list_t *)ret->ptr, list->objects[i]); 
    }
  }
  mud_scope_free(new_scope);
  free(args);
  return ret;
}

mud_object_t * _mud_op_list_reject_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 524
  mud_object_t * org = ME_ARG(0);
  mud_list_t * list = (mud_list_t *)org->ptr;
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
  ret->ptr = mud_list_alloc();
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t ** args = (mud_object_t **)malloc(2 * sizeof(mud_object_t *));
  for ( unsigned i = 0; i < list->count; i++ ) {
    args[0] = list->objects[i];
    args[1] = mud_int_init(i);
    if ( ! mud_object_try_cast_boolean(evaluator->pool, _mud_lambda_object_apply(ME_ARG(1), new_scope, args, 2)) ) {
      mud_list_append((mud_list_t *)ret->ptr, list->objects[i]); 
    }
  }
  mud_scope_free(new_scope);
  free(args);
  return ret;
}

mud_object_t * _mud_op_list_sort_by_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 525
  mud_object_t * ret = ME_ARG(0);
  mud_list_t * list = (mud_list_t *)ret->ptr;
  mud_list_sort_by_t ** sort_bies = (mud_list_sort_by_t **)malloc(list->count * sizeof(mud_list_sort_by_t *));
  mud_object_type_e sort_by_type;
  mud_object_t * sort_by_object;
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t ** args = (mud_object_t **)malloc(2 * sizeof(mud_object_t *));

  for ( unsigned i = 0; i < list->count; i++ ) {
    if ( i == 0 ) {
      sort_by_type = list->objects[i]->type;
    }
    if ( ME_ARGC > 1 ) {
      args[0] = list->objects[i];
      args[1] = mud_int_init(i);
      sort_by_object = _mud_lambda_object_apply(ME_ARG(1), new_scope, args, 2);
    } else {
      sort_by_object = list->objects[i];
    }
    sort_bies[i] = (mud_list_sort_by_t *)mud_list_sort_by_alloc(sort_by_object, evaluator->pool, sort_by_type);
    sort_bies[i]->object = list->objects[i];
  }

  mud_list_sort_bies_sort(sort_bies, list->count, sort_by_type);
  
  for ( unsigned i = 0; i < list->count; i++ ) {
    list->objects[i] = sort_bies[i]->object;
    free(sort_bies[i]);
  }
  free(sort_bies);
  mud_scope_free(new_scope);
  free(args);
  return ret;
}

mud_object_t * _mud_op_list_sort_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 526
  if ( ME_ARGC > 1 ) {
    mud_object_t * ret = ME_ARG(0);
    mud_list_t * list = (mud_list_t *)ret->ptr;
    _mud_list_sort_scope = mud_scope_push(evaluator->scope);
    _mud_list_sort_args = (mud_object_t **)malloc(2 * sizeof(mud_object_t *));
    _mud_list_sort_lambda = ME_ARG(1);
    _mud_list_sort_pool = evaluator->pool;
    qsort(list->objects, list->count, sizeof(mud_object_t *), _mud_list_sort_by_compare_lambda);
    mud_scope_free(_mud_list_sort_scope);
    free(_mud_list_sort_args);
    return ret;
  } else {
    return _mud_op_list_sort_by_evaluate(evaluator);
  }
}

mud_object_t * _mud_op_list_all_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 527
  mud_object_t * org = ME_ARG(0);
  mud_list_t * list = (mud_list_t *)org->ptr;
  mud_boolean_t ret = true;
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t ** args = (mud_object_t **)malloc(2 * sizeof(mud_object_t *));
  for ( unsigned i = 0; i < list->count; i++ ) {
    args[0] = list->objects[i];
    args[1] = mud_int_init(i);
    ret = ret && mud_object_try_cast_boolean(evaluator->pool, _mud_lambda_object_apply(ME_ARG(1), new_scope, args, 2));
    if ( !ret ) {
      break;
    }
  }
  mud_scope_free(new_scope);
  free(args);
  return mud_boolean_init(ret);
}

mud_object_t * _mud_op_list_any_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 528
  mud_object_t * org = ME_ARG(0);
  mud_list_t * list = (mud_list_t *)org->ptr;
  mud_boolean_t ret = false;
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t ** args = (mud_object_t **)malloc(2 * sizeof(mud_object_t *));
  for ( unsigned i = 0; i < list->count; i++ ) {
    args[0] = list->objects[i];
    args[1] = mud_int_init(i);
    ret = ret || mud_object_try_cast_boolean(evaluator->pool, _mud_lambda_object_apply(ME_ARG(1), new_scope, args, 2));
    if ( ret ) {
      break;
    }
  }
  mud_scope_free(new_scope);
  free(args);
  return mud_boolean_init(ret);
}