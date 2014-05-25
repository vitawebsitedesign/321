#include <iostream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include <string.h>
#include <string>

using namespace rapidxml;
using namespace std;

void IDchecker(int classamount, int i, string IDerror[],string genClass[],string quaClass[],string linkClass[], int classCount, ofstream& ofs);
void missInhertence(int genClasscount,int attCount ,int classCount,string genClass[], string att[][100], ofstream& ofs);
void missGen(int genAssCount, string genAss[][3], ofstream& ofs);
void checkMuti(bool qulification,char* pNode3name,char* pNode3value, ofstream& ofs);
void nonremoveAtt(int attCount, char* pNodevalue,string attributes[], ofstream& ofs);

void nonremoveAtt(int attCount, char* pNodevalue,string attributes[], ofstream& ofs)
{
    for(int i =0; i < attCount; i++)
       {                       
                  if(pNodevalue == attributes[i])
                       {                                                    
                                  ofs << "~Error: Attributes: "<<pNodevalue<<" used in qualification must be removed from a class on the other side of qualification" << endl;    
                                                                                 
                                  cout<<"Error: Attributes: "<<pNodevalue<<" used in qualification must be removed from a class on the other side of qualification"<<endl;
                                                          
                                   break;
                         }
           }
}

void checkMuti(bool qulification,char* pNode3name,char* pNode3value, ofstream& ofs)
{
  
 
     if (qulification && strcmp(pNode3name,"multiplicity")==0  )
         {                
         char* star = strstr(pNode3value,"*");
          if (star)
          {
            ofs <<"~Error: Wrong multiplicity: "<<pNode3value<<" on the other side of qualification"<<endl;        
            cout<<"Error: Wrong multiplicity: "<<pNode3value<<" on the other side of qualification"<<endl;
          }
         }
}

void missGen(int genAssCount, string genAss[][3], ofstream& ofs)
{
     int CountSameRow[genAssCount][genAssCount];
      int SameRow[genAssCount];
     for(int i =0; i< genAssCount; i++)
      {
          SameRow[i] = -1;
      }
      int count =0;
      for(int i = 0; i < genAssCount ; i++)
      {
          bool temp = true;
          bool exist = false;
          for(int n=0; n<genAssCount ; n++)
          {
          
              if(i == SameRow[n])
              {
                  temp =false;
              }
          }
          if(temp)
          {
                  int m =0;
                  bool flag =false;
                  for(int j = i+1; j <genAssCount; j++)
                  {
                       
                      if(genAss[i][0] == genAss[j][0] && genAss[i][1] == genAss[j][1])
                      {
                        
                          CountSameRow[i][m] = j;
                         
                          if(flag == false)
                          {
                              ofs<<"~Warning:"<<genAss[i][2];   
                              cout<<"Warning:"<<genAss[i][2];
                              flag = true;
                          }  
                          exist = true;
                          ofs<<" and "<<genAss[CountSameRow[i][m]][2];
                          cout<<" and "<<genAss[CountSameRow[i][m]][2];
                          m++;
                          SameRow[count] = j;
                          count++;
                      }
                  }
                  if(exist)
                  {
                   ofs<<" can be generated to one class "<<endl;
                   cout<<" can be generated to one class"<<endl;
                   }
          }
                 
          
      }
     }

void missInhertence(int genClasscount,int attCount ,int classCount,string genClass[], string att[][100], ofstream& ofs)
{
      if(genClasscount>0){
      int sameClass[genClasscount];
      
      
      for(int jj = 0; jj < classCount ; jj++)
      {
                 for(int kk =0 ;kk < genClasscount; kk++)
                {
                        if (genClass[kk] == att[jj][0])
                        {
                            sameClass[kk] = jj;
                        }
                 }
      }
    
      string value="tmp";
    
      for (int m =0; m < attCount ; m++)
      {
                for(int n =0 ;n < attCount; n++)
                {
                        
                    if(att[sameClass[0]][m] == att[sameClass[1]][n] && att[sameClass[0]][m] != "")
                    {                       
                        value = att[sameClass[0]][m];
            
                        break;
                    }
                        
                     
                }
      }
   
      int y=2;
      for( y;y<genClasscount ;y++)
      {
          for(int y1=1;y1<attCount;y1++)
          {
               
              if(value==att[y][y1])
                  break;
            
          }
      }
          if(y==genClasscount&& value!="tmp")
          {
              ofs  <<"~Error: "<< value <<" can be in the parent class"<<endl;
              cout <<"Error: "<< value <<" can be in the parent class"<<endl;
          }
      
      }
}

