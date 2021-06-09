/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./src/parser/Parser.yy"

    #include <iostream>
    #include <limits.h>
    #include "ast/ast.hh"
    #include "irgen/generator.hh"
    extern int yylex(void);
    void yyerror(const char* s);

#line 79 "./src/Parser.cc"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 270 "./src/Parser.cc"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_HH_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   354

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  142
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  270

#define YYUNDEFTOK  2
#define YYMAXUTOK   338


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   231,   231,   238,   247,   250,   253,   259,   262,   265,
     268,   271,   274,   277,   280,   286,   289,   292,   298,   301,
     304,   307,   310,   317,   323,   329,   335,   339,   342,   348,
     352,   359,   365,   368,   371,   374,   377,   383,   386,   392,
     396,   403,   409,   412,   415,   421,   424,   427,   430,   433,
     439,   445,   451,   455,   462,   468,   472,   479,   482,   488,
     492,   499,   505,   509,   513,   517,   521,   527,   533,   539,
     545,   551,   554,   560,   564,   571,   574,   580,   586,   592,
     598,   604,   608,   614,   618,   624,   627,   630,   633,   636,
     639,   642,   645,   648,   654,   657,   660,   666,   669,   675,
     681,   684,   690,   696,   702,   708,   711,   717,   723,   727,
     734,   737,   740,   746,   752,   755,   758,   761,   764,   767,
     770,   776,   779,   782,   785,   791,   794,   797,   800,   803,
     809,   812,   815,   818,   821,   824,   827,   830,   833,   839,
     842,   848,   852
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_AND", "KW_ARRAY", "KW_BEGIN",
  "KW_CASE", "KW_CONST", "KW_DIV", "KW_DO", "KW_DOWNTO", "KW_ELSE",
  "KW_END", "KW_FOR", "KW_FUNCTION", "KW_GOTO", "KW_IF", "KW_IN", "KW_MOD",
  "KW_NOT", "KW_OF", "KW_OR", "KW_PACKED", "KW_PROCEDURE", "KW_PROGRAM",
  "KW_RECORD", "KW_REPEAT", "KW_SET", "KW_THEN", "KW_TO", "KW_TYPE",
  "KW_UNTIL", "KW_VAR", "KW_WHILE", "KW_WITH", "SYS_FALSE", "SYS_MAXINT",
  "SYS_TRUE", "SYS_ABS", "SYS_CHR", "SYS_ODD", "SYS_ORD", "SYS_PRED",
  "SYS_SQR", "SYS_SQRT", "SYS_SUCC", "SYS_WRITE", "SYS_WRITELN",
  "SYS_BOOLEAN", "SYS_CHAR", "SYS_INTEGER", "SYS_REAL", "SYS_STRING",
  "SYS_READ", "OP_LP", "OP_RP", "OP_LB", "OP_RB", "OP_DOT", "OP_COMMA",
  "OP_COLON", "OP_PLUS", "OP_MINUS", "OP_MUL", "OP_DIV", "OP_GE", "OP_GT",
  "OP_LE", "OP_LT", "OP_EQUAL", "OP_UNEQUAL", "OP_AND", "OP_OR", "OP_NOT",
  "OP_ASSIGN", "OP_MOD", "OP_DOTDOT", "OP_SEMI", "NAME", "CONST_REAL",
  "CONST_INTEGER", "CONST_CHAR", "CONST_STRING", "EMPTY_ROUTINE_PART",
  "$accept", "program", "program_head", "sys_con", "sys_funct", "sys_proc",
  "sys_type", "routine", "sub_routine", "routine_head", "label_part",
  "const_part", "const_decl_list", "const_decl", "const_value",
  "type_part", "type_decl_list", "type_decl", "type", "simple_type",
  "array_type", "record_type", "field_decl_list", "field_decl",
  "name_list", "var_part", "var_decl_list", "var_decl", "routine_part",
  "function_decl", "function_head", "procedure_decl", "procedure_head",
  "parameters", "para_decl_list", "para_type_list", "var_para_list",
  "val_para_list", "routine_body", "compound_stmt", "stmt_list", "stmt",
  "non_label_stmt", "assign_stmt", "proc_stmt", "if_stmt", "else_clause",
  "repeat_stmt", "while_stmt", "for_stmt", "direction", "case_stmt",
  "case_expr_list", "case_expr", "goto_stmt", "expression", "expr", "term",
  "factor", "args_list", "non_empty_args_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338
};
# endif

