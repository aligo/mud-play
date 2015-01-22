/*
  lambda
    - lambda: 130
    - apply:  131
*/

mud_object_t * _mud_op_lambda_lambda_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 130
  mud_object_t * ret = mud_lambda_init();
  mud_lambda_t * lambda = (mud_lambda_t *)ret->ptr;
  if ( ME_ARGC > 1 ) {
    lambda->block = _ME_ORG(1);
  } else {
    lambda->block = _ME_ORG(0);
  }
  return ret;
}

mud_object_t * _mud_op_lambda_apply_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 131 
  mud_object_t * obj = ME_ARG(0);
  mud_lambda_t * lambda = (mud_lambda_t *)obj->ptr;
  mud_scope_t * new_scope = mud_scope_push(evaluator->scope);
  mud_object_t * ret = mud_lambda_apply(lambda, new_scope);
  mud_scope_free(new_scope);
  return ret;
}
