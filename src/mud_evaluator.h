mud_object_t * mud_evaluate(mud_object_t * object, mud_scope_t * scope, mud_gc_stack_t * stack);

mud_object_t * _mud_expr_evaluate(mud_expr_t * expr, mud_scope_t * scope, mud_gc_stack_t * stack);
mud_object_t * _mud_exprs_evaluate(mud_exprs_t * exprs, mud_scope_t * scope, mud_gc_stack_t * stack);
