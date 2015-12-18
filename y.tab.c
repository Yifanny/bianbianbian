/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TYPE = 258,
     NUMBER = 259,
     INGREDIENT = 260,
     OPERATION = 261,
     SPLITE = 262,
     CONJUNCTION = 263,
     NEW = 264,
     NO_MORE_SPLITE = 265
   };
#endif
/* Tokens.  */
#define TYPE 258
#define NUMBER 259
#define INGREDIENT 260
#define OPERATION 261
#define SPLITE 262
#define CONJUNCTION 263
#define NEW 264
#define NO_MORE_SPLITE 265




/* Copy the first part of user declarations.  */
#line 1 "fastfood.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "init.h"
	#include "config.h"
	int yylex(void);
	void yyerror(char*);
	commandes create_commande(int num, char* type);
	node* create_ingredient(char* opr, char* name);
	node* create_ingredients(char* opr, char* name, node* in2);
	node* create_entity(int num, node* in1);
	node* combine_entities(node* ent1, char* spl, node* ent2);
	commandes add_requirement(commandes* cmd, node* req);
	commandes add_condition(commandes* cmd, char* spl, node* cons);
	void nshow(node* point);
	cook* init();
	int check(char* ingredient, char* type);
	int verifie_commandes(node* point, char* type, char* opr, int cnt);
	char** collect_require(node* point, char** res, char* opr);
	kind* make_kind(node* head);
	kind* collect_kind(node* point, kind* res);
	version transform(node* head, char* type);
	ingredient* ingredient_list(version* ver,int num);
	version* combien_version(version* ver, int count);
	void pshow(version* v);
	
	cook* menu;
	int count;
	int is_meat;
	int length;
	int ret;
	int i;
	char* tmp;


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 37 "fastfood.y"
{
	int num;
	char* word;
	struct node* point;
	struct commandes* cmd;
}
/* Line 193 of yacc.c.  */
#line 159 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 172 "y.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   13

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  11
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  6
/* YYNRULES -- Number of rules.  */
#define YYNRULES  11
/* YYNRULES -- Number of states.  */
#define YYNSTATES  18

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   265

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
       5,     6,     7,     8,     9,    10
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     8,    12,    15,    17,    22,    25,
      28,    32
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      12,     0,    -1,    -1,    12,    13,     9,    -1,    16,     7,
      14,    -1,    16,    15,    -1,    16,    -1,     4,    15,     7,
      14,    -1,     4,    15,    -1,     6,     5,    -1,     6,     5,
      15,    -1,     4,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    62,    62,    65,   107,   113,   117,   124,   127,   133,
     136,   142
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "NUMBER", "INGREDIENT",
  "OPERATION", "SPLITE", "CONJUNCTION", "NEW", "NO_MORE_SPLITE", "$accept",
  "program", "condition", "expr", "taste", "simple", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    11,    12,    12,    13,    13,    13,    14,    14,    15,
      15,    16
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     3,     2,     1,     4,     2,     2,
       3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     6,    11,     3,     0,     0,
       5,     9,     0,     4,    10,     8,     0,     7
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     4,    13,    10,     5
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -7
static const yytype_int8 yypact[] =
{
      -7,     0,    -7,     4,    -1,    -5,    -7,    -7,    -2,     5,
      -7,     6,     6,    -7,    -7,     3,     5,    -7
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -7,    -7,    -7,    -3,    -6,    -7
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       2,     8,     9,    11,     3,    14,    15,     6,     7,    12,
      16,     0,     8,    17
};

