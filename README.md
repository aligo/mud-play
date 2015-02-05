[![Build Status](https://travis-ci.org/aligo/mud-play.svg?branch=master)](https://travis-ci.org/aligo/mud-play)

# Ref

## Operators

### Base
  * 100:  `quote, ...`
  * 101:  `eval, (expr)`
  * 102:  `expr, operator, ..., (eargs, (list, ...), arg2), ...`
  * 103:  `eargs, arg1, arg2, arg3 ...`

### Conditional
  * 111:  `if, cond, (then statement exprs), (else statement exprs)`
  * 112:  `when`, alias for `if`
  * 113:  `unless, cond, (then statement exprs), (else statement exprs)`

### Scope
  * 120: `sget, name`
  * 121: `sset, name, value`
  * 122: `sarg, i`
  * 123: `sargc`

### Lambda
  * 130: `lambda, (list, arg1, arg2, ...), (exprs)`, `lambda, (exprs)`
  * 131: `apply, (lambda), arg1, arg2, ...`

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
  * 213:   `rand`, `rand, 1024`

### Float
  * 206:   `**, 2, 10`
  * 207:   `abs, -1`
  * 208:   `exp, 1`
  * 220-229: `cos, n`, `sin, n`, `tan, n`, `acos, n`, `asin, n`, `atan, n`, `atan2, n, p`, `log10, n`, `log1p, n`, `log2, n`

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
  * 309:   `join, ",", a, b, ...`

### Regex
  * 310:   `regex, "(.*)"`
  * 311:   `rtest, (regex, ...), "string"`
  * 312:   `rmatch, (regex, ...), "string"`
  * 313:   `rmatch_all, (regex, ...), "string"`, `rmatch_all, (regex, ...), "string", true`
  * 314:   `rrep_all, (regex, ...), "string", "rep"`, `rrep_all, (regex, ...), "string", (lambda, ...)`

### List
  * 500:   `list, a, b, ...`
  * 501:   `lcount (list)`
  * 502:   `lnth, (list), 0`
  * 503:   `lappend, (list), ...`
  * 504:   `lprepend, (list), ...`
  * 505:   `lpush, (list), item, 1`
  * 506:   `lreplace, (list), item, 1`
  * 507:   `lremove, (list), 1, ...`
  * 508:   `lfind, (list), item`
  * 509:   `lstr, "abc"`, `lstr, "a,b,c", ","`

  * 510:   `lreverse, (list)`
  * 511:   `lflatten, (list)`, `lflatten, (list), [shallow]`
  * 512:   `luniq, (list)`
  * 513:   `lintersection, (list1), (list2)`
  * 514:   `ldifference, (list1), (list2)`
  * 515:   `lconcat, (list1), (list2)`
  * 516:   `lunion, (list1), (list2)`
  * 517:   `lhead, (list), n`
  * 518:   `ltail, (list), n`
  * 519:   `lslice, (list), start, end`

  * 520:   `leach, (list), (lambda, (list, 'el', 'i'), ...)`
  * 521:   `lmap, (list), (lambda, (list, 'el', 'i'), ...)`
  * 522:   `lreduce, (list), ret, (lambda, (list, 'ret', 'el', 'i'), ...)`
  * 523:   `lfilter, (list), (lambda, (list, 'el', 'i'), ...)`
  * 524:   `lreject, (list), (lambda, (list, 'el', 'i'), ...)`
  * 525:   `lsort_by, (list), (lambda, (list, 'el', 'i'), ...)`
  * 526:   `lsort, (list), (lambda, (list, 'a', 'b'), ...)`
  * 527:   `lall, (list), (lambda, (list, 'el', 'i'), ...)`
  * 528:   `lany, (list), (lambda, (list, 'el', 'i'), ...)`

### Hash Table
  * 600:   `ht, key1, value1, key2, value2`, `ht, (list, key1, value1), (list, key2, value2)`
  * 601:   `htcount, (ht)`
  * 602:   `htget, (ht), key`
  * 603:   `htset, (ht), key, value`
  * 604:   `htkeys, (ht)`
  * 605:   `htvalues, (ht)`
  * 606:   `htpairs, (ht)`
  * 607:   `htmerge, (ht), (ht1), (ht2), (ht3), ...`
  * 608:   `htinvert, (ht)`

  * 620:   `hteach, (ht), (lambda, (list, 'key', 'value'), ...)`
  * 621:   `htmap, (ht), (lambda, (list, 'key', 'value'), ...)`
  * 625:   `htsort_by, (ht), (lambda, (list, 'key', 'value'), ...)`
  