#define YYPACT_NINF (-184)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -3,   -53,    27,  -184,   -49,  -184,     0,    58,    69,  -184,
    -184,  -184,  -184,  -184,    29,    75,    88,    41,    29,  -184,
      34,    81,   230,  -184,    37,    51,   230,  -184,   230,  -184,
    -184,  -184,   -34,    77,    85,  -184,    68,  -184,  -184,  -184,
    -184,  -184,  -184,  -184,  -184,  -184,   171,  -184,    84,    34,
    -184,    66,    33,  -184,  -184,  -184,  -184,  -184,  -184,  -184,
    -184,  -184,  -184,  -184,   230,   230,   230,    82,  -184,  -184,
    -184,  -184,  -184,   104,  -184,   178,    57,    53,  -184,    86,
    -184,   221,   117,   160,   230,   230,    97,   230,   146,   230,
    -184,    99,     1,  -184,  -184,    38,    66,  -184,   100,   102,
      33,  -184,   105,  -184,   106,   -36,  -184,  -184,   230,   230,
     107,   230,   154,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   141,   230,   141,
     269,   122,   127,   248,   126,   269,  -184,   147,  -184,   153,
      66,  -184,  -184,  -184,  -184,  -184,    66,   134,  -184,   137,
     138,  -184,  -184,  -184,   136,     1,  -184,   162,   162,  -184,
    -184,  -184,  -184,  -184,   163,   263,  -184,   165,   141,   195,
     196,     6,  -184,    57,    57,    57,    57,    57,    57,    53,
      53,    53,  -184,  -184,  -184,  -184,   194,   211,   269,  -184,
    -184,   230,   157,   230,  -184,   245,    -1,  -184,    67,     9,
     176,   171,  -184,  -184,   180,   -16,   198,  -184,   199,    58,
     200,  -184,  -184,  -184,   201,   141,   141,  -184,  -184,  -184,
    -184,   230,   141,  -184,   269,   230,   269,   222,  -184,  -184,
       1,  -184,  -184,  -184,  -184,    66,  -184,   224,   -32,  -184,
     225,   238,   245,  -184,  -184,  -184,  -184,   223,   229,   172,
    -184,   269,   281,   242,   224,  -184,   -17,   245,   245,  -184,
    -184,  -184,   141,     1,  -184,  -184,  -184,  -184,  -184,  -184
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    26,     0,     1,     0,     0,    28,     3,
       2,    82,    23,    79,     0,    38,     0,     0,    27,    30,
       0,    58,     0,    80,     0,     0,     0,    82,     0,    15,
      16,    17,     0,     0,     0,    87,     0,    84,    85,    86,
      88,    89,    90,    91,    92,    93,     0,    29,     0,    37,
      40,     0,    66,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,   130,    33,    32,
      34,    35,    36,     0,   133,     0,   120,   124,   129,     0,
     113,     0,     0,     0,   140,     0,     0,     0,     0,   140,
      81,     0,     0,    39,    56,     0,    57,    60,     0,     0,
      25,    64,     0,    65,     0,     0,   136,   135,   140,     0,
       0,   140,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     142,     0,   139,     0,     0,    94,    83,     0,    31,     0,
       0,    18,    19,    20,    21,    22,     0,    46,    45,     0,
       0,    42,    43,    44,     0,     0,    59,     0,     0,    62,
      63,    26,    26,   134,     0,     0,   138,     0,     0,     0,
       0,     0,   109,   114,   115,   116,   117,   118,   119,   121,
     122,   123,   125,   126,   128,   127,     0,   101,   102,   103,
      97,     0,     0,     0,    98,     0,     0,    53,     0,     0,
       0,     0,    41,    55,     0,     0,     0,    70,     0,     0,
       0,   131,   137,   132,     0,     0,     0,   107,   108,   106,
     105,     0,     0,    99,   141,     0,    96,     0,    51,    52,
       0,    47,    49,    48,    61,     0,    72,    78,     0,    74,
       0,     0,     0,    67,    24,    69,   112,     0,     0,     0,
     100,    95,     0,     0,    77,    71,     0,     0,     0,    68,
     111,   110,     0,     0,    54,    73,    75,    76,   104,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,   140,   301,
    -184,  -184,  -184,   289,   -46,  -184,  -184,   272,  -152,  -183,
    -184,  -184,  -184,   150,  -136,  -184,  -184,   226,  -184,   247,
    -184,   249,  -184,   190,  -184,    94,  -184,  -184,   142,    -6,
     325,  -120,   265,  -184,  -184,  -184,  -184,  -184,  -184,  -184,
    -184,  -184,  -184,   183,  -184,   -20,   227,   -29,   -52,   -54,
    -184
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    72,    73,    34,   148,     6,   208,   209,
       8,    15,    18,    19,    74,    21,    49,    50,   150,   151,
     152,   153,   196,   197,    95,    52,    96,    97,   100,   101,
     102,   103,   104,   206,   238,   239,   240,   241,    12,    35,
      16,    36,    37,    38,    39,    40,   223,    41,    42,    43,
     221,    44,   171,   172,    45,   130,    76,    77,    78,   131,
     132
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      91,    13,    75,   204,   198,   139,    81,   187,    83,   189,
     199,   228,   227,   106,   107,   235,   235,   168,   217,   163,
      84,     1,    85,   255,    86,     4,   140,     5,     9,   113,
     114,   115,   116,   117,   118,   137,    53,    54,    55,   236,
      87,    53,    54,    55,   105,   256,   149,    98,   214,   141,
     142,   143,   144,   145,   164,   146,    99,   167,    10,   259,
     198,    94,    94,    11,   231,   133,   170,   135,   154,   237,
     182,   183,   184,   185,   266,   267,    14,    94,   253,   147,
      68,    69,    70,    71,   169,    68,    69,    70,    71,   165,
     179,   180,   181,    11,    22,   247,   248,   154,   155,   254,
      23,    24,   250,    25,    26,    20,   186,    17,   188,   149,
      46,   269,    48,    51,    27,    79,   122,   123,   119,   120,
     237,    28,    11,    22,   124,   170,   154,   230,   125,   121,
      24,    80,    25,    26,    29,    30,   108,    88,   109,    89,
     110,    31,   268,    27,    94,    90,    11,    22,   128,   149,
      28,    11,    22,    92,    24,   233,    25,    26,   111,    24,
     126,    25,    26,    29,    30,   168,    32,    27,    33,   129,
      31,   224,    27,   226,    28,   134,   138,   190,   157,    28,
     158,   262,   161,   162,   149,   166,   191,    29,    30,    53,
      54,    55,    29,    30,    31,    32,   149,    33,   112,    31,
     193,   249,   194,    13,   219,   251,    53,    54,    55,   195,
     200,   149,   149,   201,   203,   202,   205,   149,   211,    32,
     213,    33,   222,   220,    32,   113,   114,   115,   116,   117,
     118,   225,   169,    68,    69,    70,    71,   113,   114,   115,
     116,   117,   118,   113,   114,   115,   116,   117,   118,   127,
      68,    69,    70,    71,   232,   215,   216,   234,   242,   113,
     114,   115,   116,   117,   118,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,   243,   245,   246,   252,
      53,    54,    55,   154,    64,   257,   113,   114,   115,   116,
     117,   118,    65,   141,   142,   143,   144,   145,   258,   146,
     260,   263,   210,    66,     7,   192,   261,    47,    67,    68,
      69,    70,    71,   113,   114,   115,   116,   117,   118,   264,
     212,    93,   156,   147,    68,    69,    70,    71,   113,   114,
     115,   116,   117,   118,   113,   114,   115,   116,   117,   118,
     173,   174,   175,   176,   177,   178,   229,   159,   207,   160,
     265,   244,    82,   136,   218
};

