
/* 
 * File:   xmlSch.cpp
 * XML schema project
 * Author: Xingfang Huang
 */
#include "xmlSch.h"

xmlSclass::xmlSclass(){//initial the class
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
    Havebelong=false;
    minimum=0;
    maximum=11;
    readornot = false;
}

xmlSclass::~xmlSclass(){//delete the class
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
bool xmlSclass::setattribute(attribute temp){//set or add the attribute into the attribute linklist
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
        while(current != NULL){
            if((strcmp(temp.att_name, current->att_name)) == 0){same = true;}
            pre = current;
            current = current->next;
        }
        if(same ==false){//if the attribute name is not the same with all other attribute, add it
            attribute * att = new attribute;
            strcpy(att->att_name, temp.att_name);
            att->isId = temp.isId;
            att->ismulti= temp.ismulti;
            att->max = temp.max;
            att->min = temp.min;
            att->next = NULL;
            pre->next = att;
        }
        
    }
}
attribute * xmlSclass::getattribute(){//return the detail of the attribute one by one;
    attribute * temp;
    if(prev_attribute ==NULL){
        prev_attribute = head_attribute->next;
        temp = head_attribute;
    }
    else{
        temp = prev_attribute;
        prev_attribute = prev_attribute->next;
    }
    return temp;
}
bool xmlSclass::setassociation(associate temp){ //set or add the association into the linklist
    associate * ass = new associate;
    strcpy(ass->ass_name, temp.ass_name);
    ass->base_multi = temp.base_multi;
    ass->to_multi = temp.to_multi;
    ass->to_Max = temp.to_Max;
    ass->to_Min = temp.to_Min;
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
associate * xmlSclass::getassociation(int rang){//return the detail of the one association in the class
    associate * temp;
    if(rang ==0){
        temp = head_associate;
        prev_associate = head_associate;
    }else{
        prev_associate = head_associate;
        for(int i=0; i<rang; i++ ){
            prev_associate = prev_associate->next;
            temp = prev_associate;
        }
            
    }
    
    return temp;
    
}
 int xmlSclass::getAttributeAmount(){/*return the amount of attribute in the class*/
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
 int xmlSclass::getAssociaAmount(){/*return the amount of the association of the class*/
     associAmount =0;
     associate * temp = head_associate;
     if(head_associate !=NULL){
         for(associAmount =0;temp!=NULL; associAmount++){
             temp = temp->next;
         }
     }
     return associAmount;
     
 }
void xmlSclass::setlevel(int temp){//set the xml schema class level
    if(level_class==0 && temp==4){
        level_class=temp;
    }
    if(level_class < temp){
        level_class =temp;
    }
}
int xmlSclass::getlevel() {//return the level of the class
    return level_class;
}
void xmlSclass::setname(string tname) {//set the name of the class
    x_name = tname;
}
string xmlSclass::getname(){//return the name of the class
    return x_name;
}
bool xmlSclass::setbelong_to(string tempbelong){//set the name of the class of the ISA relationship
    belong_to = tempbelong;
    return true;
}
string xmlSclass::getbelong_to() {//return the name of the class is ISA class 
    return belong_to;
}

void xmlSclass::print_detail(ofstream& fout, int & tab ){/*print all attribute detail of the class*/
    attribute * temp;
    temp = head_attribute;
    
    while (head_attribute != NULL && temp!=NULL){
        for(int i=0;i<tab;i++){fout <<"   ";}
        fout << "    <xsd:element name=\""<< temp->att_name<<"\" type=\"xsd:";
        if(temp->isId == true){
            fout<<"ID\" ";
        }else{fout <<"string\" ";}
        if(temp->ismulti == true){
            fout<< " maxOccurs=\"";
            if(temp->max>10){
                fout<<"unbounded";
            }else{
                fout<<temp->max;
            }
            fout<<"\" minOccurs = \"" << temp->min<<"\"";
                    
        }
        fout<<" />"<<endl;
        
        temp = temp->next;
    }
}
void xmlSclass::setread(bool temp){/*set the class has already write into the xsd file*/
    readornot = temp;
}

bool xmlSclass::getread(){/*return the class has write or not into the xsd file*/
    return readornot;
}

bool xmlSclass::operator<(const xmlSclass& rclass) const{//use for the sort the level between the class
    if(this->level_class != rclass.level_class){
        return this->level_class < rclass.level_class;
    }
    else{
        return this->associAmount > rclass.associAmount;
    }
}
void xmlSclass::setRef(bool tr){//set the class is not reference class 
    isRef =tr;
}
bool xmlSclass::getRef(){//return the class is reference or not
    return isRef;
}

void xmlSclass::setInHeader(bool temp){//seat the isInHeader being true
    isInHeader = temp;
}
bool xmlSclass::getInHeader(){//get the isInHeader 
    return isInHeader;
}
void xmlSclass::setMin(int min){//set the minimum
        minimum = min;
}
int xmlSclass::getMin(){//get the minimum
    return minimum;
}
void xmlSclass::setMax(int max){//set the maximum
        maximum = max;
}
int xmlSclass::getMax(){//get the maximum
    return maximum;
}
void xmlSclass::setHavebelong(bool temp){//set if have any class belong this class
    Havebelong=temp;
}
bool xmlSclass::getHavebelong(){//return if have any class belong this class
    return Havebelong;
}