static const yytype_int8 yycheck[] =
{
       0,     6,     7,     5,     4,    11,    12,     3,     9,     4,
       7,    -1,     6,    16
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    12,     0,     4,    13,    16,     3,     9,     6,     7,
      15,     5,     4,    14,    15,    15,     7,    14
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
        case 2:
#line 62 "fastfood.y"
    {
		printf("waiting for the new command\n");
	}
    break;

  case 3:
#line 65 "fastfood.y"
    {		
		printf("%s, nice choice\n", sandwich[count - 1].type);
		//nshow(&sandwich[count - 1].head);
		printf("henji\n");
		if (!strcmp(fromage, sandwich[count - 1].type)) {
			is_meat = 0;
			ret = verifie_commandes(&sandwich[count - 1].head, sandwich[count - 1].type, NULL, 2 * sandwich[count - 1].head.left->content.num);
		}
		else {
			is_meat = 1;
			ret = verifie_commandes(&sandwich[count - 1].head, sandwich[count - 1].type, NULL, 2 * sandwich[count - 1].head.left->content.num);
		}
		printf("lalal: %d\n", ret);
		if (ret < 0 || is_meat > 1) {
			yyerror("error input\n");
			return 1;
		}
		
		order = malloc(count * sizeof(version));
		printf("start transform\n");
		length = ret;
		for (i = 0; i < count; i++) {
			order[i] = transform(&sandwich[i].head, sandwich[i].type);
		}
		if (length > 0 && length != sandwich[count - 1].head.left->content.num) {
			order[count - 1].num++;
			order[count - 1].types = realloc(order[count - 1].types, order[count - 1].num * sizeof(kind));
			order[count - 1].types[order[count - 1].num - 1].require = malloc(2 * sizeof(char*));
			order[count - 1].types[order[count - 1].num - 1].require[0] = NULL;
			order[count - 1].types[order[count - 1].num - 1].require[1] = NULL;
			order[count - 1].types[order[count - 1].num - 1].num = 2;
			order[count - 1].types[order[count - 1].num - 1].cnt = length;
		} 
		printf("finish transform\n");
		pshow(order);
		
		printf("waiting for the new command\n");

	}
    break;

  case 4:
#line 107 "fastfood.y"
    {
		printf("require are %s\n", sandwich[count - 1].type);
		sandwich[count - 1] = add_condition((yyvsp[(1) - (3)].cmd), (yyvsp[(2) - (3)].word), (yyvsp[(3) - (3)].point));
		
		(yyval.cmd) = &sandwich[count - 1];
	}
    break;

  case 5:
#line 113 "fastfood.y"
    {
		sandwich[count - 1] = add_requirement((yyvsp[(1) - (2)].cmd), (yyvsp[(2) - (2)].point));
		(yyval.cmd) = &sandwich[count - 1];
	}
    break;

  case 6:
#line 117 "fastfood.y"
    {
		(yyval.cmd) = (yyvsp[(1) - (1)].cmd);
		printf("No %d: order finish\n", count);
	}
    break;

  case 7:
#line 124 "fastfood.y"
    {
		(yyval.point) = combine_entities(create_entity((yyvsp[(1) - (4)].num), (yyvsp[(2) - (4)].point)), (yyvsp[(3) - (4)].word), (yyvsp[(4) - (4)].point));
	}
    break;

  case 8:
#line 127 "fastfood.y"
    {
		(yyval.point) = create_entity((yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].point));
	}
    break;

  case 9:
#line 133 "fastfood.y"
    {
		(yyval.point) = create_ingredient((yyvsp[(1) - (2)].word), (yyvsp[(2) - (2)].word));
	}
    break;

  case 10:
#line 136 "fastfood.y"
    {
		(yyval.point) = create_ingredients((yyvsp[(1) - (3)].word), (yyvsp[(2) - (3)].word), (yyvsp[(3) - (3)].point));
	}
    break;

  case 11:
#line 142 "fastfood.y"
    {
		printf("%s\n", (yyvsp[(2) - (2)].word));
		if (count) {
			sandwich = realloc(sandwich, (count + 1) * sizeof(commandes));
		}
		else {
			sandwich = malloc(sizeof(commandes));
		}
			
		sandwich[count++] = create_commande((yyvsp[(1) - (2)].num), (yyvsp[(2) - (2)].word));
		printf("%s commande taken!\n", sandwich[count - 1].type);
		(yyval.cmd) = &sandwich[count - 1];
		
	}
    break;


/* Line 1267 of yacc.c.  */
#line 1488 "y.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 158 "fastfood.y"



#include "init.h"
#include <stdlib.h>

commandes create_commande(int num, char* type) {
	commandes cmd;
	printf("creating %s \n", type);
	cmd.type = type;
	cmd.head.typenode = 4;
	cmd.head.content.word = NULL;
	cmd.head.left = malloc(sizeof(node));
	if (cmd.head.left == NULL) {
		yyerror("not enough memory!\n");
	}
	cmd.head.left->typenode = 1;
	cmd.head.left->content.num = num;
	cmd.head.left->left = NULL;
	cmd.head.left->right = NULL;
	cmd.head.right = NULL;
	
	return cmd;
}

