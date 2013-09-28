The command line:
g++ -o project *.cpp -mwindows glut32.lib -lopengl32 -lglu32

Copy glut.h to the MinGW\include\GL directory. 
Copy glut32.lib to your build directory (i.e., the directory that you compile into and link from). 
Copy glut32.dll to the same directory where your executable will be created. 
(You can actually put glut32.dll in any directory in your path.) 

You must #include <windows.h> before you #include <"GL/glut.h"> 
When you link, you must link-in glut32.lib (and not use the -lglut32). 