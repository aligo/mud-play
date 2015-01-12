/*
  string
    - str_conact: 300
*/


mud_object_t * _mud_op_str_concat_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 300
  char ** _strs = (char **)malloc(evaluator->argc * sizeof(char *));
  size_t length = 0;
  for ( unsigned i = 0; i < evaluator->argc; i++ ) {
    _strs[i] = (char *)mud_expr_evaluator_get_str(evaluator, i);
    length += strlen(_strs[i]);
  }
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_STRING);
  ret->ptr = (char *)malloc(length * sizeof(char *));
  for ( unsigned i = 0; i < evaluator->argc; i++ ) {
    strcat(ret->ptr, _strs[i]);
  }
  free(_strs);
  return ret;
}