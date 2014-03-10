
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LEFT_BRACKET = 258,
     RIGHT_BRACKET = 259,
     SEMICOLON = 260,
     COMMA = 261,
     VARIABLE = 262,
     MULTIPLICITY = 263,
     ID = 264,
     ASSOCIATION = 265,
     ASSOCIATION_KEYWORD = 266,
     END_OF_FILE = 267,
     AS_KEYWORD = 268,
     COLON = 269,
     LEFT_ROUND_BRACKET = 270,
     RIGHT_ROUND_BRACKET = 271,
     ISA_KEYWORD = 272,
     GENERALIZATION_TYPE = 273,
     END_OF_DEFINITION = 274,
     END_DEF = 275,
     UNEXPECTED_INPUT = 276
   };
#endif
/* Tokens.  */
#define LEFT_BRACKET 258
#define RIGHT_BRACKET 259
#define SEMICOLON 260
#define COMMA 261
#define VARIABLE 262
#define MULTIPLICITY 263
#define ID 264
#define ASSOCIATION 265
#define ASSOCIATION_KEYWORD 266
#define END_OF_FILE 267
#define AS_KEYWORD 268
#define COLON 269
#define LEFT_ROUND_BRACKET 270
#define RIGHT_ROUND_BRACKET 271
#define ISA_KEYWORD 272
#define GENERALIZATION_TYPE 273
#define END_OF_DEFINITION 274
#define END_DEF 275
#define UNEXPECTED_INPUT 276




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 84 "compiler.y"

	char *str;



/* Line 1676 of yacc.c  */
#line 100 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


