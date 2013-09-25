%{
#include<stdio.h>
#include<string.h>
#include"compiler.tab.h"
int startDef = 0;	/*start the class definition*/
int ignoreInput = 0;
void add_token(char *tokenCN,char *tokenN,char *tokenV,int lineN);
extern char *className;
extern char *fileName;
int yylineno = 0;
%}

%%
<<EOF>>	{
	FILE *fp;
	fp = fopen("information.xml","a");
	fprintf(fp,"</project>\n");
	fclose(fp);
	exit(0);
}

";"	{
		
		if(ignoreInput==0){
			yylval.str=strdup(yytext);
			add_token("","SEMICOLUM",yylval.str,yylineno);
			return SEMICOLON;
		}
		else if(ignoreInput==1){
			ignoreInput = 0;
			/*return END_DEF;*/
		}

}

\n	{yylineno++;}
[ \t]+	{;}

"{"	{
		if(ignoreInput==0){
			yylval.str=strdup(yytext);
			add_token("","LEFT_BRACKET",yylval.str,yylineno);
			return LEFT_BRACKET;
		}
}

"}"	{	
		if(ignoreInput==0){
			yylval.str=strdup(yytext);
			add_token("","RIGHT_BRACKET",yylval.str,yylineno);
			return RIGHT_BRACKET;
		}
}

","	{
		if(ignoreInput==0){
			yylval.str=strdup(yytext);
			add_token("","COMMA",yylval.str,yylineno);
			return COMMA;
		}
}


":"	{
		if(ignoreInput==0){
			add_token("ASSOCIATION","COLOM",yylval.str,yylineno);
			return COLON;
	}
}


"("	{
		if(ignoreInput==0){
			add_token("ASSOCIATION","LEFT_ROUND_BRACKET",yylval.str,yylineno);
			return LEFT_ROUND_BRACKET;
	}
}

")"	{
		if(ignoreInput==0){
			add_token("ASSOCIATION","RIGHT_ROUND_BRACKET",yylval.str,yylineno);
			return RIGHT_ROUND_BRACKET;
	}
}

"ID"[0-9]*|"id"[0-9]*	{
		if(ignoreInput==0){
			yylval.str=strdup(yytext);
			add_token(className,"ID",yylval.str,yylineno);
			return ID;
		}
}

"AS"	{
		if(ignoreInput==0){
			yylval.str=strdup(yytext);
			add_token("ASSOCIATION","AS_KEYWORD",yylval.str,yylineno);
			return (AS_KEYWORD);
	}
}

"ISA"	{
		if(ignoreInput==0){
			yylval.str=strdup(yytext);
			add_token("GENERALIZATION","ISA_KEYWORD",yylval.str,yylineno);
			return (ISA_KEYWORD);
		}
}

[_a-zA-Z]*[a-zA-Z0-9]+[#]*[-]*[_]*[a-zA-Z]*	{
		if(ignoreInput==0){
			yylval.str=strdup(yytext);
			add_token(className,"VARIABLE",yylval.str,yylineno);
			return (VARIABLE);
		}
}

"["[0]"]"	{
	yyerror(fileName,"multiplicity should be defined larger than 1",yylineno);
}

("["[1-9]*[0-9]+\.{2}[0-9]+"]") | 
("["[1-9]*[0-9]+\.{2}\*"]") |
("["\*"]") |
("["[0-9]+"]")	{
		if(ignoreInput==0){
			yylval.str=strdup(yytext);
			add_token(className,"MULTIPLICITY",yylval.str,yylineno);
			return MULTIPLICITY;
		}
}

"["[^0-9]	{
	yyerror(fileName,"expected number after left bracket '['. ",yylineno);
}


"("[!-@{-~[-^]+	{
	yyerror(fileName,"expected unqualified-id after left round bracket '('.",yylineno);
}	


"(t-e)" | 
"(p-e)" | 
"(t-o)" | 
"(p-o)" {
		if(ignoreInput==0){
			yylval.str=strdup(yytext);
			add_token("GENERALIZATION","GENERALIZATION_TYPE",yylval.str,yylineno);
			return (GENERALIZATION_TYPE);
	}
}


%%

yyerror(char *fileName,char *errorMeg,int lineno)
{
	ignoreInput = 1;
	
	FILE *fp;
	if((fp = fopen("errorMessage.txt","a+"))==NULL){
		fprintf(stderr,"Can not open output file.\n");
		return 1;
	}
	
	
	if(strcmp(fileName,"syntax error")!=0){
		fprintf(fp,"line:%d:	error: %s\n",lineno,errorMeg);		
	}

	fclose(fp);
}


struct token {
	char *tokenClassName;
	char *tokenName;
	char *tokenValue;
	int lineNo;
	struct token *next;
};

struct token *tokenList = NULL;

void add_token(char *tokenCN,char *tokenN,char *tokenV,int lineN)
{
	struct token *newNode;
	newNode = (struct token *) malloc (sizeof(struct token));
	
	newNode->tokenClassName = (char *) malloc(strlen(tokenCN)+1);
	strcpy(newNode->tokenClassName,tokenCN);

	newNode->tokenName = (char *) malloc(strlen(tokenN)+1);
	strcpy(newNode->tokenName,tokenN);
	
	newNode->tokenValue = (char *) malloc(strlen(tokenV)+1);
	strcpy(newNode->tokenValue,tokenV);
	
	newNode->lineNo = lineN;
	newNode->next = NULL;
	
	struct token *tmp;
	tmp = tokenList;
	if(tmp==NULL){
		tokenList = newNode;
	}else{
		while(tmp->next!=NULL){
			tmp = tmp->next;
		}
		tmp->next = newNode;
	}
}



int yywrap()
{
	return 1;
}





