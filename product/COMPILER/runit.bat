del errorMessage.txt
compiler %1
type errorMessage.txt
copy information.xml ..\SQL
cd ..\SQL
sqlApp
copy information.xml ..\DTD
cd ..\DTD
dtdApp
copy information.xml ..\XMLSCHEMA
cd ..\XMLSCHEMA
xmlApp
copy information.xml ..\DRAFT
cd ..\DRAFT
digApp
cd ..\COMPILER
