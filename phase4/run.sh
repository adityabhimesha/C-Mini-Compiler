yacc -d --warning=none Yacc.y
lex lex.l
gcc -w Yacc.tab.c lex.yy.c