static const yytype_int16 yycheck[] =
{
      46,     7,    22,   155,   140,     4,    26,   127,    28,   129,
     146,    12,   195,    65,    66,    32,    32,    11,    12,    55,
      54,    24,    56,    55,    58,    78,    25,     0,    77,    65,
      66,    67,    68,    69,    70,    89,    35,    36,    37,    55,
      74,    35,    36,    37,    64,    77,    92,    14,   168,    48,
      49,    50,    51,    52,   108,    54,    23,   111,    58,   242,
     196,    78,    78,     5,    55,    85,   112,    87,    59,   205,
     122,   123,   124,   125,   257,   258,     7,    78,   230,    78,
      79,    80,    81,    82,    78,    79,    80,    81,    82,   109,
     119,   120,   121,     5,     6,   215,   216,    59,    60,   235,
      12,    13,   222,    15,    16,    30,   126,    78,   128,   155,
      69,   263,    78,    32,    26,    78,    63,    64,    61,    62,
     256,    33,     5,     6,    71,   171,    59,    60,    75,    72,
      13,    80,    15,    16,    46,    47,    54,    60,    56,    54,
      58,    53,   262,    26,    78,    77,     5,     6,    31,   195,
      33,     5,     6,    69,    13,   201,    15,    16,    54,    13,
      74,    15,    16,    46,    47,    11,    78,    26,    80,     9,
      53,   191,    26,   193,    33,    78,    77,    55,    78,    33,
      78,     9,    77,    77,   230,    78,    59,    46,    47,    35,
      36,    37,    46,    47,    53,    78,   242,    80,    20,    53,
      74,   221,    55,   209,    10,   225,    35,    36,    37,    56,
      76,   257,   258,    76,    78,    77,    54,   263,    55,    78,
      55,    80,    11,    29,    78,    65,    66,    67,    68,    69,
      70,    74,    78,    79,    80,    81,    82,    65,    66,    67,
      68,    69,    70,    65,    66,    67,    68,    69,    70,    28,
      79,    80,    81,    82,    78,    60,    60,    77,    60,    65,
      66,    67,    68,    69,    70,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    77,    77,    77,    57,
      35,    36,    37,    59,    54,    60,    65,    66,    67,    68,
      69,    70,    62,    48,    49,    50,    51,    52,    60,    54,
      77,    20,   162,    73,     3,    57,    77,    18,    78,    79,
      80,    81,    82,    65,    66,    67,    68,    69,    70,    77,
      57,    49,    96,    78,    79,    80,    81,    82,    65,    66,
      67,    68,    69,    70,    65,    66,    67,    68,    69,    70,
     113,   114,   115,   116,   117,   118,   196,   100,   158,   100,
     256,   209,    27,    88,   171
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    85,    86,    78,     0,    91,    93,    94,    77,
      58,     5,   122,   123,     7,    95,   124,    78,    96,    97,
      30,    99,     6,    12,    13,    15,    16,    26,    33,    46,
      47,    53,    78,    80,    89,   123,   125,   126,   127,   128,
     129,   131,   132,   133,   135,   138,    69,    97,    78,   100,
     101,    32,   109,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    54,    62,    73,    78,    79,    80,
      81,    82,    87,    88,    98,   139,   140,   141,   142,    78,
      80,   139,   124,   139,    54,    56,    58,    74,    60,    54,
      77,    98,    69,   101,    78,   108,   110,   111,    14,    23,
     112,   113,   114,   115,   116,   139,   142,   142,    54,    56,
      58,    54,    20,    65,    66,    67,    68,    69,    70,    61,
      62,    72,    63,    64,    71,    75,    74,    28,    31,     9,
     139,   143,   144,   139,    78,   139,   126,   143,    77,     4,
      25,    48,    49,    50,    51,    52,    54,    78,    90,    98,
     102,   103,   104,   105,    59,    60,   111,    78,    78,   113,
     115,    77,    77,    55,   143,   139,    78,   143,    11,    78,
      98,   136,   137,   140,   140,   140,   140,   140,   140,   141,
     141,   141,   142,   142,   142,   142,   139,   125,   139,   125,
      55,    59,    57,    74,    55,    56,   106,   107,   108,   108,
      76,    76,    77,    78,   102,    54,   117,   117,    92,    93,
      92,    55,    57,    55,   125,    60,    60,    12,   137,    10,
      29,   134,    11,   130,   139,    74,   139,   103,    12,   107,
      60,    55,    78,    98,    77,    32,    55,   108,   118,   119,
     120,   121,    60,    77,   122,    77,    77,   125,   125,   139,
     125,   139,    57,   102,   108,    55,    77,    60,    60,   103,
      77,    77,     9,    20,    77,   119,   103,   103,   125,   102
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    86,    87,    87,    87,    88,    88,    88,
      88,    88,    88,    88,    88,    89,    89,    89,    90,    90,
      90,    90,    90,    91,    92,    93,    94,    95,    95,    96,
      96,    97,    98,    98,    98,    98,    98,    99,    99,   100,
     100,   101,   102,   102,   102,   103,   103,   103,   103,   103,
     104,   105,   106,   106,   107,   108,   108,   109,   109,   110,
     110,   111,   112,   112,   112,   112,   112,   113,   114,   115,
     116,   117,   117,   118,   118,   119,   119,   120,   121,   122,
     123,   124,   124,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   127,   127,   127,   128,   128,   129,
     130,   130,   131,   132,   133,   134,   134,   135,   136,   136,
     137,   137,   137,   138,   139,   139,   139,   139,   139,   139,
     139,   140,   140,   140,   140,   141,   141,   141,   141,   141,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   143,
     143,   144,   144
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     5,     0,     2,     0,     2,
       1,     4,     1,     1,     1,     1,     1,     2,     0,     2,
       1,     4,     1,     1,     1,     1,     1,     3,     3,     3,
       6,     3,     2,     1,     4,     3,     1,     2,     0,     2,
       1,     4,     2,     2,     1,     1,     0,     4,     5,     4,
       3,     3,     2,     3,     1,     3,     3,     2,     1,     1,
       3,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     6,     5,     4,     4,     5,
       2,     0,     4,     4,     8,     1,     1,     5,     2,     1,
       4,     4,     3,     2,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     1,     3,     3,     3,     3,     1,
       1,     4,     4,     1,     3,     2,     2,     4,     3,     1,
       0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

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
#line 231 "./src/parser/Parser.yy"
                                {
        (yyval.node_program) = new ASTNode_Program((yyvsp[-2].node_name),(yyvsp[-1].node_routine));
        ASTHandler::setASTHead((yyval.node_program));
    }
#line 1678 "./src/Parser.cc"
    break;

  case 3:
#line 238 "./src/parser/Parser.yy"
                            {
        (yyval.node_name) = (yyvsp[-1].node_name);
    }
#line 1686 "./src/Parser.cc"
    break;

  case 4:
#line 247 "./src/parser/Parser.yy"
              {
        (yyval.node_const) = new ASTNode_ConstBoolean(false);
    }
#line 1694 "./src/Parser.cc"
    break;

  case 5:
#line 250 "./src/parser/Parser.yy"
                {
        (yyval.node_const) = new ASTNode_ConstInteger(INT_MAX);
    }
#line 1702 "./src/Parser.cc"
    break;

  case 6:
#line 253 "./src/parser/Parser.yy"
              {
        (yyval.node_const) = new ASTNode_ConstBoolean(true);
    }
#line 1710 "./src/Parser.cc"
    break;

  case 7:
#line 259 "./src/parser/Parser.yy"
            {
        (yyval.node_name) = new ASTNode_Name("abs");
    }
#line 1718 "./src/Parser.cc"
    break;

  case 8:
#line 262 "./src/parser/Parser.yy"
             {
        (yyval.node_name) = new ASTNode_Name("chr");
    }
#line 1726 "./src/Parser.cc"
    break;

  case 9:
#line 265 "./src/parser/Parser.yy"
             {
        (yyval.node_name) = new ASTNode_Name("odd");
    }
#line 1734 "./src/Parser.cc"
    break;

  case 10:
#line 268 "./src/parser/Parser.yy"
             {
        (yyval.node_name) = new ASTNode_Name("ord");
    }
#line 1742 "./src/Parser.cc"
    break;

  case 11:
#line 271 "./src/parser/Parser.yy"
              {
        (yyval.node_name) = new ASTNode_Name("pred");
    }
#line 1750 "./src/Parser.cc"
    break;

  case 12:
#line 274 "./src/parser/Parser.yy"
             {
        (yyval.node_name) = new ASTNode_Name("sqr");
    }
#line 1758 "./src/Parser.cc"
    break;

  case 13:
#line 277 "./src/parser/Parser.yy"
              {
        (yyval.node_name) = new ASTNode_Name("sqrt");
    }
#line 1766 "./src/Parser.cc"
    break;

  case 14:
#line 280 "./src/parser/Parser.yy"
              {
        (yyval.node_name) = new ASTNode_Name("succ");
    }
#line 1774 "./src/Parser.cc"
    break;

  case 15:
#line 286 "./src/parser/Parser.yy"
              {
        (yyval.node_name) = new ASTNode_Name("write");
    }
#line 1782 "./src/Parser.cc"
    break;

  case 16:
#line 289 "./src/parser/Parser.yy"
                 {
        (yyval.node_name) = new ASTNode_Name("writeln");
    }
#line 1790 "./src/Parser.cc"
    break;

  case 17:
#line 292 "./src/parser/Parser.yy"
              {
        (yyval.node_name) = new ASTNode_Name("read");
    }
#line 1798 "./src/Parser.cc"
    break;

  case 18:
#line 298 "./src/parser/Parser.yy"
                {
        (yyval.node_simple_type) = new ASTNode_SimpleTypePlain("boolean");
    }
#line 1806 "./src/Parser.cc"
    break;

  case 19:
#line 301 "./src/parser/Parser.yy"
              {
        (yyval.node_simple_type) = new ASTNode_SimpleTypePlain("char");
    }
#line 1814 "./src/Parser.cc"
    break;

  case 20:
#line 304 "./src/parser/Parser.yy"
                 {
        (yyval.node_simple_type) = new ASTNode_SimpleTypePlain("integer");
    }
#line 1822 "./src/Parser.cc"
    break;

  case 21:
#line 307 "./src/parser/Parser.yy"
              {
        (yyval.node_simple_type) = new ASTNode_SimpleTypePlain("real");
    }
#line 1830 "./src/Parser.cc"
    break;

  case 22:
#line 310 "./src/parser/Parser.yy"
                {
        (yyval.node_simple_type) = new ASTNode_SimpleTypePlain("string");
    }
#line 1838 "./src/Parser.cc"
    break;

  case 23:
#line 317 "./src/parser/Parser.yy"
                              {
        (yyval.node_routine) = new ASTNode_Routine((yyvsp[-1].node_routine_head),(yyvsp[0].node_stmt_compound));
    }
#line 1846 "./src/Parser.cc"
    break;

  case 24:
#line 323 "./src/parser/Parser.yy"
                              {
        (yyval.node_sub_routine) = new ASTNode_SubRoutine((yyvsp[-1].node_routine_head),(yyvsp[0].node_stmt_compound));
    }
#line 1854 "./src/Parser.cc"
    break;

  case 25:
#line 329 "./src/parser/Parser.yy"
                                                          {
        (yyval.node_routine_head) = new ASTNode_RoutineHead((yyvsp[-3].node_const_decl_list),(yyvsp[-2].node_type_decl_list),(yyvsp[-1].node_var_decl_list),(yyvsp[0].node_routine_part));
    }
#line 1862 "./src/Parser.cc"
    break;

  case 27:
#line 339 "./src/parser/Parser.yy"
                             {
        (yyval.node_const_decl_list) = (yyvsp[0].node_const_decl_list);
    }
#line 1870 "./src/Parser.cc"
    break;

  case 28:
#line 342 "./src/parser/Parser.yy"
             {
        (yyval.node_const_decl_list) = nullptr;
    }
#line 1878 "./src/Parser.cc"
    break;

  case 29:
#line 348 "./src/parser/Parser.yy"
                               {
        (yyval.node_const_decl_list) = (yyvsp[-1].node_const_decl_list);
        (yyval.node_const_decl_list)->append((yyvsp[0].node_const_decl));
    }
#line 1887 "./src/Parser.cc"
    break;

  case 30:
#line 352 "./src/parser/Parser.yy"
                 {
        (yyval.node_const_decl_list) = new ASTNode_ConstDeclList();
        (yyval.node_const_decl_list)->append((yyvsp[0].node_const_decl));
    }
#line 1896 "./src/Parser.cc"
    break;

  case 31:
#line 359 "./src/parser/Parser.yy"
                                      {
        (yyval.node_const_decl) = new ASTNode_ConstDecl((yyvsp[-3].node_name),(yyvsp[-1].node_const));
    }
#line 1904 "./src/Parser.cc"
    break;

  case 32:
#line 365 "./src/parser/Parser.yy"
                  {
        (yyval.node_const) = (yyvsp[0].node_const);
    }
#line 1912 "./src/Parser.cc"
    break;

  case 33:
#line 368 "./src/parser/Parser.yy"
                 {
        (yyval.node_const) = (yyvsp[0].node_const);
    }
#line 1920 "./src/Parser.cc"
    break;

  case 34:
#line 371 "./src/parser/Parser.yy"
                 {
        (yyval.node_const) = (yyvsp[0].node_const);
    }
#line 1928 "./src/Parser.cc"
    break;

  case 35:
#line 374 "./src/parser/Parser.yy"
                   {
        (yyval.node_const) = (yyvsp[0].node_const);
    }
#line 1936 "./src/Parser.cc"
    break;

  case 36:
#line 377 "./src/parser/Parser.yy"
              {
        (yyval.node_const) = (yyvsp[0].node_const);
    }
#line 1944 "./src/Parser.cc"
    break;

  case 37:
#line 383 "./src/parser/Parser.yy"
                           {
        (yyval.node_type_decl_list) = (yyvsp[0].node_type_decl_list);
    }
#line 1952 "./src/Parser.cc"
    break;

  case 38:
#line 386 "./src/parser/Parser.yy"
             {
        (yyval.node_type_decl_list) = nullptr;
    }
#line 1960 "./src/Parser.cc"
    break;

  case 39:
#line 392 "./src/parser/Parser.yy"
                             {
        (yyval.node_type_decl_list) = (yyvsp[-1].node_type_decl_list);
        (yyval.node_type_decl_list)->append((yyvsp[0].node_type_decl));
    }
#line 1969 "./src/Parser.cc"
    break;

  case 40:
#line 396 "./src/parser/Parser.yy"
                {
        (yyval.node_type_decl_list) = new ASTNode_TypeDeclList();
        (yyval.node_type_decl_list)->append((yyvsp[0].node_type_decl));
    }
#line 1978 "./src/Parser.cc"
    break;

  case 41:
#line 403 "./src/parser/Parser.yy"
                               {
        (yyval.node_type_decl) = new ASTNode_TypeDecl((yyvsp[-3].node_name),(yyvsp[-1].node_type));
    }
#line 1986 "./src/Parser.cc"
    break;

  case 42:
#line 409 "./src/parser/Parser.yy"
                {
        (yyval.node_type) = (yyvsp[0].node_simple_type);
    }
#line 1994 "./src/Parser.cc"
    break;

  case 43:
#line 412 "./src/parser/Parser.yy"
                 {
        (yyval.node_type) = (yyvsp[0].node_array_type);
    }
#line 2002 "./src/Parser.cc"
    break;

  case 44:
#line 415 "./src/parser/Parser.yy"
                  {
        (yyval.node_type) = (yyvsp[0].node_record_type);
    }
#line 2010 "./src/Parser.cc"
    break;

  case 45:
#line 421 "./src/parser/Parser.yy"
             {
        (yyval.node_simple_type) = (yyvsp[0].node_simple_type);
    }
#line 2018 "./src/Parser.cc"
    break;

  case 46:
#line 424 "./src/parser/Parser.yy"
           {
        (yyval.node_simple_type) = new ASTNode_SimpleTypePlain((yyvsp[0].node_name));
    }
#line 2026 "./src/Parser.cc"
    break;

  case 47:
#line 427 "./src/parser/Parser.yy"
                            {
        (yyval.node_simple_type) = new ASTNode_SimpleTypeEnumerate((yyvsp[-1].node_name_list));
    }
#line 2034 "./src/Parser.cc"
    break;

  case 48:
#line 430 "./src/parser/Parser.yy"
                                        {
        (yyval.node_simple_type) = new ASTNode_SimpleTypeSubRange((yyvsp[-2].node_const),(yyvsp[0].node_const));
    }
#line 2042 "./src/Parser.cc"
    break;

  case 49:
#line 433 "./src/parser/Parser.yy"
                          {
        (yyval.node_simple_type) = new ASTNode_SimpleTypeSubRange((yyvsp[-2].node_name),(yyvsp[0].node_name));
    }
#line 2050 "./src/Parser.cc"
    break;

  case 50:
#line 439 "./src/parser/Parser.yy"
                                                {
        (yyval.node_array_type) = new ASTNode_ArrayType((yyvsp[-3].node_simple_type),(yyvsp[0].node_type));
    }
#line 2058 "./src/Parser.cc"
    break;

  case 51:
#line 445 "./src/parser/Parser.yy"
                                     {
        (yyval.node_record_type) = new ASTNode_RecordType((yyvsp[-1].node_field_decl_list));
    }
#line 2066 "./src/Parser.cc"
    break;

  case 52:
#line 451 "./src/parser/Parser.yy"
                               {
        (yyval.node_field_decl_list) = (yyvsp[-1].node_field_decl_list);
        (yyval.node_field_decl_list)->append((yyvsp[0].node_field_decl));
    }
#line 2075 "./src/Parser.cc"
    break;

  case 53:
#line 455 "./src/parser/Parser.yy"
                 {
        (yyval.node_field_decl_list) = new ASTNode_FieldDeclList();
        (yyval.node_field_decl_list)->append((yyvsp[0].node_field_decl));
    }
#line 2084 "./src/Parser.cc"
    break;

  case 54:
#line 462 "./src/parser/Parser.yy"
                                    {
        (yyval.node_field_decl) = new ASTNode_FieldDecl((yyvsp[-3].node_name_list),(yyvsp[-1].node_type));
    }
#line 2092 "./src/Parser.cc"
    break;

  case 55:
#line 468 "./src/parser/Parser.yy"
                            {
        (yyval.node_name_list) = (yyvsp[-2].node_name_list);
        (yyval.node_name_list)->insert((yyvsp[0].node_name));
    }
#line 2101 "./src/Parser.cc"
    break;

  case 56:
#line 472 "./src/parser/Parser.yy"
           {
        (yyval.node_name_list) = new ASTNode_NameList();
        (yyval.node_name_list)->insert((yyvsp[0].node_name));
    }
#line 2110 "./src/Parser.cc"
    break;

  case 57:
#line 479 "./src/parser/Parser.yy"
                         {
        (yyval.node_var_decl_list) = (yyvsp[0].node_var_decl_list);
    }
#line 2118 "./src/Parser.cc"
    break;

  case 58:
#line 482 "./src/parser/Parser.yy"
             {
        (yyval.node_var_decl_list) = nullptr;
    }
#line 2126 "./src/Parser.cc"
    break;

  case 59:
#line 488 "./src/parser/Parser.yy"
                           {
        (yyval.node_var_decl_list) = (yyvsp[-1].node_var_decl_list);
        (yyval.node_var_decl_list)->append((yyvsp[0].node_var_decl));
    }
#line 2135 "./src/Parser.cc"
    break;

  case 60:
#line 492 "./src/parser/Parser.yy"
               {
        (yyval.node_var_decl_list) = new ASTNode_VarDeclList();
        (yyval.node_var_decl_list)->append((yyvsp[0].node_var_decl));
    }
#line 2144 "./src/Parser.cc"
    break;

  case 61:
#line 499 "./src/parser/Parser.yy"
                                    {
        (yyval.node_var_decl) = new ASTNode_VarDecl((yyvsp[-3].node_name_list),(yyvsp[-1].node_type));
    }
#line 2152 "./src/Parser.cc"
    break;

  case 62:
#line 505 "./src/parser/Parser.yy"
                               {
        (yyval.node_routine_part) = (yyvsp[-1].node_routine_part);
        (yyval.node_routine_part)->append((yyvsp[0].node_function_decl));
    }
#line 2161 "./src/Parser.cc"
    break;

  case 63:
#line 509 "./src/parser/Parser.yy"
                                  {
        (yyval.node_routine_part) = (yyvsp[-1].node_routine_part);
        (yyval.node_routine_part)->append((yyvsp[0].node_procedure_decl));
    }
#line 2170 "./src/Parser.cc"
    break;

  case 64:
#line 513 "./src/parser/Parser.yy"
                    {
        (yyval.node_routine_part) = new ASTNode_RoutinePart();
        (yyval.node_routine_part)->append((yyvsp[0].node_function_decl));
    }
#line 2179 "./src/Parser.cc"
    break;

  case 65:
#line 517 "./src/parser/Parser.yy"
                     {
        (yyval.node_routine_part) = new ASTNode_RoutinePart();
        (yyval.node_routine_part)->append((yyvsp[0].node_procedure_decl));
    }
#line 2188 "./src/Parser.cc"
    break;

  case 66:
#line 521 "./src/parser/Parser.yy"
                                      {
        (yyval.node_routine_part) = nullptr;
    }
#line 2196 "./src/Parser.cc"
    break;

  case 67:
#line 527 "./src/parser/Parser.yy"
                                              {
        (yyval.node_function_decl) = new ASTNode_FunctionDecl((yyvsp[-3].node_function_head),(yyvsp[-1].node_sub_routine));
    }
#line 2204 "./src/Parser.cc"
    break;

  case 68:
#line 533 "./src/parser/Parser.yy"
                                                     {
        (yyval.node_function_head) = new ASTNode_FunctionHead((yyvsp[-3].node_name),(yyvsp[-2].node_para_decl_list),(yyvsp[0].node_simple_type));
    }
#line 2212 "./src/Parser.cc"
    break;

  case 69:
#line 539 "./src/parser/Parser.yy"
                                               {
        (yyval.node_procedure_decl) = new ASTNode_ProcedureDecl((yyvsp[-3].node_procedure_head),(yyvsp[-1].node_sub_routine));
    }
#line 2220 "./src/Parser.cc"
    break;

  case 70:
#line 545 "./src/parser/Parser.yy"
                                 {
        (yyval.node_procedure_head) = new ASTNode_ProcedureHead((yyvsp[-1].node_name),(yyvsp[0].node_para_decl_list));
    }
#line 2228 "./src/Parser.cc"
    break;

  case 71:
#line 551 "./src/parser/Parser.yy"
                               {
        (yyval.node_para_decl_list) = (yyvsp[-1].node_para_decl_list);
    }
#line 2236 "./src/Parser.cc"
    break;

  case 72:
#line 554 "./src/parser/Parser.yy"
                  {
        (yyval.node_para_decl_list) = new ASTNode_ParaDeclList();
    }
#line 2244 "./src/Parser.cc"
    break;

  case 73:
#line 560 "./src/parser/Parser.yy"
                                          {
        (yyval.node_para_decl_list) = (yyvsp[-2].node_para_decl_list);
        (yyval.node_para_decl_list)->append((yyvsp[0].node_para_type_list));
    }
#line 2253 "./src/Parser.cc"
    break;

  case 74:
#line 564 "./src/parser/Parser.yy"
                     {
        (yyval.node_para_decl_list) = new ASTNode_ParaDeclList();
        (yyval.node_para_decl_list)->append((yyvsp[0].node_para_type_list));
    }
#line 2262 "./src/Parser.cc"
    break;

  case 75:
#line 571 "./src/parser/Parser.yy"
                                       {
        (yyval.node_para_type_list) = new ASTNode_ParaTypeList((yyvsp[-2].node_var_para_list),(yyvsp[0].node_simple_type));
    }
#line 2270 "./src/Parser.cc"
    break;

  case 76:
#line 574 "./src/parser/Parser.yy"
                                         {
        (yyval.node_para_type_list) = new ASTNode_ParaTypeList((yyvsp[-2].node_val_para_list),(yyvsp[0].node_simple_type));
        }
#line 2278 "./src/Parser.cc"
    break;

  case 77:
#line 580 "./src/parser/Parser.yy"
                     {
        (yyval.node_var_para_list) = new ASTNode_VarParaList((yyvsp[0].node_name_list));
    }
#line 2286 "./src/Parser.cc"
    break;

  case 78:
#line 586 "./src/parser/Parser.yy"
              {
        (yyval.node_val_para_list) = new ASTNode_ValParaList((yyvsp[0].node_name_list));
    }
#line 2294 "./src/Parser.cc"
    break;

  case 79:
#line 592 "./src/parser/Parser.yy"
                  {
        (yyval.node_stmt_compound) = (yyvsp[0].node_stmt_compound);
    }
#line 2302 "./src/Parser.cc"
    break;

  case 80:
#line 598 "./src/parser/Parser.yy"
                              {
        (yyval.node_stmt_compound) = new ASTNode_StmtCompound((yyvsp[-1].node_stmt_list));
    }
#line 2310 "./src/Parser.cc"
    break;

  case 81:
#line 604 "./src/parser/Parser.yy"
                           {
        (yyval.node_stmt_list) = (yyvsp[-2].node_stmt_list);
        (yyval.node_stmt_list)->append((yyvsp[-1].node_stmt));
    }
#line 2319 "./src/Parser.cc"
    break;

  case 82:
#line 608 "./src/parser/Parser.yy"
             {
        (yyval.node_stmt_list) = new ASTNode_StmtList();
    }
#line 2327 "./src/Parser.cc"
    break;

  case 83:
#line 614 "./src/parser/Parser.yy"
                                          {
        (yyval.node_stmt) = (yyvsp[0].node_stmt);
        (yyval.node_stmt)->setLabel((yyvsp[-2].node_const));
    }
#line 2336 "./src/Parser.cc"
    break;

  case 84:
#line 618 "./src/parser/Parser.yy"
                     {
        (yyval.node_stmt) = (yyvsp[0].node_stmt);
    }
#line 2344 "./src/Parser.cc"
    break;

  case 85:
#line 624 "./src/parser/Parser.yy"
                {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_assign);
    }
