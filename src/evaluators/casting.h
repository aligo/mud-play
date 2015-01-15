#define MUD_OBJECT_CASTING_TMP_POOL_ALLOC_SIZE 128;

typedef struct mud_object_casting_pool_s mud_object_casting_pool_t;
struct mud_object_casting_pool_s {
  void **           pool;
  unsigned          size;
  unsigned          count;
};

mud_object_casting_pool_t * mud_object_casting_pool_init();
void mud_object_casting_pool_free(mud_object_casting_pool_t * pool);

void * _mud_object_casting_pool_malloc(mud_object_casting_pool_t * pool, size_t size);

int _mud_object_try_cast_snprintf(mud_object_t * object, char * ret, size_t n, const char * fmt);
int _mud_object_try_cast_sprintf(mud_object_t * object, char * ret, const char * fmt);

const char * mud_object_try_cast_str_format(mud_object_casting_pool_t * pool, mud_object_t * object, const char * fmt);
const char * mud_object_try_cast_str(mud_object_casting_pool_t * pool, mud_object_t * object);
mud_boolean_t mud_object_try_cast_boolean(mud_object_casting_pool_t * pool, mud_object_t * object);
mud_int_t mud_object_try_cast_int(mud_object_casting_pool_t * pool, mud_object_t * object);
mud_float_t mud_object_try_cast_float(mud_object_casting_pool_t * pool, mud_object_t * object);