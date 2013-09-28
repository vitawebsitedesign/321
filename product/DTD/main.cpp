/* 
 * File:   main.cpp
 * project
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
#include "dtdc.h"
using namespace std;
bool CompRule(dtdclass* lclass, dtdclass* rclass);//rule of compare
bool read(deque<dtdclass *>& d_class);/*main reading function to read the file */
void readSingleClass(ifstream & fin, dtdclass * tempclass);/*read a single class detail*/
void readAssoClass(ifstream &fin, associate & basAsso, associate& toAsso, int & level, bool & havequali, deque<attribute * > & quali);/*read class detail in the association*/
void readSingleAssociation(ifstream &fin, deque<dtdclass *>&d_class);/*read a single association*/
bool readLinkAttribute(char* tempChar, dtdclass* linkClass, ifstream& fin);/*read the linker classes attribute*/
bool readAssoQua(ifstream & fin, deque<dtdclass *>&d_class, char * name, associate & basAsso, associate& toAsso);/*read the linker's qualification*/
void findMaxMin(string tetemp, int & max, int & min);//find the max and min
int findLevel(string temp, int & max, int & min);/*find the class level*/
void setGeneralisation(deque<dtdclass *>& d_class, string className, string ISAname);/*set the generalisation of the class*/
void setClassLevel(deque<dtdclass *> & d_Class);/*when the class is 0..1 or 0..*, set the class be level 4*/
void setReferenceClass(deque<dtdclass *> & d_Class, string className);/*set the class is the reference class*/
string getReferenceClass(deque<dtdclass *> & d_Class, string root);//function to find the reference class
bool getISA(deque<dtdclass*> & d_Class, string temp, string & ISAname);/*get the generalisation class*/

bool writeClass(deque<dtdclass *> &dClass);/*write the detail into the DTD format document*/
bool writeSingleClass(ofstream& fout, deque<dtdclass *> & d_Class, string rootName, deque<string> & element);/*write the class and it sub-class into dtd file*/
void writeReferenceClass(ofstream& fout, deque<dtdclass *> & d_Class, deque<string> & element);/*write the reference class into file*/
/*
 * 
 */
int main() {
    deque<dtdclass*> dClass;
    
   if(read(dClass)==false){/*read the output from the compiler*/
       cout << "read xml error."<< endl;
       return 0;
   }
   else{
       if(!dClass.empty()){
           setClassLevel(dClass);/*set all class being in the standard level*/
           sort(dClass.begin(), dClass.end(), CompRule);/*sort the level of the class, and get the lowest one*/
           writeClass(dClass);/*write the detail into the DTD format document*/
       }
       
   }
    
    return 0;
}

bool CompRule(dtdclass* lclass,  dtdclass* rclass){//rule of compare
    return lclass->getlevel() < rclass->getlevel();
}

bool read(deque<dtdclass*>& d_class){/*read from the compiler's out put */
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
                dtdclass * tempclass = new dtdclass();
                readSingleClass(fin, tempclass);/*Call read single class function to get detail*/
                d_class.push_back(tempclass);/*push the class into the deque*/
                
            }
            else if(temp=="association"){/*if it is association, add association into class*/
                
                readSingleAssociation(fin, d_class);
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
                /*find the same name class in the deque, and set the depend name.*/
                if(generlisation.size()==1){
                    setGeneralisation(d_class, className, ISAname);//call set function to set the generalisation
                }
                else if(generlisation.size() >1){
                    deque<string>::iterator firstGen = generlisation.begin();
                    deque<string>::iterator lastGen = generlisation.end();
                    for(firstGen; firstGen != lastGen; firstGen++){
                        string tempGenClass;
                        tempGenClass = *firstGen;
                        setGeneralisation(d_class, tempGenClass, ISAname);//call set function to set the generalisation
                    }
                }
                
            }
        }
        
    }
    fin.close();
    return true;
}

