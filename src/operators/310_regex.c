#import <regex.h>

/*
  regex
    - regex:        310
    - rtest:        311
    - rmatch:       312
    - rmatch_all:   313
*/

mud_object_t * _mud_op_regex_regex_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 310
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_REGEX);
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
    return mud_boolean_init(0);
  } else {
    return mud_boolean_init(1);
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
    return mud_boolean_init(0);
  } else {
    mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
    ret->ptr = mud_list_alloc();
    for ( unsigned i = 0; i < groups_count; i++ ) {
      unsigned start = groups[i].rm_so;
      unsigned end = groups[i].rm_eo;
      size_t len = end - start;
      char * str = (char *)malloc((len + 1) * sizeof(char));
      strncpy(str, to_match + start, len);
      str[len] = '\0';
      mud_object_t * matched = mud_object_alloc(MUD_OBJ_TYPE_STRING);
      matched->ptr = str;
      mud_list_append((mud_list_t *)ret->ptr, matched);
    }
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
    return mud_boolean_init(0);
  } else {
    mud_object_t * matched;
    mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
    ret->ptr = mud_list_alloc();
    mud_boolean_t sub_groups = ME_ARG_BOOLEAN(2);
    unsigned match_start = 0;
    do {
      if ( sub_groups ) {
        matched = mud_object_alloc(MUD_OBJ_TYPE_LIST);
        matched->ptr = mud_list_alloc();
      }
      for ( unsigned i = 0; i < groups_count; i++ ) {
        unsigned start = match_start + groups[i].rm_so;
        unsigned end = match_start + groups[i].rm_eo;
        size_t len = end - start;
        char * str = (char *)malloc((len + 1) * sizeof(char));
        strncpy(str, to_match + start, len);
        str[len] = '\0';
        if ( sub_groups ) {
          mud_object_t * sub = mud_object_alloc(MUD_OBJ_TYPE_STRING);
          sub->ptr = str;
          mud_list_append((mud_list_t *)matched->ptr, sub);
        } else {
          matched = mud_object_alloc(MUD_OBJ_TYPE_STRING);
          matched->ptr = str;
          break;
        }
      }
      mud_list_append((mud_list_t *)ret->ptr, matched);
      match_start += groups[0].rm_eo;
    } while ( regexec(regex, &to_match[match_start], groups_count, groups, 0) == 0 );
    return ret;
  }
}