// auto-generated: operators includes - begin
// auto-generated: operators includes - end

// auto-generated: operators enum - begin
#define  MUD_OP_BASE_QUOTE 100
#define  MUD_OP_BASE_EVAL 101
#define  MUD_OP_BASE_EXPR 102
#define  MUD_OP_BASE_EARGS 103
#define  MUD_OP_COND_IF 111
#define  MUD_OP_COND_WHEN 112
#define  MUD_OP_COND_UNLESS 113
#define  MUD_OP_SCOPE_GET 120
#define  MUD_OP_SCOPE_SET 121
#define  MUD_OP_SCOPE_ARG 122
#define  MUD_OP_SCOPE_ARGC 123
#define  MUD_OP_LAMBDA_LAMBDA 130
#define  MUD_OP_LAMBDA_APPLY 131
#define  MUD_OP_BOOLEAN_NOT 190
#define  MUD_OP_BOOLEAN_AND 191
#define  MUD_OP_BOOLEAN_OR 192
#define  MUD_OP_ARITHMETIC_ADDING 200
#define  MUD_OP_ARITHMETIC_SUBTRACTING 201
#define  MUD_OP_ARITHMETIC_MULTIPLYING 202
#define  MUD_OP_ARITHMETIC_DIVIDING 203
#define  MUD_OP_ARITHMETIC_REMAINDER 204
#define  MUD_OP_INT_ROUND 210
#define  MUD_OP_INT_FLOOR 211
#define  MUD_OP_INT_CEIL 212
#define  MUD_OP_INT_RAND 213
#define  MUD_OP_FLOAT_POW 205
#define  MUD_OP_FLOAT_ABS 206
#define  MUD_OP_FLOAT_LOG 207
#define  MUD_OP_FLOAT_EXP 208
#define  MUD_OP_FLOAT_COS 220
#define  MUD_OP_FLOAT_SIN 221
#define  MUD_OP_FLOAT_TAN 222
#define  MUD_OP_FLOAT_ACOS 223
#define  MUD_OP_FLOAT_ASIN 224
#define  MUD_OP_FLOAT_ATAN 225
#define  MUD_OP_FLOAT_ATAN2 226
#define  MUD_OP_FLOAT_LOG10 227
#define  MUD_OP_FLOAT_LOG1P 228
#define  MUD_OP_FLOAT_LOG2 229
#define  MUD_OP_COMPARE_EQ_TO 290
#define  MUD_OP_COMPARE_NOT_EQ_TO 291
#define  MUD_OP_COMPARE_GT 292
#define  MUD_OP_COMPARE_LT 293
#define  MUD_OP_COMPARE_GT_OR_EQ 294
#define  MUD_OP_COMPARE_LT_OR_EQ 295
#define  MUD_OP_STRING_CONCAT 300
#define  MUD_OP_STRING_FORMAT 301
#define  MUD_OP_STRING_STRLEN_BYTE 302
#define  MUD_OP_STRING_STRSTR_BYTE 303
#define  MUD_OP_STRING_SUBSTR_BYTE 304
#define  MUD_OP_STRING_STRLEN 305
#define  MUD_OP_STRING_STRSTR 306
#define  MUD_OP_STRING_SUBSTR 307
#define  MUD_OP_STRING_STRREP 308
#define  MUD_OP_STRING_JOIN 309
#define  MUD_OP_REGEX_REGEX 310
#define  MUD_OP_REGEX_TEST 311
#define  MUD_OP_REGEX_MATCH 312
#define  MUD_OP_REGEX_MATCH_ALL 313
#define  MUD_OP_REGEX_REP_ALL 314
#define  MUD_OP_LIST_LIST 500
#define  MUD_OP_LIST_COUNT 501
#define  MUD_OP_LIST_NTH 502
#define  MUD_OP_LIST_APPEND 503
#define  MUD_OP_LIST_PREPEND 504
#define  MUD_OP_LIST_PUSH 505
#define  MUD_OP_LIST_REPLACE 506
#define  MUD_OP_LIST_REMOVE 507
#define  MUD_OP_LIST_FIND 508
#define  MUD_OP_LIST_STR 509
#define  MUD_OP_LIST_REVERSE 510
#define  MUD_OP_LIST_FLATTEN 511
#define  MUD_OP_LIST_UNIQ 512
#define  MUD_OP_LIST_INTERSECTION 513
#define  MUD_OP_LIST_DIFFERENCE 514
#define  MUD_OP_LIST_CONCAT 515
#define  MUD_OP_LIST_UNION 516
#define  MUD_OP_LIST_HEAD 517
#define  MUD_OP_LIST_TAIL 518
#define  MUD_OP_LIST_SLICE 519
#define  MUD_OP_LIST_EACH 520
#define  MUD_OP_LIST_MAP 521
#define  MUD_OP_LIST_REDUCE 522
#define  MUD_OP_LIST_FILTER 523
#define  MUD_OP_LIST_REJECT 524
#define  MUD_OP_LIST_SORT_BY 525
#define  MUD_OP_LIST_SORT 526
#define  MUD_OP_LIST_ALL 527
#define  MUD_OP_LIST_ANY 528
#define  MUD_OP_HASH_TABLE_HT 600
#define  MUD_OP_HASH_TABLE_COUNT 601
#define  MUD_OP_HASH_TABLE_GET 602
#define  MUD_OP_HASH_TABLE_SET 603
#define  MUD_OP_HASH_TABLE_KEYS 604
#define  MUD_OP_HASH_TABLE_VALUES 605
#define  MUD_OP_HASH_TABLE_PAIRS 606
#define  MUD_OP_HASH_TABLE_MERGE 607
#define  MUD_OP_HASH_TABLE_INVERT 608
#define  MUD_OP_HASH_TABLE_EACH 620
#define  MUD_OP_HASH_TABLE_MAP 621
#define  MUD_OP_HASH_TABLE_FILTER 623
#define  MUD_OP_HASH_TABLE_REJECT 624
#define  MUD_OP_HASH_TABLE_SORT_BY 625
#define  MUD_OP_HASH_TABLE_SORT 626
#define  MUD_OP_NS_INFO 1200
// auto-generated: operators enum - end

