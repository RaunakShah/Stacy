:To compile lex and yacc
flex C_lang.l
bison -dy C_lang.y
gcc lex.yy.c y.tab.c
