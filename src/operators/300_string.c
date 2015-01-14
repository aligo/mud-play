/*
  string
    - concat: 300
    - format: 301
    - strlen_byte: 302
    - strstr_byte: 303
    - substr_byte: 304
    - strlen_byte: 305
*/

char * _mud_string_substr(const char * src, size_t start, size_t length) {
  char * ret = (char *)malloc((length + 1) * sizeof(char));
  memcpy(ret, &src[start], length);
  ret[length] = '\0';
  return ret;
}

int _mud_string_strlen_utf8(const char * s) {
  int i = 0, j = 0;
  while (s[i]) {
    if ((s[i] & 0xc0) != 0x80) j++;
    i++;
  }
  return j;
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
  ret->ptr = (char *)malloc((length + 1) * sizeof(char));
  size_t cpy_len = 0;
  length = 0;
  for ( unsigned i = 0; i < evaluator->argc; i++ ) {
    cpy_len = strlen(_strs[i]) * sizeof(char);
    memcpy(ret->ptr + length, _strs[i], cpy_len);
    length += cpy_len;
  }
  free(_strs);
  _strs = NULL;
  *(char *)(ret->ptr + length) = '\0';
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
  size_t partial_res_size = 0;
  size_t ret_old_size = 0;
  for ( size_t i = 0; i < (fmt_len + 1); i++ ) {
    if ( '%' == fmt[i] || i == fmt_len ) {
      if ( i > 0 ) {
        partial_fmt_len = i - s;
        partial_fmt = _mud_string_substr(fmt, s, partial_fmt_len);
        partial_res_size = _mud_expr_evaluator_snprintf(evaluator, partial_fmt_arg, NULL, 0, partial_fmt);
        ret_old_size = strlen((char *)ret->ptr) * sizeof(char);
        ret->ptr = (char *)realloc( ret->ptr, ret_old_size + partial_res_size);
        _mud_expr_evaluator_sprintf(evaluator, partial_fmt_arg, (char *)(ret->ptr + ret_old_size), partial_fmt);
        free(partial_fmt);
        partial_fmt = NULL;
      }
      partial_fmt_arg++;
      s = i;
    }
  }
  *(char *)(ret->ptr + ret_old_size + partial_res_size - 1) = '\0';
  return ret;
}

mud_object_t * _mud_op_string_strlen_byte_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 302
  return mud_int_init(
    strlen((char *)mud_expr_evaluator_get_str(evaluator, 0))
  );
}

mud_object_t * _mud_op_string_strstr_byte_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 303
  char * str = (char *)mud_expr_evaluator_get_str(evaluator, 0);
  char * ptr = strstr(str, (char *)mud_expr_evaluator_get_str(evaluator, 1));
  if ( ptr ) {
    return mud_int_init(ptr - str);
  } else {
    return mud_nil_init();
  }
}

mud_object_t * _mud_op_string_substr_byte_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 304
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_STRING);
  ret->ptr = _mud_string_substr((char *)mud_expr_evaluator_get_str(evaluator, 0), mud_expr_evaluator_get_int(evaluator, 1), mud_expr_evaluator_get_int(evaluator, 2));
  return ret;
}

mud_object_t * _mud_op_string_strlen_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 305
  return mud_int_init(
    _mud_string_strlen_utf8((char *)mud_expr_evaluator_get_str(evaluator, 0))
  );
}