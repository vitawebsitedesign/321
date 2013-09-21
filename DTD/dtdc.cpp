/* 
 * File:   dtdclass.cpp
 * project
 * Author: Xingfang Huang
 */
#include <deque>

#include "dtdc.h"

dtdclass::dtdclass(){//init the class
    level_class = -1;
    attriAmount =0;
    associAmount =0;
    readornot = false;
    isRef =  true;
    isInHeader=false;
    head_attribute = NULL;
    prev_attribute = NULL;
    head_associate = NULL;
    prev_associate = NULL;
    readornot = false;
}

dtdclass::~dtdclass(){//delete the class
    attribute * temp;
    while(head_attribute!=NULL){
        temp = head_attribute->next;
        delete head_attribute;
        head_attribute = temp;
    }
    if(prev_attribute!=NULL){delete prev_attribute;}
    associate * tempa;
    while(head_associate!=NULL){
        tempa = head_associate->next;
        delete head_associate;
        head_associate = tempa;
    }
    if(prev_associate!=NULL){delete prev_associate;}
}
bool dtdclass::setattribute(attribute temp){//set or add the attribute into the attribute linklist
    attribute * current = head_attribute;
    bool same = false;
    /*start check the attribute format have "#" or not*/
    char * position, buffer[64];
    position = strchr(temp.att_name, '#');
    if(position){
        memset(buffer, 0, sizeof(buffer));
        strncpy(buffer, temp.att_name, position - temp.att_name);
    }else{strcpy(buffer,temp.att_name );}
    /*finish check the attribute format*/
    
    if(current ==NULL){//put into head attribute when it is empty
        attribute * att = new attribute;
        strcpy(att->att_name, buffer);
        att->isId = temp.isId;
        att->ismulti= temp.ismulti;
        att->max = temp.max;
        att->min = temp.min;
        att->next = NULL;
        head_attribute = att;
    }
    else{
        attribute *pre = NULL;
        while(current != NULL){//check if the attribute name is same with before attribute
            if((strcmp(temp.att_name, current->att_name))==0){same = true;}
            pre = current;
            current = current->next;
        }
        if(same ==false){//if the attribute name is not the same with all other attribute, add it
            attribute * att = new attribute;
            strcpy(att->att_name, buffer);
            att->isId = temp.isId;
            att->ismulti= temp.ismulti;
            att->max = temp.max;
            att->min = temp.min;
            att->next = NULL;
            pre->next = att;
        }
        
    }
}
attribute * dtdclass::getattribute(){//return the detail of the attribute;
    attribute * temp;
    if(prev_attribute ==NULL){
        prev_attribute = head_attribute->next;//set the current attribute is the head->next
        temp = head_attribute;
    }
    else{
        temp = prev_attribute;
        prev_attribute = prev_attribute->next;
    }
    return temp;/*return the current attribute */
}
bool dtdclass::setassociation(associate temp){ // set or add the association into the linklist
    associate * ass = new associate;
    strcpy(ass->ass_name, temp.ass_name);
    ass->base_multi = temp.base_multi;
    ass->to_multi = temp.to_multi;
    ass->to_Min = temp.to_Min;
    ass->to_Max = temp.to_Max;
    ass->base_Max = temp.base_Max;
    ass->base_Min=temp.base_Min;
    strcpy(ass->tclass_name, temp.tclass_name);
    ass->next = NULL;
    associate * current_asso = head_associate;
    if(head_associate == NULL){head_associate = ass;}//put head association into class
    else{
        associate * pre_asso = NULL;
        while(current_asso!=NULL){
            pre_asso = current_asso;
            current_asso = current_asso->next;
        }
        pre_asso->next = ass;
    }
}
associate * dtdclass::getassociation(int rang){//return the detail of the current association
    associate * temp;
    if(rang ==0){
        temp = head_associate;
        prev_associate = head_associate;
    }else{
        prev_associate = head_associate;
        for(int i=0; i<rang; i++ ){
            prev_associate = prev_associate->next;//current association become current->next
            temp = prev_associate;
        }
            
    }
    /*return one association each time*/
    return temp;
    
}
 int dtdclass::getAttributeAmount(){//return the total attribute amount
     attriAmount =0;
     attribute * temp = head_attribute;
     if(temp ==NULL){return attriAmount;}
     else{
         for(attriAmount =0;temp!=NULL; attriAmount++){
             temp = temp->next;
         }
     }
     return attriAmount;
 }
 int dtdclass::getAssociaAmount(){//return the total association amount
     associAmount =0;
     associate * temp = head_associate;
     if(head_associate !=NULL){
         for(associAmount =0;temp!=NULL; associAmount++){
             temp = temp->next;
         }
     }
     return associAmount;
     
 }
