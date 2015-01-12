#import "mud_evaluator.h"

mud_object_t * mud_evaluate(mud_object_t * object) {
  switch ( object->type ) {
    case MUD_OBJ_TYPE_EXPR:
      return _mud_expr_evaluate(object->ptr);
      break;
    default:
      return object;
      break;
  }
}

mud_expr_evaluator_t * mud_expr_evaluator_init(mud_expr_t * expr) {
  mud_expr_evaluator_t * evaluator = (mud_expr_evaluator_t *)malloc(sizeof(mud_expr_evaluator_t));
  
  // need evaluate every args
  evaluator->args = (mud_object_t **)malloc(expr->argc * sizeof(mud_object_t *));
  for (unsigned i = 0; i < expr->argc; i++) {
    evaluator->args[i] = mud_evaluate(expr->args[i]);
  }
  
  evaluator->argc = expr->argc;
  return evaluator;
}

void mud_expr_evaluator_free(mud_expr_evaluator_t * evaluator) {
  free(evaluator->args);
  evaluator->args = NULL;
  evaluator->argc = 0;
  free(evaluator);
}

const char * mud_expr_evaluator_get_str(mud_expr_evaluator_t * evaluator, unsigned i) {
  mud_object_t * arg = evaluator->args[i];
  switch ( arg->type ) {
    case MUD_OBJ_TYPE_STRING:
      return arg->ptr;
      break;
    default:
      mud_warning(@"casting Type:%lu as mud_string", arg->type);
      return "";
      break;
  }
}