mud_hash_table_t * mud_hash_table_alloc() {
  mud_hash_table_t * hash_table = NULL;
  return hash_table;
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