#line 2352 "./src/Parser.cc"
    break;

  case 86:
#line 627 "./src/parser/Parser.yy"
                {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_proc);
    }
#line 2360 "./src/Parser.cc"
    break;

  case 87:
#line 630 "./src/parser/Parser.yy"
                    {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_compound);
    }
#line 2368 "./src/Parser.cc"
    break;

  case 88:
#line 633 "./src/parser/Parser.yy"
              {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_if);
    }
#line 2376 "./src/Parser.cc"
    break;

  case 89:
#line 636 "./src/parser/Parser.yy"
                  {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_repeat);
    }
#line 2384 "./src/Parser.cc"
    break;

  case 90:
#line 639 "./src/parser/Parser.yy"
                 {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_while);
    }
#line 2392 "./src/Parser.cc"
    break;

  case 91:
#line 642 "./src/parser/Parser.yy"
               {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_for);
    }
#line 2400 "./src/Parser.cc"
    break;

  case 92:
#line 645 "./src/parser/Parser.yy"
                {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_case);
    }
#line 2408 "./src/Parser.cc"
    break;

  case 93:
#line 648 "./src/parser/Parser.yy"
                {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_goto);
    }
#line 2416 "./src/Parser.cc"
    break;

  case 94:
#line 654 "./src/parser/Parser.yy"
                              {
        (yyval.node_stmt_assign) = new ASTNode_StmtAssignSimpleType((yyvsp[-2].node_name),(yyvsp[0].node_expr));
    }
