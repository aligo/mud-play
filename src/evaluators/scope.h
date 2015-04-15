typedef struct mud_scope_s mud_scope_t;
typedef struct mud_scope_vars_s mud_scope_vars_t;
typedef struct mud_scope_slot_s mud_scope_slot_t;

struct mud_scope_s {
  mud_scope_t *         prev;
  mud_scope_vars_t *    vars;
  mud_object_t **       args;
  unsigned              argc;
  void *                context;
};

struct mud_scope_vars_s {
    const char *        name;
    mud_scope_slot_t *  slot;
    UT_hash_handle      hh;
};

struct mud_scope_slot_s {
  mud_object_t *        value;
  mud_scope_t *         belongs_to;
};


mud_scope_t * mud_scope_init();
void mud_scope_free(mud_scope_t * scope);

mud_scope_t * mud_scope_push(mud_scope_t * scope);

mud_object_t * mud_scope_get(mud_scope_t * scope, const char * name);
void mud_scope_set(mud_scope_t * scope, const char * name, mud_object_t * value);
mud_object_t * mud_scope_arg(mud_scope_t * scope, mud_int_t i);