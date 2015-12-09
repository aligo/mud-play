/*
  string
    - concat: 300
    - format: 301
    - strlen_byte: 302
    - strstr_byte: 303
    - substr_byte: 304
    - strlen: 305
    - strstr: 306
    - substr: 307
    - strrep: 308
    - join:   309
*/

char * _mud_string_substr(const char * src, size_t start, size_t length) {
  char * ret = (char *)malloc((length + 1) * sizeof(char));
  memcpy(ret, &src[start], length);
  ret[length] = '\0';
  return ret;
}

size_t _mud_string_strlen_utf8(const char * s) {
  size_t i = 0, j = 0;
  while (s[i]) {
    if ((s[i] & 0xc0) != 0x80) j++;
    i++;
  }
  return j;
}

mud_int_t _mud_string_strstr_utf8(const char * str, const char * search) {
  char * ptr = strstr(str, search);
  if ( ptr ) {
    char * part = _mud_string_substr(str, 0, ptr - str);
    size_t len = _mud_string_strlen_utf8(part);
    free(part);
    return len;
  } else {
    return -1;
  }
}

char * _mud_string_substr_utf8(const char * str, size_t start, size_t length) {
  size_t i = 0, j = 0, s = start, l = length;
  while (str[i]) {
    if ( j == start ) s = i;
    if ((str[i] & 0xc0) != 0x80) j++;
    i++;
    if ( j == ( start + length + 1 ) ) {
      l = i - s - 1;
      break;
    }
  }
  return _mud_string_substr(str, s, l);
}

char * _mud_string_strrep(const char * str, const char * search, const char * replace, mud_boolean_t all) {
  char * ptr = strstr(str, search);
  if ( ptr ) {
    char * _str = (char *)str;
    char * ret = NULL;
    size_t r_len = strlen(replace);
    size_t s_len = strlen(search);
    int need_free_str = 0;
    do {
      size_t str_len = strlen(_str);
      size_t ret_len = str_len - s_len + r_len;
      ret = (char *)malloc( (ret_len + 1) * sizeof(char));
      char * suf = (char *)&_str[ptr - _str + s_len * sizeof(char)];
      size_t suf_start = ptr - _str + r_len * sizeof(char);
      memcpy(ret, _str, ( ptr - _str ));
      memcpy((char *)&ret[ptr - _str], replace, r_len * sizeof(char));
      memcpy((char *)&ret[suf_start], suf, str_len * sizeof(char) - ( suf - _str ) );
      ret[ret_len] = '\0';
      if ( all ) {
        if ( need_free_str ) {
          free(_str);
        }
        _str = ret;
        ptr = strstr((char *)&_str[suf_start], search);
        if ( ptr ) {
          _str = strdup(ret);
          need_free_str = 1;
          ptr = ptr - ret + _str;
          free(ret);
        }
      } else {
        ptr = NULL;
      }
    } while ( ptr );
    return ret;
  } else {
    return (char *)str;
  }
}

mud_object_t * _mud_op_string_concat_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 300
  size_t * _strs_len = (size_t *)malloc(ME_ARGC * sizeof(size_t));
  char ** _strs = (char **)malloc(ME_ARGC * sizeof(char *));
  size_t length = 0;
  for ( unsigned i = 0; i < ME_ARGC; i++ ) {
    _strs[i] = (char *)ME_ARG_STR(i);
    _strs_len[i] = strlen(_strs[i]);
    length += _strs_len[i];
  }
  mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_STRING);
  ret->ptr = (char *)malloc((length + 1) * sizeof(char));
  size_t cpy_len = 0;
  length = 0;
  for ( unsigned i = 0; i < ME_ARGC; i++ ) {
    cpy_len = _strs_len[i] * sizeof(char);
    memcpy(ret->ptr + length, _strs[i], cpy_len);
    length += cpy_len;
  }
  free(_strs);
  free(_strs_len);
  _strs_len = NULL; 
  _strs = NULL;
  *(char *)(ret->ptr + length) = '\0';
  return ret;
}

