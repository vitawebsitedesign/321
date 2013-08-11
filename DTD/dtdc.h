/* 
 * File:   dtdc.h
 * project
 * Author: Xingfang Huang
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

#ifndef DTDC_H
#define	DTDC_H
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
    char tclass_name[64];//record the name of the association class 
    int to_Min;
    int to_Max;
    int base_Max;
    int base_Min;
    associate *next;//link to the next
};

class dtdclass{
    string d_name;//name of the class
    string belong_to;//recond the name of the father class if the class ISA some class
    int level_class;//recond the level of the class, use to find the "root" class
    bool readornot; //record the class has been write to the docunment or not
    bool isRef;//record the class is the reference class or not
    bool isInHeader;//record the class is in other class header
    int attriAmount;//record the number of attribute;
    int associAmount;// record the number of association
    attribute * head_attribute;//linklist of the attribute
    attribute * prev_attribute;
    associate * head_associate;//linklist of the association
    associate * prev_associate;

    
        public:
            dtdclass();
            ~dtdclass();//delete the class
            bool setattribute(attribute temp);//set or add the attribute into the attribute linklist
            attribute * getattribute();//return the detail of the attribute;
            int getAttributeAmount();//return the amount of the attribute
            bool setassociation(associate temp); // set or add the association into the linklist
            void setRef(bool);/*set the class is the reference class*/
            bool getRef();/*return the class is the reference class or not*/
            void setInHeader(bool);//set the isInHeader being true
            bool getInHeader();//get the isInHeader 
            associate * getassociation(int);//return the detail of the association
            int getAssociaAmount();//return the amount of the association
            void setlevel(int temp);//set the class level in the dtd file
            int getlevel();//return the level of the class 
            void setname(string tname);//set the name of the class
            string getname();//return the name of the class
            bool setbelong_to(string tempbelong);//set the name of the class of the ISA relationship
            string getbelong_to();//return the name of the class is ISA class 
            void print_detail(ofstream & fout , deque<string> & element);//return all attrubute detail of the class
            void printAttributeHead(ofstream& fout);/*print attribute name in the header*/
            void setread(bool);//set the class has been read.
            bool getread();//return the class has been read into the file or not
            bool operator<(const dtdclass& rclass)const;//use for the sort the level between the class
            bool operator==(const dtdclass& rclass) const;
};
#endif	/* DTDC_H */

