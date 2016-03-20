#import "support.h"

int main() {
  mud_gc_stack_t * stack1 = mud_gc_stack_init();

  mud_object_t * obj1 = mud_string_init(stack1, "hello");

  NSLog(@"ref_count should be: 1 == %d", obj1->ref_count);
  NSLog(@"ptr should not be free: %d", (int)obj1->ptr);
  mud_gc_stack_free(stack1);

  NSLog(@"ptr should be free: %d", (int)obj1->ptr);


  mud_gc_stack_t * stack2 = mud_gc_stack_init();

  mud_object_t * obj2 = mud_string_init(stack2, "hello");
  obj2->ref_count += 1;
  
  NSLog(@"ref_count should be: 2 == %d", obj2->ref_count);
  NSLog(@"ptr should not be free: %d", (int)obj2->ptr);
  mud_gc_stack_free(stack2);
  NSLog(@"ref_count should be: 1 == %d", obj2->ref_count);
  NSLog(@"ptr should not be free: %d", (int)obj2->ptr);
  mud_object_free(obj2);
  NSLog(@"ptr should be free: %d", (int)obj2->ptr);
}