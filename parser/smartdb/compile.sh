#!/bin/sh -x

fail() {
  echo 'Fail!!'
  exit 1
}

yacc -dv sql1.y || fail
mv y.tab.c sql1.c
mv y.tab.h sql1.h

flex -I scn1.l || fail
mv lex.yy.c scn1.c

gcc -DYYDEBUG=1 -o sql1 sql1.c scn1.c
