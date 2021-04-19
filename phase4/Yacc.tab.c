/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 2 "Yacc.y"

    #include <stdio.h>
    #include <stdlib.h>
	#include <string.h>
	#include <ctype.h>


	int yylex();
	int yydebug = 0;
	void yyerror(const char*);
	extern int yylineno;
	extern int st[100];
	extern int top;
	extern int count;
	extern void display();
	extern void insert_in_st(char*, char*, int, char*);
	char st1[100][100];
	char i_[2]="0";
	int temp_i = 0;							//in available temporary number
	char tmp_i[10];				//an array to hold temporary variable number as string. We assume this is below 999999999				
	char temp[10]="";				//currentemp[10]="";			//an array to hold temporary varialbe name as string. We assume this is below T999999999	
	int label[20];
	int lnum = 0;				//current available label number.
	int ltop = 0;
	// int abcd = 0;
	int l_while=0;
	// int l_for=0;
	// int flag_set = 1;
	int stop = -1;				//top of stack
	char G_val[10];
	//FILE* ast_tree_output;


	typedef struct quadruples
  	{
  	  char *op;
  	  char *arg1;
  	  char *arg2;
  	  char *res;
  	}quad;
  	int quadindex = 0;														//current index of Q to store the quadruple in.
	quad Q[100];

	void push(char *a)			//push to top of stack
	{
		strcpy(st1[++stop],a);
	}

	void TAC()				//to be called after any expression. say expr is b*c -> pop top three , ti = b*c and insert ti.
	{
	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = %s %s %s\n",temp,st1[stop-2],st1[stop],st1[stop - 1]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop-2]));
	    Q[quadindex].arg2 = (char*)malloc(sizeof(char)*strlen(st1[stop - 1]));
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,st1[stop]);
	    strcpy(Q[quadindex].arg1,st1[stop-2]);
	    strcpy(Q[quadindex].arg2,st1[stop - 1]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;
	    stop-=2;
	    strcpy(st1[stop],temp);
		temp_i++;
	}

	void TAC_assign()
	{
	    printf("%s = %s\n",st1[stop-2],st1[stop - 1]);
	    Q[quadindex].op = (char*)malloc(sizeof(char));
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop - 1]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(st1[stop-2]));
	    strcpy(Q[quadindex].op,"=");
	    strcpy(Q[quadindex].arg1,st1[stop - 1]);
	    strcpy(Q[quadindex].res,st1[stop-2]);
	    quadindex++;
	    stop-=2;
	}

	void TAC_assign_back()
	{
		temp_i--;
	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
		temp_i++;
		printf("%s = %s\n",G_val,temp);
	    Q[quadindex].op = (char*)malloc(sizeof(char));
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(G_val));
	    strcpy(Q[quadindex].op,"=");
		strcpy(Q[quadindex].arg1,temp);
	    strcpy(Q[quadindex].res,G_val);
		quadindex++;
	}
	// ICG - While

	// Create label for while
	void While_Loop_Label()
	{
	
	    label[ltop++] = lnum++;			
	    printf("L%d: \n", label[ltop - 1]);			// print label and increase label number for next use	
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);		//a label's quad 	
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum + 2));   //lum + 2 is a safe way to have enough space for L0, L1, ... etc. 
	    strcpy(Q[quadindex].op,"Label");
	    char x[10];
		x[0] = '0' + label[ltop - 1];
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	}

	// While Loop Condition
	void While_loop_cond()
	{
	 	strcpy(temp,"T");			
	 	sprintf(tmp_i, "%d", temp_i);		//if temp_i = 0, tmp_i has "0"		
	 	strcat(temp,tmp_i);					//temp has "T0"
	 	printf("%s = not %s\n",temp,st1[stop]);		//T0 has not of condition

		//since this is a unary operator, one of the operands is NULL
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;

		//if T0 goto label which will be placed after body
		//in this case op -> if, arg1 -> T0 , res -> L1
	    printf("if %s goto L%d\n",temp,lnum);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	 	temp_i++;
		
		label[ltop++] = lnum;
		lnum++;
	}

	// End While loop
	void While_END()			// in the end insert goto label and also insert the label which should be branched to if condition fails
	{
		printf("goto L%d \n",label[ltop - 2]);	//ltop - 2 contains the label to be branched if true
		Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(l_while+2));
	    strcpy(Q[quadindex].op,"goto");
	    char x[10];
	    sprintf(x,"%d",label[ltop]);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;

	    printf("L%d: \n", label[ltop - 1]);		//ltop - 1 contains the label to be branched if false
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x1[10];
	    sprintf(x1,"%d", label[ltop - 1]);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,x1));
	    quadindex++;
		ltop -= 2;							//since these labels have been used, decrease ltop by two 
	}

	void IFSTMT()
	{

	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = not %s\n",temp,st1[stop]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;

	    printf("if %s goto L%d\n",temp,lnum);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	    temp_i++;
		
	    label[ltop++] = lnum;
		++lnum;									//increase lnum for next needed label.
		
	}

	void Elif()
	{
		printf("L%d: \n",label[--ltop]);		
	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = not %s\n",temp,st1[stop]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;
		

	    printf("if %s goto L%d\n",temp,lnum);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	    temp_i++;

	    label[ltop++] = lnum;							//store this as top of label stack and increase ltop
		++lnum;										//increase lnum for next needed label.
	}

	void if_else_cleanup()
	{
		int y;
		y = label[--ltop];
		printf("L%d: \n",y);
		Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(y+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x[10];
	    sprintf(x,"%d",y);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	}
	
	char LineBreaker[] = "\n_______________________________________________________________________________________________________\n";
	
	//node in AST
	typedef struct ASTNode
	{
		struct ASTNode *left;
		struct ASTNode *right;
		char *token;
	} node;
	
	node *Construct_AST(node *left, node *right, char *token)
	{
		node *newnode = (node *)malloc(sizeof(node));
		char *newstr = (char *)malloc(strlen(token)+1);
		strcpy(newstr, token);
		newnode->left = left;
		newnode->right = right;
		newnode->token = newstr;
		return(newnode); 
	}
	


/* Line 371 of yacc.c  */
#line 364 "Yacc.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "Yacc.tab.h".  */
#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_keyword = 258,
     T_int = 259,
     T_main = 260,
     T_type = 261,
     T_return = 262,
     T_for = 263,
     T_if = 264,
     T_else = 265,
     T_while = 266,
     T_InputStream = 267,
     T_OutputStream = 268,
     T_openParenthesis = 269,
     T_closedParanthesis = 270,
     T_openFlowerBracket = 271,
     T_closedFlowerBracket = 272,
     T_RelationalOperator = 273,
     T_LogicalOperator = 274,
     T_UnaryOperator = 275,
     T_AssignmentOperator = 276,
     T_Semicolon = 277,
     T_identifier = 278,
     T_numericConstants = 279,
     T_stringLiteral = 280,
     T_character = 281,
     T_plus = 282,
     T_minus = 283,
     T_mod = 284,
     T_divide = 285,
     T_multiply = 286,
     T_whiteSpace = 287,
     T_shortHand = 288,
     T_LogicalOr = 289,
     T_LogicalAnd = 290,
     T_not_equal = 291,
     T_equal_equal = 292,
     T_greater_equal = 293,
     T_greater = 294,
     T_less_equal = 295,
     T_less = 296
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 298 "Yacc.y"

	char *str;
	struct ASTNode *NODE;


/* Line 387 of yacc.c  */
#line 454 "Yacc.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 482 "Yacc.tab.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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

# define YYCOPY_NEEDED 1

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

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   385

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNRULES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,    10,    13,    15,    18,    20,    22,    25,
      27,    30,    32,    34,    37,    40,    41,    42,    50,    51,
      59,    60,    69,    70,    74,    75,    80,    81,    84,    86,
      89,    92,    94,    98,   102,   107,   112,   117,   122,   127,
     129,   133,   137,   141,   145,   149,   153,   157,   161,   165,
     169,   173,   177,   181,   183,   185,   187,   191,   195,   199,
     203,   207,   211,   215,   219,   223,   227,   231,   235,   239,
     241,   243,   245,   247
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,     4,     5,    14,    15,    65,    44,    -1,
      47,    46,    -1,    66,    -1,    65,    44,    -1,    47,    -1,
      22,    -1,    47,    46,    -1,    66,    -1,    61,    22,    -1,
      51,    -1,    48,    -1,    59,    22,    -1,     1,    22,    -1,
      -1,    -1,    11,    49,    14,    61,    15,    50,    45,    -1,
      -1,     9,    14,    61,    15,    52,    45,    53,    -1,    -1,
      10,     9,    14,    61,    15,    54,    45,    53,    -1,    -1,
      10,    55,    57,    -1,    -1,    10,    56,    65,    44,    -1,
      -1,    58,    46,    -1,    22,    -1,    61,    22,    -1,    59,
      22,    -1,    48,    -1,    62,    21,    61,    -1,    62,    33,
      61,    -1,     6,    62,    21,    60,    -1,     6,    62,    21,
      63,    -1,     6,    62,    21,    64,    -1,     4,    62,    21,
      60,    -1,     4,    62,    21,    64,    -1,    62,    -1,    61,
      27,    61,    -1,    61,    28,    61,    -1,    61,    30,    61,
      -1,    61,    31,    61,    -1,    61,    29,    61,    -1,    61,
      35,    61,    -1,    61,    34,    61,    -1,    61,    41,    61,
      -1,    61,    40,    61,    -1,    61,    39,    61,    -1,    61,
      38,    61,    -1,    61,    37,    61,    -1,    61,    36,    61,
      -1,    64,    -1,    63,    -1,    62,    -1,    61,    27,    61,
      -1,    61,    28,    61,    -1,    61,    30,    61,    -1,    61,
      31,    61,    -1,    61,    29,    61,    -1,    61,    35,    61,
      -1,    61,    34,    61,    -1,    61,    41,    61,    -1,    61,
      40,    61,    -1,    61,    39,    61,    -1,    61,    38,    61,
      -1,    61,    37,    61,    -1,    61,    36,    61,    -1,    23,
      -1,    25,    -1,    24,    -1,    16,    -1,    17,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   328,   328,   332,   333,   338,   339,   340,   343,   344,
     347,   348,   349,   351,   352,   356,   356,   356,   358,   358,
     360,   360,   361,   361,   362,   362,   363,   366,   367,   370,
     371,   372,   376,   377,   378,   379,   380,   381,   382,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,   414,   415,   416,   417,   418,   419,   423,
     425,   427,   434,   435
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_keyword", "T_int", "T_main", "T_type",
  "T_return", "T_for", "T_if", "T_else", "T_while", "T_InputStream",
  "T_OutputStream", "T_openParenthesis", "T_closedParanthesis",
  "T_openFlowerBracket", "T_closedFlowerBracket", "T_RelationalOperator",
  "T_LogicalOperator", "T_UnaryOperator", "T_AssignmentOperator",
  "T_Semicolon", "T_identifier", "T_numericConstants", "T_stringLiteral",
  "T_character", "T_plus", "T_minus", "T_mod", "T_divide", "T_multiply",
  "T_whiteSpace", "T_shortHand", "T_LogicalOr", "T_LogicalAnd",
  "T_not_equal", "T_equal_equal", "T_greater_equal", "T_greater",
  "T_less_equal", "T_less", "$accept", "Start", "block_end_flower",
  "block", "Multiple_stmts", "stmt", "while_stmt", "$@1", "$@2", "if_stmt",
  "$@3", "elseif_else_empty", "$@4", "$@5", "$@6", "Multiple_stmts_not_if",
  "stmt_without_if", "Assignment_stmt", "expr_without_constants", "expr",
  "idid", "sc", "nc", "openflower", "closeflower", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      47,    47,    47,    47,    47,    49,    50,    48,    52,    51,
      54,    53,    55,    53,    56,    53,    53,    57,    57,    58,
      58,    58,    59,    59,    59,    59,    59,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    62,
      63,    64,    65,    66
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     2,     1,     2,     1,     1,     2,     1,
       2,     1,     1,     2,     2,     0,     0,     7,     0,     7,
       0,     8,     0,     3,     0,     4,     0,     2,     1,     2,
       2,     1,     3,     3,     4,     4,     4,     4,     4,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,    72,     0,     0,
       0,     0,     0,    15,    73,    69,    71,    70,     2,     0,
      12,    11,     0,     0,    55,    54,    53,     4,    14,     0,
       0,     0,     0,     3,     0,     9,    13,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    55,     0,     8,    56,
      57,    60,    58,    59,    62,    61,    68,    67,    66,    65,
      64,    63,    32,    33,    37,     0,    55,    53,    34,    54,
      53,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,    56,    57,
      60,    58,    59,    62,    61,    68,    67,    66,    65,    64,
      63,     7,    26,     6,     0,     0,    22,    19,     5,    17,
       0,     0,     0,     0,    28,    31,    23,     0,     0,     0,
       0,     0,    27,    30,    29,    25,    20,     0,    26,    21
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    18,   112,    33,    19,    20,    32,   115,    21,
      96,   117,   137,   121,   122,   126,   127,    22,    74,    23,
      56,    25,    26,   114,    27
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -108
static const yytype_int16 yypact[] =
{
      10,    17,    25,    19,  -108,    29,    31,  -108,   187,    37,
      30,    30,    46,  -108,  -108,  -108,  -108,  -108,  -108,   187,
    -108,  -108,    48,   194,    -9,  -108,  -108,  -108,  -108,    50,
      54,    -7,    62,  -108,   187,  -108,  -108,  -108,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,     0,  -108,    -7,  -108,    65,
      65,  -108,  -108,  -108,   299,   299,   354,   354,   354,   354,
     354,   354,   269,   269,  -108,   284,    67,    75,  -108,    77,
      78,  -108,    27,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    68,  -108,    51,    56,
      79,    81,    82,   234,   254,    21,   126,   319,   329,   339,
     349,  -108,    95,  -108,   187,    68,     4,  -108,  -108,  -108,
      94,   195,    31,    -7,  -108,  -108,  -108,   187,    87,   214,
     187,   132,  -108,  -108,  -108,  -108,  -108,    68,    95,  -108
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -108,  -108,  -107,  -105,   -29,   -13,   -11,  -108,  -108,  -108,
    -108,   -27,  -108,  -108,  -108,  -108,  -108,    -6,    64,    92,
      -8,    66,   -45,    -5,   -15
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -53
static const yytype_int16 yytable[] =
{
      24,     8,    29,    30,    35,    58,    34,   118,    77,    80,
     119,    24,    51,   120,     1,    81,    15,    16,    17,    35,
     -24,    34,     3,   135,    52,     4,    24,    38,    39,    40,
      41,    42,   138,     5,    43,    44,    45,    46,    47,    48,
      49,    50,    97,   -52,     6,    76,    76,     7,    38,    39,
      40,    41,    42,    15,    38,    39,    40,    41,    42,    28,
      31,    43,    44,    45,    46,    47,    48,    49,    50,     9,
      36,    53,    10,   -40,    11,    54,    57,    12,   -41,    13,
      40,    41,    42,   113,     7,    40,    41,    42,    24,   -39,
     111,    15,    16,    17,    40,    41,    42,   -38,   132,   -35,
     -36,   -44,   113,   -42,   -43,   116,    24,    24,   123,   133,
     125,   139,    35,    24,    34,   128,     0,   130,    78,    24,
      79,     0,    24,    55,   113,     0,     0,     0,     0,    24,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    75,    75,   136,   -51,    82,
       0,     0,     0,    38,    39,    40,    41,    42,     0,    38,
      39,    40,    41,    42,     0,     0,    43,    44,    45,    46,
      47,    48,    49,    50,     0,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,     9,     0,
       0,    10,     0,    11,     0,     0,    12,     0,    13,    10,
       0,    11,     0,     0,    14,     0,    13,     0,     0,     0,
      15,    16,    17,   129,     0,   131,    37,   124,    15,    16,
      17,    38,    39,    40,    41,    42,     0,     0,    43,    44,
      45,    46,    47,    48,    49,    50,   134,     0,     0,     0,
       0,    38,    39,    40,    41,    42,     0,     0,    43,    44,
      45,    46,    47,    48,    49,    50,   -46,     0,     0,     0,
       0,    38,    39,    40,    41,    42,     0,     0,     0,     0,
      45,    46,    47,    48,    49,    50,   -45,     0,     0,     0,
       0,    38,    39,    40,    41,    42,     0,     0,     0,     0,
      45,    46,    47,    48,    49,    50,    38,    39,    40,    41,
      42,     0,     0,    43,    44,    45,    46,    47,    48,    49,
      50,    83,    84,    85,    86,    87,     0,     0,    88,    89,
      90,    91,    92,    93,    94,    95,    38,    39,    40,    41,
      42,     0,     0,     0,     0,    45,    46,    47,    48,    49,
      50,   -50,     0,     0,     0,     0,    38,    39,    40,    41,
      42,   -49,     0,     0,     0,     0,    38,    39,    40,    41,
      42,   -48,     0,     0,     0,     0,    38,    39,    40,    41,
      42,   -47,     0,     0,     0,     0,    38,    39,    40,    41,
      42,    38,    39,    40,    41,    42
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-108)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       8,     6,    10,    11,    19,    34,    19,   114,    53,    54,
     115,    19,    21,     9,     4,    15,    23,    24,    25,    34,
      16,    34,     5,   130,    33,     0,    34,    27,    28,    29,
      30,    31,   137,    14,    34,    35,    36,    37,    38,    39,
      40,    41,    15,    22,    15,    53,    54,    16,    27,    28,
      29,    30,    31,    23,    27,    28,    29,    30,    31,    22,
      14,    34,    35,    36,    37,    38,    39,    40,    41,     1,
      22,    21,     4,    22,     6,    21,    14,     9,    22,    11,
      29,    30,    31,    96,    16,    29,    30,    31,    96,    22,
      22,    23,    24,    25,    29,    30,    31,    22,   127,    22,
      22,    22,   115,    22,    22,    10,   114,   115,    14,    22,
     121,   138,   127,   121,   127,   121,    -1,   122,    54,   127,
      54,    -1,   130,    31,   137,    -1,    -1,    -1,    -1,   137,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    15,    22,    57,
      -1,    -1,    -1,    27,    28,    29,    30,    31,    -1,    27,
      28,    29,    30,    31,    -1,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,     1,    -1,
      -1,     4,    -1,     6,    -1,    -1,     9,    -1,    11,     4,
      -1,     6,    -1,    -1,    17,    -1,    11,    -1,    -1,    -1,
      23,    24,    25,   121,    -1,   123,    22,    22,    23,    24,
      25,    27,    28,    29,    30,    31,    -1,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    22,    -1,    -1,    -1,
      -1,    27,    28,    29,    30,    31,    -1,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    22,    -1,    -1,    -1,
      -1,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    22,    -1,    -1,    -1,
      -1,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    27,    28,    29,    30,
      31,    -1,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    27,    28,    29,    30,    31,    -1,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,    22,    -1,    -1,    -1,    -1,    27,    28,    29,    30,
      31,    22,    -1,    -1,    -1,    -1,    27,    28,    29,    30,
      31,    22,    -1,    -1,    -1,    -1,    27,    28,    29,    30,
      31,    22,    -1,    -1,    -1,    -1,    27,    28,    29,    30,
      31,    27,    28,    29,    30,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    43,     5,     0,    14,    15,    16,    65,     1,
       4,     6,     9,    11,    17,    23,    24,    25,    44,    47,
      48,    51,    59,    61,    62,    63,    64,    66,    22,    62,
      62,    14,    49,    46,    47,    66,    22,    22,    27,    28,
      29,    30,    31,    34,    35,    36,    37,    38,    39,    40,
      41,    21,    33,    21,    21,    61,    62,    14,    46,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    60,    61,    62,    64,    60,    63,
      64,    15,    61,    27,    28,    29,    30,    31,    34,    35,
      36,    37,    38,    39,    40,    41,    52,    15,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    22,    45,    47,    65,    50,    10,    53,    44,    45,
       9,    55,    56,    14,    22,    48,    57,    58,    59,    61,
      65,    61,    46,    22,    22,    44,    15,    54,    45,    53
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1792 of yacc.c  */
#line 328 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(6) - (6)].NODE);}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 332 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 333 "Yacc.y"
    {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 338 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(2) - (2)].NODE);}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 339 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 340 "Yacc.y"
    {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 343 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 344 "Yacc.y"
    {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 347 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);  }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 348 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);  }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 349 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 351 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);  }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 352 "Yacc.y"
    {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 356 "Yacc.y"
    {While_Loop_Label();}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 356 "Yacc.y"
    {While_loop_cond();}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 356 "Yacc.y"
    {While_END();(yyval.NODE) = Construct_AST((yyvsp[(3) - (7)].str), (yyvsp[(5) - (7)].str), "While"); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 358 "Yacc.y"
    {IFSTMT();}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 358 "Yacc.y"
    {(yyval.NODE) = Construct_AST((yyvsp[(3) - (7)].NODE), (yyvsp[(6) - (7)].NODE), "IF");}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 360 "Yacc.y"
    {;Elif();}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 360 "Yacc.y"
    {(yyval.NODE) = Construct_AST((yyvsp[(4) - (8)].NODE), (yyvsp[(7) - (8)].NODE), "ELSEIF"); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 361 "Yacc.y"
    {if_else_cleanup();}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 361 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(3) - (3)].NODE);}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 362 "Yacc.y"
    {if_else_cleanup();}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 362 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(4) - (4)].NODE);}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 363 "Yacc.y"
    {if_else_cleanup(); (yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 366 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 367 "Yacc.y"
    {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 370 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 371 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 372 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 376 "Yacc.y"
    {push("=");TAC_assign();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE),(yyvsp[(3) - (3)].NODE),"=");}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 377 "Yacc.y"
    {push("se");TAC_assign();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE),(yyvsp[(3) - (3)].NODE),"SE"); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 378 "Yacc.y"
    {push("=");strcpy(G_val,(yyvsp[(2) - (4)].NODE)->token);TAC_assign_back();insert_in_st((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].NODE)->token, st[top], "j");(yyval.NODE) = Construct_AST((yyvsp[(2) - (4)].NODE),(yyvsp[(4) - (4)].NODE),"=");}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 379 "Yacc.y"
    {push("=");TAC_assign();insert_in_st((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].NODE)->token, st[top], (yyvsp[(4) - (4)].NODE)->token);(yyval.NODE) = Construct_AST((yyvsp[(2) - (4)].NODE),(yyvsp[(4) - (4)].NODE),"=");}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 380 "Yacc.y"
    {push("=");TAC_assign();insert_in_st((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].NODE)->token, st[top], (yyvsp[(4) - (4)].NODE)->token);(yyval.NODE) = Construct_AST((yyvsp[(2) - (4)].NODE),(yyvsp[(4) - (4)].NODE),"=");}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 381 "Yacc.y"
    {push("=");strcpy(G_val,(yyvsp[(2) - (4)].NODE)->token);TAC_assign_back();insert_in_st((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].NODE)->token, st[top], "j");(yyval.NODE) = Construct_AST((yyvsp[(2) - (4)].NODE),(yyvsp[(4) - (4)].NODE),"=");}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 382 "Yacc.y"
    {push("=");TAC_assign();insert_in_st((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].NODE)->token, st[top], (yyvsp[(4) - (4)].NODE)->token);(yyval.NODE) = Construct_AST((yyvsp[(2) - (4)].NODE),(yyvsp[(4) - (4)].NODE),"=");}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 387 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 388 "Yacc.y"
    {push("+");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "+");}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 389 "Yacc.y"
    {push("-");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "-");}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 390 "Yacc.y"
    {push("/");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "/");}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 391 "Yacc.y"
    {push("*");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "*");}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 392 "Yacc.y"
    {push("%");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "%");}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 393 "Yacc.y"
    {push("&");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "&");}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 394 "Yacc.y"
    {push("|");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "|");}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 395 "Yacc.y"
    {push("<");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "<");}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 396 "Yacc.y"
    {push("<=");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "<=");}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 397 "Yacc.y"
    {push(">");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), ">");}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 398 "Yacc.y"
    {push(">=");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), ">=");}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 399 "Yacc.y"
    {push("==");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "==");}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 400 "Yacc.y"
    {push("!=");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "!=");}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 404 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 405 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 406 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 407 "Yacc.y"
    {push("+");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "+");}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 408 "Yacc.y"
    {push("-");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "-");}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 409 "Yacc.y"
    {push("/");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "/");}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 410 "Yacc.y"
    {push("*");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "*");}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 411 "Yacc.y"
    {push("%");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "%");}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 412 "Yacc.y"
    {push("&");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "&");}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 413 "Yacc.y"
    {push("|");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "|");}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 414 "Yacc.y"
    {push("<");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "<");}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 415 "Yacc.y"
    {push("<=");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "<=");}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 416 "Yacc.y"
    {push(">");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), ">");}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 417 "Yacc.y"
    {push(">=");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), ">=");}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 418 "Yacc.y"
    {push("==");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "==");}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 419 "Yacc.y"
    {push("!=");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "!=");}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 423 "Yacc.y"
    {push((char*)yylval.str);(yyval.NODE) = Construct_AST(NULL, NULL, (char*)yylval.str); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 425 "Yacc.y"
    {push((char*)yylval.str);(yyval.NODE) = Construct_AST(NULL, NULL, (char*)yylval.str); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 427 "Yacc.y"
    {push((char*)yylval.str);(yyval.NODE) = Construct_AST(NULL, NULL, (char*)yylval.str); }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 434 "Yacc.y"
    {}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 435 "Yacc.y"
    {}
    break;


/* Line 1792 of yacc.c  */
#line 2280 "Yacc.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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


/* Line 2055 of yacc.c  */
#line 438 "Yacc.y"


void yyerror(const char *str) 
{ 
	printf("Error | Line: %d\n%s\n",yylineno,str);
} 

void symboldisplay()
{
	printf("%s",LineBreaker);
	printf("Quadruplets\n");
	for(int i=0;i<quadindex;i++)
    {
        printf("%-8s \t %-8s \t %-8s \t %-6s \n",Q[i].op,Q[i].arg1,Q[i].arg2,Q[i].res);
    }
	printf("%s",LineBreaker);
}

int isDigit(char* in)
{
	for(int i = 0; i < strlen(in); ++i)
	{
		if(!isdigit(in[i])) return 0;
	}
	return 1;
}

int main()
{
	yyparse();				//parse through the input. This step effectively also fills the symbol table, generates the AST and computes & prints ICG.
	
	printf("\n**************************************Symbol Table****************************************\n");
	
	display();				//display the symbol table. The function is defined in lex.l
	
	printf("\n*************************************************************************************************\n");
	
	printf("Before Optimization:\n");
	symboldisplay();

	return 0;
}
