%{
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <signal.h>
	
	
	struct node{
		char *class_name;
		char *attribute_name;
		char *attribute_value;
		char *attribute_multiplicity;
		char *attribute_id;
		int used;	/*if the node has been write to the txt,the value will be set to 1,otherwise values 0*/
		struct node *next;
	};
	
	struct Cname{
		char *name;
		int displayInFile;	/* if the class information has been write to the file, the value will change to 1 */
		struct Cname *next;
	};
	
	struct AssociationClassNode{
		char *class_name;
		char *attribute_name;
		char *attribute_value;
		int displayInFile;
		struct AssociationClassNode *next;
	};
	
	struct GeneralizationNode{
		char *attribute_name;
		char *attribute_value;
		int displayInFile;
		struct GeneralizationNode *next;
	};
	
	int add_node(char *cla_name,char *attr_name,char *attr_multi,char *attr_id);
	void write_classDefinition(char *name);
	void add_name(char *addName);
	int nameExist(char *checkName);
	int attributeExist(char *class,char *attr);
	int associationAttributeExist(char *class,char *attrN,char *attrV);
	void addAssoNode(char *classN,char *attributeN,char *attributeV);
	void resetClassName(char *classN);
	void resetAssociationClassName(char *associationN);
	void write_associationDefinition();
	void addGeneralizationNode(char *attributeN,char *attributeV);
	
	char *returnClassName();
	void writeAssociationName(FILE *fp);
	void writeLeftMultiplicity(FILE *fp,char *className);
	void writeLeftRole(FILE *fp,char *className);
	void writeLeftQualification(FILE *fp,char *className);
	void writeRightMultiplicity(FILE *fp,char *className);
	void writeRightRole(FILE *fp,char *className);
	void writeRightQualification(FILE *fp,char *className);	
	int checkLinkAttribute();
	void writeLinkAttribute(FILE *fp);
	int checkLinkAssociationClass();
	void writeLinkAssociationClass(FILE *fp);
	void writeGeneralization();
	

	char *className = "";
	char *fileName = "";
	char *currentClassInAsso = "";
	char *associationName = "";
	int lines = 0;
	struct Cname *nameList = NULL;
	extern void *malloc();
	extern int yylineno;
	extern int startDef;
	extern int insideDefinition;
	
	void clean_exit_on_sig(int sig_num)
	{
		exit(1);
	}
	
	%}

%union{
	char *str;
}

%type<str> class_definition class_name definition member_definition VARIABLE id multiplicity class_qualification left_class_name right_class_name association_multiplicity association_name association_class_name list_of_class generalization_type parentClass compulsory_multiplicity
%token LEFT_BRACKET RIGHT_BRACKET SEMICOLON COMMA VARIABLE MULTIPLICITY ID ASSOCIATION ASSOCIATION_KEYWORD END_OF_FILE AS_KEYWORD COLON  LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET ISA_KEYWORD GENERALIZATION_TYPE END_OF_DEFINITION END_DEF UNEXPECTED_INPUT

%%

text: type|text type

type: class_definition|association|generalization;

class_definition: class_name LEFT_BRACKET definition RIGHT_BRACKET SEMICOLON {
	/*display all the information of the class definition*/
	struct Cname *tmp;
	tmp = nameList;
	
	for(;tmp;tmp=tmp->next){
		if(tmp->displayInFile==0){
			write_classDefinition(tmp->name);
			tmp->displayInFile = 1;
		}
	}
	startDef = 0;
} 
| class_name LEFT_BRACKET RIGHT_BRACKET SEMICOLON {
	/*display all the information of the class definition*/
	struct Cname *tmp;
	tmp = nameList;
	for(;tmp;tmp=tmp->next){
		if(tmp->displayInFile==0){
			write_classDefinition(tmp->name);
			tmp->displayInFile = 1;		//to indicate this class has been displayed in the xml file
		}
	}
	startDef = 0;
}
/* class name missing*/
| LEFT_BRACKET {yyerror(fileName,"expected unqualified-id before '{' token.",yylineno);}
| RIGHT_BRACKET {yyerror(fileName,"expected declaration before '}'.",yylineno);}
| VARIABLE RIGHT_BRACKET{yyerror(fileName,"expected '{' before '}'.",yylineno);yyerror(fileName,"expected declaration before '}'.",yylineno);}
| VARIABLE ID {yyerror(fileName,"expected unqualified-id before attribute declaration.",yylineno);}
| COMMA {yyerror(fileName,"expected unqualified-id before ',' token",yylineno);}
/*| VARIABLE COMMA {;}		//conflict with generalisation 
 | VARIABLE MULTIPLICITY {;}	//conflict with association definition and association
 */