node* create_ingredient(char* opr, char* name) {
	node* p = malloc(sizeof(node));
	if (p == NULL) {
		yyerror("not enough memory!\n");
	}
	
	p->typenode = 3;
	p->content.word = opr;
	
	p->left = malloc(sizeof(node));
	if (p->left == NULL) {
		yyerror("not enough memory!\n");
	}
	p->left->typenode = 2;
	p->left->content.word = name;
	
	p->right = NULL;
	
	return p;
}


node* create_ingredients(char* opr, char* name, node* in2) {
	node* p = create_ingredient(opr, name);
	p->right = in2;
	
	return p;
}

node* create_entity(int num, node* in1) {
	node* p = malloc(sizeof(node));
	if (p == NULL) {
		yyerror("not enough memory!\n");
	}
	
	p->typenode = 4;
	p->content.word = NULL;
	p->left = malloc(sizeof(node));
	if (p->left == NULL) {
		yyerror("not enough memory!\n");
	}
	
	p->left->typenode = 1;
	p->left->content.num = num;
	p->left->left = NULL;
	p->left->right = NULL;
	
	p->right = in1;
	
	return p;
 
}

node* combine_entities(node* ent1, char* spl, node* ent2) {
	node* p = malloc(sizeof(node));
	if (p == NULL) {
		yyerror("not enough memory!\n");
	}
	
	p->typenode = 0;
	p->content.word = spl;
	p->left = ent1;
	p->right = ent2;
	
	return p; 
}

 commandes add_requirement(commandes* cmd, node* req) {
	 cmd->head.right = req;
	 
	 return *cmd;
	 
 }
 
 commandes add_condition(commandes* cmd, char* spl, node* cons) {
	 cmd->head.content.word = spl;
	 cmd->head.right = cons;
	 cmd->head.typenode = 0;
	 
	 return *cmd;
 }

 void nshow(node* point) {
	if (point != NULL) {
		if (point->typenode == 1) {
					printf("number: %d\n", point->content.num);
		}
		else if (point->content.word != NULL) {
			printf("%s\n", point->content.word);
		}
		
		nshow(point->left);
	 	nshow(point->right);
	 }
 }

cook* init() {
	int i;
	cook* cook_list;
	cook_list = malloc(5 * sizeof(cook));
	cook_list[0].name = "fromage";
	for(i = 0; i < sizeof(cook_fromage); i++){
			cook_list[0].material[i] = cook_fromage[i];
	}
	cook_list[1].name = "jambon-beurre";
	for(i = 0; i < sizeof(cook_jambon); i++){
		cook_list[1].material[i] = cook_jambon[i];
	}
	cook_list[2].name = "panini";
	for(i = 0; i < sizeof(cook_panini); i++){
		cook_list[2].material[i] = cook_panini[i];
	}
	cook_list[3].name = "belge";
	for(i = 0; i < sizeof(cook_belge); i++){
		cook_list[3].material[i] = cook_belge[i];
	}
	cook_list[4].name = "dieppois";
	for(i = 0; i < sizeof(cook_dieppois); i++){
		cook_list[4].material[i] = cook_dieppois[i];
	}
	return cook_list;
}

/* Return: 1 means exist, 0 means not exist */
int check(char* ingredient, char* type) {
	int i, j;
	for (i = 0; i < CNTSANDW; i++) {
		if (strstr(type, menu[i].name) != NULL) {
			for (j = 0; j < material[i]; j++) {
				if (!strcmp(ingredient, menu[i].material[j].name)) {
					return 1;
				}
			}
		}
	}
	return 0;
}


