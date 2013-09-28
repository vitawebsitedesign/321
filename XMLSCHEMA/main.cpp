/* 
 * File:   main.cpp
 * XML schema project
 * Author: Xingfang Huang
 */

#include <cstdlib>
#include <string.h>
#include <deque>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <functional>
#include <algorithm>
#include <cctype>
#include "xmlSch.h"
using namespace std;
bool CompRule(xmlSclass* lclass, xmlSclass* rclass);//rule of compare

bool read(deque<xmlSclass *>& x_class);/*main reading function to read the file */
void readSingleClass(ifstream & fin, xmlSclass * tempclass);/*read a single class detail*/
void readAssoClass(ifstream &fin, associate & basAsso, associate& toAsso, int & level, bool & havequali, deque<attribute * > & quali, int & max, int & min);
void readSingleAssociation(ifstream &fin, deque<xmlSclass *>&x_class);
bool readLinkAttribute(char* tempChar, xmlSclass* linkClass, ifstream& fin);/*read the linker classes attribute*/
bool readAssoQua(ifstream & fin, deque<xmlSclass *>&x_class, char * name, associate & basAsso, associate& toAsso);/*read the linker's qualification*/
void findMaxMin(string tetemp, int & max, int & min);//find the max and min
int findLevel(string temp, int & max, int & min);/*find the class level*/
void setGeneralisation(deque<xmlSclass *>& x_class, string className, string ISAname);
void setClassLevel(deque<xmlSclass *> & x_Class);
void setReferenceClass(deque<xmlSclass *> & x_Class, string className);

bool writeClass(deque<xmlSclass *> &xClass);/*write the detail into the DTD format document*/
bool writeSingleClass(ofstream& fout, deque<xmlSclass *> & x_Class, string rootName, int & tab, int occurMax, int occurMin);
void writeReferenceClass(ofstream& fout, deque<xmlSclass *> & x_Class, int & tab);
string findRootBelongClass(string rootBelongClass, deque<xmlSclass *> & x_Class);


int main() {
    deque<xmlSclass*> xClass;
   if(read(xClass)==false){/*read the output from the compiler*/
       cout << "read xml error."<< endl;
       return 0;
   }
   else{
       if(!xClass.empty()){
           setClassLevel(xClass);/*set all class being in the standard level*/
           sort(xClass.begin(), xClass.end(), CompRule);/*sort the level of the class, and get the lowest one*/
           writeClass(xClass);/*write the detail into the DTD format document*/
       }
       
   }
    
    return 0;
}

bool CompRule(xmlSclass* lclass,  xmlSclass* rclass){//rule of compare
    return lclass->getlevel() < rclass->getlevel();
}

bool read(deque<xmlSclass*>& x_class){/*read from the compiler's out put */
    char filedetail[256];/*record the each line of file from the compiler*/
    char * tempChar;
    string temp;
    string path= "information.xml";/*open the compiler output file*/
    ifstream fin(path.c_str(), ios::in);/* open the file and read*/
    if (fin.fail()){return false;}
    while (!fin.eof() ){/*read the file until it finish*/
        fin.getline(filedetail, 255);/*read the line*/
        if(strcmp(filedetail, "")==0){continue;}/*if the line is empty, continue*/
        else{
            tempChar = strtok(filedetail,"<>");
            temp = tempChar;
            if(temp =="project"|| temp =="/project"){
                continue;
            }
            else{
                tempChar = strtok(NULL, "<>");
            }
            temp = tempChar;
            if(temp=="class"){/*if it is the new class read the detail and set new class*/
                xmlSclass * tempclass = new xmlSclass();
                readSingleClass(fin, tempclass);/*Call read single class function to get detail*/
                x_class.push_back(tempclass);/*push the class into the deque*/
                
            }
            else if(temp=="association"){/*if it is association, add association into class*/
                
                readSingleAssociation(fin, x_class);
                }//finish handle the association
            
            else if(temp =="generlisation"){ //if it a generalisation, add ISA class name into class
                bool generalFinish = false;
                string className, ISAname;
                deque<string> generlisation;
                do{
                    fin.getline(filedetail,255);
                    if(strcmp(filedetail, "")==0){continue;}/*if the line is empty, continue*/
                    tempChar = strtok(filedetail,"<>");//cut front of "<"
                    temp = tempChar;
                    if(temp=="/generlisation"){//check if is end of one association
                        generalFinish=true;//is control while loop
                    }
                    else {
                        tempChar = strtok(NULL, ">");//get detail between < >
                        temp = tempChar;
                        if(temp=="/generlisation"){//check if is end of one association
                            generalFinish=true;//is control while loop
                        }
                        else if(temp =="class_name"){//find the class name and set association of the class
                            tempChar = strtok(NULL, "<>");
                            className =tempChar;
                            generlisation.push_back(className);
                        }
                        else if(temp=="ISA"){
                            tempChar = strtok(NULL,"<>");
                            ISAname = tempChar;
                        }
                    }
                    
                }while(generalFinish != true);
                //find the same name class in the deque, and set the depend name.
                if(generlisation.size()==1){
                    setGeneralisation(x_class, className, ISAname);//call set function to set the generalisation
                }
                else if(generlisation.size() >1){
                    deque<string>::iterator firstGen = generlisation.begin();
                    deque<string>::iterator lastGen = generlisation.end();
                    for(firstGen; firstGen != lastGen; firstGen++){
                        string tempGenClass;
                        tempGenClass = *firstGen;
                        setGeneralisation(x_class, tempGenClass, ISAname);//call set function to set the generalisation
                    }
                }
            }
        }
        
    }
    fin.close();
    return true;
}