#line 2424 "./src/Parser.cc"
    break;

  case 95:
#line 657 "./src/parser/Parser.yy"
                                                       {
        (yyval.node_stmt_assign) = new ASTNode_StmtAssignArrayType((yyvsp[-5].node_name),(yyvsp[-3].node_expr),(yyvsp[0].node_expr));
    }
#line 2432 "./src/Parser.cc"
    break;

  case 96:
#line 660 "./src/parser/Parser.yy"
                                            {
        (yyval.node_stmt_assign) = new ASTNode_StmtAssignRecordType((yyvsp[-4].node_name),(yyvsp[-2].node_name),(yyvsp[0].node_expr));
    }
#line 2440 "./src/Parser.cc"
    break;

  case 97:
#line 666 "./src/parser/Parser.yy"
                               {
        (yyval.node_stmt_proc) = new ASTNode_StmtProc((yyvsp[-3].node_name),(yyvsp[-1].node_arg_list));
    }
#line 2448 "./src/Parser.cc"
    break;

  case 98:
#line 669 "./src/parser/Parser.yy"
                                     {
        (yyval.node_stmt_proc) = new ASTNode_StmtSysProc((yyvsp[-3].node_name),(yyvsp[-1].node_arg_list));
    }
#line 2456 "./src/Parser.cc"
    break;

  case 99:
