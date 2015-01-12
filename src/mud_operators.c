// auto-generated: operators import - begin
// auto-generated: operators import - end

mud_object_t * _mud_op_evaluate(mud_operator_e operator, mud_object_t ** args) {
  mud_object_t * ret;
  switch (operator) {
// auto-generated: operators switch - begin

// auto-generated: operators switch - end
    default:
      mud_error(@"Unknown operator: %lu", operator);
      ret = mud_nil_init();
      break;
  }
  return ret;
}