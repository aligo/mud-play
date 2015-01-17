
mud_scope_t * mud_scope_init() {
  mud_scope_t * scope = (mud_scope_t *)malloc(sizeof(mud_scope_t));
  scope->vars = NULL;
  return scope;
}

void mud_scope_free(mud_scope_t * scope) {
  mud_scope_vars_t * tmp, * var = NULL;
  HASH_ITER(hh, scope->vars, var, tmp) {
    HASH_DEL(scope->vars, var);
    free((void *)var->name);
    free(var);
  }
  free(scope);
}

mud_scope_t * mud_scope_push(mud_scope_t * scope) {
  mud_scope_vars_t * tmp, * var = NULL;
  mud_scope_t * new_scope = (mud_scope_t *)malloc(sizeof(mud_scope_t));
  new_scope->vars = NULL;
  HASH_ITER(hh, scope->vars, var, tmp) {
    HASH_ADD_KEYPTR(hh, new_scope->vars, var->name, strlen(var->name), var);
  }
  return new_scope;
}

mud_object_t * mud_scope_get(mud_scope_t * scope, const char * name) {
  mud_scope_vars_t * var = NULL;
  HASH_FIND_STR(scope->vars, name, var);
  if ( var == NULL ) {
    return mud_nil_init();
  } else {
    return var->value;
  }
}

void mud_scope_set(mud_scope_t * scope, const char * name, mud_object_t * value) {
  mud_scope_vars_t * var = NULL;
  HASH_FIND_STR(scope->vars, name, var);
  if ( var == NULL ) {
    var = (mud_scope_vars_t *)malloc(sizeof(mud_scope_vars_t));
    var->name = strdup(name);
    HASH_ADD_KEYPTR(hh, scope->vars, var->name, strlen(var->name), var);
  }
  var->value = value;
}