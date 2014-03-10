
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "compiler.y"

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
	void writeLeftMultiplicity(FILE *fp);
	void writeLeftRole(FILE *fp);
	void writeLeftQualification(FILE *fp);
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
	
	

/* Line 189 of yacc.c  */
#line 157 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 84 "compiler.y"

	char *str;



/* Line 214 of yacc.c  */
#line 241 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 253 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   90

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  22
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNRULES -- Number of states.  */
#define YYNSTATES  108

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    20,    25,
      27,    29,    32,    35,    37,    41,    45,    49,    54,    59,
      65,    67,    69,    73,    76,    80,    84,    86,    89,    92,
      96,   100,   104,   108,   110,   112,   117,   121,   125,   127,
     128,   131,   134,   137,   138,   142,   145,   147,   151,   154,
     159,   166,   168,   173,   179,   186,   193,   196,   198,   200,
     201,   205,   208,   210,   214,   217,   219,   220,   224,   226,
     230,   233,   237,   239,   243,   245,   246,   249,   252,   258,
     260,   265,   267,   271,   272,   274
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      23,     0,    -1,    24,    -1,    23,    24,    -1,    25,    -1,
      31,    -1,    49,    -1,    26,     3,    27,     4,     5,    -1,
      26,     3,     4,     5,    -1,     3,    -1,     4,    -1,     7,
       4,    -1,     7,     9,    -1,     6,    -1,    26,     3,     6,
      -1,    26,     3,     8,    -1,    26,     3,     9,    -1,    26,
       3,    27,     5,    -1,    26,     3,    27,     4,    -1,    26,
       3,    27,     6,     4,    -1,     7,    -1,    28,    -1,    27,
       6,    28,    -1,    27,    28,    -1,    27,     6,     9,    -1,
      27,     6,     8,    -1,     7,    -1,     7,    29,    -1,     7,
      30,    -1,     7,    29,    29,    -1,     7,    29,    30,    -1,
       7,    30,    29,    -1,     7,    30,    30,    -1,     9,    -1,
       8,    -1,    32,    37,    46,     5,    -1,    32,    37,    46,
      -1,    33,    34,    35,    -1,     7,    -1,    -1,    13,     7,
      -1,    13,    15,    -1,    13,     8,    -1,    -1,    15,    36,
      16,    -1,    15,    16,    -1,     7,    -1,    36,     6,     7,
      -1,    36,     6,    -1,    38,    39,    40,    42,    -1,    38,
      39,    43,    14,    45,    42,    -1,    39,    -1,    38,    39,
      40,     7,    -1,    38,    39,    43,    14,     8,    -1,    38,
      39,    43,    14,     7,     5,    -1,    38,    39,    43,    14,
       7,    15,    -1,    38,    15,    -1,     8,    -1,     7,    -1,
      -1,     3,    41,     4,    -1,     3,     4,    -1,     7,    -1,
      41,     6,     7,    -1,    41,     6,    -1,     8,    -1,    -1,
      15,    44,    16,    -1,     7,    -1,    44,     6,     7,    -1,
      44,     6,    -1,    44,     6,     4,    -1,     7,    -1,    35,
      47,    48,    -1,     7,    -1,    -1,    13,     7,    -1,    13,
       5,    -1,    50,    17,    51,    52,     5,    -1,    17,    -1,
      50,    17,    51,    52,    -1,     7,    -1,    50,     6,     7,
      -1,    -1,    18,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    93,    93,    93,    95,    95,    95,    97,   110,   123,
     124,   125,   126,   127,   132,   135,   138,   142,   147,   151,
     155,   157,   158,   159,   162,   163,   165,   166,   167,   168,
     169,   170,   171,   173,   174,   177,   180,   189,   192,   203,
     204,   205,   208,   213,   214,   215,   218,   219,   220,   227,
     229,   231,   234,   237,   240,   243,   246,   250,   252,   254,
     255,   256,   260,   261,   262,   266,   268,   269,   271,   272,
     273,   276,   281,   284,   287,   299,   300,   301,   305,   308,
     311,   316,   317,   319,   320,   322
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LEFT_BRACKET", "RIGHT_BRACKET",
  "SEMICOLON", "COMMA", "VARIABLE", "MULTIPLICITY", "ID", "ASSOCIATION",
  "ASSOCIATION_KEYWORD", "END_OF_FILE", "AS_KEYWORD", "COLON",
  "LEFT_ROUND_BRACKET", "RIGHT_ROUND_BRACKET", "ISA_KEYWORD",
  "GENERALIZATION_TYPE", "END_OF_DEFINITION", "END_DEF",
  "UNEXPECTED_INPUT", "$accept", "text", "type", "class_definition",
  "class_name", "definition", "member_definition", "id", "multiplicity",
  "association", "left_class", "left_class_name", "left_class_role",
  "class_qualification", "list_of_qualification",
  "association_specification", "association_multiplicity",
  "association_name", "list_of_attributes", "link_attribute",
  "compulsory_multiplicity", "association_class_qualification",
  "list_of_association_class_qualification", "association_class_name",
  "right_class", "right_class_name", "right_class_role", "generalization",
  "list_of_class", "generalization_type", "parentClass", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    22,    23,    23,    24,    24,    24,    25,    25,    25,
      25,    25,    25,    25,    25,    25,    25,    25,    25,    25,
      26,    27,    27,    27,    27,    27,    28,    28,    28,    28,
      28,    28,    28,    29,    30,    31,    31,    32,    33,    34,
      34,    34,    34,    35,    35,    35,    36,    36,    36,    37,
      37,    37,    37,    37,    37,    37,    37,    38,    39,    40,
      40,    40,    41,    41,    41,    42,    43,    43,    44,    44,
      44,    44,    45,    46,    47,    48,    48,    48,    49,    49,
      49,    50,    50,    51,    51,    52
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     5,     4,     1,
       1,     2,     2,     1,     3,     3,     3,     4,     4,     5,
       1,     1,     3,     2,     3,     3,     1,     2,     2,     3,
       3,     3,     3,     1,     1,     4,     3,     3,     1,     0,
       2,     2,     2,     0,     3,     2,     1,     3,     2,     4,
       6,     1,     4,     5,     6,     6,     2,     1,     1,     0,
       3,     2,     1,     3,     2,     1,     0,     3,     1,     3,
       2,     3,     1,     3,     1,     0,     2,     2,     5,     1,
       4,     1,     3,     0,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     9,    10,    13,    38,    79,     0,     2,     4,     0,
       5,     0,    39,     6,     0,    11,    12,     1,     3,     0,
      58,    57,    43,     0,    51,     0,    43,     0,    83,     0,
      14,    26,    15,    16,     0,    21,     0,     0,    36,    56,
      59,    40,    42,    41,    37,    82,    84,     0,     8,    34,
      33,    27,    28,    18,    17,     0,    23,    46,    45,     0,
      74,    75,    35,     0,     0,     0,     0,    85,    80,    29,
      30,    31,    32,     7,    19,    25,    24,    22,    48,    44,
       0,    73,    61,    62,     0,    68,     0,    52,    65,    49,
       0,    78,    47,    77,    76,    60,    64,    70,    67,    72,
      53,     0,    63,    71,    69,    54,    55,    50
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    34,    35,    51,    52,    10,
      11,    12,    26,    37,    59,    22,    23,    24,    65,    84,
      89,    66,    86,   101,    38,    61,    81,    13,    14,    47,
      68
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -35
static const yytype_int8 yypact[] =
{
       6,   -35,   -35,   -35,    11,   -35,     1,   -35,   -35,    34,
     -35,    -5,    28,   -35,     5,   -35,   -35,   -35,   -35,    39,
     -35,   -35,    50,    29,   -35,    25,    50,    53,    49,    65,
     -35,    42,   -35,   -35,    51,   -35,    22,    64,    71,   -35,
      16,   -35,   -35,   -35,   -35,   -35,   -35,    70,   -35,   -35,
     -35,    42,    42,    73,   -35,    45,   -35,   -35,   -35,     0,
     -35,    66,   -35,    35,    74,    19,    68,   -35,    75,   -35,
     -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,    76,   -35,
      56,   -35,   -35,   -35,    60,   -35,    18,   -35,   -35,   -35,
      61,   -35,   -35,   -35,   -35,   -35,    77,    55,   -35,    20,
     -35,    78,   -35,   -35,   -35,   -35,   -35,   -35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -35,    79,   -35,   -35,   -35,   -34,    21,    23,   -35,
     -35,   -35,   -35,    62,   -35,   -35,   -35,    67,   -35,   -35,
     -14,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -82
static const yytype_int8 yytable[] =
{
      56,    17,    20,    21,     1,     2,    78,     3,     4,     1,
       2,    27,     3,     4,   -20,    15,    79,   -81,     5,    63,
      16,    77,    28,     5,    97,   105,    87,    88,   -81,    57,
     -66,    64,    41,    42,    98,   106,    20,    19,    58,    82,
      43,    25,    83,    29,    39,    30,    31,    32,    33,    74,
      49,    50,    31,    75,    76,    53,    54,    55,    31,   103,
      45,    93,   104,    94,    95,    36,    96,    46,    99,   100,
      48,    60,    69,    71,    70,    72,    62,    67,    73,    80,
      91,    85,    90,    92,   102,    18,    88,   107,    44,     0,
      40
};

static const yytype_int8 yycheck[] =
{
      34,     0,     7,     8,     3,     4,     6,     6,     7,     3,
       4,     6,     6,     7,     3,     4,    16,     6,    17,     3,
       9,    55,    17,    17,     6,     5,     7,     8,    17,     7,
      14,    15,     7,     8,    16,    15,     7,     3,    16,     4,
      15,    13,     7,     4,    15,     6,     7,     8,     9,     4,
       8,     9,     7,     8,     9,     4,     5,     6,     7,     4,
       7,     5,     7,     7,     4,    15,     6,    18,     7,     8,
       5,     7,    51,    52,    51,    52,     5,     7,     5,    13,
       5,     7,    14,     7,     7,     6,     8,   101,    26,    -1,
      23
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     6,     7,    17,    23,    24,    25,    26,
      31,    32,    33,    49,    50,     4,     9,     0,    24,     3,
       7,     8,    37,    38,    39,    13,    34,     6,    17,     4,
       6,     7,     8,     9,    27,    28,    15,    35,    46,    15,
      39,     7,     8,    15,    35,     7,    18,    51,     5,     8,
       9,    29,    30,     4,     5,     6,    28,     7,    16,    36,
       7,    47,     5,     3,    15,    40,    43,     7,    52,    29,
      30,    29,    30,     5,     4,     8,     9,    28,     6,    16,
      13,    48,     4,     7,    41,     7,    44,     7,     8,    42,
      14,     5,     7,     5,     7,     4,     6,     6,    16,     7,
       8,    45,     7,     4,     7,     5,    15,    42
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 7:

/* Line 1455 of yacc.c  */
#line 97 "compiler.y"
    {
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
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 110 "compiler.y"
    {
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
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 123 "compiler.y"
    {yyerror(fileName,"expected unqualified-id before '{' token.",yylineno);}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 124 "compiler.y"
    {yyerror(fileName,"expected declaration before '}'.",yylineno);}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 125 "compiler.y"
    {yyerror(fileName,"expected '{' before '}'.",yylineno);yyerror(fileName,"expected declaration before '}'.",yylineno);}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 126 "compiler.y"
    {yyerror(fileName,"expected unqualified-id before attribute declaration.",yylineno);}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 127 "compiler.y"
    {yyerror(fileName,"expected unqualified-id before ',' token",yylineno);}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 132 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id before ',' token.",yylineno);
}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 135 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id before multiplicity token .",yylineno);
}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 138 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id before identifier token .",yylineno);
}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 142 "compiler.y"
    {
	yyerror(fileName,"expected '}' at the end of input.",yylineno);
	yyerror(fileName,"expected unqualified-id at the end of input.",yylineno);
}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 147 "compiler.y"
    {
	yyerror(fileName,"expected ';' at the end of the class definition.",yylineno);
}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 151 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id before '}' token .",yylineno);
}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 155 "compiler.y"
    {className=(yyval.str);add_name(className);}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 157 "compiler.y"
    {;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 158 "compiler.y"
    {;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 159 "compiler.y"
    {
		yyerror(fileName,"expected comma between member definition",yylineno);
}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 162 "compiler.y"
    {yyerror(fileName,"expected unqualified-id before identifier",yylineno);}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 163 "compiler.y"
    {yyerror(fileName,"expected unqualified-id before multiplicity",yylineno);}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 165 "compiler.y"
    {add_node(className,(yyvsp[(1) - (1)].str),"","");}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 166 "compiler.y"
    {add_node(className,(yyvsp[(1) - (2)].str),"",(yyvsp[(2) - (2)].str));}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 167 "compiler.y"
    {add_node(className,(yyvsp[(1) - (2)].str),(yyvsp[(2) - (2)].str),"");}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 168 "compiler.y"
    {yyerror(fileName,"expected comma before identifier",yylineno); }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 169 "compiler.y"
    {yyerror(fileName,"expected comma before multiplicity",yylineno); }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 170 "compiler.y"
    {yyerror(fileName,"the attribute with multiplicity can not be identifier.",yylineno);}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 171 "compiler.y"
    {yyerror(fileName,"expected unqualified-id before multiplicity.",yylineno); }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 173 "compiler.y"
    {(yyval.str)=strdup(yylval.str);}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 174 "compiler.y"
    {(yyval.str)=strdup(yylval.str);}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 177 "compiler.y"
    {
	write_associationDefinition();
}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 180 "compiler.y"
    {
	/*
	 can not detect the semicolon at the moment,because the next character to semicolon is EOF,the program will 
	 exit when it scan to this EOF token
	 */
	yyerror(fileName,"expected ';' at the end of the class definition.",yylineno);
}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 189 "compiler.y"
    {;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 192 "compiler.y"
    {
	if(nameExist((yyval.str))==1){
		currentClassInAsso = (yyval.str);
		addAssoNode("","CLASS_NAME",currentClassInAsso);
		
	}
	else if(nameExist((yyval.str))==0){
		yyerror(fileName,"class has not been defined before the association definition.",yylineno);
	}
}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 203 "compiler.y"
    {;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 204 "compiler.y"
    {addAssoNode(currentClassInAsso,"ROLE",(yyvsp[(2) - (2)].str));}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 205 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id after 'AS' token .",yylineno);
}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 208 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id after 'AS' token .",yylineno);
}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 213 "compiler.y"
    {;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 214 "compiler.y"
    {;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 215 "compiler.y"
    {;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 218 "compiler.y"
    {addAssoNode(currentClassInAsso,"QUALIFICATION",(yyvsp[(1) - (1)].str));}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 219 "compiler.y"
    {addAssoNode(currentClassInAsso,"QUALIFICATION",(yyvsp[(3) - (3)].str));}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 220 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id before ')' token .",yylineno);
}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 227 "compiler.y"
    {;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 229 "compiler.y"
    {;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 231 "compiler.y"
    {
	yyerror(fileName,"multiplicity is compulsory of the left class",yylineno);
}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 234 "compiler.y"
    {
	yyerror(fileName,"multiplicity is compulsory of the right class",yylineno);
}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 237 "compiler.y"
    {
	yyerror(fileName,"expected association class name before multiplicity",yylineno);
}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 240 "compiler.y"
    {
	yyerror(fileName,"expected association class name before the right class",yylineno);
}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 243 "compiler.y"
    {
	yyerror(fileName,"unexpected qualification at the end of association definition",yylineno);
}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 246 "compiler.y"
    {
	yyerror(fileName,"unexpected qualification before association name",yylineno);
}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 250 "compiler.y"
    {addAssoNode(currentClassInAsso,"MULTIPLICITY",(yyval.str));}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 252 "compiler.y"
    {associationName=(yyval.str);addAssoNode(associationName,"ASSOCIATION_NAME",(yyvsp[(1) - (1)].str));currentClassInAsso="RightClass";}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 254 "compiler.y"
    {;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 255 "compiler.y"
    {;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 256 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id before '}' token .",yylineno);
}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 260 "compiler.y"
    {addAssoNode(associationName,"ATTRIBUTE",(yyvsp[(1) - (1)].str));}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 261 "compiler.y"
    {addAssoNode(associationName,"ATTRIBUTE",(yyvsp[(3) - (3)].str));}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 262 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id after ',' token .",yylineno);
}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 266 "compiler.y"
    {addAssoNode("RightClass","MULTIPLICITY",(yyval.str));}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 268 "compiler.y"
    {;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 269 "compiler.y"
    {;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 271 "compiler.y"
    {addAssoNode("ASSOCIATION_CLASS_NAME","ASSOCIATION_CLASS_QUALIFICATION",(yyvsp[(1) - (1)].str));}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 272 "compiler.y"
    {addAssoNode("ASSOCIATION_CLASS_NAME","ASSOCIATION_CLASS_QUALIFICATION",(yyvsp[(3) - (3)].str));}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 273 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id after ',' token .",yylineno);
}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 276 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id after ',' token .",yylineno);
}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 281 "compiler.y"
    {associationName=(yyval.str);resetAssociationClassName(associationName); addAssoNode("","ASSOCIATION_CLASS_NAME",associationName);currentClassInAsso="RightClass";}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 284 "compiler.y"
    {;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 287 "compiler.y"
    {
	if(nameExist((yyval.str))==1){
		currentClassInAsso = (yyval.str);
		addAssoNode("","CLASS_NAME",currentClassInAsso);
		resetClassName(currentClassInAsso);		/*reset the "RightClass" class to right_class_name*/
		
	}
	else if(nameExist((yyval.str))==0){
		yyerror(fileName,"class has not been defined before the association definition.",yylineno);
	}
}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 299 "compiler.y"
    {;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 300 "compiler.y"
    {addAssoNode(currentClassInAsso,"ROLE",(yyvsp[(2) - (2)].str));}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 301 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id after 'AS' token .",yylineno);
}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 305 "compiler.y"
    {
	writeGeneralization();
}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 308 "compiler.y"
    {
	yyerror(fileName,"expected unqualified-id before 'ISA' token .",yylineno);
}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 311 "compiler.y"
    {
	yyerror(fileName,"expected ';' at the end of the generalization definition.",yylineno);
}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 316 "compiler.y"
    {addGeneralizationNode("CHILDREN_CLASS",(yyvsp[(1) - (1)].str));}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 317 "compiler.y"
    {addGeneralizationNode("CHILDREN_CLASS",(yyvsp[(3) - (3)].str));}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 319 "compiler.y"
    {;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 320 "compiler.y"
    {addGeneralizationNode("GENERALIZATION_TYPE",(yyval.str));}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 322 "compiler.y"
    {addGeneralizationNode("PARENT_CLASS",(yyval.str));}
    break;



/* Line 1455 of yacc.c  */
#line 2212 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 325 "compiler.y"


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
	char a;
	struct node *search = nodeList;
	FILE *fp;
	fp = fopen("information.xml","a");
	
	fprintf(fp,"\t<class>\n");
	fprintf(fp,"\t\t<class_name>%s</class_name>\n",className);
	
	
	for(;search;search=search->next){
		if(strcmp(className,search->class_name)==0){
			
if(search->attribute_name[0]== '/')
{
     
                 char temp[100];
                  strcpy(temp,search->attribute_name);
             temp[0] = '\n';
            
                  fprintf(fp,"\t\t<attribute>\n");
	                fprintf(fp,"\t\t\t<derived>\n");
			 fprintf(fp,"\t\t\t<attribute_name>%s</attribute_name>\n",temp);
			 fprintf(fp,"\t\t\t<identifier>%s</identifier>\n",search->attribute_id);	
			 fprintf(fp,"\t\t\t<multiplicity>%s</multiplicity>\n",search->attribute_multiplicity);
                        fprintf(fp,"\t\t\t</derived>\n");
		fprintf(fp,"\t\t</attribute>\n");
}
else{
                 fprintf(fp,"\t\t<attribute>\n");
                        fprintf(fp,"\t\t\t<attribute_name>%s</attribute_name>\n",search->attribute_name);
			fprintf(fp,"\t\t\t<identifier>%s</identifier>\n",search->attribute_id);
			fprintf(fp,"\t\t\t<multiplicity>%s</multiplicity>\n",search->attribute_multiplicity);
	         fprintf(fp,"\t\t\t</attribute>\n");
}

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
	
	writeLeftMultiplicity(fp);
	writeLeftRole(fp);
	writeLeftQualification(fp);
	
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

void writeLeftQualification(FILE *fp)
{

	struct AssociationClassNode *tmp;
	tmp = assNodeList;
	int qualificationExist = 0;
	while(tmp!=NULL){
		if(strcmp(tmp->attribute_name,"QUALIFICATION")==0 && tmp->displayInFile==0){
			fprintf(fp,"\t\t\t<qualification>%s</qualification>\n",tmp->attribute_value);
			tmp->displayInFile = 1;
			qualificationExist  = 1;
		}
		tmp=tmp->next;
	}
        if(qualificationExist==0){
		fprintf(fp,"\t\t\t<qualification></qualification>\n");
	}
}

void writeLeftMultiplicity(FILE *fp)
{
	/*write the multiplicity of the left class*/
	fprintf(fp,"\t\t\t<multiplicity>");
	struct AssociationClassNode *tmp;
	tmp = assNodeList;	/*reset the pointer to the beginning of the linked list*/
	while(tmp!=NULL){

		if(strcmp(tmp->attribute_name,"MULTIPLICITY")==0 && tmp->displayInFile==0){
			fprintf(fp,"%s",tmp->attribute_value);
			tmp->displayInFile = 1;
			break;
		}
		tmp = tmp->next;
	}
	fprintf(fp,"</multiplicity>\n");
	
}


void writeLeftRole(FILE *fp)
{
	
	/*write the role of the left class*/
	fprintf(fp,"\t\t\t<role>");
	struct AssociationClassNode *tmp;
	tmp = assNodeList;	/*reset the pointer to the beginning of the linked list*/
	while(tmp!=NULL){
		if(strcmp(tmp->attribute_name,"ROLE")==0 && tmp->displayInFile==0){
			fprintf(fp,"%s",tmp->attribute_value);
			tmp->displayInFile = 1;
			break;
		}
		tmp = tmp->next;
	}
	fprintf(fp,"</role>\n");
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













