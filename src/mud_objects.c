mud_object_t * mud_object_alloc(mud_gc_stack_t * stack, mud_object_type_e type) {
  mud_object_t * object = (mud_object_t *)malloc(sizeof(mud_object_t));
  object->ptr  = NULL;
  object->type = type;
  object->ref_count = 1;
  mud_gc_stack_push(stack, object);
  return object;
}

void mud_object_free(mud_object_t * object) {
  object->ref_count -= 1;
  if ( object->ref_count == 0 ) {
    if ( object->type == MUD_OBJ_TYPE_EXPR ) {
      mud_expr_t * expr = (mud_expr_t *)object->ptr;
      free(expr->args);
      expr->args = NULL;
      expr->argc = 0;
      expr->oper = 0;
    } else if ( object->type == MUD_OBJ_TYPE_EXPRS ) {
      mud_exprs_t * exprs = (mud_exprs_t *)object->ptr;
      free(exprs->exprs);
      exprs->exprs = NULL;
      exprs->count = 0;
    } else if ( object->type == MUD_OBJ_TYPE_LAMBDA ) {
      mud_lambda_free(object->ptr);
    } else if ( object->type == MUD_OBJ_TYPE_LIST ) {
      mud_list_free(object->ptr);
    } else if ( object->type == MUD_OBJ_TYPE_HASH_TABLE ) {
      mud_hash_table_free(object->ptr);
      object->ptr = NULL;
    } else if ( object->type == MUD_OBJ_TYPE_REGEX ) {
      regfree(object->ptr);
    } else if ( object->type >= MUD_OBJ_TYPE_BRIDGE ) {
      mud_object_bridge_free(object);
    }
    if ( object->ptr ) {
      free(object->ptr);
      object->ptr = NULL;
    }
    object->type = 0;
    object->ref_count = 0;
    free(object);
  }
}

mud_object_t * mud_nil_init(mud_gc_stack_t * stack) {
  return stack->_nil;
}

mud_object_t * mud_boolean_init(mud_gc_stack_t * stack, mud_boolean_t value) {
  mud_object_t * object = mud_object_alloc(stack, MUD_OBJ_TYPE_BOOLEAN);
  object->ptr = malloc(sizeof(mud_boolean_t));
  * (mud_boolean_t *)object->ptr = value;
  return object;
}

mud_object_t * mud_int_init(mud_gc_stack_t * stack, mud_int_t value) {
  mud_object_t * object = mud_object_alloc(stack, MUD_OBJ_TYPE_INT);
  object->ptr = malloc(sizeof(mud_int_t));
  * (mud_int_t *)object->ptr = value;
  return object;
}
mud_object_t * mud_float_init(mud_gc_stack_t * stack, mud_float_t value){
  mud_object_t * object = mud_object_alloc(stack, MUD_OBJ_TYPE_FLOAT);
  object->ptr = malloc(sizeof(mud_float_t));
  * (mud_float_t *)object->ptr = value;
  return object;
}

mud_object_t * mud_string_init(mud_gc_stack_t * stack, const char * value) {
  mud_object_t * object = mud_object_alloc(stack, MUD_OBJ_TYPE_STRING);
  object->ptr = strdup(value);
  return object; 
}

mud_object_t * mud_expr_init(mud_gc_stack_t * stack, mud_operator_e oper, mud_object_t ** args, size_t argc) {
  mud_object_t * object = mud_object_alloc(stack, MUD_OBJ_TYPE_EXPR);
  object->ptr = malloc(sizeof(mud_expr_t));
  mud_expr_t * expr = (mud_expr_t *)object->ptr;
  expr->oper = oper;
  expr->args = args;
  expr->argc = argc;
  return object;
}

mud_object_t * mud_exprs_init(mud_gc_stack_t * stack, mud_object_t ** exprs, size_t count) {
  mud_object_t * object = mud_object_alloc(stack, MUD_OBJ_TYPE_EXPRS);
  object->ptr = malloc(sizeof(mud_exprs_t));
  mud_exprs_t * mud_exprs = (mud_exprs_t *)object->ptr;
  mud_exprs->exprs = exprs;
  mud_exprs->count = count;
  return object;
}

mud_object_t * mud_lambda_init(mud_gc_stack_t * stack) {
  mud_object_t * object = mud_object_alloc(stack, MUD_OBJ_TYPE_LAMBDA);
  object->ptr = mud_lambda_alloc();
  return object;
}

mud_gc_stack_t * mud_gc_stack_init() {
  mud_gc_stack_t * stack = (mud_gc_stack_t *)malloc(sizeof(mud_gc_stack_t));
  stack->count = 0;
  stack->size  = MUD_GC_POOL_ALLOC_SIZE;
  stack->pool  = (mud_object_t **)malloc(stack->size * sizeof(mud_object_t *));
  stack->prev  = NULL;
  stack->_nil  = mud_object_alloc(stack, MUD_OBJ_TYPE_NIL);
  return stack;
}

void mud_gc_stack_free(mud_gc_stack_t * stack) {
  _mud_gc_stack_release(stack);
  free(stack->pool);
  stack->pool = NULL;
  stack->prev = NULL;
  stack->_nil  = NULL;
  stack->count = stack->size = 0;
  free(stack);
}

void mud_gc_stack_push(mud_gc_stack_t * stack, mud_object_t * mud_object) {
  if (stack->count == stack->size) {
    _mud_gc_stack_realloc(stack);
  }
  stack->pool[stack->count++] = mud_object;
}

void _mud_gc_stack_realloc(mud_gc_stack_t * stack) {
  stack->size *= 2;
  stack->pool = (mud_object_t **)realloc(stack->pool, stack->size * sizeof(mud_object_t *));
}

void _mud_gc_stack_release(mud_gc_stack_t * stack) {
  for ( unsigned int i = 0; i < stack->count; i++ ) {
    if ( stack->pool[i] ) {
      mud_object_free((mud_object_t *)stack->pool[i]);
    }
  }
  stack->count = 0;
}