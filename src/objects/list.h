#define MUD_LIST_ALLOC_SIZE 256;

typedef struct mud_list_s mud_list_t;
struct mud_list_s {
  mud_object_t **       objects;
  unsigned int          count;
  unsigned int          size;
};


mud_list_t * mud_list_init();
void mud_list_append(mud_list_t * list, mud_object_t * item);
void mud_list_free(mud_list_t * list);