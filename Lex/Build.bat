:To compile lex and yacc
flex C_lang.l
"C:\users\pcs\downloads\win_flex_bison-latest\win_bison"  C_lang.y
gcc lex.yy.c C_lang.tab.c graph.c
