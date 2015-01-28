/*
  ns
    - info:  1200
*/

mud_object_t * _mud_op_ns_info_evaluate(mud_expr_evaluator_t * evaluator) {
// Enum: 1200
  mud_object_t * ret = ME_ARG(0);
  MudInfoToNSLog("%@", nsWithMudObject(ret));
  return ret;
}