int verifie_commandes(node* point, char* type, char* opr, int cnt) {
	int ret;
	if (point != NULL) {
		switch (point->typenode) {
			case 4:
			case 0:
				if ((ret = verifie_commandes(point->left, type, NULL, cnt)) >= 0) {
					return verifie_commandes(point->right, type, NULL, ret);
				}
				else {
					return -1;
				}
				break;
			case 1:
				printf("cnt: %d, current: %d\n", cnt, point->content.num);
				if (cnt - point->content.num < 0) {
					return -1;
				}
				else {
					return cnt - point->content.num;
				}
				break;
			case 2:
				ret = check(point->content.word, type);
				tmp = point->content.word;
				printf("%s %s %d henji\n", tmp, opr, ret);
				if (!strcmp(opr, avec) || !strcmp(opr, mais_avec)) {
					printf("now: %d\n", ret);
					if (!strcmp(tmp, steak) || !strcmp(tmp, thon) || !strcmp(tmp, jambon)) {
						is_meat++;
					}
					if (ret) {
						return -1;
					}
					else {
						return cnt;
					}
				}
				else if (!strcmp(opr, sans) || !strcmp(opr, mais_sans)) {
					if (ret) {
						if (!strcmp(tmp, steak) || !strcmp(tmp, thon) || !strcmp(tmp, jambon)) {
							is_meat--;
						}
						return cnt;
					}
					else {
						return -1;
					}
				}
				else if (!strcmp(opr, avec_double) || !strcmp(opr, mais_avec_double)) {
					if (ret) {
						if (!strcmp(tmp, steak) || !strcmp(tmp, thon) || !strcmp(tmp, jambon)) {
							return -1;
						}
						else {
							return cnt;
						}
					}
					else {
						return -1;
					}
				}
				else {
					return -1;
				}
			case 3:
				if (!strcmp(point->content.word, sans) || !strcmp(point->content.word, mais_sans) || !strcmp(point->content.word, avec_double) || 
					!strcmp(point->content.word, mais_avec_double) || !strcmp(point->content.word, avec) || !strcmp(point->content.word, mais_avec)) {
					if ((ret = verifie_commandes(point->left, type, point->content.word, cnt)) >= 0) {
						return verifie_commandes(point->right, type, point->content.word, ret);
					}
					else {
						return -1;
					}
				}
				else if (!strcmp(point->content.word, ni) || !strcmp(point->content.word, et) || !strcmp(point->content.word, comma)) {
					if (strstr(opr, twice) != NULL) {
						if (strstr(opr, avec) != NULL) {
							if ((ret = verifie_commandes(point->left, type, avec, cnt)) >= 0) {
								return verifie_commandes(point->right, type, avec, ret);
							}
							else {
								return -1;
							}
						}
						else if (strstr(opr, sans) != NULL) {
							if ((ret = verifie_commandes(point->left, type, sans, cnt)) >= 0) {
								return verifie_commandes(point->right, type, sans, ret);
							}
							else {
								return -1;
							}
						}
					}
					else {
						if ((ret = verifie_commandes(point->left, type, opr, cnt)) >= 0) {
								return verifie_commandes(point->right, type, opr, ret);
							}
						else {
							return -1;
						}
					}
				}
				else if (!strcmp(point->content.word, et_double) || !strcmp(point->content.word, comma_double)) {
					if (strstr(opr, avec) != NULL) {
						if ((ret = verifie_commandes(point->left, type, avec_double, cnt)) >= 0) {
							return verifie_commandes(point->right, type, opr, ret);
						}
						else {
							return -1;
						}
					}
					else {
						return -1;
					}
				}
				else {
					return -1;
				}
		}
	}
	return cnt;
}

