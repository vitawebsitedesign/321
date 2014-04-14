flex compiler.l
bison -dy compiler.y
gcc lex.yy.c y.tab.c -o compiler.exe
compiler.exe %1
..\rapidxml\designerror.exe
updateVisXml.exe
errMsgJs.exe
..\visualisation\index.htm