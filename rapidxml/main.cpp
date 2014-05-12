#include <iostream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
//#include "rapidxml_iterators.hpp"
#include <string.h>
#include <string>

using namespace rapidxml;
using namespace std;

int main()
{    
      file<> fdoc("information.xml");
      std::cout<<fdoc.data()<<std::endl; 
      xml_document<>   doc;    
      doc.parse<0>(fdoc.data()); 

      std::cout<<doc.name()<<"....................."<<std::endl;
      ofstream ofs;
      ofs.open("../product/errorMessage.txt",  ios::app);
  
     //! 获取根节�?
      xml_node<> *root = doc.first_node();
      //std::cout<<"First root:"<<root->name()<<std::endl;
      string IDerror[100];
      string classname[100];
      string genClass[100];
      string quaClass[100];
      string att[100][100]; // 记录每个class里面的attribute
      string genAss[100][3];
      string linkClass[100];
      int genAssCount = 0;
      int classCount = 0;
      int attCount = 0;
      int i =0;
      int genClasscount = 0; // 把所有genClasscount 改为 Classcount
   //   string classattributes[100][100];
      //int c1 =0,c2=0;
      
      //int quaClasscount = 0;
      int classamount = 0;
      int l = 0;
       int q = 0;
        string attributes[100];
      

      for(xml_node<> *pNode1=root->first_node(); pNode1; pNode1=pNode1->next_sibling()) 
      {  
         
               // std:cout<<"second root:"<<pNode1->name()<<std::endl;
        
     //! 获取根节点第�?��节点
      
                int IDcount = 0;
                int IDattCount = 0;
                bool qualification = false;
               
                int j = 0;
               
                
                for(xml_node<> *pNode2=pNode1->first_node(); pNode2; pNode2=pNode2->next_sibling())
                {
        
                       // std::cout<<"attributes name:"<<pNode2->name()<<std::endl; 
                      //  std::cout<<"attributes value:"<<pNode2->value()<<std::endl; 
                        if(strcmp(pNode2->name(),"class_name")==0)
                        {
                                classname[i] = pNode2->value();
                                 
                        }
                        //-----------------------------------------------------------------------------------------------------------------------------
                        if(strcmp(pNode2->name(),"attribute")==0)
                        {
                            IDattCount ++;
                                 
                        }
                        //-----------------------------------------------------------------------------------------------------------------------------
                        if(strcmp(pNode1->name(),"class") ==0 && strcmp(pNode2->name(),"class_name")==0 )
                        {
                            att[classCount][0] = pNode2->value();
                           
                        }
    
                     
                         //------------------------------------------------------------------------------------------------------------------------------
                                        
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
                          //------------------------------------------------------------------------------------------------------------------------------
                          if(strcmp(pNode1->name(),"association")==0 && strcmp(pNode2->name(),"nameOfAssociation")==0 && strcmp(pNode2->value(),"") != 0)
                                        {
                                      
                                             genAss[genAssCount][0] = pNode2->value();
                                          
                                            
                                        }
                        
                        //---------------------------------------------------------------------------------------------------------
                        for(xml_node<> *pNode3=pNode2->first_node(); pNode3; pNode3=pNode3->next_sibling())
                        {
  
                                if(strcmp(pNode3->name(),"")!=0)
                                {
                                       // std::cout<<"First layer node name:"<<pNode3->name()<<std::endl;
                                       // std::cout<<"First layer node value:"<<pNode3->value()<<std::endl;
      
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
                                                    //cout<<"good"<<endl;
                                                attributes[i] = pNode3->value();
                                              
                                                break;
                                                }
                                            }
                                                att[classCount][attCount] = pNode3->value();
                                               
                                                attCount++;
                                        }
                                        if(strcmp(pNode1->name(),"association")==0 && strcmp(pNode2->name(),"class")==0 && strcmp(pNode3->name(),"qualification")==0 && strcmp(pNode3->value(),"") != 0)
                                        {
                                      
                                                qualification = true;           
                                                for(int i =0; i < attCount; i++)
                                                {
                                            
                                                        if(pNode3->value() == attributes[i])
                                                         {

                                                    
                                                          ofs << "~Error: Attributes used in qualification must be removed from a class on the other side of qualification" << endl;    
                                                                                 
                                                          cout<<"Error: Attributes used in qualification must be removed from a class on the other side of qualification"<<endl;
                                                          
                                                          break;
                                                          }
                                                }
                                        }
                       //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                       
                      
                                         if(strcmp(pNode1->name(),"association")==0 && strcmp(pNode2->name(),"class")==0 && strcmp(pNode3->name(),"class_name")==0) 
                                        {
                                      
                                             genAss[genAssCount][1] = pNode3->value();
                                       
                                            
                                        }
                                        
                                        if(strcmp(pNode1->name(),"association")==0 && strcmp(pNode2->name(),"other_class")==0 && strcmp(pNode3->name(),"class_name")==0) 
                                        {
                                      
                                             genAss[genAssCount][2] = pNode3->value();
                                          
                                               genAssCount++;
                                            
                                        }
                                        
                        //---------------------------------------------------------------------------------------------------------------------------------
                                        if (qualification && strcmp(pNode3->name(),"multiplicity")==0 && strcmp(pNode3->value(),"[1..*]")==0 )
                                        {
                                                ofs <<"~Error: Wrong multiplicity on the other side of qualification"<<endl;        
                                                cout<<"Error: Wrong multiplicity on the other side of qualification"<<endl;
                                        }
                       //------------------------------------------------------------------------------------------------------------------------------
                                        if(strcmp(pNode1->name(),"association")==0 && strcmp(pNode2->name(),"other_class")==0 && strcmp(pNode3->name(),"class_name")==0 && strcmp(pNode3->value(),"") != 0 && qualification )
                                        {   
                                            quaClass[q] = pNode3->value();
                                            
                                           // cout<<quaClass[q]<<"iiiiiiiiiiiiiiiiiiiiiiii"<<endl;
                                            q++;
                                           
                                           // genClasscount = genClasscount + q -1;
                                            classamount = classamount + q;
                                        }
                                            
                                   
                                 }
  
      
                                for(xml_node<> *pNode4=pNode3->first_node(); pNode4; pNode4=pNode4->next_sibling())
                                {
                                        if(strcmp(pNode4->name(),"")!=0)
                                        { 
                                                //std::cout<<"Second layer node name:"<<pNode4->name()<<std::endl;
                                               // std::cout<<"Second layer node value:"<<pNode4->value()<<std::endl;
                                                
                                        }
                                        if(strcmp(pNode2->name(),"Link") == 0 && strcmp(pNode3->name(),"association_class") == 0 && strcmp(pNode4->name(),"nameOfAssociationClass") == 0 && strcmp(pNode4->value(),"") != 0)
                                        {
                                            linkClass[l] = pNode4->value();
                                            l++;
                                            classamount ++;
                                            // genClasscount++;
                                        }
                                        if(strcmp(pNode2->name(),"Link") == 0 && strcmp(pNode3->name(),"association_class") == 0 && strcmp(pNode4->name(),"qualification") == 0 && strcmp(pNode4->value(),"") != 0)
                                        {
                                                 qualification = true;           
                                                for(int i =0; i < attCount; i++)
                                                {
                                               
                                                        if(pNode4->value() == attributes[i])
                                                         {

                                                    
                                                          ofs << "~Error: Attributes used in qualification must be removed from a class on the other side of qualification" << endl;    
                                                                                 
                                                          cout<<"Error: Attributes used in qualification must be removed from a class on the other side of qualification"<<endl;
                                                          
                                                          break;
                                                          }
                                                }
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
                         // cout<<".............Error:  This Class has no identifer............."<<endl;
                }
                classCount++;
              
      } // loop 1
     
      for(int j=0;j<i;j++)
      {
         string str1 = "~Error: The class: ";
         string str2 = " has no identifer";
         string str;
         bool tmp = false;
       // cout<<"classammount "<<classamount<<endl;
         for(int k =0 ;k < classamount; k++)
         {    
              //cout<< linkClass[k]<<endl;
                if(IDerror[j] == genClass[k] ||  IDerror[j] == quaClass[k] || IDerror[j] == linkClass[k])
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
      
     // cout << genClasscount <<
      
      //---------------------------------------------------------------------------------------------------------------------------
      if(genClasscount>0){
      int sameClass[genClasscount];
      
      //int sameAttr = 0;
      
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
    //  cout<<"...........................................s................................................"<<endl;
      string value="tmp";
    
      for (int m =0; m < attCount ; m++)
      {
                for(int n =0 ;n < attCount; n++)
                {
                     
                        
                       // cout << att[sameClass[0]][m] << endl;
                        
                    if(att[sameClass[0]][m] == att[sameClass[1]][n] && att[sameClass[0]][m] != "")
                    {                       
                        value = att[sameClass[0]][m];
                       // cout <<"error "<< value <<" can be in the parent class......"<<endl;
                        break;
                    }
                        
                     
                }
      }
     // int y=2;
    
       int y=2;
      for( y;y<genClasscount ;y++)
      {
           //cout<<"sdhjsakdhjsahdj";
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
      //---------------------------------------------------------------------------------------------------------------------------  
      }
      // for(int mm = 0; mm <genAssCount; mm ++)
      // cout<<"@@@@@@"<<genAss[mm][0]<<"@@@@@@"<<genAss[mm][1]<<"@@@@@@"<<genAss[mm][2]<<endl;
        
      
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
     
   ofs.close();
      
    // system("PAUSE");
     return EXIT_SUCCESS;
}
