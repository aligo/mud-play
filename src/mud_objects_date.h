
#define MUD_DATE_YEAR_WILDCARD MUD_INT_MAX
#define MUD_DATE_YEAR_MIN MUD_INT_MIN
#define MUD_DATE_YEAR_MAX MUD_DATE_YEAR_WILDCARD - 1

#define MUD_DATE_MON_WILDCARD UCHAR_MAX
#define MUD_DATE_MON_MIN 0
#define MUD_DATE_MON_MAX MUD_DATE_MON_WILDCARD - 1

#define MUD_DATE_MDAY_WILDCARD UCHAR_MAX
#define MUD_DATE_MDAY_MIN 0
#define MUD_DATE_MDAY_MAX MUD_DATE_MDAY_WILDCARD - 1

#define MUD_DATE_HOUR_WILDCARD UCHAR_MAX
#define MUD_DATE_HOUR_MIN 0
#define MUD_DATE_HOUR_MAX MUD_DATE_HOUR_WILDCARD - 1

#define MUD_DATE_SEC_WILDCARD USHRT_MAX
#define MUD_DATE_SEC_MIN 0
#define MUD_DATE_SEC_MAX MUD_DATE_SEC_WILDCARD - 1

#define MUD_DATE_OFF_WILDCARD MUD_INT_MAX
#define MUD_DATE_OFF_MIN MUD_INT_MIN
#define MUD_DATE_OFF_MAX MUD_DATE_OFF_WILDCARD - 1

typedef enum {
  MUD_DATE_CAL_COMMON     = 0
} mud_date_cal_e;

typedef struct mud_date_s mud_date_t;
struct mud_date_s {
  mud_date_cal_e  cal;
  mud_int_t       year;
  mud_int_t       mon;
  mud_int_t       mday;
  mud_int_t       hour;
  mud_int_t       sec;
  mud_int_t       off;
};

mud_date_t * mud_date_alloc();
mud_date_t * mud_date_alloc_from_timestamp(time_t timestamp);
mud_date_t * mud_date_alloc_from_string(char * str);

mud_int_t _mud_date_current_mon_mday_radix(mud_date_t * date);
void _mud_date_carry_all(mud_date_t * date);

void mud_date_adjust(mud_date_t * date, mud_int_t adjust);
mud_int_t mud_date_to_timestamp(mud_date_t * date);