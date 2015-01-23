#define MUD_LIST_ALLOC_SIZE 256;

typedef struct mud_list_s mud_list_t;
struct mud_list_s {
  mud_object_t **       objects;
  unsigned int          count;
  unsigned int          size;
};


mud_list_t * mud_list_alloc();
void mud_list_free(mud_list_t * list);

mud_boolean_t _mud_list_check(mud_object_t * object);

void mud_list_append(mud_list_t * list, mud_object_t * item);
void mud_list_prepend(mud_list_t * list, mud_object_t * item);
void mud_list_push(mud_list_t * list, mud_object_t * item, mud_int_t pos);
void mud_list_replace(mud_list_t * list, mud_object_t * item, mud_int_t pos);
void mud_list_remove(mud_list_t * list, mud_int_t pos);

void mud_list_flatten_to(mud_list_t * new_list, mud_list_t * cur_list, mud_boolean_t shallow, mud_boolean_t first_level);

mud_int_t mud_list_find(mud_list_t * list, mud_object_casting_pool_t * pool, mud_object_t * to_find);

mud_list_t * mud_list_alloc_uniq(mud_list_t * list, mud_object_casting_pool_t * pool);

mud_list_t * mud_list_alloc_intersection(mud_list_t * a_list, mud_list_t * b_list, mud_object_casting_pool_t * pool);
mud_list_t * mud_list_alloc_difference(mud_list_t * a_list, mud_list_t * b_list, mud_object_casting_pool_t * pool);