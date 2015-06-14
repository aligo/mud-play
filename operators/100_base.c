/*
  base
    - quote:  100
    - eval:   101
    - expr:   102
    - eargs:  103
*/

mud_object_t * _mud_op_base_quote_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 100
  if ( ME_ARGC == 1 ) {
    return _ME_ORG(0);
  } else {
    mud_object_t ** exprs = malloc(ME_ARGC * sizeof(mud_object_t *));
    for ( size_t i = 0; i < ME_ARGC; i++ ) {
      exprs[i] = _ME_ORG(i);
    }
    return mud_exprs_init(evaluator->stack, exprs, ME_ARGC);
  }
}

mud_object_t * _mud_op_base_eval_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 101
  return mud_evaluate(ME_ARG(0), evaluator->scope, evaluator->stack);
}

mud_object_t * _mud_op_base_expr_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 102
  size_t argc = 0;
  size_t args_size = ME_ARGC - 1;
  mud_object_t ** args = (mud_object_t **)malloc(args_size * sizeof(mud_object_t *));
  mud_object_t * org;
  for (unsigned i = 1; i < ME_ARGC; i++) {
    org = _ME_ORG(i);
    if ( org->type == MUD_OBJ_TYPE_EXPR ) {
      mud_expr_t * expr = (mud_expr_t *)org->ptr;
      if ( expr->oper == MUD_OP_BASE_EARGS ) {
        args_size += expr->argc - 1;
        args = (mud_object_t ** )realloc(args, args_size * sizeof(mud_object_t *));
        for (unsigned j = 0; j < expr->argc; j++) {
          mud_object_t * earg = mud_evaluate(expr->args[j], evaluator->scope, evaluator->stack);
          if ( earg->type == MUD_OBJ_TYPE_LIST ) {
            mud_list_t * list = (mud_list_t *)earg->ptr;
            args_size += list->count - 1;
            args = (mud_object_t ** )realloc(args, args_size * sizeof(mud_object_t *));
            for (unsigned k = 0; k < list->count; k++) {
              args[argc++] = list->objects[k];
            }
          } else {
            args[argc++] = earg;
          }
        }
      } else {
        args[argc++] = org;
      }
    } else {
      args[argc++] = org;
    }
  }
  mud_object_t * expr = mud_expr_init(evaluator->stack, (int)ME_ARG_INT(0), args, argc);
  return mud_evaluate(expr, evaluator->scope, evaluator->stack);
}

mud_object_t * _mud_op_base_eargs_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 103
  return _ME_ORG(0);
}