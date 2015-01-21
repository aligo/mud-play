#define MUD_LIST_ALLOC_SIZE 256;

mud_list_t * mud_list_init() {
  mud_list_t * list = (mud_list_t *)malloc(sizeof(mud_list_t));
  list->count   = 0;
  list->size    = MUD_LIST_ALLOC_SIZE;
  list->objects = (mud_object_t **)malloc(list->size * sizeof(mud_object_t *));
  return list;
}

void mud_list_append(mud_list_t * list, mud_object_t * item) {
  if (list->count == list->size) {
    list->size *= 2;
    list->objects = (mud_object_t **)realloc(list->objects, list->size * sizeof(void *));
  }
  list->objects[list->count++] = item;
}

void mud_list_prepend(mud_list_t * list, mud_object_t * item) {
  if (list->count == list->size) {
    list->size *= 2;
    list->objects = (mud_object_t **)realloc(list->objects, list->size * sizeof(void *));
  }
  memcpy(&list->objects[1], list->objects, list->count * sizeof(mud_object_t *));
  list->objects[0] = item;
  list->count++;
}

void mud_list_free(mud_list_t * list) {
  free(list->objects);
  list->objects = NULL;
  list->count = list->size = 0;
}