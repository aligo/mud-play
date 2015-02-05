mud_hash_table_t * mud_hash_table_alloc() {
  return (mud_hash_table_t *)NULL;
}

void mud_hash_table_free(mud_hash_table_t * hash_table) {
  mud_hash_table_t * tmp, * cur_hash = NULL;
  HASH_ITER(hh, hash_table, cur_hash, tmp) {
    HASH_DEL(hash_table, cur_hash);
    free((char *)cur_hash->key);
    free(cur_hash);
  }
}

mud_object_t * mud_hash_table_get(mud_hash_table_t * hash_table, const char * key) {
  mud_hash_table_t * cur_hash = NULL;
  HASH_FIND_STR(hash_table, key, cur_hash);
  if ( cur_hash == NULL ) {
    return mud_nil_init();
  } else {
    return cur_hash->value;
  }
}

mud_hash_table_t * mud_hash_table_set(mud_hash_table_t * hash_table, const char * key, mud_object_t * value) {
  mud_hash_table_t * cur_hash = NULL;
  HASH_FIND_STR(hash_table, key, cur_hash);
  if ( cur_hash == NULL ) {
    cur_hash = (mud_hash_table_t *)malloc(sizeof(mud_hash_table_t));
    cur_hash->key = strdup(key);
    HASH_ADD_KEYPTR(hh, hash_table, cur_hash->key, strlen(cur_hash->key), cur_hash);
  }
  cur_hash->value = value;
  return hash_table;
}

int _mud_hash_table_sort_by_compare_lambda(mud_hash_table_t * a, mud_hash_table_t * b) {
  _mud_list_sort_args[0] = a->value;
  _mud_list_sort_args[1] = b->value;
  _mud_list_sort_args[2] = mud_string_init(a->key);
  _mud_list_sort_args[3] = mud_string_init(b->key);
  mud_object_t * ret = _mud_lambda_object_apply(_mud_list_sort_lambda, _mud_list_sort_scope, _mud_list_sort_args, 4);
  mud_float_t float_diff;
  switch ( ret->type ) {
    case MUD_OBJ_TYPE_FLOAT:
      float_diff = *(mud_float_t *)ret->ptr;
      if ( float_diff != 0 ) {
        return ( float_diff > 0 ) ? 1 : -1;
      } else {
        return 0;
      }
    default:
      return mud_object_try_cast_int(_mud_list_sort_pool, ret);
  }
  
}