void readSingleClass(ifstream & fin, xmlSclass * tempclass){/*read a single class detail*/
    bool classFinish=false, IDexist=false;
    char filedetail[256];/*record the each line of file from the compiler*/
    char * tempChar;
    string temp;
    do{
        fin.getline(filedetail,255);
        if(strcmp(filedetail, "")==0){continue;}/*if the line is empty, continue*/
        tempChar = strtok(filedetail,"<>");/*cut front of "<"*/
        temp = tempChar;
        if(temp=="/class"){/*check if is end of one class*/
            classFinish=true;/*is control while loop*/
        }
        else {
            tempChar = strtok(NULL, ">");/*get detail between < >*/
            temp = tempChar;
        }
        if(temp=="/class"){/*check if is end of one class*/
            classFinish=true;/*is control while loop*/
        }
        else if(temp == "class_name"){
            tempChar = strtok(NULL,"<>");/*get the name of the class*/
            tempclass->setname(tempChar);
        }
        else if(temp=="attribute"){
            /*if it is attribute, get detail of the new attribute*/
            attribute tempattribute;
            do{
                fin.getline(filedetail,255);
                if(strcmp(filedetail, "")==0){continue;}/*if the line is empty, continue*/
                tempChar = strtok(filedetail,"<>");/*cut front of "<"*/
                tempChar = strtok(NULL, ">");/*get detail between < >*/
                temp = tempChar;
                if(temp=="attribute_name"){
                    tempChar=strtok(NULL,"<>");
                    strcpy(tempattribute.att_name, tempChar);
                }
                else if(temp=="identifier"){/*check the attribute is ID or not*/
                    tempChar = strtok(NULL,"<>");
                    temp = tempChar;
                    if(temp =="ID" || temp =="ID1"){/*check if the attribute is ID or not*/
                        if(IDexist == false){//if the class do not have ID exist, set ID.
                            IDexist =true;
                            tempattribute.isId = true;
                        }
                        else{tempattribute.isId= false;}//if the class have ID exist, do not set ID
                    }else{tempattribute.isId= false;}
                }
                else if(temp=="multiplicity"){
                    tempChar=strtok(NULL,"]<");
                    string tetemp = tempChar;
                    if((tetemp.compare("["))>0){/*the attribute is multi*/
                        tempattribute.ismulti = true;
                        findMaxMin(tetemp, tempattribute.max, tempattribute.min);//call the function to find the max and min
                        if(tempattribute.min <0){tempattribute.min=0;}
                    }else{tempattribute.ismulti = false;}
                }
            }while(temp !="/attribute");
            tempclass->setattribute(tempattribute);/*put attribute into the class*/
        }
    }while(classFinish != true );
}
void readAssoClass(ifstream &fin, associate & basAsso, associate& toAsso, int & level, bool & havequali, deque<attribute *> & qualification, int & max, int & min){
    char filedetail[256];/*record the each line of file from the compiler*/
    char * tempChar;
    string temp;
    bool finishReadAssoClass = false;
    do{
        fin.getline(filedetail,255);
        if(strcmp(filedetail, "")==0){continue;}/*if the line is empty, continue*/
        tempChar = strtok(filedetail,"<>");
        tempChar = strtok(NULL, ">");//get detail between < >
        temp = tempChar;
        if(temp == "multiplicity"){
            tempChar= strtok(NULL, "/]");
            temp = tempChar;
            if(temp !="<"){
                level = findLevel(temp, max, min);//find the level of the class
                if(min ==0){level = 0;}//if[0..1] or [0..2], set the level being 0
                basAsso.base_multi = level;
                toAsso.to_multi =level;//the 0...1 is 0, 1..1is 1, 1...* is 3 use to decide the "+, *" in DTD
                if(level ==1 && max >1){toAsso.to_multi = max; basAsso.base_multi = max;}
                toAsso.to_Max = max;
                toAsso.to_Min = min;
            }
            else{
                level = 1;//default set the class being 1
                basAsso.base_multi = 1;
                toAsso.to_multi =1;
                toAsso.to_Max = 1;
                toAsso.to_Min = 1;
            }
        }
        else if(temp =="qualification" ){
            tempChar = strtok(NULL, "/");
            temp = tempChar;
            if(temp !="<"){
                attribute * quali = new attribute;
                havequali = true;
                int stringl=temp.length()-1;//get the length of the temp and cut out the "<"
                strcpy(quali->att_name,tempChar);
                *(quali->att_name + stringl)='\0';//cut out the "< " in the att_name
                quali->isId = true;
                quali->ismulti = false;
                
                qualification.push_back(quali);
                
            }
        }
        else if(temp == "/class" || temp == "/other_class"){
            finishReadAssoClass = true;
        }
    }while(finishReadAssoClass !=true);
}