void readSingleClass(ifstream & fin, dtdclass * tempclass){/*read a single class detail*/
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
            tempChar = strtok(NULL,"<>");//get the name of the class*/
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
void readAssoClass(ifstream &fin, associate & basAsso, associate& toAsso, int & level, bool & havequali, deque<attribute *> & qualification){
    char filedetail[256];/*record the each line of file from the compiler*/
    char * tempChar;
    string temp;
    bool finishReadAssoClass = false;
    int max=11, min=0;
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
                level = findLevel(temp, max, min);//the level of the class
                basAsso.base_multi = level;
                basAsso.base_Max = max;
                basAsso.base_Min =min;
                toAsso.to_Min = min;
                toAsso.to_Max =max;
                toAsso.to_multi =level;//the 0...1 is 0, 1..1is 1, 1...* is 3 use to decide the "+, *" in DTD
            }
            else{
                level = 1;
                basAsso.base_multi = 1;
                basAsso.base_Max =1;
                basAsso.base_Min =min;
                toAsso.to_Min = min;
                toAsso.to_Max =1;
                toAsso.to_multi =1;
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

void readSingleAssociation(ifstream &fin, deque<dtdclass *>&d_class){
   
    bool associationFinish=false;
    bool firstclass = true;
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
    deque<dtdclass*>::iterator first;/*recond the first position of the deque*/
    deque<dtdclass*>::iterator last;/*recond the last position of the deque*/
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
                    readAssoClass(fin, basAsso, toAsso, baseLevel,haveToquali,toQualification);
                    
                    firstclass = !firstclass;
                    strcpy(toAsso.tclass_name, tempChar);/*record the relation class*/
                    base_name = tempChar;
                    Slinker_name = base_name;/*record the name of first class*/
                    }
                else{
                    /*call function to read detail of the association of the second class*/
                    readAssoClass(fin, toAsso, basAsso, toLevel,haveBasequali, baseQualification );
                    
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
                            dtdclass * linkClass = new dtdclass();/*creast a linker class*/
                            linkClass->setname(Slinker_name);
                            linkClass->setlevel(1);
                            int tempMulti;
                            tempMulti = basAsso.to_multi;/*change the multi link of the association*/
                            basAsso.to_multi =1;
                            linkClass->setassociation(basAsso);/*set the association of the link class*/
                            /*get back the original multi link number of the association*/
                            basAsso.to_multi = tempMulti;
                            tempMulti = toAsso.to_multi;
                            toAsso.to_multi = 1;
                            linkClass->setassociation(toAsso);
                            toAsso.to_multi = tempMulti;

                            readLinkAttribute(tempChar, linkClass, fin);/*call the read attribute name*/
                            strcpy(linker_name, Slinker_name.c_str());
                            strcpy(basAsso.tclass_name, linker_name);/*change the relation class name*/
                            basAsso.base_multi =1;
                            strcpy(toAsso.tclass_name, linker_name);
                            toAsso.base_multi =1;
                            d_class.push_back(linkClass);//add link class into deque
                        }
                    }
                    else{
                        attribute base;
                        strcpy(base.att_name, tempChar);
                        base.isId = false;
                        base.ismulti = false;
                        base.max=1;
                        base.min=1;
                        first = d_class.begin();//get the begin of the deque
                        last = d_class.end();//get the end of the deque
                        for (deque<dtdclass *>::iterator i=first; i !=last;i++){
                            if(base_name ==(*i)->getname()){
                                (*i)->setattribute(base);
                            }
                        }
                    }
                    
                    
                }
                else if(temp == "association_class"){
                    bool haveAssociation;/*record the true or false have association class*/
                    //call read association qualification function
                    haveAssociation = readAssoQua(fin, d_class, linker_name, basAsso, toAsso);
                    if(haveAssociation == true){
                        haveLink = true;/*record the two class have link class*/
                        strcpy(basAsso.tclass_name, linker_name);/*change the relation class name*/
                        basAsso.base_multi =1;
                        strcpy(toAsso.tclass_name, linker_name);
                        toAsso.base_multi =1;
                    }
                }
                
            }
        }
    }while(associationFinish != true); //end of read the association
    //search correct class in the deque and put the association in it
    
    if(!d_class.empty()){//check the deque is not empty
        first = d_class.begin();//get the begin of the deque
        last = d_class.end();//get the end of the deque
        if(baseLevel==1 && toLevel ==3){baseLevel =2;}//if the relate is 1...*
        if(haveLink == true){//set the class level being 3, as a reference in DTD
            baseLevel =3;
            toLevel =3;
        }
        for (deque<dtdclass *>::iterator i=first; i !=last;i++){
            if(base_name ==(*i)->getname()){//add association into class
                (*i)->setassociation(basAsso);//add association
                (*i)->setlevel(baseLevel);
                if(haveBasequali == true){
                    if(!baseQualification.empty()){/*get the qualification attribute from the deque and add it into the class*/
                        deque<attribute *>::iterator firstAttribute = baseQualification.begin();
                        deque<attribute *>::iterator lastAttribute =   baseQualification.end();
                        for(deque<attribute * >::iterator attributeI = firstAttribute; attributeI != lastAttribute; attributeI++){
                            strcpy(basequali.att_name, (*attributeI)->att_name);
                            basequali.isId = (*attributeI)->isId;
                            basequali.ismulti= (*attributeI)->ismulti;
                            (*i)->setattribute(basequali);
                        }
                    }
                    
                }//add attribute if there any
            }
            else if(to_name==(*i)->getname()){
                (*i)->setassociation(toAsso);
                (*i)->setlevel(toLevel);
                if(haveToquali ==true){ 
                    if(!toQualification.empty()){/*get the qualification attribute from the deque and add it into the class*/
                        deque<attribute *>::iterator firstToAttribute = toQualification.begin();
                        deque<attribute *>::iterator lastToAttribute =   toQualification.end();
                        for(deque<attribute * >::iterator attributeI = firstToAttribute; attributeI != lastToAttribute; attributeI++){
                            strcpy(toquali.att_name, (*attributeI)->att_name);
                            toquali.isId = (*attributeI)->isId;
                            toquali.ismulti= (*attributeI)->ismulti;
                            (*i)->setattribute(toquali);
                        }
                    }
                        
                }
            }
        }//finish add association
    } 
}

