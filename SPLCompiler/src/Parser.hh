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
    OP_AND = 326,
    OP_OR = 327,
    OP_NOT = 328,
    OP_ASSIGN = 329,
    OP_MOD = 330,
    OP_DOTDOT = 331,
    OP_SEMI = 332,
    NAME = 333,
    CONST_REAL = 334,
    CONST_INTEGER = 335,
    CONST_CHAR = 336,
    CONST_STRING = 337,
    EMPTY_ROUTINE_PART = 338
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "./src/parser/Parser.yy"

    class ASTNode* node;
    class ASTNode_Name* node_name;
    
    class ASTNode_Const* node_const;
    class ASTNode_ConstDecl* node_const_decl;
    class ASTNode_ConstDeclList* node_const_decl_list;

    class ASTNode_Expr* node_expr;
    class ASTNode_ArgList* node_arg_list;

    class ASTNode_Type* node_type;
    class ASTNode_SimpleType* node_simple_type;
    class ASTNode_ArrayType* node_array_type;
    class ASTNode_RecordType* node_record_type;
    class ASTNode_TypeDecl* node_type_decl;
    class ASTNode_TypeDeclList* node_type_decl_list;
    class ASTNode_FieldDecl* node_field_decl;
    class ASTNode_FieldDeclList* node_field_decl_list;
    class ASTNode_NameList* node_name_list;

    class ASTNode_RoutinePart* node_routine_part;
    class ASTNode_FunctionDecl* node_function_decl;
    class ASTNode_FunctionHead* node_function_head;
    class ASTNode_ProcedureDecl* node_procedure_decl;
    class ASTNode_ProcedureHead* node_procedure_head;
    
    class ASTNode_VarDecl* node_var_decl;
    class ASTNode_VarDeclList* node_var_decl_list;

    class ASTNode_ParaDeclList* node_para_decl_list;
    class ASTNode_ParaTypeList* node_para_type_list;
    class ASTNode_VarParaList* node_var_para_list;
    class ASTNode_ValParaList* node_val_para_list;

    class ASTNode_Stmt* node_stmt;
    class ASTNode_StmtList* node_stmt_list;
    class ASTNode_StmtAssign* node_stmt_assign;
    class ASTNode_StmtProc* node_stmt_proc;
    class ASTNode_StmtCompound* node_stmt_compound;
    class ASTNode_StmtIf* node_stmt_if;
    class ASTNode_StmtRepeat* node_stmt_repeat;
    class ASTNode_StmtWhile* node_stmt_while;
    class ASTNode_StmtFor* node_stmt_for;
    class ASTNode_StmtCase* node_stmt_case;
    class ASTNode_StmtGoto* node_stmt_goto;
    class ASTNode_CaseExpr* node_case_expr;
    class ASTNode_CaseExprList* node_case_expr_list;

    class ASTNode_Program* node_program;
    class ASTNode_Routine* node_routine;
    class ASTNode_SubRoutine* node_sub_routine;
    class ASTNode_RoutineHead* node_routine_head;

#line 196 "./src/Parser.hh"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_HH_INCLUDED  */
