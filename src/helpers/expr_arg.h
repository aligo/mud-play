
#define _ME_ORG(I)               evaluator->orgs[I]

#define ME_ARGC                  evaluator->argc
#define ME_ARG(I)                _mud_expr_evaluator_get(evaluator, I)
#define ME_ARG_STR_FMT(I, FMT)   mud_object_try_cast_str_format(evaluator->pool, _mud_expr_evaluator_get(evaluator, I), FMT)
#define ME_ARG_STR(I)            mud_object_try_cast_str(evaluator->pool, _mud_expr_evaluator_get(evaluator, I))
#define ME_ARG_BOOLEAN(I)        mud_object_try_cast_boolean(evaluator->pool, _mud_expr_evaluator_get(evaluator, I))
#define ME_ARG_INT(I)            mud_object_try_cast_int(evaluator->pool, _mud_expr_evaluator_get(evaluator, I))
#define ME_ARG_FLOAT(I)          mud_object_try_cast_float(evaluator->pool, _mud_expr_evaluator_get(evaluator, I))