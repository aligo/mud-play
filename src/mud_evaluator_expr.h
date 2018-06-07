struct mud_expr_evaluator_s {
  mud_object_t **               args;
  mud_object_t **               orgs;
  size_t                        argc;
  mud_scope_t *                 scope;
  mud_gc_stack_t *              stack;
  mud_object_casting_pool_t *   pool;
};

mud_expr_evaluator_t * mud_expr_evaluator_init(mud_expr_t * expr, mud_scope_t * scope, mud_gc_stack_t * stack);
void mud_expr_evaluator_free(mud_expr_evaluator_t * evaluator);

mud_object_t * _mud_expr_evaluator_get(mud_expr_evaluator_t * evaluator, size_t i);
