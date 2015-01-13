#import "mud_helpers.c"

#define MUD_EXPR_EVALUATOR_TMP_POOL_ALLOC_SIZE 128;

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

void * _mud_expr_evaluator_tmp_pool_alloc(mud_expr_evaluator_t * evaluator, size_t size);

int _mud_expr_evaluator_snprintf(mud_expr_evaluator_t * evaluator, unsigned i, char * ret, size_t n, const char * fmt);
int _mud_expr_evaluator_sprintf(mud_expr_evaluator_t * evaluator, unsigned i, char * ret, const char * fmt);

const char * mud_expr_evaluator_get_str_format(mud_expr_evaluator_t * evaluator, unsigned i, const char * fmt);
const char * mud_expr_evaluator_get_str(mud_expr_evaluator_t * evaluator, unsigned i);