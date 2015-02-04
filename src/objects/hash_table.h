typedef struct mud_hash_table_s mud_hash_table_t;

struct mud_hash_table_s {
    const char *        key;
    mud_object_t *      value;
    UT_hash_handle      hh;
};

mud_hash_table_t * mud_hash_table_alloc();
void mud_hash_table_free(mud_hash_table_t * hash_table);

mud_hash_table_t * mud_hash_table_set(mud_hash_table_t * hash_table, const char * key, mud_object_t * value);