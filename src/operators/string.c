/*
  string
    - concat: 300
    - format: 301
*/

char * substr(const char * src, size_t start, size_t length) {
  char * ret = (char *)malloc((length + 1) * sizeof(char));
  memcpy(ret, &src[start], length);
  ret[length] = '\0';
  return ret;
} 

mud_object_t * _mud_op_string_concat_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 300
  char ** _strs = (char **)malloc(evaluator->argc * sizeof(char *));
  size_t length = 0;
  for ( unsigned i = 0; i < evaluator->argc; i++ ) {
    _strs[i] = (char *)mud_expr_evaluator_get_str(evaluator, i);
    length += strlen(_strs[i]);
  }
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_STRING);
  ret->ptr = (char *)malloc_empty(length * sizeof(char));
  for ( unsigned i = 0; i < evaluator->argc; i++ ) {
    strcat(ret->ptr, _strs[i]);
  }
  free(_strs);
  _strs = NULL;
  return ret;
}

mud_object_t * _mud_op_string_format_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 301
  mud_object_t * ret = mud_string_init("");
  
  char * fmt = (char *)mud_expr_evaluator_get_str(evaluator, 0);
  size_t fmt_len = strlen(fmt);

  size_t s = 0;
  unsigned partial_fmt_arg = 0;
  size_t partial_fmt_len = 0;
  char * partial_fmt;
  char * partial_res;
  size_t partial_res_size = 0;
  size_t ret_old_size = 0;
  for ( size_t i = 0; i < (fmt_len + 1); i++ ) {
    if ( '%' == fmt[i] || i == fmt_len ) {
      if ( i > 0 ) {
        partial_fmt_len = i - s;
        partial_fmt = substr(fmt, s, partial_fmt_len);
        partial_res = (char *)mud_expr_evaluator_sprintf(evaluator, partial_fmt, partial_fmt_arg);
        free(partial_fmt);
        partial_fmt = NULL;
        partial_res_size = strlen(partial_res) * sizeof(char) + 1;
        ret_old_size = strlen((char *)ret->ptr) * sizeof(char);
        ret->ptr = (char *)realloc( ret->ptr, ret_old_size + partial_res_size);
        memcpy(ret->ptr + ret_old_size, partial_res, partial_res_size);
      }
      partial_fmt_arg++;
      s = i;
    }
  }
  return ret;
}