ECHO Producing "digApp.exe"
g++ -o digApp main.cpp read.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp -mwindows glut32.lib -lopengl32 -lglu32