/*first attribute missing*/
| class_name LEFT_BRACKET COMMA {
	yyerror(fileName,"expected unqualified-id before ',' token.",yylineno);
}
| class_name LEFT_BRACKET MULTIPLICITY {
	yyerror(fileName,"expected unqualified-id before multiplicity token .",yylineno);
}
| class_name LEFT_BRACKET ID {
	yyerror(fileName,"expected unqualified-id before identifier token .",yylineno);
}
/*right bracket missing*/
| class_name LEFT_BRACKET definition SEMICOLON {
	yyerror(fileName,"expected '}' at the end of input.",yylineno);
	yyerror(fileName,"expected unqualified-id at the end of input.",yylineno);
}
/*semicolum missing*/
| class_name LEFT_BRACKET definition RIGHT_BRACKET {
	yyerror(fileName,"expected ';' at the end of the class definition.",yylineno);
}
/*extra comma at the end of the attribute definition*/
| class_name LEFT_BRACKET definition COMMA RIGHT_BRACKET {
	yyerror(fileName,"expected unqualified-id before '}' token .",yylineno);
}

class_name: VARIABLE {className=$$;add_name(className);}

definition: member_definition{;}
|definition COMMA member_definition {;}
|definition member_definition{
		yyerror(fileName,"expected comma between member definition",yylineno);
}
|definition COMMA ID{yyerror(fileName,"expected unqualified-id before identifier",yylineno);}
|definition COMMA MULTIPLICITY{yyerror(fileName,"expected unqualified-id before multiplicity",yylineno);}

member_definition: VARIABLE {add_node(className,$1,"","");}
|VARIABLE id {add_node(className,$1,"",$2);}
|VARIABLE multiplicity {add_node(className,$1,$2,"");}
|VARIABLE id id{yyerror(fileName,"expected comma before identifier",yylineno); }
|VARIABLE id multiplicity{yyerror(fileName,"expected comma before multiplicity",yylineno); }
|VARIABLE multiplicity id {yyerror(fileName,"the attribute with multiplicity can not be identifier.",yylineno);}
|VARIABLE multiplicity multiplicity{yyerror(fileName,"expected unqualified-id before multiplicity.",yylineno); }

id: ID {$$=strdup(yylval.str);}
multiplicity: MULTIPLICITY {$$=strdup(yylval.str);}


association: left_class association_specification right_class SEMICOLON {
	write_associationDefinition();
}
|left_class association_specification right_class {
	/*
	 can not detect the semicolon at the moment,because the next character to semicolon is EOF,the program will 
	 exit when it scan to this EOF token
	 */
	yyerror(fileName,"expected ';' at the end of the class definition.",yylineno);
}

/*left class definition*/
left_class: left_class_name left_class_role class_qualification {;}


left_class_name: VARIABLE {
	if(nameExist($$)==1){
		currentClassInAsso = $$;
		addAssoNode("","CLASS_NAME",currentClassInAsso);
		
	}
	else if(nameExist($$)==0){
		yyerror(fileName,"class has not been defined before the association definition.",yylineno);
	}
}

left_class_role: {;}
|AS_KEYWORD VARIABLE {addAssoNode(currentClassInAsso,"ROLE",$2);}
|AS_KEYWORD LEFT_ROUND_BRACKET{
	yyerror(fileName,"expected unqualified-id after 'AS' token .",yylineno);
}
|AS_KEYWORD MULTIPLICITY{
	yyerror(fileName,"expected unqualified-id after 'AS' token .",yylineno);
}


class_qualification: {;}
|LEFT_ROUND_BRACKET list_of_qualification RIGHT_ROUND_BRACKET {;}
|LEFT_ROUND_BRACKET RIGHT_ROUND_BRACKET{;}


list_of_qualification: VARIABLE {addAssoNode(currentClassInAsso,"QUALIFICATION",$1);}
| list_of_qualification COMMA VARIABLE {addAssoNode(currentClassInAsso,"QUALIFICATION",$3);}
| list_of_qualification COMMA {
	yyerror(fileName,"expected unqualified-id before ')' token .",yylineno);
}

