#import "mud_objects.h"

#define MUD_GC_POOL_ALLOC_SIZE 4096

typedef struct mud_gc_stack_s mud_gc_stack_t;
struct mud_gc_stack_s {
  mud_object_t **       pool;
  unsigned int          count;
  unsigned int          size;
  mud_gc_stack_t *      prev;
};

mud_gc_stack_t * _mud_gc_stack_cur = NULL;

void mud_gc_stack_start();
void mud_gc_stack_finish();
void mud_gc_stack_cur_push(mud_object_t * mud_object);

mud_gc_stack_t * _mud_gc_stack_init();
void _mud_gc_stack_push(mud_gc_stack_t * stack, mud_object_t * mud_object);
void _mud_gc_stack_realloc(mud_gc_stack_t * stack);
void _mud_gc_stack_release(mud_gc_stack_t * stack);
void _mud_gc_stack_free(mud_gc_stack_t * stack);