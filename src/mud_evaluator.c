#import "mud_evaluator.h"
#import "evaluators/casting.c"
#import "evaluators/expr.c"

mud_object_t * mud_evaluate(mud_object_t * object) {
  switch ( object->type ) {
    case MUD_OBJ_TYPE_EXPR:
      return _mud_expr_evaluate(object->ptr);
    case MUD_OBJ_TYPE_EXPRS:
      return _mud_exprs_evaluate(object->ptr);
    default:
      return object;
  }
}

mud_object_t * _mud_exprs_evaluate(mud_exprs_t * exprs) {
  mud_object_t * ret;
  for ( unsigned i = 0; i < exprs->count; i++ ) {
    ret = mud_evaluate(exprs->exprs[i]);
  }
  return ret;
}

