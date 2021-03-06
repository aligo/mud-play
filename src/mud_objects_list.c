mud_object_t *                _mud_list_sort_lambda;
mud_expr_evaluator_t *        _mud_list_sort_evaluator;
mud_object_t **               _mud_list_sort_args;
mud_scope_t *                 _mud_list_sort_scope;
mud_gc_stack_t *              _mud_list_sort_stack;

mud_list_t * mud_list_alloc() {
  return mud_list_alloc_with_size(MUD_LIST_ALLOC_SIZE);
}

mud_list_t * mud_list_alloc_with_size(size_t size) {
  mud_list_t * list = (mud_list_t *)malloc(sizeof(mud_list_t));
  list->count   = 0;
  list->size    = size;
  list->objects = (mud_object_t **)malloc(list->size * sizeof(mud_object_t *));
  return list;
}

mud_list_t * _mud_list_init_with_args(mud_object_t ** args, size_t count) {
  mud_list_t * list = (mud_list_t *)malloc(sizeof(mud_list_t));
  list->count   = count;
  list->size    = count;
  list->objects = (mud_object_t **)malloc(list->size * sizeof(mud_object_t *));
  memcpy(list->objects, args, count * sizeof(mud_object_t *));
  return list;
}

mud_object_t * _mud_object_list_init_with_args(mud_gc_stack_t * stack, mud_object_t ** args, size_t count) {
  mud_object_t * ret = mud_object_alloc(stack, MUD_OBJ_TYPE_LIST);
  ret->ptr = _mud_list_init_with_args(args, count);
  return ret;
}

void mud_list_free(mud_list_t * list) {
  free(list->objects);
  list->objects = NULL;
  list->count = list->size = 0;
}

mud_boolean_t _mud_list_check(mud_object_t * object) {
  return object->type == MUD_OBJ_TYPE_LIST;
}

void _mud_list_resize(mud_list_t * list) {
  if ( list->size < MUD_LIST_ALLOC_SIZE ) {
    list->size += MUD_LIST_ALLOC_SIZE;
    list->objects = (mud_object_t **)realloc(list->objects, list->size * sizeof(void *));
  } else if (list->count == list->size) {
    list->size *= 2;
    list->objects = (mud_object_t **)realloc(list->objects, list->size * sizeof(void *));
  }
}

void mud_list_append(mud_list_t * list, mud_object_t * item) {
  if ( item ) {
    _mud_list_resize(list);
    list->objects[list->count++] = item;
  }
}

void mud_list_prepend(mud_list_t * list, mud_object_t * item) {
  _mud_list_resize(list);
  memcpy(&list->objects[1], list->objects, list->count * sizeof(mud_object_t *));
  list->objects[0] = item;
  list->count++;
}

void mud_list_push(mud_list_t * list, mud_object_t * item, mud_int_t pos) {
  if ( pos <= list->count ) {
    _mud_list_resize(list);
    memcpy(&list->objects[pos + 1], &list->objects[pos], (list->count - pos) * sizeof(mud_object_t *));
    list->objects[pos] = item;
    list->count++;
  }
}


void mud_list_replace(mud_list_t * list, mud_object_t * item, mud_int_t pos) {
  if ( pos < list->count ) {
    list->objects[pos] = item;
  }
}

void mud_list_remove(mud_list_t * list, mud_int_t pos) {
  if ( pos < list->count ) {
    list->count--;
    memcpy(&list->objects[pos], &list->objects[pos + 1], (list->count - pos) * sizeof(mud_object_t *));
  }
}

void mud_list_flatten_to(mud_list_t * new_list, mud_list_t * list, mud_boolean_t shallow, mud_boolean_t first_level) {
  for ( unsigned i = 0; i < list->count; i++ ) {
    mud_object_t * obj = list->objects[i];
    if ( ( first_level || shallow ) && ( obj->type == MUD_OBJ_TYPE_LIST ) ) {
      mud_list_flatten_to(new_list, (mud_list_t *)obj->ptr, shallow, 0);
    } else {
      mud_list_append(new_list, obj);
    }
  }
}

mud_int_t mud_list_find(mud_expr_evaluator_t * evaluator, mud_list_t * list, mud_object_t * to_find) {
  for ( unsigned i = 0; i < list->count; i++ ) {
    if ( mud_object_compare(evaluator, to_find, list->objects[i]) == 0 ) {
      return i;
    }
  }
  return -1;
}

mud_list_t * mud_list_alloc_uniq(mud_list_t * list, mud_expr_evaluator_t * evaluator) {
  mud_list_t * new_list = mud_list_alloc_with_size(list->count);
  for ( unsigned i = 0; i < list->count; i++ ) {
    mud_object_t * obj = list->objects[i];
    if ( mud_list_find(evaluator, new_list, obj) == -1 ){
      mud_list_append(new_list, obj);
    }
  }
  return new_list;
}

mud_list_t * mud_list_alloc_intersection(mud_expr_evaluator_t * evaluator, mud_list_t * a_list, mud_list_t * b_list) {
  mud_list_t * new_list = mud_list_alloc_with_size(a_list->count + b_list->count);
  for ( unsigned i = 0; i < a_list->count; i++ ) {
    mud_object_t * obj = a_list->objects[i];
    if ( ( mud_list_find(evaluator, new_list, obj) == -1 ) && ( mud_list_find(evaluator, b_list, obj) != -1 ) ) {
      mud_list_append(new_list, obj);
    }
  }
  return new_list;
}

