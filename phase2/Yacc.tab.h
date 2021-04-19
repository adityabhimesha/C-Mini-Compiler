/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2058 of yacc.c  */
#line 16 "Yacc.y"

    char *str;


/* Line 2058 of yacc.c  */
#line 103 "Yacc.tab.h"
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
