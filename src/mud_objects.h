typedef enum {
  MUD_OBJ_TYPE_EXPR       = 10,
  MUD_OBJ_TYPE_EXPRS      = 20,
  MUD_OBJ_TYPE_LAMBDA     = 30,
  MUD_OBJ_TYPE_NIL        = 100,
  MUD_OBJ_TYPE_BOOLEAN    = 110,
  MUD_OBJ_TYPE_INT        = 120,
  MUD_OBJ_TYPE_FLOAT      = 121,
  MUD_OBJ_TYPE_STRING     = 130,
  MUD_OBJ_TYPE_REGEX      = 135,
  MUD_OBJ_TYPE_LIST       = 150,
  MUD_OBJ_TYPE_HASH_TABLE = 160,
  MUD_OBJ_TYPE_DATE       = 200,
  MUD_OBJ_TYPE_BRIDGE     = 300
} mud_object_type_e;

typedef struct mud_expr_evaluator_s mud_expr_evaluator_t;

typedef signed char   mud_boolean_t;
typedef long          mud_int_t;
typedef double        mud_float_t;
typedef unsigned      mud_operator_e;

typedef struct mud_object_s mud_object_t;
struct mud_object_s {
  mud_object_type_e     type;
  void *                ptr;
  unsigned int          ref_count;
};

typedef struct mud_expr_s mud_expr_t;
struct mud_expr_s {
  mud_operator_e        oper;
  mud_object_t **       args;
  size_t                argc;
};

typedef struct mud_exprs_s mud_exprs_t;
struct mud_exprs_s {
  mud_object_t **       exprs;
  size_t                count;
};

typedef struct mud_gc_stack_s mud_gc_stack_t;
struct mud_gc_stack_s {
  mud_object_t **       pool;
  unsigned int          count;
  unsigned int          size;
  mud_gc_stack_t *      prev;
  mud_object_t *        _nil;
};


#define MUD_INT_MIN LONG_MIN
#define MUD_INT_MAX LONG_MAX

#define MUD_FLOAT_MIN DBL_MIN
#define MUD_FLOAT_MAX DBL_MAX

#define MUD_GC_POOL_ALLOC_SIZE 4096

mud_object_t * mud_object_alloc(mud_gc_stack_t * stack, mud_object_type_e type);
void mud_object_free(mud_object_t * object);

mud_object_t * mud_nil_init(mud_gc_stack_t * stack);
mud_object_t * mud_boolean_init(mud_gc_stack_t * stack, mud_boolean_t value);
mud_object_t * mud_int_init(mud_gc_stack_t * stack, mud_int_t value);
mud_object_t * mud_float_init(mud_gc_stack_t * stack, mud_float_t value);
mud_object_t * mud_string_init(mud_gc_stack_t * stack, const char * value);

mud_object_t * mud_expr_init(mud_gc_stack_t * stack, mud_operator_e oper, mud_object_t ** args, size_t argc);
mud_object_t * mud_exprs_init(mud_gc_stack_t * stack, mud_object_t ** exprs, size_t count);
mud_object_t * mud_lambda_init(mud_gc_stack_t * stack);

void mud_object_bridge_free(mud_object_t * object);

mud_gc_stack_t * mud_gc_stack_init();
mud_gc_stack_t * mud_gc_stack_retain(mud_gc_stack_t * old_stack);
void mud_gc_stack_free(mud_gc_stack_t * stack);
void mud_gc_stack_push(mud_gc_stack_t * stack, mud_object_t * mud_object);

void _mud_gc_stack_realloc(mud_gc_stack_t * stack);
void _mud_gc_stack_release(mud_gc_stack_t * stack);