void readSingleAssociation(ifstream &fin, deque<xmlSclass *>&x_class){
   
    bool associationFinish=false;
    bool firstclass = true;
    int baseMax=1, baseMin=1, toMax=1, toMin=1;/*record the minimum and maximum occuar of the class*/
    string base_name, to_name;/*save the name and two class name of the association*/
    int baseLevel, toLevel;/*to save the level of both class of the association*/
    deque<attribute * > baseQualification, toQualification; /*save the list of qualification*/
    attribute basequali, toquali;/*save the name of the qualification*/
    associate basAsso, toAsso;
    bool haveBasequali = false;/*check if there have qualification in first class*/
    bool haveToquali = false;/*check if there have qualification in second class*/
    bool haveLink=false;/*check the association have link or not*/
    char filedetail[256];/*record the each line of file from the compiler*/
    char linker_name[64];
    string Slinker_name;
    char * tempChar;
    string temp;
    deque<xmlSclass*>::iterator first;/*record the first position of the deque*/
    deque<xmlSclass*>::iterator last;/*record the last position of the deque*/
    
    do{
        fin.getline(filedetail,255);
        if(strcmp(filedetail, "")==0){continue;}/*if the line is empty, continue*/
        tempChar = strtok(filedetail,"<>");//cut front of "<"
        temp = tempChar;
        if(temp=="/association"){//check if is end of one association
            associationFinish=true;//is control while loop
        }
        else {
            tempChar = strtok(NULL, ">");//get detail between < >
            temp = tempChar;
            if(temp=="/association"){//check if is end of one association
                associationFinish=true;//is control while loop
            }
            else if(temp == "nameOfAssociation"){
                tempChar = strtok(NULL,"<>");//get the name of the association
                strcpy(basAsso.ass_name, tempChar);
                strcpy(toAsso.ass_name , tempChar);
            }
            else if(temp =="class_name"){/*find the class name of the association of the class*/
                tempChar = strtok(NULL, "<>");/*get the class name*/
                if(firstclass ==true){
                    /*call function to read detail of the association of the first class*/
                    readAssoClass(fin, basAsso, toAsso, baseLevel,haveToquali,toQualification, baseMax, baseMin);
                    
                    firstclass = !firstclass;
                    strcpy(toAsso.tclass_name, tempChar);/*record the relation class*/
                    base_name = tempChar;
                    Slinker_name = base_name;/*record the name of first class*/
                    }
                else{
                    /*call function to read detail of the association of the second class*/
                    readAssoClass(fin, toAsso, basAsso, toLevel,haveBasequali, baseQualification, toMax, toMin );
                    
                    strcpy(basAsso.tclass_name , tempChar);/*record the relation class name */
                    to_name = tempChar;
                    Slinker_name = Slinker_name + to_name;/*record the name of the second class*/
                }
            }
            else if(temp =="Link"){
                fin.getline(filedetail,255);
                if(strcmp(filedetail, "")==0){continue;}/*if the line is empty, continue*/
                tempChar = strtok(filedetail,"<>");//cut front of "<"
                tempChar = strtok(NULL,"<>");/*get the detail in "<>" */
                temp = tempChar;
                if(temp=="/association"|| temp =="/Link"){//check if is end of one association
                    associationFinish=true;//is control while loop
                }
                else if(temp == "link_attribute"){
                    fin.getline(filedetail, 255);
                    if(strcmp(filedetail, "")==0){continue;}/*if the line is empty, continue*/
                    tempChar = strtok(filedetail,"<>");//cut front of "<"
                    tempChar = strtok(NULL, ">");//get detail between < >
                    tempChar = strtok(NULL, "<>");
                    temp = tempChar; 
                    
                    if(strcmp(toAsso.tclass_name, basAsso.tclass_name)!=0){//the two class name is not the same
                        haveLink = true;/*record the two class have link class*/
                        if(temp !="<"){
                            xmlSclass * linkClass = new xmlSclass();/*create a linker class*/
                            linkClass->setname(Slinker_name);
                            linkClass->setlevel(1);

                            int tempMulti;
                            tempMulti = basAsso.to_Max;
                            basAsso.to_Max = 1;/*change the multi link of the association*/
                            linkClass->setassociation(basAsso);/*set the association of the link class*/

                            basAsso.to_Max = tempMulti;/*get back the original multi link number of the association*/


                            tempMulti = toAsso.to_Max;
                            toAsso.to_Max =1;
                            linkClass->setassociation(toAsso);

                            toAsso.to_Max = tempMulti;
                            basAsso.base_multi =1;
                            toAsso.base_multi =1;
                            readLinkAttribute(tempChar, linkClass, fin);/*call the read attribute name*/
                            strcpy(linker_name, Slinker_name.c_str());
                            strcpy(basAsso.tclass_name, linker_name);/*change the relation class name*/

                            strcpy(toAsso.tclass_name, linker_name);

                            x_class.push_back(linkClass);//add link class into deque
                        }
                    }
                    else{
                        attribute base;
                        strcpy(base.att_name, tempChar);
                        base.isId = false;
                        base.ismulti = false;
                        base.max=1;
                        base.min=1;
                        first = x_class.begin();//get the begin of the deque
                        last = x_class.end();//get the end of the deque
                        for (deque<xmlSclass *>::iterator i=first; i !=last;i++){
                            if(base_name ==(*i)->getname()){
                                (*i)->setattribute(base);
                            }
                        }
                    }
                    
                }
                else if(temp == "association_class"){
                    bool haveAssociation;/*record the true or false have association class*/
                    //call read association qualification function
                    haveAssociation = readAssoQua(fin, x_class, linker_name, basAsso, toAsso);
                    if(haveAssociation == true){
                        haveLink = true;/*record the two class have link class*/
                        strcpy(basAsso.tclass_name, linker_name);/*change the relation class name*/
                        strcpy(toAsso.tclass_name, linker_name);
                    }
                }
                
            }
        }
    }while(associationFinish != true); //end of read the association
    //search correct class in the deque and put the association in it
    
    if(!x_class.empty()){//check the deque is not empty
        first = x_class.begin();//get the begin of the deque
        last = x_class.end();//get the end of the deque
        if(baseLevel==1 && toLevel ==3){baseLevel =2;}//if the relate is 1...*
        if(haveLink == true){//set the class level being 3, as a reference in DTD
            baseLevel =3;
            toLevel =3;
        }
        for (deque<xmlSclass *>::iterator i=first; i !=last;i++){
            if(base_name ==(*i)->getname()){//add association into class
                (*i)->setassociation(basAsso);//add association
                (*i)->setlevel(baseLevel);
                (*i)->setMax(baseMax);
                (*i)->setMin(baseMin);
                if(haveBasequali == true){
                    if(!baseQualification.empty()){/*get the qualification attribute from the deque and add it into the class*/
                        deque<attribute *>::iterator firstAttribute = baseQualification.begin();
                        deque<attribute *>::iterator lastAttribute =   baseQualification.end();
                        for(deque<attribute * >::iterator attributeI = firstAttribute; attributeI != lastAttribute; attributeI++){
                            strcpy(basequali.att_name, (*attributeI)->att_name);
                            basequali.isId = (*attributeI)->isId;
                            basequali.ismulti= (*attributeI)->ismulti;
                            basequali.max= basequali.min = 1;
                            (*i)->setattribute(basequali);
                        }
                    }
                    
                }//finish add attribute if there any
            }
            else if(to_name==(*i)->getname()){
                (*i)->setassociation(toAsso);
                (*i)->setlevel(toLevel);
                (*i)->setMax(toMax);
                (*i)->setMin(toMin);
                
                if(haveToquali ==true){ 
                    if(!toQualification.empty()){/*get the qualification attribute from the deque and add it into the class*/
                        deque<attribute *>::iterator firstToAttribute = toQualification.begin();
                        deque<attribute *>::iterator lastToAttribute =   toQualification.end();
                        for(deque<attribute * >::iterator attributeI = firstToAttribute; attributeI != lastToAttribute; attributeI++){
                            strcpy(toquali.att_name, (*attributeI)->att_name);
                            toquali.isId = (*attributeI)->isId;
                            toquali.ismulti= (*attributeI)->ismulti;
                            toquali.max = toquali.min =1;
                            (*i)->setattribute(toquali);
                        }
                    }
                        
                }
            }
        }//finish add association
    } 
}

