yacc -d --warning=none foryaac.y
lex lex.l
gcc -w foryaac.tab.c lex.yy.c