/*association specification*/
association_specification: 
/*rule 1 in specification*/
association_multiplicity association_name list_of_attributes compulsory_multiplicity {;}
/*rule 2 in specification*/
|association_multiplicity association_name association_class_qualification COLON association_class_name compulsory_multiplicity{;}
/*incorrect input*/
|association_name{
	yyerror(fileName,"multiplicity is compulsory of the left class",yylineno);
}
|association_multiplicity association_name list_of_attributes VARIABLE{
	yyerror(fileName,"multiplicity is compulsory of the right class",yylineno);
}
|association_multiplicity association_name association_class_qualification COLON MULTIPLICITY{
	yyerror(fileName,"expected association class name before multiplicity",yylineno);
}
|association_multiplicity association_name association_class_qualification COLON VARIABLE SEMICOLON{
	yyerror(fileName,"expected association class name before the right class",yylineno);
}
|association_multiplicity association_name association_class_qualification COLON VARIABLE LEFT_ROUND_BRACKET{
	yyerror(fileName,"unexpected qualification at the end of association definition",yylineno);
}
|association_multiplicity LEFT_ROUND_BRACKET{
	yyerror(fileName,"unexpected qualification before association name",yylineno);
}

association_multiplicity: MULTIPLICITY {addAssoNode(currentClassInAsso,"MULTIPLICITY",$$);}

association_name: VARIABLE {associationName=$$;addAssoNode(associationName,"ASSOCIATION_NAME",$1);currentClassInAsso="RightClass";}

list_of_attributes:{;}
| LEFT_BRACKET link_attribute RIGHT_BRACKET{;}
| LEFT_BRACKET RIGHT_BRACKET {
	yyerror(fileName,"expected unqualified-id before '}' token .",yylineno);
}

link_attribute: VARIABLE {addAssoNode(associationName,"ATTRIBUTE",$1);}
|link_attribute COMMA VARIABLE{addAssoNode(associationName,"ATTRIBUTE",$3);}
|link_attribute COMMA {
	yyerror(fileName,"expected unqualified-id after ',' token .",yylineno);
}

compulsory_multiplicity: MULTIPLICITY {addAssoNode("RightClass","MULTIPLICITY",$$);}

association_class_qualification: {;}
|LEFT_ROUND_BRACKET list_of_association_class_qualification RIGHT_ROUND_BRACKET {;}

list_of_association_class_qualification: VARIABLE {addAssoNode("ASSOCIATION_CLASS_NAME","ASSOCIATION_CLASS_QUALIFICATION",$1);}
| list_of_association_class_qualification COMMA VARIABLE {addAssoNode("ASSOCIATION_CLASS_NAME","ASSOCIATION_CLASS_QUALIFICATION",$3);}
| list_of_association_class_qualification COMMA {
	yyerror(fileName,"expected unqualified-id after ',' token .",yylineno);
}
| list_of_association_class_qualification COMMA RIGHT_BRACKET {
	yyerror(fileName,"expected unqualified-id after ',' token .",yylineno);
}


association_class_name: VARIABLE {associationName=$$;resetAssociationClassName(associationName); addAssoNode("","ASSOCIATION_CLASS_NAME",associationName);currentClassInAsso="RightClass";}

/*right class definition*/
right_class: class_qualification right_class_name right_class_role {;}


right_class_name: VARIABLE {
	if(nameExist($$)==1){
		currentClassInAsso = $$;
		addAssoNode("","CLASS_NAME",currentClassInAsso);
		resetClassName(currentClassInAsso);		/*reset the "RightClass" class to right_class_name*/
		
	}
	else if(nameExist($$)==0){
		yyerror(fileName,"class has not been defined before the association definition.",yylineno);
	}
}

right_class_role:{;}
|AS_KEYWORD VARIABLE {addAssoNode(currentClassInAsso,"ROLE",$2);}
|AS_KEYWORD SEMICOLON{
	yyerror(fileName,"expected unqualified-id after 'AS' token .",yylineno);
}

