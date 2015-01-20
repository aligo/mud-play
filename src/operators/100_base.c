/*
  base
    - quote: 100
    - eval: 101
    - expr: 102
*/

mud_object_t * _mud_op_base_quote_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 100
  return _ME_ORG(0);
}

mud_object_t * _mud_op_base_eval_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 101
  return mud_evaluate(ME_ARG(0), evaluator->scope);
}

mud_object_t * _mud_op_base_expr_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 102
  size_t argc = 0;
  size_t args_size = ME_ARGC - 1;
  mud_object_t ** args = (mud_object_t **)malloc(args_size * sizeof(mud_object_t *));
  mud_object_t * org;
  for (unsigned i = 1; i < ME_ARGC; i++) {
    org = _ME_ORG(i);
    if ( ( org->type == MUD_OBJ_TYPE_INT ) && ( *(mud_int_t *)org->ptr == 100 ) ) {
      i++;
      mud_object_t * n_org = ME_ARG(i);
      if ( n_org->type == MUD_OBJ_TYPE_LIST ) {
        mud_list_t * list = (mud_list_t *)n_org->ptr;
        args_size += -2 + list->count;
        args = (mud_object_t ** )realloc(args, args_size * sizeof(mud_object_t *));
        for (unsigned j = 0; j < list->count; j++) {
          args[argc++] = list->objects[j];
        }
      }
    } else {
      args[argc++] = org;
    }
  }
  mud_object_t * expr = mud_expr_init(ME_ARG_INT(0), args, argc);
  return mud_evaluate(expr, evaluator->scope);
}