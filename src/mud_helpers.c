// void * malloc_empty(size_t size) {
//   void * ptr = malloc(size);
//   memset(ptr, 0, size);
//   return ptr;
// }

// void * exalloc_empty(void * ptr, size_t old_size, size_t expand_size) {
//   ptr = realloc(ptr, old_size + expand_size );
//   memset((char *)ptr + old_size, 0, expand_size);
//   return ptr;      
// }