mud_object_t * _mud_op_string_format_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 301
  mud_object_t * ret = mud_string_init(evaluator->stack, "");
  char * fmt = (char *)ME_ARG_STR(0);
  size_t fmt_len = strlen(fmt);

  size_t s = 0;
  unsigned partial_fmt_arg = 0;
  size_t partial_fmt_len = 0;
  char * partial_fmt = NULL;
  size_t partial_res_size = 0;
  size_t ret_old_size = 0;
  for ( size_t i = 0; i < (fmt_len + 1); i++ ) {
    if ( '%' == fmt[i] || i == fmt_len ) {
      if ( i > 0 ) {
        mud_object_t * arg = ME_ARG(partial_fmt_arg);
        partial_fmt_len = i - s;
        partial_fmt = _mud_string_substr(fmt, s, partial_fmt_len);
        partial_res_size = ( _mud_object_try_cast_snprintf(arg, NULL, 0, partial_fmt) + 1 ) * sizeof(char);
        ret_old_size = strlen((char *)ret->ptr) * sizeof(char);
        ret->ptr = (char *)realloc( ret->ptr, ret_old_size + partial_res_size );
        _mud_object_try_cast_sprintf(arg, (char *)(ret->ptr + ret_old_size), partial_fmt);
        free(partial_fmt);
        partial_fmt = NULL;
      }
      partial_fmt_arg++;
      s = i;
    }
  }
  // *(char *)(ret->ptr + ret_old_size + partial_res_size ) = '\0';
  return ret;
}

mud_object_t * _mud_op_string_strlen_byte_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 302
  return mud_int_init(evaluator->stack, 
    strlen((char *)ME_ARG_STR(0))
  );
}

mud_object_t * _mud_op_string_strstr_byte_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 303
  char * str = (char *)ME_ARG_STR(0);
  char * ptr = strstr(str, (char *)ME_ARG_STR(1));
  if ( ptr ) {
    return mud_int_init(evaluator->stack, ptr - str);
  } else {
    return mud_nil_init(evaluator->stack);
  }
}

mud_object_t * _mud_op_string_substr_byte_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 304
  mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_STRING);
  ret->ptr = _mud_string_substr((char *)ME_ARG_STR(0), ME_ARG_INT(1), ME_ARG_INT(2));
  return ret;
}

mud_object_t * _mud_op_string_strlen_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 305
  return mud_int_init(evaluator->stack, 
    _mud_string_strlen_utf8((char *)ME_ARG_STR(0))
  );
}

mud_object_t * _mud_op_string_strstr_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 306
  mud_int_t pos = _mud_string_strstr_utf8((char *)ME_ARG_STR(0), (char *)ME_ARG_STR(1));
  if ( pos == -1 ) {
    return mud_nil_init(evaluator->stack);
  } else {
    return mud_int_init(evaluator->stack, pos);
  }
}

mud_object_t * _mud_op_string_substr_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 307
  mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_STRING);
  ret->ptr = _mud_string_substr_utf8((char *)ME_ARG_STR(0), ME_ARG_INT(1), ME_ARG_INT(2));
  return ret;
}

mud_object_t * _mud_op_string_strrep_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 308
  mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_STRING);
  ret->ptr = _mud_string_strrep((char *)ME_ARG_STR(0), (char *)ME_ARG_STR(1), (char *)ME_ARG_STR(2), ME_ARG_BOOLEAN(3));
  return ret;
}

mud_object_t * _mud_op_string_join_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 309
  size_t * _strs_len = (size_t *)malloc(ME_ARGC * sizeof(size_t));
  char ** _strs = (char **)malloc(ME_ARGC * sizeof(char *));
  size_t length = 0;
  for ( unsigned i = 0; i < ME_ARGC; i++ ) {
    _strs[i] = (char *)ME_ARG_STR(i);
    _strs_len[i] = strlen(_strs[i]);
    length += _strs_len[i];
  }
  length += _strs_len[0] * (ME_ARGC - 3);
  mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_STRING);
  ret->ptr = (char *)malloc((length + 1) * sizeof(char));
  size_t cpy_len = 0;
  length = 0;
  for ( unsigned i = 1; i < ME_ARGC; i++ ) {
    cpy_len = _strs_len[i] * sizeof(char);
    memcpy(ret->ptr + length, _strs[i], cpy_len);
    length += cpy_len;
    if ( i < (ME_ARGC - 1) ) {
      cpy_len = _strs_len[0] * sizeof(char);
      memcpy(ret->ptr + length, _strs[0], cpy_len);
      length += cpy_len;
    }
  }
  free(_strs);
  free(_strs_len);
  _strs_len = NULL; 
  _strs = NULL;
  *(char *)(ret->ptr + length) = '\0';
  return ret;
}
