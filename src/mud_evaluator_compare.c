int _mud_float_compare(mud_float_t a, mud_float_t b) {
  mud_float_t float_diff =  a - b;
  if ( float_diff == 0 ) {
    return 0;
  } else if ( float_diff > 0 ) {
    return ceil(float_diff);
  } else {
    return ceil(float_diff) - 1;
  }
}

mud_int_t mud_object_compare(mud_expr_evaluator_t * evaluator, mud_object_t * a, mud_object_t * b) {
  mud_int_t type_diff;
  switch ( a->type ) {
    case MUD_OBJ_TYPE_INT:
      return ( mud_object_try_cast_int(evaluator, a) - mud_object_try_cast_int(evaluator, b) );
    case MUD_OBJ_TYPE_FLOAT:
      return _mud_float_compare( mud_object_try_cast_float(evaluator, a), mud_object_try_cast_float(evaluator, b) );
    case MUD_OBJ_TYPE_STRING:
      return strcmp( mud_object_try_cast_str(evaluator, a), mud_object_try_cast_str(evaluator, b) );
    default:
      type_diff = a->type - b->type;
      if ( type_diff == 0 ) {
        switch ( a->type ) {
          case MUD_OBJ_TYPE_LIST:
            return mud_list_compare(evaluator, (mud_list_t *)a->ptr, (mud_list_t *)b->ptr);
          default:
            return a->ptr - b->ptr;
        }
      } else {
        return type_diff;
      }
  }
}

mud_int_t mud_list_compare(mud_expr_evaluator_t * evaluator, mud_list_t * a_list, mud_list_t * b_list) {
  mud_int_t diff = a_list->count - b_list->count;
  if ( diff != 0 ) {
    return diff;
  } else {
    for ( unsigned i = 0; i < a_list->count; i++ ) {
      diff = mud_object_compare(evaluator, a_list->objects[i], b_list->objects[i]);
      if ( diff != 0 ) {
        break;
      }
    }
    return diff;
  }
}
