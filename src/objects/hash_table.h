typedef struct mud_hash_table_s mud_hash_table_t;

struct mud_hash_table_s {
    const char *        key;
    mud_object_t *      value;
    UT_hash_handle      hh;
};

mud_hash_table_t * mud_hash_table_alloc();
void mud_hash_table_free(mud_hash_table_t * hash_table);

mud_object_t * mud_hash_table_get(mud_hash_table_t * hash_table, const char * key);
mud_hash_table_t * mud_hash_table_set(mud_hash_table_t * hash_table, const char * key, mud_object_t * value);

int _mud_hash_table_sort_by_compare_lambda(mud_hash_table_t * a, mud_hash_table_t * b);