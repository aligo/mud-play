// auto-generated: operators import - begin
#import "../../operators/string.c"
#import "../../bridges/ns/operators/ns.m"
// auto-generated: operators import - end

mud_object_t * _mud_op_evaluate(mud_operator_e operator, mud_object_t ** args) {
  mud_object_t * ret;
  switch (operator) {
// auto-generated: operators switch - begin
    case MUD_OP_STR_CONCAT:
      ret = _mud_op_str_concat_evaluate(args);
      break;
// auto-generated: operators switch - end
    default:
      mud_error(@"Unknown operator: %lu", operator);
      ret = mud_nil_init();
      break;
  }
  return ret;
}