bool readLinkAttribute(char* tempChar, xmlSclass* linkClass, ifstream& fin){/*read the link attribute*/
    bool link_attribute = false;
    char filedetail[256];
    string temp;
    do{
        attribute base;
        strcpy(base.att_name, tempChar);
        base.isId = false;
        base.ismulti = false;
        base.max=1;
        base.min=1;
        linkClass->setattribute(base);
        fin.getline(filedetail, 255);
        if(strcmp(filedetail, "")==0){continue;}/*if the line is empty, continue*/
        tempChar = strtok(filedetail,"<>");//cut front of "<"
        tempChar = strtok(NULL, ">");//get detail between < >
        temp = tempChar;
        if(temp == "/link_attribute"){
            link_attribute = true;
        }else{
            tempChar = strtok(NULL, "<>");
        }
    }while(link_attribute !=true);
    
}

bool readAssoQua(ifstream & fin, deque<xmlSclass *>&x_class, char * name, associate & basAsso, associate& toAsso){
    char filedetail[256];/*record the each line of file from the compiler*/
    char * tempChar;
    string temp, qualiClass;
    bool finishQualiAssoClass = false;
    bool haveQualification = false;
    bool haveAssociation = false;/*check the association have detail or not*/
    attribute tempattribute;
    deque<attribute *> tempQualification;
    
    deque<xmlSclass*>::iterator first;/*record the first position of the deque*/
    deque<xmlSclass*>::iterator last;/*record the last position of the deque*/
    do{
        fin.getline(filedetail,255);
        if(strcmp(filedetail, "")==0){continue;}/*if the line is empty, continue*/
        tempChar = strtok(filedetail,"<>");//cut front of "<"
        tempChar = strtok(NULL, "<>");/*get the detail between <> */
        temp = tempChar;
        if(temp=="/association_class" || temp =="/Link"){//check if is end of one association class
            finishQualiAssoClass=true;//is control while loop
        }
        else if(temp == "nameOfAssociationClass"){
            haveAssociation=true;
            tempChar = strtok(NULL, "<>");
            strcpy(name, tempChar);
            qualiClass = tempChar;
            if(!x_class.empty()){//check the deque is not empty
                    first = x_class.begin();//get the begin of the deque
                    last = x_class.end();//get the end of the deque
                    for (deque<xmlSclass *>::iterator i=first; i !=last;i++){
                        if(qualiClass ==(*i)->getname()){//add association into class
                            (*i)->setlevel(1);
                            int tempMulti;
                            tempMulti = basAsso.to_Max;
                            basAsso.to_Max=1;
                            (*i)->setassociation(basAsso);//add association
                            basAsso.to_Max = tempMulti;/*get back the original max link number of the association*/
                            basAsso.base_multi =1;/*change the multi link of the association*/
                            
                            tempMulti = toAsso.to_Max;
                            toAsso.to_Max =1;
                            (*i)->setassociation(toAsso);//add association
                            toAsso.to_Max = tempMulti;/*get back the original multi link number of the association*/
                            toAsso.base_multi =1;/*change the multi link of the association*/
                            if(haveQualification == true){
                                if(!tempQualification.empty()){/*get the qualification attribute from the deque and add it into the class*/
                                    deque<attribute *>::iterator firstAttribute = tempQualification.begin();
                                    deque<attribute *>::iterator lastAttribute =  tempQualification.end();
                                    for(deque<attribute * >::iterator attributeI = firstAttribute; attributeI != lastAttribute; attributeI++){
                                        strcpy(tempattribute.att_name, (*attributeI)->att_name);
                                        tempattribute.isId = (*attributeI)->isId;
                                        tempattribute.ismulti= (*attributeI)->ismulti;
                                        tempattribute.max = tempattribute.min =1;
                                        (*i)->setattribute(tempattribute);//add the attribute into the class
                                    }
                                }
                            }/*finish add all qualification into the class*/
                        }
                    }
                }
        }
        else if(temp == "qualification"){
            haveAssociation = true;
            tempChar = strtok(NULL, "/<");
            temp = tempChar;
            if(temp !="<"){
                attribute * tempAttri = new attribute;
                strcpy(tempAttri->att_name,tempChar);
                tempAttri->isId = true;
                tempAttri->ismulti = false;
                haveQualification =true;
                tempQualification.push_back(tempAttri);
            }
        }
        
    }while(finishQualiAssoClass !=true);
    return haveAssociation;
}
void findMaxMin(string tetemp, int & max, int & min){//find the max and min
    int stringLength = tetemp.length();
    char charString[10];
    string stringA;
    tetemp.copy(charString, stringLength, 0);
    *(charString + stringLength)='\0';
    max = 11;
    min = -1;
    if(stringLength ==2){//set the max and min is same when it only one charater between[]
        if(isdigit(tetemp[1])){
            stringA = charString[1];
            max=min=atoi(stringA.c_str());
        }
    }else{//get the max and min when it more than one charater  between []
        if(isdigit(tetemp[1])){//get the min
            stringA= charString[1];
            min=atoi(stringA.c_str());
            if(isdigit(tetemp[2])){
                stringA= charString[1]; 
                int a= min*10;
                min=atoi(stringA.c_str())+a;                
            }
        }
        if(isdigit(tetemp[stringLength-1])){//get the max
            stringA = charString[stringLength-1];
            max = atoi(stringA.c_str());
            if(isdigit(tetemp[stringLength-2])){
                stringA= charString[stringLength-2];
                int a= atoi(stringA.c_str());
                max= a*10 +max;                
            }
        }
        
    }
}
int findLevel(string temp, int& max, int& min){//find the class level
    int k=-1;
    findMaxMin(temp, max, min);//call function to find the max and min
    if(min == 0){k=0;}
    else if(min==1){k =1;}
    else if(min ==-1){min=1; k=3;}
    else {k=3;}
    return k;
}