// auto-generated: operators declaration - begin
mud_object_t * _mud_op_base_quote_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_base_eval_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_base_expr_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_base_eargs_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_cond_if_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_cond_when_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_cond_unless_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_scope_get_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_scope_set_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_scope_arg_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_scope_argc_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_lambda_lambda_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_lambda_apply_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_boolean_not_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_boolean_and_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_boolean_or_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_arithmetic_adding_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_arithmetic_subtracting_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_arithmetic_multiplying_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_arithmetic_dividing_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_arithmetic_remainder_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_int_round_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_int_floor_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_int_ceil_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_int_rand_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_pow_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_abs_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_log_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_exp_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_cos_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_sin_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_tan_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_acos_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_asin_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_atan_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_atan2_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_log10_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_log1p_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_float_log2_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_compare_eq_to_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_compare_not_eq_to_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_compare_gt_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_compare_lt_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_compare_gt_or_eq_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_compare_lt_or_eq_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_string_concat_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_string_format_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_string_strlen_byte_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_string_strstr_byte_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_string_substr_byte_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_string_strlen_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_string_strstr_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_string_substr_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_string_strrep_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_string_join_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_regex_regex_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_regex_test_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_regex_match_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_regex_match_all_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_regex_rep_all_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_list_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_count_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_nth_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_append_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_prepend_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_push_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_replace_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_remove_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_find_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_str_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_reverse_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_flatten_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_uniq_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_intersection_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_difference_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_concat_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_union_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_head_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_tail_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_slice_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_each_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_map_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_reduce_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_filter_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_reject_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_sort_by_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_sort_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_all_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_list_any_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_ht_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_count_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_get_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_set_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_keys_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_values_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_pairs_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_merge_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_invert_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_each_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_map_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_filter_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_reject_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_sort_by_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_hash_table_sort_evaluate(mud_expr_evaluator_t * evaluator);
mud_object_t * _mud_op_ns_info_evaluate(mud_expr_evaluator_t * evaluator);
// auto-generated: operators declaration - end
