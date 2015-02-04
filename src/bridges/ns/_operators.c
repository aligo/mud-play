// auto-generated: operators import - begin
#import "../../operators/100_base.c"
#import "../../operators/110_cond.c"
#import "../../operators/120_scope.c"
#import "../../operators/130_lambda.c"
#import "../../operators/190_boolean.c"
#import "../../operators/200_arithmetics.c"
#import "../../operators/210_int.c"
#import "../../operators/220_float.c"
#import "../../operators/290_compare.c"
#import "../../operators/300_string.c"
#import "../../operators/310_regex.c"
#import "../../operators/500_list.c"
#import "../../operators/510_list.c"
#import "../../operators/520_list.c"
#import "../../operators/600_hash_table.c"
#import "../../bridges/ns/operators/ns.m"
// auto-generated: operators import - end

mud_object_t * _mud_expr_evaluate(mud_expr_t * expr, mud_scope_t * scope) {
  mud_object_t * ret;
  mud_expr_evaluator_t * evaluator = mud_expr_evaluator_init(expr, scope);
  
  switch (expr->oper) {
// auto-generated: operators switch - begin
    case MUD_OP_BASE_QUOTE:
      ret = _mud_op_base_quote_evaluate(evaluator);
      break;
    case MUD_OP_BASE_EVAL:
      ret = _mud_op_base_eval_evaluate(evaluator);
      break;
    case MUD_OP_BASE_EXPR:
      ret = _mud_op_base_expr_evaluate(evaluator);
      break;
    case MUD_OP_BASE_EARGS:
      ret = _mud_op_base_eargs_evaluate(evaluator);
      break;
    case MUD_OP_COND_IF:
      ret = _mud_op_cond_if_evaluate(evaluator);
      break;
    case MUD_OP_COND_WHEN:
      ret = _mud_op_cond_when_evaluate(evaluator);
      break;
    case MUD_OP_COND_UNLESS:
      ret = _mud_op_cond_unless_evaluate(evaluator);
      break;
    case MUD_OP_SCOPE_GET:
      ret = _mud_op_scope_get_evaluate(evaluator);
      break;
    case MUD_OP_SCOPE_SET:
      ret = _mud_op_scope_set_evaluate(evaluator);
      break;
    case MUD_OP_SCOPE_ARG:
      ret = _mud_op_scope_arg_evaluate(evaluator);
      break;
    case MUD_OP_SCOPE_ARGC:
      ret = _mud_op_scope_argc_evaluate(evaluator);
      break;
    case MUD_OP_LAMBDA_LAMBDA:
      ret = _mud_op_lambda_lambda_evaluate(evaluator);
      break;
    case MUD_OP_LAMBDA_APPLY:
      ret = _mud_op_lambda_apply_evaluate(evaluator);
      break;
    case MUD_OP_BOOLEAN_NOT:
      ret = _mud_op_boolean_not_evaluate(evaluator);
      break;
    case MUD_OP_BOOLEAN_AND:
      ret = _mud_op_boolean_and_evaluate(evaluator);
      break;
    case MUD_OP_BOOLEAN_OR:
      ret = _mud_op_boolean_or_evaluate(evaluator);
      break;
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
    case MUD_OP_INT_ROUND:
      ret = _mud_op_int_round_evaluate(evaluator);
      break;
    case MUD_OP_INT_FLOOR:
      ret = _mud_op_int_floor_evaluate(evaluator);
      break;
    case MUD_OP_INT_CEIL:
      ret = _mud_op_int_ceil_evaluate(evaluator);
      break;
    case MUD_OP_INT_RAND:
      ret = _mud_op_int_rand_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_POW:
      ret = _mud_op_float_pow_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_ABS:
      ret = _mud_op_float_abs_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_LOG:
      ret = _mud_op_float_log_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_EXP:
      ret = _mud_op_float_exp_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_COS:
      ret = _mud_op_float_cos_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_SIN:
      ret = _mud_op_float_sin_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_TAN:
      ret = _mud_op_float_tan_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_ACOS:
      ret = _mud_op_float_acos_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_ASIN:
      ret = _mud_op_float_asin_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_ATAN:
      ret = _mud_op_float_atan_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_ATAN2:
      ret = _mud_op_float_atan2_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_LOG10:
      ret = _mud_op_float_log10_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_LOG1P:
      ret = _mud_op_float_log1p_evaluate(evaluator);
      break;
    case MUD_OP_FLOAT_LOG2:
      ret = _mud_op_float_log2_evaluate(evaluator);
      break;
    case MUD_OP_COMPARE_EQ_TO:
      ret = _mud_op_compare_eq_to_evaluate(evaluator);
      break;
    case MUD_OP_COMPARE_NOT_EQ_TO:
      ret = _mud_op_compare_not_eq_to_evaluate(evaluator);
      break;
    case MUD_OP_COMPARE_GT:
      ret = _mud_op_compare_gt_evaluate(evaluator);
      break;
    case MUD_OP_COMPARE_LT:
      ret = _mud_op_compare_lt_evaluate(evaluator);
      break;
    case MUD_OP_COMPARE_GT_OR_EQ:
      ret = _mud_op_compare_gt_or_eq_evaluate(evaluator);
      break;
    case MUD_OP_COMPARE_LT_OR_EQ:
      ret = _mud_op_compare_lt_or_eq_evaluate(evaluator);
      break;
    case MUD_OP_STRING_CONCAT:
      ret = _mud_op_string_concat_evaluate(evaluator);
      break;
    case MUD_OP_STRING_FORMAT:
      ret = _mud_op_string_format_evaluate(evaluator);
      break;
    case MUD_OP_STRING_STRLEN_BYTE:
      ret = _mud_op_string_strlen_byte_evaluate(evaluator);
      break;
    case MUD_OP_STRING_STRSTR_BYTE:
      ret = _mud_op_string_strstr_byte_evaluate(evaluator);
      break;
    case MUD_OP_STRING_SUBSTR_BYTE:
      ret = _mud_op_string_substr_byte_evaluate(evaluator);
      break;
    case MUD_OP_STRING_STRLEN:
      ret = _mud_op_string_strlen_evaluate(evaluator);
      break;
    case MUD_OP_STRING_STRSTR:
      ret = _mud_op_string_strstr_evaluate(evaluator);
      break;
    case MUD_OP_STRING_SUBSTR:
      ret = _mud_op_string_substr_evaluate(evaluator);
      break;
    case MUD_OP_STRING_STRREP:
      ret = _mud_op_string_strrep_evaluate(evaluator);
      break;
    case MUD_OP_STRING_JOIN:
      ret = _mud_op_string_join_evaluate(evaluator);
      break;
    case MUD_OP_REGEX_REGEX:
      ret = _mud_op_regex_regex_evaluate(evaluator);
      break;
    case MUD_OP_REGEX_TEST:
      ret = _mud_op_regex_test_evaluate(evaluator);
      break;
    case MUD_OP_REGEX_MATCH:
      ret = _mud_op_regex_match_evaluate(evaluator);
      break;
    case MUD_OP_REGEX_MATCH_ALL:
      ret = _mud_op_regex_match_all_evaluate(evaluator);
      break;
    case MUD_OP_REGEX_REP_ALL:
      ret = _mud_op_regex_rep_all_evaluate(evaluator);
      break;
    case MUD_OP_LIST_LIST:
      ret = _mud_op_list_list_evaluate(evaluator);
      break;
    case MUD_OP_LIST_COUNT:
      ret = _mud_op_list_count_evaluate(evaluator);
      break;
    case MUD_OP_LIST_NTH:
      ret = _mud_op_list_nth_evaluate(evaluator);
      break;
    case MUD_OP_LIST_APPEND:
      ret = _mud_op_list_append_evaluate(evaluator);
      break;
    case MUD_OP_LIST_PREPEND:
      ret = _mud_op_list_prepend_evaluate(evaluator);
      break;
    case MUD_OP_LIST_PUSH:
      ret = _mud_op_list_push_evaluate(evaluator);
      break;
    case MUD_OP_LIST_REPLACE:
      ret = _mud_op_list_replace_evaluate(evaluator);
      break;
    case MUD_OP_LIST_REMOVE:
      ret = _mud_op_list_remove_evaluate(evaluator);
      break;
    case MUD_OP_LIST_FIND:
      ret = _mud_op_list_find_evaluate(evaluator);
      break;
    case MUD_OP_LIST_STR:
      ret = _mud_op_list_str_evaluate(evaluator);
      break;
    case MUD_OP_LIST_REVERSE:
      ret = _mud_op_list_reverse_evaluate(evaluator);
      break;
    case MUD_OP_LIST_FLATTEN:
      ret = _mud_op_list_flatten_evaluate(evaluator);
      break;
    case MUD_OP_LIST_UNIQ:
      ret = _mud_op_list_uniq_evaluate(evaluator);
      break;
    case MUD_OP_LIST_INTERSECTION:
      ret = _mud_op_list_intersection_evaluate(evaluator);
      break;
    case MUD_OP_LIST_DIFFERENCE:
      ret = _mud_op_list_difference_evaluate(evaluator);
      break;
    case MUD_OP_LIST_CONCAT:
      ret = _mud_op_list_concat_evaluate(evaluator);
      break;
    case MUD_OP_LIST_UNION:
      ret = _mud_op_list_union_evaluate(evaluator);
      break;
    case MUD_OP_LIST_HEAD:
      ret = _mud_op_list_head_evaluate(evaluator);
      break;
    case MUD_OP_LIST_TAIL:
      ret = _mud_op_list_tail_evaluate(evaluator);
      break;
    case MUD_OP_LIST_SLICE:
      ret = _mud_op_list_slice_evaluate(evaluator);
      break;
    case MUD_OP_LIST_EACH:
      ret = _mud_op_list_each_evaluate(evaluator);
      break;
    case MUD_OP_LIST_MAP:
      ret = _mud_op_list_map_evaluate(evaluator);
      break;
    case MUD_OP_LIST_REDUCE:
      ret = _mud_op_list_reduce_evaluate(evaluator);
      break;
    case MUD_OP_LIST_FILTER:
      ret = _mud_op_list_filter_evaluate(evaluator);
      break;
    case MUD_OP_LIST_REJECT:
      ret = _mud_op_list_reject_evaluate(evaluator);
      break;
    case MUD_OP_LIST_SORT_BY:
      ret = _mud_op_list_sort_by_evaluate(evaluator);
      break;
    case MUD_OP_LIST_SORT:
      ret = _mud_op_list_sort_evaluate(evaluator);
      break;
    case MUD_OP_LIST_ALL:
      ret = _mud_op_list_all_evaluate(evaluator);
      break;
    case MUD_OP_LIST_ANY:
      ret = _mud_op_list_any_evaluate(evaluator);
      break;
    case MUD_OP_HASH_TABLE_HT:
      ret = _mud_op_hash_table_ht_evaluate(evaluator);
      break;
    case MUD_OP_NS_INFO:
      ret = _mud_op_ns_info_evaluate(evaluator);
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
