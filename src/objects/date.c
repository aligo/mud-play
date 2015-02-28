
mud_date_t * mud_date_alloc() {
  mud_date_t * date = (mud_date_t *)malloc(sizeof(mud_date_t));
  date->cal = MUD_DATE_CAL_COMMON;
  date->year = 1970;
  date->mon = 1;
  date->mday = 1;
  date->hour = 0;
  date->sec = 0;
  date->off = 0;
  return date;
}

mud_date_t * mud_date_alloc_from_timestamp(time_t timestamp) {
  mud_date_t * date = mud_date_alloc();
  struct tm * t = gmtime(&timestamp);
  date->year = t->tm_year + 1900;
  date->mon  = t->tm_mon + 1;
  date->mday = t->tm_mday;
  date->hour = t->tm_hour;
  date->sec  = t->tm_min * 60 + t->tm_sec;
  free(t);
  return date;
}

mud_date_t * mud_date_alloc_from_string(char * str) {
  mud_date_t * date = mud_date_alloc();
  regex_t * regex = (regex_t *)malloc(sizeof(regex_t));
  regcomp(regex, "^(-?[0-9]+)-([0-9]+)-([0-9]+)[T\\s]([0-9]+):([0-9]+):([0-9]+)[Z\\s]?(\\+|-)?(([0-9]{2}):?([0-9]{2}))?$", REG_EXTENDED);
  size_t groups_count = regex->re_nsub + 1;
  regmatch_t * groups = (regmatch_t *)malloc(groups_count * sizeof(regmatch_t));
  if ( regexec(regex, str, groups_count, groups, 0) == 0 ) {
    char * year = _mud_regmatch_get_str(groups, str, 1);
    date->year = atol(year);
    free(year);
    char * mon = _mud_regmatch_get_str(groups, str, 2);
    date->mon = atoi(mon);
    free(mon);
    char * mday = _mud_regmatch_get_str(groups, str, 3);
    date->mday = atoi(mday);
    free(mday);
    char * hour = _mud_regmatch_get_str(groups, str, 4);
    date->hour = atoi(hour);
    free(hour);
    char * min = _mud_regmatch_get_str(groups, str, 5);
    char * sec = _mud_regmatch_get_str(groups, str, 6);
    date->sec = atoi(min) * 60 + atoi(sec);
    free(min);
    free(sec);
    char * off_sign = _mud_regmatch_get_str(groups, str, 7);
    char * off_pre = _mud_regmatch_get_str(groups, str, 8);
    char * off_suf = _mud_regmatch_get_str(groups, str, 9);
    if ( ( strlen(off_sign) + strlen(off_pre) ) > 0 ) {
      mud_int_t off = atoi(off_pre) * 3600 + atoi(off_suf) * 60;
      if ( ( strlen(off_sign) > 0 ) && ( off_sign[0] == '-' ) ) {
        off = - off;
      }
      date->off = off;
      mud_date_adjust(date, -off);
    }
  }
  return date;
}

mud_int_t _mud_date_current_mon_mday_radix(mud_date_t * date) {
  if ( date->mon == 2 ) {
    if ( ( date->year % 4 == 0 ) && ( date->year % 100 != 0 ) ) {
      return 29;
    } else {
      return 28;
    }
  } else {
    if ( date->mon == 4 || date->mon == 6 || date->mon == 9 || date->mon == 11 ) {
      return 30;
    } else {
      return 31;
    }
  }
}

#define _mud_date_carry_onestep(low, high, radix, base) {   \
  if ( low > (radix - 1 + base) ) {                         \
    high += 1;                                              \
    low -= radix;                                           \
    next_carry = 1;                                         \
  } else if ( low < base ) {                                \
    high -= 1;                                              \
    low += radix;                                           \
    next_carry = 1;                                         \
  }                                                         \
}

#define _mud_date_carry_mon_mday(date) {                        \
  mud_int_t radix = _mud_date_current_mon_mday_radix(date);     \
  if ( date->mday > radix ) {                                   \
    date->mon += 1;                                             \
    date->mday -= radix;                                        \
    next_carry = 1;                                             \
  } else if ( date->mday < 1 ) {                                \
    date->mon -= 1;                                             \
    date->mday += _mud_date_current_mon_mday_radix(date);       \
  }                                                             \
}

void _mud_date_carry_all(mud_date_t * date) {
  mud_boolean_t next_carry = 0;
  _mud_date_carry_onestep(date->sec, date->hour, 3600, 0);
  _mud_date_carry_onestep(date->hour, date->mday, 24, 0);
  _mud_date_carry_mon_mday(date);
  _mud_date_carry_onestep(date->mon, date->year, 12, 1);
  if ( next_carry ) {
    _mud_date_carry_all(date);
  }
}

void mud_date_adjust(mud_date_t * date, mud_int_t adjust) { 
  date->sec += adjust;
  _mud_date_carry_all(date);
}

mud_int_t mud_date_to_timestamp(mud_date_t * date) {
  struct tm t = { 0 };
  t.tm_isdst = -1;
  t.tm_year = date->year - 1900;
  t.tm_mon = date->mon - 1;
  t.tm_mday = date->mday;
  t.tm_hour = date->hour;
  t.tm_min = date->sec / 60;
  t.tm_sec = date->sec % 60;
  return mktime(&t);
}