void setGeneralisation(deque<xmlSclass *>& x_class, string className, string ISAname){
    string tempGeneral,fatherClass;
    deque<xmlSclass*>::iterator first;/*record the first position of the deque*/
    deque<xmlSclass*>::iterator last;/*record the last position of the deque*/
    if(!x_class.empty()){
        first = x_class.begin();//get the begin of the deque
        last = x_class.end();//get the end of the deque
        for (deque<xmlSclass *>::iterator i=first; i!= last;i++){
            tempGeneral = (*i)->getname();
            if(tempGeneral == className){
                (*i)->setbelong_to(ISAname);//set the belong_to class name
                for(deque<xmlSclass *>::iterator j=first; j!= last;j++){
                    fatherClass = (*j)->getname();
                    int amountAtt = (*j)->getAttributeAmount();
                    if(fatherClass == ISAname){//find the class, and get the attribute
                        (*j)->setHavebelong(true);
                        (*j)->setlevel(1);
                        for(int tempAmount = 0; tempAmount <amountAtt; tempAmount ++){
                            attribute *newAttribute = (*j)->getattribute();
                            attribute tempAttribute;
                            strcpy(tempAttribute.att_name, newAttribute->att_name);
                            tempAttribute.isId= newAttribute->isId;
                            tempAttribute.ismulti= newAttribute->ismulti;
                            (*i)->setattribute(tempAttribute);//copy attribute from the "father" to the "son" class
                        }
                    }
                }
            }
        }
    }
}

