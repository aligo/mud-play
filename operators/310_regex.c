mud_object_t * _mud_op_regex_regex_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 310
  mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_REGEX);
  regex_t * regex = (regex_t *)malloc(sizeof(regex_t));
  regcomp(regex, ME_ARG_STR(0), REG_EXTENDED);
  ret->ptr = regex;
  return ret;
}

mud_object_t * _mud_op_regex_test_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 311
  mud_object_t * obj = ME_ARG(0);
  regex_t * regex = (regex_t *)obj->ptr;
  if ( regexec(regex, ME_ARG_STR(1), 0, NULL, 0) != 0 ) {
    return mud_boolean_init(evaluator->stack, 0);
  } else {
    return mud_boolean_init(evaluator->stack, 1);
  }
}

mud_object_t * _mud_op_regex_match_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 312
  mud_object_t * obj = ME_ARG(0);
  regex_t * regex = (regex_t *)obj->ptr;
  char * to_match = (char *)ME_ARG_STR(1);
  size_t groups_count = regex->re_nsub + 1;
  regmatch_t * groups = (regmatch_t *)malloc(groups_count * sizeof(regmatch_t));
  if ( regexec(regex, to_match, groups_count, groups, 0) != 0 ) {
    return mud_boolean_init(evaluator->stack, 0);
  } else {
    mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_LIST);
    ret->ptr = mud_list_alloc();
    for ( unsigned i = 0; i < groups_count; i++ ) {
      mud_object_t * matched = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_STRING);
      matched->ptr = _mud_regmatch_get_str(groups, to_match, i);
      mud_list_append((mud_list_t *)ret->ptr, matched);
    }
    free(groups);
    return ret;
  }
}

mud_object_t * _mud_op_regex_match_all_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 313
  mud_object_t * obj = ME_ARG(0);
  regex_t * regex = (regex_t *)obj->ptr;
  char * to_match = (char *)ME_ARG_STR(1);
  size_t groups_count = regex->re_nsub + 1;
  regmatch_t * groups = (regmatch_t *)malloc(groups_count * sizeof(regmatch_t));
  if ( regexec(regex, to_match, groups_count, groups, 0) != 0 ) {
    return mud_boolean_init(evaluator->stack, 0);
  } else {
    mud_object_t * matched;
    mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_LIST);
    ret->ptr = mud_list_alloc();
    mud_boolean_t sub_groups = ME_ARG_BOOLEAN(2);
    unsigned match_start = 0;
    do {
      if ( sub_groups ) {
        matched = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_LIST);
        matched->ptr = mud_list_alloc();
      } else {
        matched = obj;
      }
      for ( unsigned i = 0; i < groups_count; i++ ) {
        char * str = _mud_regmatch_get_str(groups, &to_match[match_start], i);
        if ( sub_groups ) {
          mud_object_t * sub = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_STRING);
          sub->ptr = str;
          mud_list_append((mud_list_t *)matched->ptr, sub);
        } else {
          matched = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_STRING);
          matched->ptr = str;
          break;
        }
      }
      mud_list_append((mud_list_t *)ret->ptr, matched);
      match_start += groups[0].rm_eo;
    } while ( regexec(regex, &to_match[match_start], groups_count, groups, 0) == 0 );
    free(groups);
    return ret;
  }
}

mud_object_t * _mud_op_regex_rep_all_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 314
  mud_object_t * obj = ME_ARG(0);
  regex_t * regex = (regex_t *)obj->ptr;
  char * to_match = (char *)ME_ARG_STR(1);
  size_t groups_count = regex->re_nsub + 1;
  regmatch_t * groups = (regmatch_t *)malloc(groups_count * sizeof(regmatch_t));
  if ( regexec(regex, to_match, groups_count, groups, 0) != 0 ) {
    return ME_ARG(1);
  } else {
    mud_object_t * ret = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_STRING);
    ret->ptr = strdup(to_match);
    size_t ret_len = strlen(ret->ptr);
    size_t cur_len = 0;
    unsigned ret_start = 0;
    unsigned match_start = 0;
    char * rep_str = NULL;
    size_t rep_len = 0;
    mud_object_t * rep_obj = ME_ARG(2);
    mud_scope_t * new_scope = NULL;
    mud_object_t ** args = NULL;
    if ( rep_obj->type == MUD_OBJ_TYPE_LAMBDA ) {
      new_scope = mud_scope_push(evaluator->scope);
      args = (mud_object_t **)malloc(groups_count * sizeof(mud_object_t *));
    } else {
      rep_str = (char *)ME_ARG_STR(2);
    }

    do {
      if ( new_scope && args ) {
        for ( unsigned i = 0; i < groups_count; i++ ) {
          mud_object_t * matched = mud_object_alloc(evaluator->stack, MUD_OBJ_TYPE_STRING);
          matched->ptr = _mud_regmatch_get_str(groups, &to_match[match_start], i);
          args[i] = matched;
        }
        rep_str = (char *)mud_object_try_cast_str(evaluator->pool, _mud_lambda_object_apply(rep_obj, new_scope, evaluator->stack, args, groups_count));
      }
      if ( rep_str ) {
        rep_len = strlen(rep_str);
      }

      cur_len += groups[0].rm_so + rep_len;
      if ( cur_len > ret_len ) {
        ret->ptr = realloc(ret->ptr, (cur_len + 1) * sizeof(char));
      }
      strncpy(&ret->ptr[ret_start], &to_match[match_start], groups[0].rm_so);
      strncpy(&ret->ptr[ret_start + groups[0].rm_so], rep_str, rep_len);
      match_start += groups[0].rm_eo;
      ret_start += groups[0].rm_so + rep_len;
    } while ( regexec(regex, &to_match[match_start], groups_count, groups, 0) == 0 );
    ((char *)ret->ptr)[cur_len] = '\0';
    if ( new_scope ) {
      mud_scope_free(new_scope);
      free(args);
    }
    free(groups);
    return ret;
  }
}