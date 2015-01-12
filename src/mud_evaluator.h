#define MUD_EXPR_EVALUATOR_TMP_POOL_ALLOC_SIZE 128;

typedef enum {
  MUD_TMP_ARG_STRING,
  MUD_TMP_ARG_COUNT
} mud_tmp_arg_e;


typedef struct mud_expr_evaluator_s mud_expr_evaluator_t;
struct mud_expr_evaluator_s {
  mud_object_t **       args;
  unsigned              argc;
  void **           tmp_args;

  void **           tmp_pool;
  unsigned     tmp_pool_size;
  unsigned     tmp_pool_count;
};

mud_object_t * mud_evaluate(mud_object_t * object);

mud_object_t * _mud_exprs_evaluate(mud_exprs_t * exprs);

mud_expr_evaluator_t * mud_expr_evaluator_init(mud_expr_t * expr);

void mud_expr_evaluator_free(mud_expr_evaluator_t * evaluator);

void * mud_expr_evaluator_tmp_args_alloc(mud_expr_evaluator_t * evaluator, size_t size);

void * mud_expr_evaluator_tmp_arg_get(mud_expr_evaluator_t * evaluator, mud_tmp_arg_e tmp_arg, unsigned i);
void mud_expr_evaluator_tmp_arg_set(mud_expr_evaluator_t * evaluator, mud_tmp_arg_e tmp_arg, unsigned i, void * ptr);

const char * mud_expr_evaluator_get_str(mud_expr_evaluator_t * evaluator, unsigned i);