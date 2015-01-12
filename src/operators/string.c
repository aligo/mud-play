/*
  string
    - str_conact: 300
*/


mud_object_t * _mud_op_str_concat_evaluate(mud_expr_t * expr) {
  // Enum: 300
  // char * _str;
  for ( unsigned i = 0; i < expr->argc; i++ ) {
    printf("%p\n", expr->args[i]);
  }
  mud_object_t * ret = mud_string_init("xxxx");
  return ret;
}