#line 675 "./src/parser/Parser.yy"
                                              {
        (yyval.node_stmt_if) = new ASTNode_StmtIf((yyvsp[-3].node_expr),(yyvsp[-1].node_stmt),(yyvsp[0].node_stmt));
    }
#line 2464 "./src/Parser.cc"
    break;

  case 100:
#line 681 "./src/parser/Parser.yy"
                 {
        (yyval.node_stmt) = (yyvsp[0].node_stmt);
    }
#line 2472 "./src/Parser.cc"
    break;

  case 101:
#line 684 "./src/parser/Parser.yy"
                           {
        (yyval.node_stmt) = nullptr;
    }
#line 2480 "./src/Parser.cc"
    break;

  case 102:
#line 690 "./src/parser/Parser.yy"
                                            {
        (yyval.node_stmt_repeat) = new ASTNode_StmtRepeat((yyvsp[-2].node_stmt_list),(yyvsp[0].node_expr));
    }
#line 2488 "./src/Parser.cc"
    break;

  case 103:
#line 696 "./src/parser/Parser.yy"
                                   {
        (yyval.node_stmt_while) = new ASTNode_StmtWhile((yyvsp[-2].node_expr),(yyvsp[0].node_stmt));
    }
#line 2496 "./src/Parser.cc"
    break;

  case 104:
