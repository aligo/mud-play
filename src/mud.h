#import "mud_objects.h"
#import "mud_gc.h"
#import "mud_evaluator.h"

void * malloc_empty(size_t size) {
  void * ptr = malloc(size);
  memset(ptr, 0, size);
  return ptr;
}