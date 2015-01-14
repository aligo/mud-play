// auto-generated: operators import - begin
#import "../../operators/200_arithmetics.c"
#import "../../operators/210_int.c"
#import "../../operators/220_float.c"
#import "../../operators/300_string.c"
#import "../../bridges/ns/operators/ns.m"
// auto-generated: operators import - end

mud_object_t * _mud_expr_evaluate(mud_expr_t * expr) {
  mud_object_t * ret;
  mud_expr_evaluator_t * evaluator = mud_expr_evaluator_init(expr);
  // printf("%p\n", evaluator);
  // mud_object_t ** args = expr->args;
  switch (expr->oper) {
// auto-generated: operators switch - begin
    case MUD_OP_ARITHMETIC_ADDING:
      ret = _mud_op_arithmetic_adding_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_SUBTRACTING:
      ret = _mud_op_arithmetic_subtracting_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_MULTIPLYING:
      ret = _mud_op_arithmetic_multiplying_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_DIVIDING:
      ret = _mud_op_arithmetic_dividing_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_REMAINDER:
      ret = _mud_op_arithmetic_remainder_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_ROUND:
      ret = _mud_op_float_round_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_FLOOR:
      ret = _mud_op_float_floor_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_CEIL:
      ret = _mud_op_float_ceil_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_POW:
      ret = _mud_op_arithmetic_pow_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_ABS:
      ret = _mud_op_arithmetic_abs_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_LOG:
      ret = _mud_op_arithmetic_log_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_EXP:
      ret = _mud_op_arithmetic_exp_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_COS:
      ret = _mud_op_arithmetic_cos_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_SIN:
      ret = _mud_op_arithmetic_sin_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_TAN:
      ret = _mud_op_arithmetic_tan_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_ACOS:
      ret = _mud_op_arithmetic_acos_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_ASIN:
      ret = _mud_op_arithmetic_asin_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_ATAN:
      ret = _mud_op_arithmetic_atan_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_ATAN2:
      ret = _mud_op_arithmetic_atan2_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_LOG10:
      ret = _mud_op_arithmetic_log10_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_LOG1P:
      ret = _mud_op_arithmetic_log1p_evaluate(evaluator);
      break;
    case MUD_OP_ARITHMETIC_LOG2:
      ret = _mud_op_arithmetic_log2_evaluate(evaluator);
      break;
    case MUD_OP_STRING_CONCAT:
      ret = _mud_op_string_concat_evaluate(evaluator);
      break;
    case MUD_OP_STRING_FORMAT:
      ret = _mud_op_string_format_evaluate(evaluator);
      break;
// auto-generated: operators switch - end
    default:
      mud_error("Unknown operator: %lu", expr->oper);
      ret = mud_nil_init();
      break;
  }

  mud_expr_evaluator_free(evaluator);
  return ret;
}