void dtdclass::setlevel(int temp){//set the class level in the dtd file
    if(level_class==0 && temp==4){
        level_class=temp;
    }
    if(level_class < temp){
        level_class =temp;
    }
}
int dtdclass::getlevel() {//return the level of the class
    return level_class;
}
void dtdclass::setname(string tname) {//set the name of the class
    d_name = tname;
}
string dtdclass::getname(){//return the name of the class
    return d_name;
}

bool dtdclass::setbelong_to(string tempbelong){//set the name of the class of the ISA relationship
    belong_to = tempbelong;
    return true;
}
string dtdclass::getbelong_to() {//return the name of the class is ISA class 
    return belong_to;
}
void dtdclass::printAttributeHead(ofstream& fout){/*print attribute name in the header*/
    attribute * temp;
    temp = head_attribute;
    if(isRef == true){/*if this is the reference class, add idNum attribute and set the attribute could be appear 0 or more time*/
        fout<<"IDREF";
        while (head_attribute != NULL && temp!=NULL){
            fout <<"|"<< temp->att_name;
            temp = temp->next;
        }
    }else{
        while (head_attribute != NULL && temp!=NULL){
            fout << temp->att_name;
            if(temp->ismulti ==true){
                if(temp->max ==1 && temp->min ==0){fout<< "?";}
                else if(temp->max>1 && temp->min ==1){fout<<"+";}
                else{fout << "*";}
            }
            if(temp->next != NULL){fout << ", ";}
            temp = temp->next;
        }
    }
}
void dtdclass::print_detail(ofstream& fout, deque<string> & element ){/*print all attribute detail of the class*/
    attribute * temp;
    temp = head_attribute;
    associate * tempAssociate;
    tempAssociate = head_associate;
   
    temp = head_attribute;
    if(isRef == true){/*if this is the reference class, set idNum attribute being PCDATA*/
        fout<< "<!ELEMENT IDREF (#PCDATA) >"<<endl;
    }
    while (head_attribute != NULL && temp!=NULL){
        deque<string>::iterator first = element.begin();
        deque<string>::iterator last = element.end();
        bool same = false;
        if(element.empty()==false){//check the element has define in the file before
            for(;first!=last;first++){
                if((strcmp(temp->att_name, (*first).c_str()))==0){same = true;}
            }
        }
        if(same ==false){//if the element not define in the file before, write it into the file
            string writeElement = temp->att_name;
            element.push_back(writeElement);
            fout << "<!ELEMENT "<< temp->att_name<<" (#PCDATA) >"<<endl;
            
        }
        temp = temp->next;
    }
}
void dtdclass::setread(bool temp){//set the class in read already state
    readornot = temp;
}

bool dtdclass::getread(){//return the class has read into the file or not
    return readornot;
}

bool dtdclass::operator<(const dtdclass& rclass) const{//use for the sort the level between the class
    if(this->level_class != rclass.level_class){
        return this->level_class < rclass.level_class;
    }
    else{
        return this->associAmount > rclass.associAmount;
    }
}

bool dtdclass::operator==(const dtdclass& rclass)const{
    return this->level_class == rclass.level_class;
}
void dtdclass::setRef(bool tr){//set the class is not reference class 
    isRef =tr;
}
bool dtdclass::getRef(){//return the class is reference or not
    return isRef;
}

void dtdclass::setInHeader(bool temp){//set the isInHeader being true
    isInHeader = temp;
}
bool dtdclass::getInHeader(){//get the isInHeader 
    return isInHeader;
}

