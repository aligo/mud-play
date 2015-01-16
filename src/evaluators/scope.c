
mud_scope_t * mud_scope_init() {
  mud_scope_t * scope = (mud_scope_t *)malloc(sizeof(mud_scope_t));
  return scope;
}

void mud_scope_free(mud_scope_t * scope) {
  free(scope);
}