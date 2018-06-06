
typedef struct mud_object_casting_pool_s mud_object_casting_pool_t;
struct mud_object_casting_pool_s {
  void *                        ptr;
  mud_object_casting_pool_t *   prev;
};

mud_object_casting_pool_t * mud_object_casting_pool_init();
void mud_object_casting_pool_free(mud_object_casting_pool_t * pool);

void * _mud_object_casting_pool_malloc(mud_object_casting_pool_t * pool, size_t size);

int _mud_object_try_cast_snprintf(mud_object_t * object, char * ret, size_t n, const char * fmt);
int _mud_object_try_cast_sprintf(mud_object_t * object, char * ret, const char * fmt);

const char * mud_object_try_cast_str_format(mud_object_casting_pool_t * pool, mud_object_t * object, const char * fmt);

const char * mud_object_try_cast_str_with_default(mud_object_casting_pool_t * pool, mud_object_t * object, const char * _default);
mud_boolean_t mud_object_try_cast_boolean_with_default(mud_object_casting_pool_t * pool, mud_object_t * object, mud_boolean_t _default);
mud_int_t mud_object_try_cast_int_with_default(mud_object_casting_pool_t * pool, mud_object_t * object, mud_int_t _default);
mud_float_t mud_object_try_cast_float_with_default(mud_object_casting_pool_t * pool, mud_object_t * object, mud_float_t _default);

#define mud_object_try_cast_str(pool, object) mud_object_try_cast_str_with_default(pool, object, "")
#define mud_object_try_cast_boolean(pool, object) mud_object_try_cast_boolean_with_default(pool, object, 0)
#define mud_object_try_cast_int(pool, object) mud_object_try_cast_int_with_default(pool, object, 0)
#define mud_object_try_cast_float(pool, object) mud_object_try_cast_float_with_default(pool, object, 0.0)