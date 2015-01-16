typedef struct mud_scope_s mud_scope_t;
struct mud_scope_s {
  mud_scope_t *         prev;
};


mud_scope_t * mud_scope_init();
void mud_scope_free(mud_scope_t * scope);

mud_scope_t * mud_scope_push(mud_scope_t * scope);
// mud_scope_t * mud_scope_pop(mud_scope_t * scope);