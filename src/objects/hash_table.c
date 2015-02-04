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