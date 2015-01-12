#import "mud_gc.h"

void mud_gc_stack_start() {
  mud_gc_stack_t * new_stack = _mud_gc_stack_init();
  if ( _mud_gc_stack_cur ) {
    new_stack->prev = _mud_gc_stack_cur;
  }
  _mud_gc_stack_cur = new_stack;
}

void mud_gc_stack_finish() {
  if ( _mud_gc_stack_cur ) {
    mud_gc_stack_t * prev = _mud_gc_stack_cur->prev;
    _mud_gc_stack_release(_mud_gc_stack_cur);
    _mud_gc_stack_free(_mud_gc_stack_cur);
    if ( prev ) {
      _mud_gc_stack_cur = prev;
    }
  }
}

void mud_gc_stack_cur_push(mud_object_t * mud_object) {
  if ( _mud_gc_stack_cur ) {
    _mud_gc_stack_push(_mud_gc_stack_cur, mud_object);
  }
}

mud_gc_stack_t * _mud_gc_stack_init() {
  mud_gc_stack_t * stack = (mud_gc_stack_t *)malloc(sizeof(mud_gc_stack_t));
  stack->count = 0;
  stack->size  = MUD_GC_POOL_ALLOC_SIZE;
  stack->pool  = (mud_object_t **)malloc_empty(stack->size * sizeof(mud_object_t *));
  return stack;
}

void _mud_gc_stack_push(mud_gc_stack_t * stack, mud_object_t * mud_object) {
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
}

void _mud_gc_stack_free(mud_gc_stack_t * stack) {
  free(stack->pool);
  stack->pool = NULL;
  stack->prev = NULL;
  stack->count = stack->size = 0;
  free(stack);
}