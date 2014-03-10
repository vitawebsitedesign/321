flex compiler.l
bison -dy compiler.y
gcc lex.yy.c y.tab.c -o compiler.exe