mud_list_t * mud_list_alloc_difference(mud_expr_evaluator_t * evaluator, mud_list_t * a_list, mud_list_t * b_list) {
  mud_list_t * new_list = mud_list_alloc_with_size(a_list->count + b_list->count);
  for ( unsigned i = 0; i < a_list->count; i++ ) {
    mud_object_t * obj = a_list->objects[i];
    if ( ( mud_list_find(evaluator, new_list, obj) == -1 ) && ( mud_list_find(evaluator, b_list, obj) == -1 ) ) {
      mud_list_append(new_list, obj);
    }
  }
  for ( unsigned i = 0; i < b_list->count; i++ ) {
    mud_object_t * obj = b_list->objects[i];
    if ( ( mud_list_find(evaluator, new_list, obj) == -1 ) && ( mud_list_find(evaluator, a_list, obj) == -1 ) ) {
      mud_list_append(new_list, obj);
    }
  }
  return new_list;
}

mud_list_t * mud_list_alloc_concat(mud_expr_evaluator_t * evaluator, mud_list_t * a_list, mud_list_t * b_list) {
  mud_list_t * new_list = mud_list_alloc_with_size(a_list->count + b_list->count);
  for ( unsigned i = 0; i < a_list->count; i++ ) {
    mud_list_append(new_list, a_list->objects[i]);
  }
  for ( unsigned i = 0; i < b_list->count; i++ ) {
    mud_list_append(new_list, b_list->objects[i]);
  }
  return new_list;
}

mud_list_t * mud_list_alloc_union(mud_expr_evaluator_t * evaluator, mud_list_t * a_list, mud_list_t * b_list) {
  mud_list_t * new_list = mud_list_alloc_with_size(a_list->count + b_list->count);
  for ( unsigned i = 0; i < a_list->count; i++ ) {
    mud_object_t * obj = a_list->objects[i];
    if ( mud_list_find(evaluator, new_list, obj) == -1 ){
      mud_list_append(new_list, obj);
    }
  }
  for ( unsigned i = 0; i < b_list->count; i++ ) {
    mud_object_t * obj = b_list->objects[i];
    if ( mud_list_find(evaluator, new_list, obj) == -1 ){
      mud_list_append(new_list, obj);
    }
  }
  return new_list;
}

mud_list_sort_by_t * mud_list_sort_by_alloc(mud_expr_evaluator_t * evaluator, mud_object_t * object, mud_object_type_e sort_by_type) {
  mud_list_sort_by_t * sort_by = (mud_list_sort_by_t *)malloc(sizeof(mud_list_sort_by_t));
  switch ( sort_by_type ) {
    case MUD_OBJ_TYPE_INT:
      sort_by->_int = mud_object_try_cast_int(evaluator, object);
      break;
    case MUD_OBJ_TYPE_FLOAT:
      sort_by->_float = mud_object_try_cast_float(evaluator, object);
      break;
    case MUD_OBJ_TYPE_STRING:
      sort_by->_ptr = (void *)mud_object_try_cast_str(evaluator, object);
      break;
    default:
      sort_by->_ptr = object->ptr;
      break;
  }
  return sort_by;
}

int _mud_list_sort_by_compare_lambda(const void * a, const void * b) {
  _mud_list_sort_args[0] = *(mud_object_t **)a;
  _mud_list_sort_args[1] = *(mud_object_t **)b;
  mud_object_t * ret = _mud_lambda_object_apply(_mud_list_sort_lambda, _mud_list_sort_scope, _mud_list_sort_stack, _mud_list_sort_args, 2);
  mud_float_t float_diff;
  switch ( ret->type ) {
    case MUD_OBJ_TYPE_FLOAT:
      float_diff = *(mud_float_t *)ret->ptr;
      if ( float_diff != 0 ) {
        return ( float_diff > 0 ) ? 1 : -1;
      } else {
        return 0;
      }
    default:
      return (int)mud_object_try_cast_int(_mud_list_sort_evaluator, ret);
  }
  
}

int _mud_list_sort_by_compare_int(const void * a, const void * b) {
  return (int)((*(mud_list_sort_by_t **)a)->_int - (*(mud_list_sort_by_t **)b)->_int);
}

int _mud_list_sort_by_compare_float(const void * a, const void * b) {
  return (int)(_mud_float_compare( (*(mud_list_sort_by_t **)a)->_float, (*(mud_list_sort_by_t **)b)->_float ));
}

int _mud_list_sort_by_compare_str(const void * a, const void * b) {
  return strcmp( (*(mud_list_sort_by_t **)a)->_ptr, (*(mud_list_sort_by_t **)b)->_ptr );
}

int _mud_list_sort_by_compare_ptr(const void * a, const void * b) {
  return (int)((*(mud_list_sort_by_t **)a)->_ptr - (*(mud_list_sort_by_t **)b)->_ptr);
}

void mud_list_sort_bies_sort(mud_list_sort_by_t ** sort_bies, size_t count, mud_object_type_e sort_by_type) {
  switch ( sort_by_type ) {
    case MUD_OBJ_TYPE_INT:
      qsort(sort_bies, count, sizeof(mud_list_sort_by_t *), _mud_list_sort_by_compare_int);
      break;
    case MUD_OBJ_TYPE_FLOAT:
      qsort(sort_bies, count, sizeof(mud_list_sort_by_t *), _mud_list_sort_by_compare_float);
      break;
    case MUD_OBJ_TYPE_STRING:
      qsort(sort_bies, count, sizeof(mud_list_sort_by_t *), _mud_list_sort_by_compare_str);
      break;
    default:
      qsort(sort_bies, count, sizeof(mud_list_sort_by_t *), _mud_list_sort_by_compare_ptr);
      break;
  }
}