char** collect_require(node* point, char** res, char* opr) {
	int i, j;
	printf("%s  \n", opr);
	if (point != NULL) {
		printf("hereh\n");
		tmp = point->content.word;
		printf("%d %s as\n", point->typenode, tmp);
		if (strstr(tmp, avec) != NULL) {	
			printf("lalalalalalalala\n");
			if (res[0] == NULL) {
			printf(" current condition is : %s \n", res[0]);
				i = strlen(tmp) + strlen(point->left->content.word) + 2;
				res[0] = malloc(i * sizeof(char));
				res[0] = memset(res[0], '\0', i);
				printf(" current condition is : %s \n", res[0]);
				printf(" current add is : %s \n", tmp);
				printf(" current condition is : %s \n", res[0]);
				res[0] = strcat(res[0], tmp);
				printf(" current condition is : %s \n", res[0]);
				res[0] = strcat(res[0], point->left->content.word);
				printf(" current condition is : %s \n", res[0]);
				i = strlen(res[0]);
				res[0][i] = ' ';
				res[0][i + 1] = '\0';
			}
			else {
				res[0] = realloc(res[0], (strlen(res[0]) + strlen(tmp) + strlen(point->left->content.word) + 2) * sizeof(char));
				res[0] = strcat(res[0], tmp);
				res[0] = strcat(res[0], point->left->content.word);
				i = strlen(res[0]);
				res[0][i] = ' ';
				res[0][i + 1] = '\0';
			}
			opr = avec;
			
		}
		else if (strstr(tmp, sans) != NULL) {
			printf("herer?\n");
			if (res[1] == NULL) {
				i = strlen(tmp) + strlen(point->left->content.word) + 2;
				res[1] = malloc(i * sizeof(char));
				res[1] = memset(res[1], '\0', i);
				res[1] = strcat(res[1], tmp);
				printf("muamua\n");
				res[1] = strcat(res[1], point->left->content.word);
				i = strlen(res[1]);
				res[1][i] = ' ';
				res[1][i + 1] = '\0';
			}
			else {
				res[1] = realloc(res[1], (strlen(res[1]) + strlen(tmp) + strlen(point->left->content.word) + 2) * sizeof(char));
				res[1] = strcat(res[1], tmp);
				res[1] = strcat(res[1], point->left->content.word);
				i = strlen(res[1]);
				res[1][i] = ' ';
				res[1][i + 1] = '\0';
			}
			opr = sans;
		}
		else {
			i = strstr(opr, avec) != NULL?0:1;
			res[i] = realloc(res[i], (strlen(res[i]) + strlen(tmp) + strlen(point->left->content.word) + 2) * sizeof(char));
			printf(" current condition is : %s \n", res[i]);
			res[i] = strcat(res[i], tmp);	
			printf(" current condition is : %s \n", res[i]);	
			res[i] = strcat(res[i], point->left->content.word);
			j = strlen(res[i]);
			res[i][j] = ' ';
			res[i][j + 1] = '\0';
			
			
		}
		return collect_require(point->right, res, opr);
	}
	return res;
	
} 

kind* make_kind(node* head) {
	kind* res;
	char** result = malloc(2 * sizeof(char*));
	result[0] = NULL;
	result[1] = NULL;
	res = malloc(sizeof(kind));
	res->cnt = head->left->content.num;
	printf("number of type: %d\n", res->cnt); 
	if (head->right != NULL) {
		res->require = collect_require(head->right, result, head->right->content.word);
	}
	else {
		res->require = result;
	}
	printf("ls\n");
	res->num = 2;
	return res;
}

kind* collect_kind(node* point, kind* res) {
	kind* ans;
	printf("here %d\n", point->typenode);
	if (point->typenode == 4) {
		ans = make_kind(point);
		printf("inside %d\n", ret);
		res = realloc(res, (ret + 1) * sizeof(kind));
		res[ret] = *ans;
		ret++;
		return res;
	}
	else if (point->typenode == 0) {
		ans = collect_kind(point->left, res);
		return collect_kind(point->right, ans);
	}
	return res;
}

version transform(node* head, char* type) {
	version res;
	ret = 0;
	res.types = NULL;
	res.type = type;
	res.types = collect_kind(head, res.types);
	printf("finish collect\n");
	res.num = ret;
	return res;
}
	