generalization: list_of_class ISA_KEYWORD generalization_type parentClass SEMICOLON{
	writeGeneralization();
}
|ISA_KEYWORD{
	yyerror(fileName,"expected unqualified-id before 'ISA' token .",yylineno);
}
|list_of_class ISA_KEYWORD generalization_type parentClass{
	yyerror(fileName,"expected ';' at the end of the generalization definition.",yylineno);
}


list_of_class: VARIABLE{addGeneralizationNode("CHILDREN_CLASS",$1);}
| list_of_class COMMA VARIABLE{addGeneralizationNode("CHILDREN_CLASS",$3);}

generalization_type: {;}
|GENERALIZATION_TYPE {addGeneralizationNode("GENERALIZATION_TYPE",$$);}

parentClass: VARIABLE {addGeneralizationNode("PARENT_CLASS",$$);}


%%

int main(argc,argv)
int argc;
char **argv;
{
	char *fileName;
	fileName = argv[1];
	fileName = (char *)malloc(500);
	strcpy(fileName,argv[1]);
		
	if(argc>2){
		int i = 2;
		for(;i<argc;i++){
			strcat(fileName," ");
			strcat(fileName,argv[i]);
		}
	}

	signal(SIGSEGV, clean_exit_on_sig);
	
		FILE *f = fopen(fileName,"r");
		if(!f){
			perror(fileName);
			return (1);
		}
		

		/*
		fileName = argv[1];
		fileName = (char *)malloc(50);
		strcpy(fileName,argv[1]);
		
		if(argc>2){
			int i = 2;
			for(;i<argc;i++){
				strcat(fileName," ");
				strcat(fileName,argv[i]);
			}
		}*/
		

		remove("errorMessage.txt");
		remove("information.xml");
		yyrestart(f);
		
		
		FILE *fp;
		fp = fopen("information.xml","a");
		fprintf(fp,"<project>\n");
		fclose(fp);
		yyparse();
		fclose(f);
}	

struct node *nodeList = NULL;
extern void *malloc();

int add_node(char *cla_name,char *attr_name,char *attr_multi,char *attr_id)
{	
	/*assign the value to the newNode*/
	struct node *newNode;
	newNode = (struct node *) malloc(sizeof(struct node));
	
	newNode->class_name = (char *) malloc(strlen(cla_name)+50);
	strcpy(newNode->class_name,cla_name);
	
	newNode->attribute_name = (char *) malloc(strlen(attr_name)+50);
	strcpy(newNode->attribute_name,attr_name);
	
	newNode->attribute_multiplicity = (char *) malloc(strlen(attr_multi)+50);
	strcpy(newNode->attribute_multiplicity,attr_multi);
	
	newNode->attribute_id = (char *) malloc(strlen(attr_id)+50);
	strcpy(newNode->attribute_id,attr_id);
	
	newNode->used = 0;
	
	newNode->next = NULL;
	/*find the insert position*/
	struct node *tmp;
	tmp = nodeList;
	if(tmp==NULL){
		nodeList = newNode;
	}else{
		if(attributeExist(cla_name,attr_name)==0){
			while(tmp->next!=NULL){
				tmp = tmp->next;
			}
			tmp->next = newNode;
		}
		else {
			char errorMessage[200] = "attribute ";
			strcat(errorMessage,attr_name);
			strcat(errorMessage," in class ");
			strcat(errorMessage,cla_name);
			strcat(errorMessage," has been defined");
			yyerror(fileName,errorMessage,yylineno);
		}
	}	
}

void write_classDefinition(char *className)
{
	struct node *search = nodeList;
	FILE *fp;
	fp = fopen("information.xml","a");
	
	fprintf(fp,"\t<class>\n");
	fprintf(fp,"\t\t<class_name>%s</class_name>\n",className);
	
	
	for(;search;search=search->next){
		if(strcmp(className,search->class_name)==0){
			fprintf(fp,"\t\t<attribute>\n");
			fprintf(fp,"\t\t\t<attribute_name>%s</attribute_name>\n",search->attribute_name);
			fprintf(fp,"\t\t\t<identifier>%s</identifier>\n",search->attribute_id);	
			fprintf(fp,"\t\t\t<multiplicity>%s</multiplicity>\n",search->attribute_multiplicity);
			fprintf(fp,"\t\t</attribute>\n");
		}
	}
	
	fprintf(fp,"\t</class>\n");
	fclose(fp);
}


