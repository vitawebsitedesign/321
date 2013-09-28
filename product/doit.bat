ECHO Producing "compiler.exe"
cd COMPILER
flex compiler.l
bison -d compiler.y
gcc -o compiler compiler.tab.c lex.yy.c
cd ..
ECHO ~~~~~~~~~~~~~~~~~~~~~~~~
ECHO Producing "digApp.exe"
cd DRAFT
g++ -o digApp main.cpp read.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp -mwindows glut32.lib -lopengl32 -lglu32
cd ..
ECHO ~~~~~~~~~~~~~~~~~~~~~~~~
cd SQL
ECHO Producing "sqlApp.exe"
g++ -o sqlApp.exe -Wno-deprecated main.cpp Table.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp
cd ..
ECHO ~~~~~~~~~~~~~~~~~~~~~~~~
cd DTD
ECHO Producing "dtdApp.exe"
g++ -o dtdApp.exe main.cpp dtdc.cpp
cd ..
ECHO ~~~~~~~~~~~~~~~~~~~~~~~~
cd XMLSCHEMA
ECHO Producing "xmlApp.exe"
g++ -o xmlApp.exe main.cpp xmlSch.cpp
cd ..
ECHO Done.
