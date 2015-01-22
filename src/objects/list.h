#define MUD_LIST_ALLOC_SIZE 256;

typedef struct mud_list_s mud_list_t;
struct mud_list_s {
  mud_object_t **       objects;
  unsigned int          count;
  unsigned int          size;
};


mud_list_t * mud_list_init();
void mud_list_free(mud_list_t * list);

mud_boolean_t _mud_list_check(mud_object_t * object);

void mud_list_append(mud_list_t * list, mud_object_t * item);
void mud_list_prepend(mud_list_t * list, mud_object_t * item);
void mud_list_push(mud_list_t * list, mud_object_t * item, mud_int_t pos);
void mud_list_replace(mud_list_t * list, mud_object_t * item, mud_int_t pos);
void mud_list_remove(mud_list_t * list, mud_int_t pos);