void add_name(char *addName)
{
	if(nameExist(addName)==0){
		/*assigning the value to newNode if the class name is not existed*/
		struct Cname *newNode;
		newNode = (struct Cname *) malloc(sizeof(struct Cname));
		newNode->name = (char *) malloc(strlen(addName)+50);
		strcpy(newNode->name,addName);
		newNode->displayInFile = 0;
		newNode->next = NULL;
		
		/*find the insert position*/
		struct Cname *tmp;
		tmp = nameList;
		if(tmp==NULL){
			nameList = newNode;
		}else{
			while(tmp->next!=NULL){
				tmp = tmp->next;
			}
			tmp->next = newNode;
		}
	}
	else {
		yyerror(fileName,"class has already been defined.",yylineno);
	}	
}

int nameExist(char *checkName)
{
	struct Cname *tmp;
	tmp = nameList;
	for(;tmp;tmp=tmp->next){
		if(strcmp(tmp->name,checkName)==0){
			return 1;
		}
	}
	return 0;
}

int attributeExist(char *class,char *attr)
{
	struct node* tmp = nodeList;
	while(tmp!=NULL){
		if(strcmp(tmp->class_name,class)==0 && strcmp(tmp->attribute_name,attr)==0){
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

struct AssociationClassNode *assNodeList = NULL;
extern void *malloc();

void addAssoNode(char *classN,char *attributeN,char *attributeV)
{
	struct AssociationClassNode *newNode;
	newNode = (struct AssociationClassNode *) malloc(sizeof(struct AssociationClassNode));
	
	newNode->class_name = (char *) malloc(strlen(classN)+50);
	strcpy(newNode->class_name,classN);
	
	newNode->attribute_name = (char *) malloc(strlen(attributeN)+50);
	strcpy(newNode->attribute_name,attributeN);
	
	newNode->attribute_value = (char *) malloc(strlen(attributeV)+50);
	strcpy(newNode->attribute_value,attributeV);	
	
	newNode->displayInFile = 0;
	newNode->next = NULL;
	
	/*find the insert position*/
	struct AssociationClassNode *tmp;
	tmp = assNodeList;

	
	if(strcmp(attributeN,"ASSOCIATION_CLASS_NAME")==0){
		if(nameExist(attributeV)==0){
			char errorMessage[200] = "association class name in association ";
			strcat(errorMessage,classN);
			strcat(errorMessage," has not previously been defined");
			yyerror(fileName,errorMessage,yylineno);
		}
	}


	if(tmp==NULL){
		assNodeList = newNode;
	}else{
		if(associationAttributeExist(classN,attributeN,attributeV)==0){
			while(tmp->next!=NULL){
				tmp = tmp->next;
			}
			tmp->next = newNode;
		}
		else {
			char errorMessage[200] = "attribute ";
			strcat(errorMessage,attributeV);
			strcat(errorMessage," in class ");
			strcat(errorMessage,classN);
			strcat(errorMessage," has been defined");
			yyerror(fileName,errorMessage,yylineno);
		}
	}
}

int associationAttributeExist(char *class,char *attributeN,char *attributeV)
{
	struct AssociationClassNode* tmp;
	tmp = assNodeList;
	while(tmp!=NULL){
		if(strcmp(tmp->class_name,"")!=0 && strcmp(tmp->class_name,class)==0 && strcmp(tmp->attribute_value,attributeV)==0 && strcmp(attributeN,"MULTIPLICITY")!=0){
			if(strcmp(attributeN,"ASSOCIATION_NAME")==0){
				return 0;
			}
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

void resetClassName(char *classN)
{
	struct AssociationClassNode *tmp;
	tmp = assNodeList;
	while(tmp!=NULL){
		if(strcmp(tmp->class_name,"RightClass")==0){
			strcpy(tmp->class_name,classN);
		}
		tmp = tmp->next;
	}
}

void resetAssociationClassName(char *associationN)
{
	struct AssociationClassNode *tmp;
	tmp = assNodeList;
	while(tmp!=NULL){
		if(strcmp(tmp->class_name,"ASSOCIATION_CLASS_NAME")==0){
			strcpy(tmp->class_name,associationN);
		}
		tmp = tmp->next;
	}
}

void write_associationDefinition()
{	
	FILE *fp;
	fp = fopen("information.xml","a");
	
	fprintf(fp,"\t<association>\n");
	writeAssociationName(fp);
	
	
	/*write the left class attribute to information.xml*/
	char *className = returnClassName(fp);
	fprintf(fp,"\t\t<class>\n");
	fprintf(fp,"\t\t\t<class_name>%s</class_name>\n",className);
	
	writeLeftMultiplicity(fp, associationName);
	writeLeftRole(fp, associationName);
	writeLeftQualification(fp, associationName);
	
	fprintf(fp,"\t\t</class>\n");
	
	/*write the attribute of right information.xml*/
	fprintf(fp,"\t\t<other_class>\n");
	className = returnClassName();
	fprintf(fp,"\t\t\t<class_name>%s</class_name>\n",className);
	writeRightMultiplicity(fp,className);
	writeRightRole(fp,className);
	writeRightQualification(fp,className);
	fprintf(fp,"\t\t</other_class>\n");
	
	
	/*write the link attribute of the association to the information.xml*/
	fprintf(fp,"\t\t<Link>");
	

	int emptyAttribute = checkLinkAttribute();
	int emptyAssocaitionClass = checkLinkAssociationClass();

	writeLinkAttribute(fp);
	writeLinkAssociationClass(fp);
	
	if(emptyAttribute==1 || emptyAssocaitionClass==1){
		fprintf(fp,"\t\t</Link>\n");
	}
	else{
		fprintf(fp,"</Link>\n");
	}
	fprintf(fp,"\t</association>\n");
	
	
	fclose(fp);
}


char *returnClassName()
{
	struct AssociationClassNode *tmp;
	tmp = assNodeList;
	while(tmp!=NULL){
		if(strcmp(tmp->attribute_name,"CLASS_NAME")==0 && tmp->displayInFile == 0){
			tmp->displayInFile = 1;
			return tmp->attribute_value;
		}
		tmp = tmp->next;
	}
	return NULL;
}

void writeAssociationName(FILE *fp)
{
	/*display the association name*/
	struct AssociationClassNode *tmp;
	tmp = assNodeList;
	
	while(tmp!=NULL){
		if(strcmp(tmp->attribute_name,"ASSOCIATION_NAME")==0 && tmp->displayInFile==0){
			fprintf(fp,"\t\t<nameOfAssociation>%s</nameOfAssociation>\n",tmp->attribute_value);
			tmp->displayInFile = 1;
			associationName = tmp->attribute_value;
			break;
		}
		tmp=tmp->next;
	}
}


void writeLeftMultiplicity(FILE *fp,char *className)
{
	/*write the multiplicity of the left class*/
	fprintf(fp,"\t\t\t<multiplicity>");
	struct AssociationClassNode *tmp;
	tmp = assNodeList;	/*reset the pointer to the beginning of the linked list*/
	while(strcmp(tmp->class_name,className)!=0){
		if(strcmp(tmp->attribute_name,"MULTIPLICITY")==0 && tmp->displayInFile==0){
			fprintf(fp,"%s",tmp->attribute_value);
			tmp->displayInFile = 1;
			break;
		}
		tmp = tmp->next;
	}
	fprintf(fp,"</multiplicity>\n");
	
}

void writeLeftRole(FILE *fp,char *className)
{
	
	/*write the role of the left class*/
	fprintf(fp,"\t\t\t<role>");
	struct AssociationClassNode *tmp;
	tmp = assNodeList;	/*reset the pointer to the beginning of the linked list*/
	while(strcmp(tmp->class_name,className)!=0){
		if(strcmp(tmp->attribute_name,"ROLE")==0 && tmp->displayInFile==0){
			fprintf(fp,"%s",tmp->attribute_value);
			tmp->displayInFile = 1;
			break;
		}
		tmp = tmp->next;
	}
	fprintf(fp,"</role>\n");
}

void writeLeftQualification(FILE *fp,char *className)
{
	/*write the qualification of the left class*/
	struct AssociationClassNode *tmp;
	tmp = assNodeList;	/*reset the pointer to the beginning of the linked list*/	
	int qualificationExist = 0;	/*check whether the qualification of link has been found in writing document purpose*/
	while(strcmp(tmp->class_name,className)!=0){
		if(strcmp(tmp->attribute_name,"QUALIFICATION")==0 && tmp->displayInFile==0){
			fprintf(fp,"\t\t\t<qualification>%s</qualification>\n",tmp->attribute_value);
			tmp->displayInFile = 1;
			qualificationExist  = 1;
		}
		tmp = tmp->next;
	}
	if(qualificationExist==0){
		fprintf(fp,"\t\t\t<qualification></qualification>\n");
	}
}

void writeRightMultiplicity(FILE *fp,char *className)
{
	/*write the multiplicity of the right class*/
	fprintf(fp,"\t\t\t<multiplicity>");
	struct AssociationClassNode *tmp;
	tmp = assNodeList;
	int classFound = 0;	/*check whether the multiplicity of link has been found in writing document purpose*/
	while(tmp!=NULL){
		if(strcmp(tmp->class_name,className)==0 && strcmp(tmp->attribute_name,"MULTIPLICITY")==0 && tmp->displayInFile == 0){
			fprintf(fp,"%s",tmp->attribute_value);
			tmp->displayInFile = 1;
			classFound = 1;
		}
		if(classFound==1 && strcmp(tmp->class_name,className)!=0){
			break;
		}
		tmp = tmp->next;
	}
	fprintf(fp,"</multiplicity>\n");
}

void writeRightRole(FILE *fp,char *className)
{
	/*write the role of the right class*/
	fprintf(fp,"\t\t\t<role>");
	struct AssociationClassNode *tmp;
	tmp = assNodeList;	/*reset the pointer to the beginning of the linked list*/
	while(tmp!=NULL){
		if(strcmp(tmp->attribute_name,"ROLE")==0 && strcmp(tmp->class_name,className)==0 && tmp->displayInFile == 0){
			fprintf(fp,"%s",tmp->attribute_value);
			tmp->displayInFile = 1;
			break;
		}
		tmp = tmp->next;
	}
	fprintf(fp,"</role>\n");
}


void writeRightQualification(FILE *fp,char *className)
{
	/*write the qualification of the right class*/
	struct AssociationClassNode *tmp;
	tmp = assNodeList;	/*reset the pointer to the beginning of the linked list*/	
	int qualificationExist = 0;	/*to identify whether display a empty qualification in xml file or not*/
	int classFound = 0;	/*check whether the qualification of class has been found in writing document purpose*/
	while(tmp!=NULL){
		if(strcmp(tmp->attribute_name,"QUALIFICATION")==0 && strcmp(tmp->class_name,className)==0 && tmp->displayInFile == 0){
			fprintf(fp,"\t\t\t<qualification>%s</qualification>\n",tmp->attribute_value);
			tmp->displayInFile = 1;
			qualificationExist  = 1;
		}
		tmp = tmp->next;
		if(classFound==1 && strcmp(tmp->class_name,className)!=0){
			break;
		}
	}
	if(qualificationExist==0){
		fprintf(fp,"\t\t\t<qualification></qualification>\n");
	}
}

int checkLinkAttribute()
{
	struct AssociationClassNode *tmp;
	tmp = assNodeList;
	while(tmp!=NULL){
		if(tmp->displayInFile==0 && strcmp(tmp->attribute_name,"ATTRIBUTE")==0){
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

void writeLinkAttribute(FILE *fp)
{	
	if(checkLinkAttribute()==1){
		fprintf(fp,"\n\t\t\t<link_attribute>\n");
		struct AssociationClassNode *tmp;
		tmp = assNodeList;
		while(tmp!=NULL){
			if(strcmp(tmp->attribute_name,"ATTRIBUTE")==0 && tmp->displayInFile==0){
				fprintf(fp,"\t\t\t\t<link_attribute>%s</link_attribute>\n",tmp->attribute_value);
				tmp->displayInFile = 1;
			}
			tmp = tmp->next;
		}	
		fprintf(fp,"\t\t\t</link_attribute>\n");
	}
}

int checkLinkAssociationClass()
{
	struct AssociationClassNode *tmp;
	tmp = assNodeList;
	while(tmp!=NULL){
		if(tmp->displayInFile==0 && strcmp(tmp->attribute_name,"ASSOCIATION_CLASS_NAME")==0){
		/*check the association class name,because it is compulsory for the rule 2 in association specification*/
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}


void writeLinkAssociationClass(FILE *fp)
{
	if(checkLinkAssociationClass()==1){
		struct AssociationClassNode *tmp;
		tmp = assNodeList;
		fprintf(fp,"\n\t\t\t<association_class>\n");
		/*write the association class qualification in the output file*/
		while(tmp!=NULL){
			if(strcmp(tmp->attribute_name,"ASSOCIATION_CLASS_QUALIFICATION")==0 && tmp->displayInFile==0){
				fprintf(fp,"\t\t\t\t<qualification>%s</qualification>\n",tmp->attribute_value);
				tmp->displayInFile = 1;
			}
			tmp = tmp->next;
		}


		/*write the association class name in the output file*/
		tmp = assNodeList;
		while(tmp!=NULL){
			if(strcmp(tmp->attribute_name,"ASSOCIATION_CLASS_NAME")==0 && tmp->displayInFile==0){
				fprintf(fp,"\t\t\t\t<nameOfAssociationClass>%s</nameOfAssociationClass>\n",tmp->attribute_value);
				tmp->displayInFile = 1;
			}
			tmp = tmp->next;
		}
		fprintf(fp,"\t\t\t</association_class>\n");
	}
}

struct GeneralizationNode *generalizationNodeList = NULL;
extern void *malloc();

void addGeneralizationNode(char *attributeN,char *attributeV)
{
	struct GeneralizationNode *newNode;
	newNode = (struct GeneralizationNode *) malloc(sizeof(struct GeneralizationNode));
	
	newNode->attribute_name = (char *) malloc(strlen(attributeN)+1);
	strcpy(newNode->attribute_name,attributeN);
	
	newNode->attribute_value = (char *) malloc(strlen(attributeV)+1);
	strcpy(newNode->attribute_value,attributeV);	
	
	newNode->displayInFile = 0;
	newNode->next = NULL;
	
	/*find the insert position*/
	struct GeneralizationNode *tmp;
	tmp = generalizationNodeList;
	
	if(strcmp(attributeN,"CHILDREN_CLASS")==0 || strcmp(attributeN,"PARENT_CLASS")==0){
	/*check whether the class name exist or not*/
		if(nameExist(newNode->attribute_value)==0){
			char errorMessage[200] = "class name ";
			strcat(errorMessage,newNode->attribute_value);
			strcat(errorMessage," expected to be defined in previous class definition.");
			yyerror(fileName,errorMessage,yylineno);
		}
	}

	if(tmp==NULL){
		generalizationNodeList = newNode;
	}else{
		struct GeneralizationNode *cur;
		cur = generalizationNodeList;
		while(cur->next!=NULL){
			cur = cur->next;
		}
		cur->next = newNode;
	}	
}

void writeGeneralization()
{
	FILE *fp;
	fp = fopen("information.xml","a");
	
	struct GeneralizationNode *cur;
	int generlizationFound = 0;
	
	
	struct GeneralizationNode *tmp;
	tmp = generalizationNodeList;
	fprintf(fp,"\t<generlisation>");
	
	/*write all the children classes in the file*/
	while(tmp!=NULL){
		if(strcmp(tmp->attribute_name,"CHILDREN_CLASS")==0 && tmp->displayInFile==0){
			fprintf(fp,"\n\t\t<class_name>%s</class_name>",tmp->attribute_value);
			generlizationFound = 1;
			tmp->displayInFile = 1;
		}
		tmp = tmp->next;
	}
	
	/*write parent class in file*/
	tmp = generalizationNodeList;
	while(tmp!=NULL){
		if(strcmp(tmp->attribute_name,"PARENT_CLASS")==0 && tmp->displayInFile==0){
			fprintf(fp,"\n\t\t<ISA>%s</ISA>",tmp->attribute_value);
			generlizationFound = 1;
			tmp->displayInFile = 1;
		}
		tmp = tmp->next;
	}
	
	/*write generalisation type in the file*/
	tmp = generalizationNodeList;
	while(tmp!=NULL){
		if(strcmp(tmp->attribute_name,"GENERALIZATION_TYPE")==0 && tmp->displayInFile==0){
			fprintf(fp,"\n\t\t<generalisation>%s</generalisation>",tmp->attribute_value);
			generlizationFound = 1;
			tmp->displayInFile = 1;
		}
		tmp = tmp->next;
	}
	fprintf(fp,"\n\t</generlisation>\n");
	
	
	fclose(fp);
}












