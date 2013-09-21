ECHO Producing "compiler.exe"
flex compiler.l
bison -d compiler.y
gcc -o compiler compiler.tab.c lex.yy.c