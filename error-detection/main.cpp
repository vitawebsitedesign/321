#include <iostream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
//#include "rapidxml_iterators.hpp"
#include <string.h>

using namespace rapidxml;
using namespace std;

int main()
{    
      file<> fdoc("information3.xml");
      std::cout<<fdoc.data()<<std::endl; 
      xml_document<>   doc;    
      doc.parse<0>(fdoc.data()); 

      std::cout<<doc.name()<<"....................."<<std::endl;
  
     //! 获取根节点
      xml_node<> *root = doc.first_node();
      std::cout<<"First root:"<<root->name()<<std::endl;


      for(xml_node<> *pNode1=root->first_node(); pNode1; pNode1=pNode1->next_sibling()) 
      {  
         
          std:cout<<"second root:"<<pNode1->name()<<std::endl;
        
     //! 获取根节点第一个节点
      
    int IDcount = 0;
     bool qualification = false;
     char* qualivalue;;
      
     for(xml_node<> *pNode2=pNode1->first_node(); pNode2; pNode2=pNode2->next_sibling())
     {
        
      std::cout<<"attributes name:"<<pNode2->name()<<std::endl; 
     std::cout<<"attributes value:"<<pNode2->value()<<std::endl; 
    
     
     for(xml_node<> *pNode3=pNode2->first_node(); pNode3; pNode3=pNode3->next_sibling())
     {
  
         if(strcmp(pNode3->name(),"")!=0)
         {
      std::cout<<"First layer node name:"<<pNode3->name()<<std::endl;
      std::cout<<"First layer node value:"<<pNode3->value()<<std::endl;
      
        if(strcmp(pNode3->name(),"identifier")==0 && pNode3->value()[0]=='I')
		                IDcount++;
        else if(strcmp(pNode3->name(),"identifier")==0 && pNode3->value()[0]=='i')
                                IDcount++;
        if(strcmp(pNode1->name(),"class")==0 && strcmp(pNode2->name(),"attribute")==0 && strcmp(pNode3->name(),"attribute_name")==0 )
        {
            qualivalue = pNode3->value();
        }
        if(strcmp(pNode1->name(),"association")==0 && strcmp(pNode2->name(),"class")==0 && strcmp(pNode3->name(),"qualification")==0 && strcmp(pNode3->value(),"") != 0)
        {
                                      
            qualification = true;  
            if(strcmp(pNode3->value(),qualivalue))
            {
                cout<<".............Error: Attributes used in qualification must be removed from a class on the other side of qualification............."<<endl;
            }
        }
     //cout << c<<"----------------------------------------------------------"<<endl;
        if (qualification && strcmp(pNode3->name(),"multiplicity")==0 && strcmp(pNode3->value(),"[1..*]")==0 )
            
             cout<<"..............Error: Wrong multiplicity on the other side of qualification..................."<<endl;
        
         }
      //.......
  
      
      for(xml_node<> *pNode4=pNode3->first_node(); pNode4; pNode4=pNode4->next_sibling())
       {
          if(strcmp(pNode4->name(),"")!=0)
          { 
         std::cout<<"Second layer node name:"<<pNode4->name()<<std::endl;
         std::cout<<"Second layer node value:"<<pNode4->value()<<std::endl;
          
         //node111 = node111->next_sibling();
          
          }
     // node11 = node11->next_sibling();
     }
     // attribute = attribute->next_sibling();
     }
     // root2 = root2->next_sibling();
      }
    if(strcmp(pNode1->name(),"class")==0)   
         {
      if(IDcount == 0)
     cout<<".............Error:  This Class has no identifer............."<<endl;
         }
      }
     //! 修改之后再次保存
      //xml_node<>* size = root->first_node("size");
     // size->append_node(doc.allocate_node(node_element,"w","0"));
     // size->append_node(doc.allocate_node(node_element,"h","0"));
      
    // std::string text;  
  //    rapidxml::print(std::back_inserter(text),doc,0);  
    
     // std::cout<<text<<std::endl; 
    
     //std::ofstream out("information1.xml");
    // out << doc;

      system("PAUSE");
     return EXIT_SUCCESS;
}