#line 702 "./src/parser/Parser.yy"
                                                                     {
        (yyval.node_stmt_for) = new ASTNode_StmtFor((yyvsp[-6].node_name),(yyvsp[-3].node_const)->toString() == "true",(yyvsp[-4].node_expr),(yyvsp[-2].node_expr),(yyvsp[0].node_stmt));
    }
#line 2504 "./src/Parser.cc"
    break;

  case 105:
#line 708 "./src/parser/Parser.yy"
          {
        (yyval.node_const) = new ASTNode_ConstBoolean(true);
    }
#line 2512 "./src/Parser.cc"
    break;

  case 106:
#line 711 "./src/parser/Parser.yy"
                {
        (yyval.node_const) = new ASTNode_ConstBoolean(false);
    }
#line 2520 "./src/Parser.cc"
    break;

  case 107:
#line 717 "./src/parser/Parser.yy"
                                                   {
        (yyval.node_stmt_case) = new ASTNode_StmtCase((yyvsp[-3].node_expr),(yyvsp[-1].node_case_expr_list));
    }
#line 2528 "./src/Parser.cc"
    break;

  case 108:
#line 723 "./src/parser/Parser.yy"
                             {
        (yyval.node_case_expr_list) = (yyvsp[-1].node_case_expr_list);
        (yyval.node_case_expr_list)->append((yyvsp[0].node_case_expr));
    }
#line 2537 "./src/Parser.cc"
    break;

  case 109:
#line 727 "./src/parser/Parser.yy"
                {
        (yyval.node_case_expr_list) = new ASTNode_CaseExprList();
        (yyval.node_case_expr_list)->append((yyvsp[0].node_case_expr));
    }
#line 2546 "./src/Parser.cc"
    break;

  case 110:
#line 734 "./src/parser/Parser.yy"
                                      {
        (yyval.node_case_expr) = new ASTNode_CaseExprLiteral((yyvsp[-3].node_const),(yyvsp[-1].node_stmt));
    }
#line 2554 "./src/Parser.cc"
    break;

  case 111:
#line 737 "./src/parser/Parser.yy"
                                 {
        (yyval.node_case_expr) = new ASTNode_CaseExprConstVar((yyvsp[-3].node_name),(yyvsp[-1].node_stmt));
    }
#line 2562 "./src/Parser.cc"
    break;

  case 112:
#line 740 "./src/parser/Parser.yy"
                           {
        (yyval.node_case_expr) = new ASTNode_CaseExprDefault((yyvsp[-1].node_stmt));
    }
#line 2570 "./src/Parser.cc"
    break;

  case 113:
#line 746 "./src/parser/Parser.yy"
                          {
        (yyval.node_stmt_goto) = new ASTNode_StmtGoto((yyvsp[0].node_const));
    }
#line 2578 "./src/Parser.cc"
    break;

  case 114:
#line 752 "./src/parser/Parser.yy"
                          {
        (yyval.node_expr) = new ASTNode_OperatorGE((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2586 "./src/Parser.cc"
    break;

  case 115:
#line 755 "./src/parser/Parser.yy"
                            {
        (yyval.node_expr) = new ASTNode_OperatorGT((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2594 "./src/Parser.cc"
    break;

  case 116:
#line 758 "./src/parser/Parser.yy"
                            {
        (yyval.node_expr) = new ASTNode_OperatorLE((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2602 "./src/Parser.cc"
    break;

  case 117:
#line 761 "./src/parser/Parser.yy"
                            {
        (yyval.node_expr) = new ASTNode_OperatorLT((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2610 "./src/Parser.cc"
    break;

  case 118:
#line 764 "./src/parser/Parser.yy"
                               {
        (yyval.node_expr) = new ASTNode_OperatorEQ((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2618 "./src/Parser.cc"
    break;

  case 119:
#line 767 "./src/parser/Parser.yy"
                                 {
        (yyval.node_expr) = new ASTNode_OperatorNE((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2626 "./src/Parser.cc"
    break;

  case 120:
#line 770 "./src/parser/Parser.yy"
           {
        (yyval.node_expr) = (yyvsp[0].node_expr);
    }
#line 2634 "./src/Parser.cc"
    break;

  case 121:
#line 776 "./src/parser/Parser.yy"
                      {
        (yyval.node_expr) = new ASTNode_OperatorAdd((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2642 "./src/Parser.cc"
    break;

  case 122:
#line 779 "./src/parser/Parser.yy"
                         {
        (yyval.node_expr) = new ASTNode_OperatorSub((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2650 "./src/Parser.cc"
    break;

  case 123:
#line 782 "./src/parser/Parser.yy"
                      {
        (yyval.node_expr) = new ASTNode_OperatorOr((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2658 "./src/Parser.cc"
    break;

  case 124:
#line 785 "./src/parser/Parser.yy"
           {
        (yyval.node_expr) = (yyvsp[0].node_expr);
    }
#line 2666 "./src/Parser.cc"
    break;

  case 125:
#line 791 "./src/parser/Parser.yy"
                       {
        (yyval.node_expr) = new ASTNode_OperatorMul((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2674 "./src/Parser.cc"
    break;

  case 126:
#line 794 "./src/parser/Parser.yy"
                         {
        (yyval.node_expr) = new ASTNode_OperatorDiv((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2682 "./src/Parser.cc"
    break;

  case 127:
#line 797 "./src/parser/Parser.yy"
                         {
        (yyval.node_expr) = new ASTNode_OperatorMod((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2690 "./src/Parser.cc"
    break;

  case 128:
#line 800 "./src/parser/Parser.yy"
                         {
        (yyval.node_expr) = new ASTNode_OperatorAnd((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2698 "./src/Parser.cc"
    break;

  case 129:
#line 803 "./src/parser/Parser.yy"
             {
        (yyval.node_expr) = (yyvsp[0].node_expr);
    }
#line 2706 "./src/Parser.cc"
    break;

  case 130:
#line 809 "./src/parser/Parser.yy"
         {
        (yyval.node_expr) = new ASTNode_OperandVariable((yyvsp[0].node_name));
    }
#line 2714 "./src/Parser.cc"
    break;

  case 131:
#line 812 "./src/parser/Parser.yy"
                                 {
        (yyval.node_expr) = new ASTNode_OperandFunction((yyvsp[-3].node_name),(yyvsp[-1].node_arg_list));
    }
#line 2722 "./src/Parser.cc"
    break;

  case 132:
#line 815 "./src/parser/Parser.yy"
                                      {
        (yyval.node_expr) = new ASTNode_OperandSystemFunction((yyvsp[-3].node_name),(yyvsp[-1].node_arg_list));
    }
#line 2730 "./src/Parser.cc"
    break;

  case 133:
#line 818 "./src/parser/Parser.yy"
                  {
        (yyval.node_expr) = new ASTNode_OperandLiteral((yyvsp[0].node_const));
    }
#line 2738 "./src/Parser.cc"
    break;

  case 134:
#line 821 "./src/parser/Parser.yy"
                             {
        (yyval.node_expr) = (yyvsp[-1].node_expr);
    }
#line 2746 "./src/Parser.cc"
    break;

  case 135:
#line 824 "./src/parser/Parser.yy"
                    {
        (yyval.node_expr) = new ASTNode_OperatorNot((yyvsp[0].node_expr));
    }
#line 2754 "./src/Parser.cc"
    break;

  case 136:
#line 827 "./src/parser/Parser.yy"
                      {
        (yyval.node_expr) = new ASTNode_OperatorMinus((yyvsp[0].node_expr));
    }
#line 2762 "./src/Parser.cc"
    break;

  case 137:
#line 830 "./src/parser/Parser.yy"
                                  {
        (yyval.node_expr) = new ASTNode_OperandArrayElement((yyvsp[-3].node_name),(yyvsp[-1].node_expr));
    }
#line 2770 "./src/Parser.cc"
    break;

  case 138:
#line 833 "./src/parser/Parser.yy"
                       {
        (yyval.node_expr) = new ASTNode_OperandRecordMember((yyvsp[-2].node_name),(yyvsp[0].node_name));
    }
#line 2778 "./src/Parser.cc"
    break;

  case 139:
#line 839 "./src/parser/Parser.yy"
                        {
        (yyval.node_arg_list) = (yyvsp[0].node_arg_list);
    }
#line 2786 "./src/Parser.cc"
    break;

  case 140:
#line 842 "./src/parser/Parser.yy"
             {
        (yyval.node_arg_list) = new ASTNode_ArgList();
    }
#line 2794 "./src/Parser.cc"
    break;

  case 141:
#line 848 "./src/parser/Parser.yy"
                                            {
        (yyval.node_arg_list) = (yyvsp[-2].node_arg_list);
        (yyval.node_arg_list)->append((yyvsp[0].node_expr));
    }
#line 2803 "./src/Parser.cc"
    break;

  case 142:
#line 852 "./src/parser/Parser.yy"
                 {
        (yyval.node_arg_list) = new ASTNode_ArgList();
        (yyval.node_arg_list)->append((yyvsp[0].node_expr));
    }
#line 2812 "./src/Parser.cc"
    break;


#line 2816 "./src/Parser.cc"

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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 858 "./src/parser/Parser.yy"


void yyerror(const char* s)
{
    std::cerr << std::endl << s << std::endl;
    exit(1);
}
