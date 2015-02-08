
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

mud_int_t mud_date_to_timestamp(mud_date_t * date) {
  struct tm t = { 0 };
  t.tm_isdst = -1;
  t.tm_year = date->year - 1900;
  t.tm_mon = date->mon - 1;
  t.tm_mday = date->mday;
  t.tm_hour = date->hour;
  t.tm_min = date->sec / 60;
  t.tm_sec = date->sec % 60;
  return mktime(&t) + date->off;
}
