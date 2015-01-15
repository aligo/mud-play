
mud_object_casting_pool_t * mud_object_casting_pool_init() {
  mud_object_casting_pool_t * pool = (mud_object_casting_pool_t *)malloc(sizeof(mud_object_casting_pool_t));

  pool->count = 0;
  pool->size = MUD_OBJECT_CASTING_TMP_POOL_ALLOC_SIZE;
  pool->pool = (void **)malloc(pool->size * sizeof(void *));

  return pool;
}

void mud_object_casting_pool_free(mud_object_casting_pool_t * pool) {
  for ( unsigned int i = 0; i < pool->count; i++ ) {
    if ( pool->pool[i] ) {
      free(pool->pool[i]);
    }
  }
  free(pool->pool);
  pool->pool = NULL;
  pool->count = pool->size = 0;
  free(pool);
}

void * _mud_object_casting_pool_malloc(mud_object_casting_pool_t * pool, size_t size) {
  void * ptr = malloc(size);
  if (pool->count == pool->size) {
    pool->size *= 2;
    pool->pool = (void **)realloc(pool->pool, pool->size * sizeof(void *));
  }
  pool->pool[pool->count++] = ptr;
  return ptr;
}

int _mud_object_try_cast_snprintf(mud_object_t * object, char * ret, size_t n, const char * fmt) {
  switch (object->type) {
    case MUD_OBJ_TYPE_NIL:      return snprintf(ret, n, fmt, 0);
    case MUD_OBJ_TYPE_BOOLEAN:  return snprintf(ret, n, fmt, *(mud_boolean_t *)object->ptr);
    case MUD_OBJ_TYPE_INT:      return snprintf(ret, n, fmt, *(mud_int_t *)object->ptr);
    case MUD_OBJ_TYPE_FLOAT:    return snprintf(ret, n, fmt, *(mud_float_t *)object->ptr);
    default:                    return snprintf(ret, n, fmt, object->ptr);
  }
}

int _mud_object_try_cast_sprintf(mud_object_t * object, char * ret, const char * fmt) {
  switch (object->type) {
    case MUD_OBJ_TYPE_NIL:      return sprintf(ret, fmt, 0);
    case MUD_OBJ_TYPE_BOOLEAN:  return sprintf(ret, fmt, *(mud_boolean_t *)object->ptr);
    case MUD_OBJ_TYPE_INT:      return sprintf(ret, fmt, *(mud_int_t *)object->ptr);
    case MUD_OBJ_TYPE_FLOAT:    return sprintf(ret, fmt, *(mud_float_t *)object->ptr);
    default:                    return sprintf(ret, fmt, object->ptr);
  }
}
