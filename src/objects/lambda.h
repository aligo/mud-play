typedef struct mud_lambda_s mud_lambda_t;
struct mud_lambda_s {
  size_t argc;
  char ** args_names;
  mud_object_t * block;
};


mud_lambda_t * mud_lambda_alloc();
void mud_lambda_free(mud_lambda_t * lambda);