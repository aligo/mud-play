/*
  lambda
    - lambda: 130
    - apply:  131
*/

mud_object_t * _mud_op_lambda_lambda_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 130
  mud_object_t * ret = mud_lambda_init(evaluator->stack);
  mud_lambda_t * lambda = (mud_lambda_t *)ret->ptr;
  if ( ME_ARGC > 1 ) {
    lambda->block = _ME_ORG(1);
    mud_object_t * largs = ME_ARG(0);
    if ( _mud_list_check(largs) ) {
      mud_list_t * largs_names = (mud_list_t *)largs->ptr;
      char ** args_names = (char **)malloc(largs_names->count * sizeof(char *));
      for ( unsigned i = 0; i < largs_names->count; i++ ) {
        args_names[i] = strdup((char *)mud_object_try_cast_str(evaluator->pool, largs_names->objects[i]));
      }
      _mud_lambda_set_args_names(lambda, largs_names->count, args_names);
    } else {
      mud_warning("Lambda arguments list is not a list. (Type: %d)", largs->type);
    }
  } else {
    lambda->block = _ME_ORG(0);
  }
  return ret;
}

mud_object_t * _mud_op_lambda_apply_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 131
  size_t argc = ME_ARGC - 1;
  mud_object_t ** args = (mud_object_t **)malloc(argc * sizeof(mud_object_t *));
  for ( unsigned i = 0; i < argc; i++ ) {
    args[i] = ME_ARG(i + 1);
  }
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t * ret = _mud_lambda_object_apply(ME_ARG(0), new_scope, evaluator->stack, args, argc);
  mud_scope_free(new_scope);
  free(args);
  return ret;
}