void setClassLevel(deque<xmlSclass *> & x_Class){
    deque<xmlSclass*>::iterator first;/*record the first position of the deque*/
    deque<xmlSclass*>::iterator last;/*record the last position of the deque*/
    first = x_Class.begin(); 
    last = x_Class.end();
    for (deque<xmlSclass *>::iterator i=first; i!= last;i++){
        if((*i)->getlevel()==0 || (*i)->getlevel() == -1){
            (*i)->setlevel(4);/*set all class being level 4 if there is in level -1 or 0*/
        }
    }
    
}

void setReferenceClass(deque<xmlSclass *> & x_Class, string className){
    deque<xmlSclass*>::iterator first;/*record the first position of the deque*/
    deque<xmlSclass*>::iterator last;/*record the last position of the deque*/
    first = x_Class.begin();
    last = x_Class.end();
    int numberAssoication;
    for (deque<xmlSclass *>::iterator i=first; i !=last;i++){
        if((*i)->getname()== className){
            if((*i)->getRef() ==true){/*find the match class and the class Ref is true than set it false*/
                (*i)->setRef(false);
                numberAssoication = (*i)->getAssociaAmount();
                for(int current=0; current<numberAssoication; current++){/*set all classes relate to this class being the not reference class*/
                        associate * tempAsso = (*i)->getassociation(current);
                        if(tempAsso->base_multi <3 || tempAsso->to_multi <3 ){
                        string tempAssoname =  tempAsso->tclass_name;
                        setReferenceClass(x_Class, tempAssoname);/*to find are there any class have relationship with this class*/
                        }
                }
                for(deque<xmlSclass *>::iterator j = first; j!= last; j++) {
                    string belong_to; 
                    belong_to = (*j)->getbelong_to();
                    if(belong_to == (*i)->getname()){/*if the class is belong to the (*i) class, set this class is reference class*/
                        (*j)->setRef(false);
                        setReferenceClass(x_Class, (*j)->getname());/*to find are there any class is belong to this class*/
                    }
                }
            }
            
        }
    }
}

bool writeClass(deque<xmlSclass*> & x_Class){//write the detail into xmlS document
    int tab=4;
    ofstream fout("XmlSechmaFile.xsd", ios::out);
    deque<xmlSclass*>::iterator first;/*record the first position of the deque*/
    first = x_Class.begin();
    string  rootName;
    rootName = (*first)->getname();/*take the first element of the deque be the root class*/
    (*first)->setInHeader(true);
    setReferenceClass(x_Class, rootName);/*set the not relate to the root class being reference class*/
    if (fout.fail()){return false;}
    else{/*write the header */
        fout<< "<?xml version=\"1.0\"?>"<<endl;
        fout<< "<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" " <<endl;
        fout << "targetNamespace= \"http://www.w3schools.com\" "<<endl;
        fout << "xmlns =\"http://www.w3schools.com\" elementFormDefault=\"qualified\"> "<<endl;
        fout << endl<<endl;
        fout << "<xsd:element name = \"root\">"<<endl;
        fout << "   <xsd:complexType>"<<endl;
        fout << "      <xsd:choice maxOccurs=\"unbounded\" minOccurs =\"0\">"<<endl;
        /*call write a single class function*/
        writeSingleClass(fout, x_Class, rootName, tab, (*first)->getMax(), (*first)->getMin());
        writeReferenceClass(fout, x_Class, tab);
        fout << "      </xsd:choice>"<<endl;
        fout << "   </xsd:complexType>"<<endl;
        fout << "</xsd:element>"<<endl;
        fout << "</xsd:schema>"<<endl;
    }
    
    return true;
}

