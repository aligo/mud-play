mud_lambda_t * mud_lambda_alloc() {
  mud_lambda_t * lambda = (mud_lambda_t *)malloc(sizeof(mud_lambda_t));
  lambda->argc = 0;
  return lambda;
}

void mud_lambda_free(mud_lambda_t * lambda) {
  if ( lambda->argc > 0 ) {
    for ( unsigned i = 0; i < lambda->argc; i++ ) {
      free(lambda->args_names[i]);
    }
    free(lambda->args_names);
    lambda->args_names = NULL;
  }
  lambda->block = NULL;
}

void _mud_lambda_set_args_names(mud_lambda_t * lambda, size_t argc, char ** args_names) {
  lambda->argc = argc;
  lambda->args_names = args_names;
}

mud_object_t * mud_lambda_apply(mud_lambda_t * lambda, mud_scope_t * scope) {
  return mud_evaluate(lambda->block, scope);
}