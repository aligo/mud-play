char * _mud_regmatch_get_str(regmatch_t * groups, const char * to_match, unsigned i) {
  regoff_t start = groups[i].rm_so;
  regoff_t end = groups[i].rm_eo;
  size_t len = end - start;
  char * str = (char *)malloc((len + 1) * sizeof(char));
  strncpy(str, to_match + start, len);
  str[len] = '\0';
  return str;
}