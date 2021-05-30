/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_SRC_PARSER_HH_INCLUDED
# define YY_YY_SRC_PARSER_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    KW_AND = 258,
    KW_ARRAY = 259,
    KW_BEGIN = 260,
    KW_CASE = 261,
    KW_CONST = 262,
    KW_DIV = 263,
    KW_DO = 264,
    KW_DOWNTO = 265,
    KW_ELSE = 266,
    KW_END = 267,
    KW_FOR = 268,
    KW_FUNCTION = 269,
    KW_GOTO = 270,
    KW_IF = 271,
    KW_IN = 272,
    KW_MOD = 273,
    KW_NOT = 274,
    KW_OF = 275,
    KW_OR = 276,
    KW_PACKED = 277,
    KW_PROCEDURE = 278,
    KW_PROGRAM = 279,
    KW_RECORD = 280,
    KW_REPEAT = 281,
    KW_SET = 282,
    KW_THEN = 283,
    KW_TO = 284,
    KW_TYPE = 285,
    KW_UNTIL = 286,
    KW_VAR = 287,
    KW_WHILE = 288,
    KW_WITH = 289,
    SYS_FALSE = 290,
    SYS_MAXINT = 291,
    SYS_TRUE = 292,
    SYS_ABS = 293,
    SYS_CHR = 294,
    SYS_ODD = 295,
    SYS_ORD = 296,
    SYS_PRED = 297,
    SYS_SQR = 298,
    SYS_SQRT = 299,
    SYS_SUCC = 300,
    SYS_WRITE = 301,
    SYS_WRITELN = 302,
    SYS_BOOLEAN = 303,
    SYS_CHAR = 304,
    SYS_INTEGER = 305,
    SYS_REAL = 306,
    SYS_STRING = 307,
    SYS_READ = 308,
    OP_LP = 309,
    OP_RP = 310,
    OP_LB = 311,
    OP_RB = 312,
    OP_DOT = 313,
    OP_COMMA = 314,
    OP_COLON = 315,
    OP_PLUS = 316,
    OP_MINUS = 317,
    OP_MUL = 318,
    OP_DIV = 319,
    OP_GE = 320,
    OP_GT = 321,
    OP_LE = 322,
    OP_LT = 323,
    OP_EQUAL = 324,
    OP_UNEQUAL = 325,
    OP_NOT = 326,
    OP_ASSIGN = 327,
    OP_MOD = 328,
    OP_DOTDOT = 329,
    OP_SEMI = 330,
    NAME = 331,
    CONST_REAL = 332,
    CONST_INTEGER = 333,
    CONST_CHAR = 334,
    EMPTY_ROUTINE_PART = 335
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 8 "./src/Parser.yy"

	int integer;
	double real;
	char character;
    char *string;

#line 145 "./src/Parser.hh"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_HH_INCLUDED  */
