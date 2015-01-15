/*
  arithmetic
    - +: 200
    - -: 201
    - *: 202
    - /: 203
    - %: 204
*/

typedef struct mud_arithmetic_s mud_arithmetic_t;
struct mud_arithmetic_s {
  mud_object_type_e         type;
  mud_int_t *               ints;
  mud_float_t *             floats;
  mud_int_t                 int_res;
  mud_float_t               float_res;
};

mud_object_type_e mud_expr_evaluator_get_arithmetic_type(mud_expr_evaluator_t * evaluator, unsigned i) {
  mud_object_t * arg = evaluator->args[i];
  switch ( arg->type ) {
    case MUD_OBJ_TYPE_STRING:
      return ( strchr( (char *)arg->ptr, '.') ? MUD_OBJ_TYPE_FLOAT : MUD_OBJ_TYPE_INT );
    default: return arg->type;
  }
}

mud_arithmetic_t * _mud_arithmetic_init(mud_expr_evaluator_t * evaluator) {
  mud_arithmetic_t * arithmetic = malloc(sizeof(mud_arithmetic_t));
  arithmetic->type              = MUD_OBJ_TYPE_INT;
  arithmetic->ints              = malloc(evaluator->argc * sizeof(mud_int_t));
  arithmetic->floats            = malloc(evaluator->argc * sizeof(mud_float_t));
  arithmetic->int_res           = 0;
  arithmetic->float_res         = 0;
  for (unsigned i = 0; i < evaluator->argc; i++) {
    switch ( arithmetic->type ) {
      case MUD_OBJ_TYPE_INT:
        arithmetic->type = mud_expr_evaluator_get_arithmetic_type(evaluator, i);
        if ( arithmetic->type == MUD_OBJ_TYPE_INT ) {
          arithmetic->ints[i] = M_ARG_INT(i);
        }
      case MUD_OBJ_TYPE_FLOAT:
      default:
        arithmetic->floats[i] = M_ARG_FLOAT(i);
    }
  }
  return arithmetic;
}

void _mud_arithmetic_free(mud_arithmetic_t * arithmetic) {
  free(arithmetic->ints);
  free(arithmetic->floats);
  arithmetic->ints = NULL;
  arithmetic->floats = NULL;
  arithmetic->int_res = arithmetic->float_res = 0;
  free(arithmetic);
}

mud_object_t * _mud_arithmetic_return(mud_arithmetic_t * arithmetic) {
  mud_object_t * ret;
  switch ( arithmetic->type ) {
    case MUD_OBJ_TYPE_INT:
      ret = mud_int_init(arithmetic->int_res);
      break;
    case MUD_OBJ_TYPE_FLOAT:
    default:
      ret = mud_float_init(arithmetic->float_res);
      break;
  }
  _mud_arithmetic_free(arithmetic);
  return ret;
}

mud_object_t * _mud_op_arithmetic_adding_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 200
  mud_arithmetic_t * arithmetic = _mud_arithmetic_init(evaluator);
  switch ( arithmetic->type ) {
    case MUD_OBJ_TYPE_INT:
      for (unsigned i = 0; i < evaluator->argc; i++) {
        arithmetic->int_res += arithmetic->ints[i];
      }
      break;
    case MUD_OBJ_TYPE_FLOAT:
    default:
      for (unsigned i = 0; i < evaluator->argc; i++) {
        arithmetic->float_res += arithmetic->floats[i];
      }
      break;
  }
  return _mud_arithmetic_return(arithmetic);
}

mud_object_t * _mud_op_arithmetic_subtracting_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 201
  mud_arithmetic_t * arithmetic = _mud_arithmetic_init(evaluator);
  switch ( arithmetic->type ) {
    case MUD_OBJ_TYPE_INT:
      if ( evaluator->argc > 1 ) { 
        arithmetic->int_res = arithmetic->ints[0];
        for (unsigned i = 1; i < evaluator->argc; i++) {
          arithmetic->int_res -= arithmetic->ints[i];
        }
      } else {
        arithmetic->int_res = -arithmetic->ints[0];
      }
      break;
    case MUD_OBJ_TYPE_FLOAT:
    default:
      if ( evaluator->argc > 1 ) { 
        arithmetic->float_res = arithmetic->floats[0];
        for (unsigned i = 1; i < evaluator->argc; i++) {
          arithmetic->float_res -= arithmetic->floats[i];
        }
      } else {
        arithmetic->float_res = -arithmetic->floats[0];
      }
      break;
  }
  return _mud_arithmetic_return(arithmetic);
}

mud_object_t * _mud_op_arithmetic_multiplying_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 202
  mud_arithmetic_t * arithmetic = _mud_arithmetic_init(evaluator);
  switch ( arithmetic->type ) {
    case MUD_OBJ_TYPE_INT:
      arithmetic->int_res = 1;
      for (unsigned i = 0; i < evaluator->argc; i++) {
        arithmetic->int_res *= arithmetic->ints[i];
      }
      break;
    case MUD_OBJ_TYPE_FLOAT:
    default:
      arithmetic->float_res = 1;
      for (unsigned i = 0; i < evaluator->argc; i++) {
        arithmetic->float_res *= arithmetic->floats[i];
      }
      break;
  }
  return _mud_arithmetic_return(arithmetic);
}

mud_object_t * _mud_op_arithmetic_dividing_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 203
  mud_arithmetic_t * arithmetic = _mud_arithmetic_init(evaluator);
  switch ( arithmetic->type ) {
    case MUD_OBJ_TYPE_INT:
      arithmetic->int_res = arithmetic->ints[0];
      for (unsigned i = 1; i < evaluator->argc; i++) {
        if ( arithmetic->ints[i] == 0 ) {
          mud_error("dividing by zero, ignored.");
        } else {
          arithmetic->int_res /= arithmetic->ints[i];
        }
      }
      break;
    case MUD_OBJ_TYPE_FLOAT:
    default:
      arithmetic->float_res = arithmetic->floats[0];
      for (unsigned i = 1; i < evaluator->argc; i++) {
        if ( arithmetic->floats[i] == 0 ) {
          mud_error("dividing by zero, ignored.");
        } else {
          arithmetic->float_res /= arithmetic->floats[i];
        }
      }
      break;
  }
  return _mud_arithmetic_return(arithmetic);
}

mud_object_t * _mud_op_arithmetic_remainder_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 204
  mud_arithmetic_t * arithmetic = _mud_arithmetic_init(evaluator);
  if ( arithmetic->floats[1] == 0 ) {
    mud_error("dividing by zero, ignored.");
  } else {
    switch ( arithmetic->type ) {
      case MUD_OBJ_TYPE_INT:
        arithmetic->int_res = arithmetic->ints[0] % arithmetic->ints[1];
        break;
    case MUD_OBJ_TYPE_FLOAT:
      default:
        arithmetic->float_res = fmod(arithmetic->floats[0], arithmetic->floats[1]);
        break;
    }
  }
  return _mud_arithmetic_return(arithmetic);
}