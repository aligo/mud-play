mud_object_t * mud_evaluate(mud_object_t * object, mud_scope_t * scope);

mud_object_t * _mud_exprs_evaluate(mud_exprs_t * exprs, mud_scope_t * scope);

#import "evaluators/casting.h"
#import "evaluators/expr.h"

#import "helpers/expr_arg.h"