void IDchecker(int classamount, int i, string IDerror[],string genClass[],string quaClass[],string linkClass[],int classCount, ofstream& ofs)     // one to ont is fixed
{
     classamount =classamount + classCount;
     for(int j=0;j<i;j++)
      {
         string str1 = "~Error: The class: ";
         string str2 = " has no identifer";
         string str;
         bool tmp = false;
         for(int k =0 ;k < classamount; k++)
         {    
   
                if(IDerror[j] == genClass[k] ||  IDerror[j] == quaClass[k] || IDerror[j] == linkClass[k] || classCount == 2)
                {
                    tmp = true;
                     break;
                }
               
                
         } 
         if(tmp == false)
         {
         str = str1 + IDerror[j] + str2;
          ofs<<str<<endl;
          cout<<str<<endl;
         }
          
      }
     
}
     

int main()
{    
      file<> fdoc("information.xml");
      std::cout<<fdoc.data()<<std::endl; 
      xml_document<>   doc;    
      doc.parse<0>(fdoc.data()); 

  //    std::cout<<doc.name()<<"............................................"<<std::endl;
      ofstream ofs;
      ofs.open("../product/errorMessage.txt",  ios::app);
  
    
      xml_node<> *root = doc.first_node();
      
      string IDerror[100];     // store current classes without ID 
      string classname[100];  // store all classes name
      string genClass[100];  // store classes which are gened
      string quaClass[100];  // store class which are qualified
      string att[100][100];  // store the attributes if each classes
      string genAss[100][3]; // store gened class's attribute
      string linkClass[100];  // store linked classes
      int genAssCount = 0;
      int classCount = 0;
      int attCount = 0;
      int i =0;                  // amount of classes with ID error
      int genClasscount = 0; 
      int classamount = 0;
      int l = 0;                  // amount of linked classes 
      int q = 0;                 // amount of qulification classes
      string attributes[100];
      

      for(xml_node<> *pNode1=root->first_node(); pNode1; pNode1=pNode1->next_sibling()) 
      {  
         
      
                int IDcount = 0;
                int IDattCount = 0;
                bool qualification = false;
               
                int j = 0;
               
                
                for(xml_node<> *pNode2=pNode1->first_node(); pNode2; pNode2=pNode2->next_sibling())
                {
        
                       
                        if(strcmp(pNode2->name(),"class_name")==0)
                        {
                                classname[i] = pNode2->value();
                                 
                        }
                   
                        if(strcmp(pNode2->name(),"attribute")==0)
                        {
                            IDattCount ++;
                                 
                        }
 
                        if(strcmp(pNode1->name(),"class") ==0 && strcmp(pNode2->name(),"class_name")==0 )
                        {
                            att[classCount][0] = pNode2->value();
                           
                        }
    
                     
                      
                                        
                                        if(strcmp(pNode1->name(),"generlisation") == 0)
                                       {
                                           if(strcmp(pNode2->name(),"class_name")==0)
                                           {
                                           genClass[j] = pNode2->value();
                                        
                                           j++;
                                           genClasscount = j;
                                           classamount = j;
                                           }
                                       }
                        
                          if(strcmp(pNode1->name(),"association")==0 && strcmp(pNode2->name(),"nameOfAssociation")==0 && strcmp(pNode2->value(),"") != 0)
                                        {
                                      
                                             genAss[genAssCount][0] = pNode2->value();
                                          
                                            
                                        }
                   
                        for(xml_node<> *pNode3=pNode2->first_node(); pNode3; pNode3=pNode3->next_sibling())
                        {
  
                                if(strcmp(pNode3->name(),"")!=0)
                                {
                                       
      
                                        if(strcmp(pNode3->name(),"identifier")==0 && pNode3->value()[0]=='I')
                                                IDcount++;
                                        else if(strcmp(pNode3->name(),"identifier")==0 && pNode3->value()[0]=='i')
                                                IDcount++;
                                        if(strcmp(pNode1->name(),"class")==0 && strcmp(pNode2->name(),"attribute")==0 && strcmp(pNode3->name(),"attribute_name")==0 )
                                        {
                                            for(int i =0;  i<100; i++)
                                            {
                                                if(attributes[i] == "")
                                                {
                  
                                                attributes[i] = pNode3->value();
                                              
                                                break;
                                                }
                                            }
                                                att[classCount][attCount] = pNode3->value();
                                               
                                                attCount++;
                                        }
                                        if((strcmp(pNode1->name(),"association")==0 && strcmp(pNode2->name(),"class")==0 && strcmp(pNode3->name(),"qualification")==0 && strcmp(pNode3->value(),"") != 0) || (strcmp(pNode1->name(),"association")==0 && strcmp(pNode2->name(),"other_class")==0 && strcmp(pNode3->name(),"qualification")==0 && strcmp(pNode3->value(),"") != 0))
                                        {
                                          
                                                qualification = true;      
                                                nonremoveAtt(attCount, pNode3->value(), attributes, ofs);
                                                
                                        }
                    
                      
                                         if(strcmp(pNode1->name(),"association")==0 && strcmp(pNode2->name(),"class")==0 && strcmp(pNode3->name(),"class_name")==0) 
                                        {
                                      
                                             genAss[genAssCount][1] = pNode3->value();
                                       
                                            
                                        }
                                        
                                        if(strcmp(pNode1->name(),"association")==0 && strcmp(pNode2->name(),"other_class")==0 && strcmp(pNode3->name(),"class_name")==0) 
                                        {
                                      
                                             genAss[genAssCount][2] = pNode3->value();
                                          
                                               genAssCount++;
                                            
                                        }
                                  
                       
                                        checkMuti(qualification, pNode3->name(), pNode3->value(),ofs);
                                       
              
                                        if(strcmp(pNode1->name(),"association")==0 && strcmp(pNode2->name(),"other_class")==0 && strcmp(pNode3->name(),"class_name")==0 && strcmp(pNode3->value(),"") != 0 && qualification )
                                        {   
                                            quaClass[q] = pNode3->value();
                                            q++;
                                            classamount = classamount + q;
                                        }
                                            
                                   
                                 }
  
      
                                for(xml_node<> *pNode4=pNode3->first_node(); pNode4; pNode4=pNode4->next_sibling())
                                {
                                        
                                        if(strcmp(pNode2->name(),"Link") == 0 && strcmp(pNode3->name(),"association_class") == 0 && strcmp(pNode4->name(),"nameOfAssociationClass") == 0 && strcmp(pNode4->value(),"") != 0)
                                        {
                                            linkClass[l] = pNode4->value();
                                            l++;
                                            classamount ++;
                                          
                                        }
                                        if(strcmp(pNode2->name(),"Link") == 0 && strcmp(pNode3->name(),"association_class") == 0 && strcmp(pNode4->name(),"qualification") == 0 && strcmp(pNode4->value(),"") != 0)
                                        {
                                                 qualification = true;        
                                                 nonremoveAtt(attCount, pNode4->value(), attributes, ofs);
                                              
                                        }
                                        
                                } // loop 4

                        } // loop3

                } // loop 2
                if(strcmp(pNode1->name(),"class")==0)   
                {
                        if(IDcount == 0 && IDattCount != 0 )
                        {
                         IDerror[i] = classname[i];
                         i++;
                        }
                    classCount++;
                }
               
              
      } // loop 1
     IDchecker(classamount,i, IDerror,genClass,quaClass,linkClass, classCount ,ofs);
     missInhertence(genClasscount,attCount,classCount,genClass, att, ofs);
     missGen(genAssCount,genAss,ofs);
    
     ofs.close();
 
     return EXIT_SUCCESS;
}
