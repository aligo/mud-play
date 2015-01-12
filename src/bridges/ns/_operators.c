// auto-generated: operators import - begin
#import "../../operators/string.c"
#import "../../bridges/ns/operators/ns.m"
// auto-generated: operators import - end

mud_object_t * _mud_expr_evaluate(mud_expr_t * expr) {
  mud_object_t * ret;
  // mud_object_t ** args = expr->args;
  switch (expr->oper) {
// auto-generated: operators switch - begin
    case MUD_OP_STR_CONCAT:
      ret = _mud_op_str_concat_evaluate(expr);
      break;
// auto-generated: operators switch - end
    default:
      mud_error(@"Unknown operator: %lu", expr->oper);
      ret = mud_nil_init();
      break;
  }
  return ret;
}
