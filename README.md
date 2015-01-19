[![Build Status](https://travis-ci.org/aligo/mud-play.svg?branch=master)](https://travis-ci.org/aligo/mud-play)

# Ref

## Operators

### Base
  * 100:  `quote, ...`
  * 101:  `eval, (expr)`

### Conditional
  * 111:  `if, cond, (then statement exprs), (else statement exprs)`
  * 112:  `when`, alias for `if`
  * 113:  `unless, cond, (then statement exprs), (else statement exprs)`

### Scope
  * 120: `sget, name`
  * 121: `sset, name, value`

### Boolean
  * 190:  `!, expr`
  * 191:  `&&, expr1, expr2`
  * 192:  `||, expr1, expr2`

### Arithmetic
  * 200:  `+, a, b, ...`
  * 201:  `-, a, b, ...`
  * 202:  `*, a, b, ...`
  * 203:  `/, a, b, ...`
  * 204:  `%, a, b`

### Integer
  * 210:   `round, 1.1`
  * 211:   `floor, 1.1`
  * 212:   `ceil, 1.1`

### Float
  * 206:   `**, 2, 10`
  * 207:   `abs, -1`
  * 208:   `exp, 1`
  * 220-229: cos, sin, tan, acos, asin, atan, atan2, log10, log1p, log2

### Compare
  * 290:   `==, 1, 1`
  * 291:   `!=, 1, 1`
  * 292:   `>, 1, 1`
  * 293:   `<, 1, 1`
  * 294:   `>=, 1, 1`
  * 295:   `<=, 1, 1`

### String
  * 300:   `concat, a, b, ...`
  * 301:   `format, "%s", str, ...`
  * 302:   `strlen_byte, "123"`
  * 303:   `strstr_byte, "abc", "a"`
  * 304:   `substr_byte, "abc", 0, 1`
  * 305:   `strlen, "123"`
  * 306:   `strstr, "abc", "a"`
  * 307:   `substr, "abc", 0, 1`
  * 308:   `strrep, "abc", "a", "d", all`