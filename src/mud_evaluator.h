

typedef struct mud_expr_evaluator_s mud_expr_evaluator_t;
struct mud_expr_evaluator_s {
  mud_object_t **       args;
  unsigned              argc;
  // void **             e_args;
};

mud_object_t * mud_evaluate(mud_object_t * object);

mud_object_t * _mud_exprs_evaluate(mud_exprs_t * exprs);

mud_expr_evaluator_t * mud_expr_evaluator_init(mud_expr_t * expr);

void mud_expr_evaluator_free(mud_expr_evaluator_t * evaluator);

const char * mud_expr_evaluator_get_str(mud_expr_evaluator_t * evaluator, unsigned i);