bool readLinkAttribute(char* tempChar, dtdclass* linkClass, ifstream& fin){/*read the link attribute*/
    
    bool link_attribute = false;
    char filedetail[256];
    string temp;
    do{
        attribute base;
        strcpy(base.att_name, tempChar);
        base.isId = false;
        base.ismulti = false;
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

bool readAssoQua(ifstream & fin, deque<dtdclass *>&d_class, char * name, associate & basAsso, associate& toAsso){
    char filedetail[256];/*record the each line of file from the compiler*/
    char * tempChar;
    string temp, qualiClass;
    bool finishQualiAssoClass = false;
    bool haveQualification = false;
    bool haveAssociation = false;/*check the association have detail or not*/
    attribute tempattribute;
    deque<attribute *> tempQualification;
    
    deque<dtdclass*>::iterator first;/*recond the first position of the deque*/
    deque<dtdclass*>::iterator last;/*recond the last position of the deque*/
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
            if(!d_class.empty()){//check the deque is not empty
                    first = d_class.begin();//get the begin of the deque
                    last = d_class.end();//get the end of the deque
                    for (deque<dtdclass *>::iterator i=first; i !=last;i++){
                        if(qualiClass ==(*i)->getname()){//add association into class
                            (*i)->setlevel(1);
                            int tempMulti;
                            tempMulti = basAsso.to_multi;
                            basAsso.to_multi = 1;/*change the multi link of the association*/
                            (*i)->setassociation(basAsso);//add association
                            basAsso.to_multi = tempMulti;;/*get back the original multi link number of the association*/
                            tempMulti = toAsso.to_multi;
                            toAsso.to_multi =1;/*change the multi link of the association*/
                            (*i)->setassociation(toAsso);//add association
                            toAsso.to_multi = tempMulti;/*get back the original multi link number of the association*/
                            if(haveQualification == true){
                                if(!tempQualification.empty()){/*get the qualification attribute from the deque and add it into the class*/
                                    deque<attribute *>::iterator firstAttribute = tempQualification.begin();
                                    deque<attribute *>::iterator lastAttribute =  tempQualification.end();
                                    for(deque<attribute * >::iterator attributeI = firstAttribute; attributeI != lastAttribute; attributeI++){
                                        strcpy(tempattribute.att_name, (*attributeI)->att_name);
                                        tempattribute.isId = (*attributeI)->isId;
                                        tempattribute.ismulti= (*attributeI)->ismulti;
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
int findLevel(string temp, int & max, int & min){//find the class level
    int k=-1;
    findMaxMin(temp, max, min);//call function to find the max and min
    if(min == 0){k=0;}
    else if(min ==1 && max >2){k=3;}
    else if(min==1){k =1;}
    else if(min ==-1){min=1; k=3;}
    else {k=3;}
    return k;
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

void setGeneralisation(deque<dtdclass *>& d_class, string className, string ISAname){
    string tempGeneral,fatherClass;
    deque<dtdclass*>::iterator first;/*record the first position of the deque*/
    deque<dtdclass*>::iterator last;/*record the last position of the deque*/
    if(!d_class.empty()){
        first = d_class.begin();//get the begin of the deque
        last = d_class.end();//get the end of the deque
        for (deque<dtdclass *>::iterator i=first; i!= last;i++){
            tempGeneral = (*i)->getname();
            if(tempGeneral == className){
                (*i)->setbelong_to(ISAname);//set the belong_to class name
                for(deque<dtdclass *>::iterator j=first; j!= last;j++){
                    fatherClass = (*j)->getname();
                    int amountAtt = (*j)->getAttributeAmount();
                    if(fatherClass == ISAname){//find the class, and get the attribute
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

void setClassLevel(deque<dtdclass *> & d_Class){
    deque<dtdclass*>::iterator first;/*recond the first position of the deque*/
    deque<dtdclass*>::iterator last;/*recond the last position of the deque*/
    first = d_Class.begin(); 
    last = d_Class.end();
    for (deque<dtdclass *>::iterator i=first; i!= last;i++){
        if((*i)->getlevel()==0 || (*i)->getlevel() == -1){
            (*i)->setlevel(4);/*set all class being level 4 if there is in level -1 or 0*/
        }
    }
    
}

void setReferenceClass(deque<dtdclass *> & d_Class, string className){
    deque<dtdclass*>::iterator first;/*record the first position of the deque*/
    deque<dtdclass*>::iterator last;/*record the last position of the deque*/
    first = d_Class.begin();
    last = d_Class.end();
    int numberAssoication;
    for (deque<dtdclass *>::iterator i=first; i !=last;i++){
        if((*i)->getname()== className){
            if((*i)->getRef() ==true){/*find the match class and the class Ref is true than set it false*/
                (*i)->setRef(false);
                numberAssoication = (*i)->getAssociaAmount();
                for(int current=0; current<numberAssoication; current++){/*set all classes relate to this class being the not reference class*/
                        associate * tempAsso = (*i)->getassociation(current);
                        if(tempAsso->base_Max < 3 || tempAsso->to_Max < 3 ){
                        string tempAssoname =  tempAsso->tclass_name;
                        setReferenceClass(d_Class, tempAssoname);/*to find are there any class have relationship with this class*/
                        }
                }
                for(deque<dtdclass *>::iterator j = first; j!= last; j++) {
                    string belong_to; 
                    belong_to = (*j)->getbelong_to();
                    if(belong_to == (*i)->getname()){/*if the class is belong to the (*i) class, set this class is reference class*/
                        (*j)->setRef(false);
                        setReferenceClass(d_Class, (*j)->getname());/*to find are there any class is belong to this class*/
                    }
                }
            }
            
        }
    }
}


string getReferenceClass(deque<dtdclass *> & d_Class, string root){//function to find the reference class
    deque<dtdclass*>::iterator first;/*record the first position of the deque*/
    deque<dtdclass*>::iterator last;/*record the last position of the deque*/
    first = d_Class.begin();//get the begin of the deque
    last = d_Class.end();//get the end of the deque
    if(getISA(d_Class, root, root)==true){/*check the root class have any gener class*/
        root = "("+root+")+";
    }else{root = root+"+";}
    for (deque<dtdclass *>::iterator i=first; i !=last;i++){
        if(((*i)->getRef())==true && (*i)->getInHeader()==false){
            string temp;
            string ISAname;
            temp = (*i)->getname();
            ISAname = (*i)->getname();
            if(getISA(d_Class, temp, ISAname)==true){
                root = root + ", (" + ISAname + ")"; /*add the class name in to the string*/
            }
            else{
                root  = root + ", " + (*i)->getname();/*add the class name in to the string*/
            }
            if((*i)->getlevel()==1){root = root + "+";}
            else{root = root + "*";}
        }
    }
    return root;
}
bool getISA(deque<dtdclass*> & d_Class, string temp, string & ISAname){/*get the string of the class in "  |   |   | "  style*/
    deque<dtdclass*>::iterator first;/*record the first position of the deque*/
    deque<dtdclass*>::iterator last;/*record the last position of the deque*/
    first = d_Class.begin();//get the begin of the deque
    last = d_Class.end();//get the end of the deque
    deque<dtdclass*>::iterator it;
    bool haveISA= false;
    for(it = first;it!= last; it++){
        if((*it)->getbelong_to()==temp && (*it)->getInHeader() == false){
            (*it)->setInHeader(true);//set the isInHeader being true
            string temp;
            haveISA = true;
            temp = (*it)->getname();/*get the name */
            ISAname = ISAname + "|"+ temp;
            getISA(d_Class, temp, ISAname);
        }
    }
    return haveISA;
}

bool writeClass(deque<dtdclass*> & d_Class){//write the detail into dtd document
    ofstream fout("DtdFile.dtd", ios::out);
    deque<dtdclass*>::iterator first;/*record the first position of the deque*/
    deque<string> element;
    first = d_Class.begin();
    string tempName, rootName;
    rootName = (*first)->getname();/*take the first element of the deque be the root class*/
    (*first)->setInHeader(true);
    setReferenceClass(d_Class, rootName);/*set the not relate to the root class being reference class*/
    tempName = getReferenceClass(d_Class, rootName);//call the function to find the reference class
    if (fout.fail()){return false;}
    else{
        fout << "<!ELEMENT root ( " <<tempName << " )>" <<endl;
        /*call write a single class function*/
        writeSingleClass(fout, d_Class, rootName, element);
        writeReferenceClass(fout, d_Class, element);
    }
    return true;
}

bool writeSingleClass(ofstream& fout, deque<dtdclass *> & d_Class, string rootName, deque<string> & element){
    deque<dtdclass*>::iterator first;/*record the first position of the deque*/
    deque<dtdclass*>::iterator last;/*record the last position of the deque*/
    first = d_Class.begin();//get the begin of the deque
    last = d_Class.end();//get the end of the deque
    deque<dtdclass*>::iterator it;
    int numberAssoication;
    bool written = true;
    for(it = first;it!= last; it++){/*search each class in the deque*/
        if((*it)->getname() == rootName){
            if((*it)->getread() == false){/*if the class has not write into the file, write it to the file*/
                (*it)->setread(true);/*set the class being written into the file*/
                fout<<"<!ELEMENT "<<rootName <<" ( ";
                (*it)->printAttributeHead(fout);/*call function to write the class header */
                numberAssoication = (*it)->getAssociaAmount();/*get the class association amount*/
                int numberAttribute = (*it)->getAttributeAmount();/*get the class attribute amount*/
                bool haveInHearder=false;/*to control the () have detail or not*/
                for(int current=0; current<numberAssoication; current++){/*write the association into the header*/
                    associate * tempAsso = (*it)->getassociation(current);
                    string tempAssoname =  tempAsso->tclass_name;
                    for(deque<dtdclass*>::iterator associationInHead = first; associationInHead != last; associationInHead++){
                        if(tempAssoname == rootName || ((*associationInHead)->getname() ==tempAssoname && (*associationInHead)->getInHeader()==false)){
                            (*associationInHead)->setInHeader(true);
                            string getISAname;
                            getISAname = tempAssoname;
                            if(getISA(d_Class, tempAssoname, getISAname)==true){/*check this class have generlisation*/
                                if(numberAttribute !=0){
                                    if((*it)->getRef()== true){fout<< "| ";}
                                    else{fout<<", ";}
                                }
                                else if(haveInHearder != false && numberAttribute ==0 ){ 
                                    if((*it)->getRef()== true){fout<< "| ";}
                                    else{fout<<", ";}
                                }
                                else if(haveInHearder ==false){haveInHearder =true;}
                                fout<<"("<< getISAname<<")";
                            }else{
                                if(numberAttribute !=0){
                                        if((*it)->getRef()== true){fout<< "| ";}
                                        else{fout<<", ";}
                                }
                                else if(haveInHearder != false && numberAttribute ==0 ){
                                    if((*it)->getRef()== true){fout<< "| ";}
                                    else{fout<<", ";}
                                }
                                else if(haveInHearder ==false){haveInHearder =true;}
                                fout<< tempAssoname;
                            }
                            if((*it)->getRef()==false){
                                if(tempAsso->to_Min ==0 && tempAsso->to_Max ==1){fout<<"?";}
                                else if(tempAsso->to_Min==1 && tempAsso->to_Max>1 && tempAsso->to_multi !=1){fout<<"+";}/*check the association is occurs 0 or1 */
                                else{
                                    if(tempAsso->to_multi !=1){fout <<"*";}
                                }
                            }
                        break;}
                    }
                }
                /*if the header () is empty, print the #PCDATA in it*/
                if(haveInHearder == false && numberAttribute ==0 ){fout<<" #PCDATA ";}
                
                if((*it)->getRef()== true){fout<< ")*>"<<endl;}
                else{fout<< ") >"<<endl;}
                (*it)->print_detail(fout, element);
                for(int current=0; current<numberAssoication; current++){
                        associate * tempAsso = (*it)->getassociation(current);
                        if(tempAsso->base_multi !=3 || tempAsso->to_multi !=3 ){ /*the relationship is 0..1, 1..1 or 1..* write class */
                            string tempAssoname =  tempAsso->tclass_name;
                            writeSingleClass(fout, d_Class, tempAssoname, element);/*if return true, meaning the class had not write into file. return false, meaning the class had written in file*/
                        }
                }
                for(deque<dtdclass*>::iterator belongAssociation = first; belongAssociation != last; belongAssociation++){
                    if( (*belongAssociation)->getbelong_to()==rootName){/*check are there any class is ISA relationship with the association class and has not write into the file*/
                        string tempBelong = (*belongAssociation)->getname();
                        if((*belongAssociation)->getread()==false){
                            writeSingleClass(fout, d_Class, tempBelong, element);/*call the function to write the function into the file*/
                        }
                    }
                }
            }
            else{/*if the class had written into the file*/
                written = false;
            }
        }
    }
    return written;
}
void writeReferenceClass(ofstream& fout, deque<dtdclass *> & d_Class, deque<string> & element){
    deque<dtdclass*>::iterator first;/*record the first position of the deque*/
    deque<dtdclass*>::iterator last;/*record the last position of the deque*/
    first = d_Class.begin();//get the begin of the deque
    last = d_Class.end();//get the end of the deque
    deque<dtdclass*>::iterator it;
    for(it = first;it!= last; it++){
        if((*it)->getread() == false){/*if the class has not write into the file, write it to the file*/
                (*it)->setread(true);/*set the class being written into the file*/
                fout<< "<!ELEMENT "<< (*it)->getname() <<" ( " ;/*print out the detail into file*/
                (*it)->printAttributeHead(fout);
                fout<<" )* >"<<endl;
                (*it)->print_detail(fout, element);/*call class print detail of the class*/
        }
    }
    
}