/*
ingredient* ingredient_list(version* ver,int num) {
	cook* cook_list;
	cook_list = init();
	ingredient list[12] = {
		{0.0,"pain"},
		{0.0,"jambon"},
		{0.0,"beurre"},
		{0.0,"salade"},
		{0.0,"emmental"},
		{0.0,"ketchup"},
		{0.0,"moutarde"},
		{0.0,"mayonnaise"},
		{0.0,"frites"},
		{0.0,"tomate"},
		{0.0,"steak"},
		{0.0,"thon"}
	};
	
	ingredient add[12] = {
		{1.0,"pain"},
		{1.0,"jambon"},
		{10.0,"beurre"},
		{10.0,"salade"},
		{2.0,"emmental"},
		{10.0,"ketchup"},
		{10.0,"moutarde"},
		{20.0,"mayonnaise"},
		{50.0,"frites"},
		{0.5,"tomate"},
		{1.0,"steak"},
		{50.0,"thon"}
	};
	
	int n, i, j, k, r, count, sum;
	
	int material[5] = {3, 4, 5, 5, 4};
	char** sandwich;
	ingredient* cur;
	char* modingred;
	int m, f;
	
	sandwich = malloc(5 * sizeof(char*));
	for(i = 0; i < 5; i++){
		sandwich[i] = malloc(20 * sizeof(char));
	}
	sandwich[0] = "fromage";
	sandwich[1] = "jambon-beurre";
	sandwich[2] = "panini";
	sandwich[3] = "belge";
	sandwich[4] = "deippois";
	

	m = 0;
	while( m < num ) {
		sum = 0;
		f = 0;
		while(f < ver->num){
			//printf(" sum %d\n",sum);
			sum = sum + ver->types[f].cnt;;
			f++;
		}
		for (i = 0; i < 5; i++) {
			if(strcmp(ver->type,cook_list[i].name) == 0) {
				count = material[i];
				cur = malloc(count * sizeof(ingredient));
				for(r = 0; r < count; r++){
					cur[r] = cook_list[i].material[r];
				}
				for(j = 0; j < material[i]; j++){
					for(k = 0; k < 12; k++) {
						if(strcmp(list[k].name,cook_list[i].material[j].name) == 0){
							list[k].num = list[k].num + sum * cook_list[i].material[j].num;
						}
					}	
				}
				break;
			}
		}
		kind* reqs;
		n = ver->num;
		reqs = malloc(n * sizeof(kind));
		reqs = ver->types;
		for(i = 0; i < n; i++) {
			for(j = 0; j < reqs[i].num; j++) {
				if(strstr(reqs[i].require[j],"sans") != NULL || strstr(reqs[i].require[j],"avec") != NULL) {
					if(strstr(reqs[i].require[j],"mais") != NULL) {
						n = (int)sizeof(reqs[i].require[j]) - 10;
						modingred = malloc(n * sizeof(char));
						modingred = reqs[i].require[j] + 10;
					}
					else{
						n = sizeof(reqs[i].require[j]) - 5;
						modingred = malloc(n * sizeof(char));
						modingred = reqs[i].require[j] + 5;	
					}
					int l;
					char* ingred;
					l = 1;
					for(r = 0; r < strlen(modingred) - 1; ){
						for(k = 0; k < 12; k++) {
							if(modingred[r] == list[k].name[0]) {
								if(modingred[r+1] == list[k].name[1]) {
									ingred = list[k].name;
									l = strlen(list[k].name);
									if(strstr(reqs[i].require[j],"sans") != NULL){
										list[k].num = list[k].num - reqs[i].cnt * find(ver->type,ingred);
									}
									else{
										list[k].num = list[k].num + reqs[i].cnt * add[k].num;
									}
									break;
								}
							}
							else{
								l = 1;
							}
						}
						r = r + l; 
					}
				}
			}
		}
		m++;
		ver++;
	}
	return list;
}
*/

version* combien_version(version* ver, int count) {
	int a, b, c, d, num, m;
	for(a = 0; a < count; a++) {
		for(b = a + 1; b < count; b++) {
			if(strcmp(ver[a].type,ver[b].type) == 0) {
				num = ver[a].num;
				ver[a].num = ver[a].num + ver[b].num;
				ver[a].types = realloc(ver[a].types, ver[a].num * sizeof(kind));
				for(c = 0; c < ver[b].num; c++) {
					//ver[a].types[num+c] = malloc(sizeof(kind));
					ver[a].types[num+c].cnt = ver[b].types[c].cnt;
					ver[a].types[num+c].num = ver[b].types[c].num;
					m = ver[b].types[c].num;
					ver[a].types[num+c].require = malloc(m*sizeof(char*));
					for(d = 0; d < m; d++) {
						int len = strlen(ver[b].types[c].require[d]);
				    	ver[a].types[num+c].require[d] = malloc(d*sizeof(char));
						strcpy(ver[a].types[num+c].require[d], ver[b].types[c].require[d]);
					}
				}
			}
		}
	}
	return ver;
}

void pshow(version* vlist) {
	int i, j, k;
	printf("%d: aaaaaaaa\n",vlist[0].types[0].cnt);
	
	//printf("%d: %s lalalala\n", vlist[0].types[0].cnt, vlist[0].types[0].require[0]);
	for (i = 0; i < count; i++) {
		printf("type is : %s\n", vlist[i].type);
		for (j = 0; j < vlist[i].num; j++ ) {
			printf("     %d: ", vlist[i].types[j].cnt);
			for (k = 0; k < vlist[i].types[j].num; k++) {
				printf(" %s ", vlist[i].types[j].require[k]);
			}
			printf("\n");
		}
	}
}

void yyerror(char* s) {
	fprintf(stderr, "%s\n", s);
		
}

int main() {
	menu = init();
	yyparse();
	return 0;
}
