#ifndef XMLSCH_H
#define	XMLSCH_H
/* 
 * File:   xmlSch.h
 * project
 * Author: Xingfang Huang
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
struct attribute{
    char att_name[64];//name of the attribute
    bool isId;//the attribute is ID or not
    bool ismulti;//is the multi of the attribute
    int max;
    int min;
    attribute * next;//link to the next
};
struct associate{
    char ass_name[64];//name of association or the name of the link
    int base_multi;//is 0, 1,or 3 of the class itself
    int to_multi;//is 0, 1 or 3 of the relate class
    int to_Max;
    int to_Min;
    char tclass_name[64];//record the name of the association class 
    associate *next;//link to the next
};
class xmlSclass{
    string x_name;//name of the class
    string belong_to;//recond the name of the father class if the class ISA some class
    int level_class;//recond the level of the class, use to find the "root" class
    bool readornot; //record the class has been write to the docunment or not
    bool isRef;//record the class is the reference class or not
    bool isInHeader;//record the class is in other class header
    int attriAmount;//record the number of attribute;
    int associAmount;// record the number of association
    int minimum;//record the minimum
    int maximum;//record the maximun
    bool Havebelong;//record if have any class belong this class
    attribute * head_attribute;//linklist of the attribute
    attribute * prev_attribute;
    associate * head_associate;//linklist of the association
    associate * prev_associate;
    
        public:
            xmlSclass();
            ~xmlSclass();//delete the class
            bool setattribute(attribute temp);//set or add the attribute into the attribute linklist
            attribute * getattribute();//return the detail of the attribute;
            int getAttributeAmount();//return the amount of the attribute
            bool setassociation(associate temp); // set or add the association into the linklist
            void setRef(bool);
            bool getRef();
            void setInHeader(bool);//set the isInHeader being true
            bool getInHeader();//get the isInHeader 
            associate * getassociation(int);//return the detail of the association
            int getAssociaAmount();//return the amount of the association
            void setlevel(int temp);//set the class level in the xmlS file
            int getlevel();//return the level of the class 
            void setname(string tname);//set the name of the class
            string getname();//return the name of the class
            bool setbelong_to(string tempbelong);//set the name of the class of the ISA relationship
            string getbelong_to();//return the name of the class is ISA class 
            void print_detail(ofstream & fout, int & tab );//return all attrubute detail of the class
            void setread(bool);
            bool getread();
            bool operator<(const xmlSclass& rclass)const;//use for the sort the level between the class
            void setMin(int);//set the minimun
            int getMin();//get the minimun
            void setMax(int);//set the maximum
            int getMax();//get the maximun
            void setHavebelong(bool);//set if have any class belong this class
            bool getHavebelong();//return if have any class belong this class

};


#endif	/* XMLSCH_H */

