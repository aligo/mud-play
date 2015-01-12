#import "mud_operators.h"

typedef enum {
  MUD_OBJ_TYPE_EXPR     = 10,
  MUD_OBJ_TYPE_EXPRS    = 20,
  MUD_OBJ_TYPE_NIL      = 100,
  MUD_OBJ_TYPE_BOOLEAN  = 110,
  MUD_OBJ_TYPE_INT      = 120,
  MUD_OBJ_TYPE_FLOAT    = 121,
  MUD_OBJ_TYPE_STRING   = 130,
  MUD_OBJ_TYPE_ARRAY    = 140,
  MUD_OBJ_TYPE_HASH     = 150
} mud_object_type_e;


typedef struct mud_object_s mud_object_t;
struct mud_object_s {
  mud_object_type_e     type;
  void *                ptr;
};

typedef struct mud_expr_s mud_expr_t;
struct mud_expr_s {
  mud_operator_e        oper;
  mud_object_t **       args;
};

typedef signed char   mud_boolean_t;
typedef long          mud_int_t;
typedef double        mud_float_t;

mud_object_t * mud_object_alloc(mud_object_type_e type);
void mud_object_free(mud_object_t * object);

mud_object_t * mud_nil_init();
mud_object_t * mud_boolean_init(mud_boolean_t value);
mud_object_t * mud_int_init(mud_int_t value);
mud_object_t * mud_float_init(mud_float_t value);
mud_object_t * mud_string_init(const char * value);

mud_object_t * mud_expr_init(mud_operator_e oper, mud_object_t ** args);
mud_object_t * mud_exprs_init(mud_object_t ** exprs);