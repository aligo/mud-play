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