typedef enum {
  MUD_OBJ_TYPE_NIL      = 0,
  MUD_OBJ_TYPE_BOOLEAN  = 10,
  MUD_OBJ_TYPE_NUMBER   = 20,
  MUD_OBJ_TYPE_STRING   = 30,
  MUD_OBJ_TYPE_ARRAY    = 40,
  MUD_OBJ_TYPE_HASH     = 50
} mud_object_type_e;


typedef struct mud_object_s mud_object_t;
struct mud_object_s {
  mud_object_type_e type;
  void *ptr;
};

mud_object_t * mud_object_alloc(mud_object_type_e type);

mud_object_t * mud_nil_init();

mud_object_t * mud_number_init(mud_number_t value);

mud_object_t * mud_string_init(const char * value);