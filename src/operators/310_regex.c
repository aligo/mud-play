#import <regex.h>

/*
  regex
    - regex:     310
    - rmatch:    311
*/

mud_object_t * _mud_op_regex_regex_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 310
  mud_object_t * ret = mud_object_alloc(MUD_OBJ_TYPE_REGEX);
  regex_t * regex = (regex_t *)malloc(sizeof(regex_t));
  regcomp(regex, ME_ARG_STR(0), REG_EXTENDED);
  ret->ptr = regex;
  return ret;
}

mud_object_t * _mud_op_regex_match_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 311
  mud_object_t * ret;
  mud_object_t * obj = ME_ARG(0);
  regex_t * regex = (regex_t *)obj->ptr;
  char * to_match = (char *)ME_ARG_STR(1);
  size_t groups_count = regex->re_nsub + 1;
  regmatch_t * groups = (regmatch_t *)malloc(groups_count * sizeof(regmatch_t));
  if ( regexec(regex, to_match, groups_count, groups, 0) != 0 ) {
    ret = mud_boolean_init(0);
  } else {
    ret = mud_object_alloc(MUD_OBJ_TYPE_LIST);
    mud_list_t * list = mud_list_alloc();
    for ( unsigned i = 0; i < groups_count; i++ ) {
      unsigned start = groups[i].rm_so;
      unsigned end = groups[i].rm_eo;
      size_t len = end - start;
      char * str = (char *)malloc((len + 1) * sizeof(char));
      strncpy(str, to_match + start, len);
      str[len] = '\0';
      mud_object_t * matched = mud_object_alloc(MUD_OBJ_TYPE_STRING);
      matched->ptr = str;
      mud_list_append(list, matched);
    }
    ret->ptr = list;
  }
  return ret;
}

