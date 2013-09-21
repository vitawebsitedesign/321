TCML compiler source code is stored in a folder COMPILER.
SQL generator source code is stored in a folder SQL.
DTD generator source code is stored in a folder DTD.
XML Schema generator source code is stored in a folder XMLSCHEMA.
Diagram generator source code is stored in a folder DRAFT.

Copy a folder 321-4 to any location on your hard drive.

To make all programs open Command Prompt window and navigate to a folder 321-4. 
Then, run a script "doit.bat" without any parameters, for example;

E:\321-4>doit

To run the programs open Command prompt window and navigate to a folder 321-4.
Then, run a script "runit.bat" with one parameter which is a name of file that contains TCML code, 
for example:

E:\321-4>runit example1.txt

At the end of processing a diagram is displayed by a program "digApp.exe".

The intermediate results from compilation are always stored in XML file "information.xml".

The errors from compilation are stored in a file "errorMessage.txt".

Generated SQL code is stored in a file "sqlFile.sql".

Generated DTD code is stored in a file "DtdFile.dtd".

Generated XML Schema code is stored in a file "XmlSechmaFile.xsd".