bool writeSingleClass(ofstream& fout, deque<xmlSclass *> & x_Class, string rootName, int & tab, int occurMax, int occurMin){
    deque<xmlSclass*>::iterator first;/*record the first position of the deque*/
    deque<xmlSclass*>::iterator last;/*record the last position of the deque*/
    first = x_Class.begin();//get the begin of the deque
    last = x_Class.end();//get the end of the deque
    deque<xmlSclass*>::iterator it;
    int numberAssoication, numberAttribute;
    bool written = true;
    for(it = first;it!= last; it++){
        if((*it)->getname() == rootName){
            if((*it)->getread() == false){
                (*it)->setread(true);/*set the class being written into the file*/
                
                for(int i=0;i<tab;i++){fout <<"   ";}
                fout <<" <xsd:element name = \""<<rootName<< "\" maxOccurs=\"";
                if(occurMax>10){
                    fout<< "unbounded";
                }
                else{
                    fout <<occurMax;
                }
                fout<< "\" minOccurs =\"";
                if(occurMin==0){
                    fout<<"0\" > "<<endl;
                }else{fout << occurMin<<"\" > "<<endl;}
                tab++;
                for(int i=0;i<tab;i++){fout <<"   ";}
                fout << "<xsd:complexType>"<<endl;
                numberAssoication = (*it)->getAssociaAmount();
                numberAttribute = (*it)->getAttributeAmount();
                if(numberAssoication>0){
                    tab++;
                    for(int i=0;i<tab;i++){fout <<"   ";}
                    fout << "<xsd:choice maxOccurs=\"unbounded\">"<<endl;
                }else if(numberAttribute>0  &&numberAssoication==0 ){
                    tab++;
                    for(int i=0;i<tab;i++){fout <<"   ";}
                    fout << "<xsd:sequence>"<<endl;
                }
                (*it)->print_detail(fout, tab);/*print the attribute*/
                tab++;
                for(int current=0; current<numberAssoication; current++){
                        associate * tempAsso = (*it)->getassociation(current);
                        string tempAssoname = tempAsso->tclass_name;
                        if((tempAsso->base_multi <3 || tempAsso->to_multi <3 ) && tempAssoname!=rootName ){ /*the relationship is 0..1, 1..1 or 1..* write class */
                            
                            writeSingleClass(fout, x_Class, tempAssoname, tab, tempAsso->to_Max, tempAsso->to_Min);/*if return true, meaning the class had not write into file. return false, meaning the class had written in file*/
                        }else{
                            string className;
                            bool appearClass=false;
                            className = tempAsso->tclass_name;//get the association class name
                            for(deque<xmlSclass*>::iterator i = first;i!= last; i++){
                                if(className == (*i)->getname() && (*i)->getread() == true){//check whether the association class have write into the file or not 
                                    appearClass = true;
                                }
                                if(className == rootName){appearClass = false;}
                            }
                            
                            if(appearClass == false){// if the class not write into file before, write the idref into the file
                                for(int i=0;i<tab;i++){fout <<"   ";}
                                fout <<" <xsd:element name=\""<< tempAsso->tclass_name<<"\" maxOccurs=\"";
                                if(tempAsso->to_Max >10){
                                    fout <<"unbounded\" minOccurs=\" " << tempAsso->to_Min << "\" >"<<endl;
                                }else{
                                    fout<<tempAsso->to_Max<<"\" minOccurs=\" " << tempAsso->to_Min << "\" >"<<endl;
                                }
                                for(int i=0;i<tab;i++){fout <<"   ";}
                                fout << "   <xsd:complexType>"<<endl;
                                for(int i=0;i<tab+1;i++){fout <<"   ";}
                                fout << "   <xsd:sequence>"<<endl;
                                for(int i=0;i<tab+1;i++){fout <<"   ";}
                                fout << "      <xsd:element name=\"IDREF\" type=\"xsd:IDREF\" />"<<endl;
                                for(int i=0;i<tab+1;i++){fout <<"   ";}
                                fout << "   </xsd:sequence>"<<endl;
                                for(int i=0;i<tab;i++){fout <<"   ";}
                                fout << "   </xsd:complexType>"<<endl;
                                for(int i=0;i<tab;i++){fout <<"   ";}
                                fout <<" </xsd:element>"<<endl;
                            }
                        }
                }
                if(numberAssoication>0){
                    tab--;
                    for(int i=0;i<tab;i++){fout <<"   ";}
                    fout << "</xsd:choice>"<<endl;
                }else if(numberAttribute>0  &&numberAssoication==0 ){
                    tab--;
                    for(int i=0;i<tab;i++){fout <<"   ";}
                    fout << "</xsd:sequence>"<<endl;
                }
                tab--;
                
                for(int i=0;i<tab;i++){fout <<"   ";}
                fout << "</xsd:complexType>"<<endl;
                tab--;
                for(int i=0;i<tab;i++){fout <<"   ";}
                fout<<" </xsd:element>"<<endl;
                for(deque<xmlSclass*>::iterator generation = first; generation!=last; generation++){/*check the class which belong to this class*/
                    if((*generation)->getbelong_to() == rootName && (*generation)->getread()==false){
                        string tempGenName = (*generation)->getname();
                        writeSingleClass(fout, x_Class,tempGenName, tab, (*generation)->getMax(), (*generation)->getMin() );
                    }
                }
                
            }return written;
        }
    }
    return written;
}
void writeReferenceClass(ofstream& fout, deque<xmlSclass *> & x_Class, int & tab){
    deque<xmlSclass*>::iterator first;/*record the first position of the deque*/
    deque<xmlSclass*>::iterator last;/*record the last position of the deque*/
    first = x_Class.begin();//get the begin of the deque
    last = x_Class.end();//get the end of the deque
    deque<xmlSclass*>::iterator it;
    for(it = first;it!= last; it++){
        if((*it)->getread() == false){/*if the class has not write into the file, write it to the file*/
                (*it)->setread(true);/*set the class being written into the file*/
                for(int i=0;i<tab;i++){fout <<"   ";}
                fout <<" <xsd:element name = \""<<(*it)->getname()<< "\" maxOccurs=\"";
                if((*it)->getMax() >9){
                    fout <<"unbounded\" minOccurs=\" " << (*it)->getMin() << "\" >"<<endl;
                }else{
                    fout<<(*it)->getMax()<<"\" minOccurs=\" " << (*it)->getMin()<< "\" >"<<endl;
                }
                tab++;
                for(int i=0;i<tab;i++){fout <<"   ";}
                fout << "<xsd:complexType>"<<endl;
                int numberAssoication = (*it)->getAssociaAmount();
                int numberAttribute = (*it)->getAttributeAmount();
                if((numberAssoication + numberAttribute)>0){
                    tab++;
                    for(int i=0;i<tab;i++){fout <<"   ";}
                    fout << "<xsd:choice maxOccurs=\"unbounded\">"<<endl;
                }tab++;
                (*it)->print_detail(fout, tab);/*print the attribute*/
                tab++;
                for(int current=0; current<numberAssoication; current++){
                        associate * tempAsso = (*it)->getassociation(current);
                        string tempAssoname = tempAsso->tclass_name;
                        if((tempAsso->base_multi <3 || tempAsso->to_multi <3 ) && tempAssoname!=(*it)->getname() ){ /*the relationship is 0..1, 1..1 or 1..* write class */
                            
                            writeSingleClass(fout, x_Class, tempAssoname, tab, tempAsso->to_Max, tempAsso->to_Min);/*if return true, meaning the class had not write into file. return false, meaning the class had written in file*/
                        }else{
                            string className;
                            bool appearClass=false;
                            className = tempAsso->tclass_name;//get the association class name
                            for(deque<xmlSclass*>::iterator i = first;i!= last; i++){
                                if(className == (*i)->getname() && (*i)->getread() == true){//check whether the association class have write into the file or not 
                                    appearClass = true;
                                }
                                if(className == (*it)->getname()){appearClass = false;}
                            }
                            
                            if(appearClass == false){// if the class not write into file before, write the idref into the file
                                for(int i=0;i<tab;i++){fout <<"   ";}
                                fout <<" <xsd:element name=\""<< tempAsso->tclass_name<<"\" maxOccurs=\"";
                                if(tempAsso->to_Max >10){
                                    fout <<"unbounded\" minOccurs=\" " << tempAsso->to_Min << "\" >"<<endl;
                                }else{
                                    fout<<tempAsso->to_Max<<"\" minOccurs=\" " << tempAsso->to_Min << "\" >"<<endl;
                                }
                                for(int i=0;i<tab;i++){fout <<"   ";}
                                fout << "   <xsd:complexType>"<<endl;
                                for(int i=0;i<tab+1;i++){fout <<"   ";}
                                fout << "   <xsd:sequence>"<<endl;
                                for(int i=0;i<tab+1;i++){fout <<"   ";}
                                fout << "      <xsd:element name=\"IDREF\" type=\"xsd:IDREF\" />"<<endl;
                                for(int i=0;i<tab+1;i++){fout <<"   ";}
                                fout << "   </xsd:sequence>"<<endl;
                                for(int i=0;i<tab;i++){fout <<"   ";}
                                fout << "   </xsd:complexType>"<<endl;
                                for(int i=0;i<tab;i++){fout <<"   ";}
                                fout <<" </xsd:element>"<<endl;
                            }
                            
                        }
                }
                tab--;
                if((numberAssoication + numberAttribute)>0){
                    tab--;
                    for(int i=0;i<tab;i++){fout <<"   ";}
                    fout << "</xsd:choice>"<<endl;
                }
                tab--;
                for(int i=0;i<tab;i++){fout <<"   ";}
                fout << "</xsd:complexType>"<<endl;
                tab--;
                for(int i=0;i<tab;i++){fout <<"   ";}
                fout<<" </xsd:element>"<<endl;
        }
    }
    
}
