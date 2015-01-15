#define MUD_EXPR_EVALUATOR_TMP_POOL_ALLOC_SIZE 128;

typedef struct mud_expr_evaluator_s mud_expr_evaluator_t;
struct mud_expr_evaluator_s {
  mud_object_t **               args;
  unsigned                      argc;
  mud_object_casting_pool_t *   pool;
};

mud_expr_evaluator_t * mud_expr_evaluator_init(mud_expr_t * expr);
void mud_expr_evaluator_free(mud_expr_evaluator_t * evaluator);

mud_object_t * _mud_expr_evaluator_get(mud_expr_evaluator_t * evaluator, unsigned i);
