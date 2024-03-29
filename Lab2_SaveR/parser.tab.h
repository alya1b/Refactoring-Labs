/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    RECORD = 258,                  /* RECORD  */
    NAME = 259,                    /* NAME  */
    IS = 260,                      /* IS  */
    LEFT_BRACE = 261,              /* LEFT_BRACE  */
    RIGHT_BRACE = 262,             /* RIGHT_BRACE  */
    LEFT_PAREN = 263,              /* LEFT_PAREN  */
    RIGHT_PAREN = 264,             /* RIGHT_PAREN  */
    COMMA = 265,                   /* COMMA  */
    SEMICOLON = 266,               /* SEMICOLON  */
    CHAR = 267,                    /* CHAR  */
    INTEGER = 268,                 /* INTEGER  */
    FLOAT = 269,                   /* FLOAT  */
    DOUBLE = 270,                  /* DOUBLE  */
    ERROR = 271,                   /* ERROR  */
    IDENTIFIER = 272,              /* IDENTIFIER  */
    NUMBER = 273                   /* NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
  char * IDENTIFIER;                       /* IDENTIFIER  */
  long NUMBER;                             /* NUMBER  */
  struct attribute attribute;              /* attribute  */
  struct attribute_list * attribute_list;  /* attribute_list  */
  struct attribute_list * dangling_comma_attribute_list; /* dangling_comma_attribute_list  */
  struct attribute_type attribute_type;    /* attribute_type  */
  struct relation relation;                /* relation  */
  struct relation_list * relation_list;    /* relation_list  */

#line 91 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (struct relation_list **result);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
