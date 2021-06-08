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
    OP_NOT = 326,
    OP_ASSIGN = 327,
    OP_MOD = 328,
    OP_DOTDOT = 329,
    OP_SEMI = 330,
    NAME = 331,
    CONST_REAL = 332,
    CONST_INTEGER = 333,
    CONST_CHAR = 334,
    CONST_STRING = 335,
    EMPTY_ROUTINE_PART = 336
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

#line 268 "./src/Parser.cc"

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
#define YYLAST   378

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  142
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  269

#define YYUNDEFTOK  2
#define YYMAXUTOK   336


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
      75,    76,    77,    78,    79,    80,    81
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   229,   229,   236,   245,   248,   251,   257,   260,   263,
     266,   269,   272,   275,   278,   284,   287,   290,   296,   299,
     302,   305,   308,   315,   321,   327,   333,   337,   340,   346,
     350,   357,   363,   366,   369,   372,   375,   381,   384,   390,
     394,   401,   407,   410,   413,   419,   422,   425,   428,   431,
     437,   443,   449,   453,   460,   466,   470,   477,   480,   486,
     490,   497,   503,   507,   511,   515,   519,   525,   531,   537,
     543,   549,   552,   558,   562,   569,   572,   578,   584,   590,
     596,   602,   606,   612,   616,   622,   625,   628,   631,   634,
     637,   640,   643,   646,   652,   655,   658,   664,   667,   673,
     679,   682,   688,   694,   700,   706,   709,   715,   721,   725,
     732,   735,   738,   744,   750,   753,   756,   759,   762,   765,
     768,   774,   777,   780,   783,   789,   792,   795,   798,   801,
     807,   810,   813,   816,   819,   822,   825,   828,   831,   837,
     840,   846,   850
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
  "OP_LE", "OP_LT", "OP_EQUAL", "OP_UNEQUAL", "OP_NOT", "OP_ASSIGN",
  "OP_MOD", "OP_DOTDOT", "OP_SEMI", "NAME", "CONST_REAL", "CONST_INTEGER",
  "CONST_CHAR", "CONST_STRING", "EMPTY_ROUTINE_PART", "$accept", "program",
  "program_head", "sys_con", "sys_funct", "sys_proc", "sys_type",
  "routine", "sub_routine", "routine_head", "label_part", "const_part",
  "const_decl_list", "const_decl", "const_value", "type_part",
  "type_decl_list", "type_decl", "type", "simple_type", "array_type",
  "record_type", "field_decl_list", "field_decl", "name_list", "var_part",
  "var_decl_list", "var_decl", "routine_part", "function_decl",
  "function_head", "procedure_decl", "procedure_head", "parameters",
  "para_decl_list", "para_type_list", "var_para_list", "val_para_list",
  "routine_body", "compound_stmt", "stmt_list", "stmt", "non_label_stmt",
  "assign_stmt", "proc_stmt", "if_stmt", "else_clause", "repeat_stmt",
  "while_stmt", "for_stmt", "direction", "case_stmt", "case_expr_list",
  "case_expr", "goto_stmt", "expression", "expr", "term", "factor",
  "args_list", "non_empty_args_list", YY_NULLPTR
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
     335,   336
};
# endif

#define YYPACT_NINF (-153)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       0,   -47,    38,  -153,   -30,  -153,   -11,    49,    57,  -153,
    -153,  -153,  -153,  -153,    -8,    40,   121,     5,    -8,  -153,
      -1,    61,   262,  -153,    18,    -2,   262,  -153,   262,  -153,
    -153,  -153,   -38,    37,    50,  -153,    23,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,   278,  -153,    34,    -1,
    -153,    29,    14,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,   262,   262,   262,   -31,  -153,  -153,
    -153,  -153,  -153,    53,  -153,   110,    -4,    28,  -153,    39,
    -153,   261,   176,    91,   262,   262,    41,   262,     6,   262,
    -153,    43,    36,  -153,  -153,    -9,    29,  -153,    52,    55,
      14,  -153,    60,  -153,    63,   279,  -153,  -153,   262,   262,
      56,   262,   195,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   212,   262,   212,
     181,    84,    81,   294,    70,   181,  -153,    88,  -153,    90,
      29,  -153,  -153,  -153,  -153,  -153,    29,    74,  -153,    76,
      77,  -153,  -153,  -153,    75,    36,  -153,    99,    99,  -153,
    -153,  -153,  -153,  -153,   107,   308,  -153,   108,   212,   104,
     105,    44,  -153,    -4,    -4,    -4,    -4,    -4,    -4,    28,
      28,    28,  -153,  -153,  -153,  -153,   226,   155,   181,  -153,
    -153,   262,    97,   262,  -153,   232,     1,  -153,     3,   -29,
      94,   278,  -153,  -153,   111,   -27,   112,  -153,   113,    49,
     115,  -153,  -153,  -153,   118,   212,   212,  -153,  -153,  -153,
    -153,   262,   212,  -153,   181,   262,   181,   128,  -153,  -153,
      36,  -153,  -153,  -153,  -153,    29,   135,   -40,  -153,   127,
     136,   232,  -153,  -153,  -153,  -153,   123,   125,   174,  -153,
     181,   184,   133,   135,  -153,   -27,   232,   232,  -153,  -153,
    -153,   212,    36,  -153,  -153,  -153,  -153,  -153,  -153
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
       0,    42,    43,    44,     0,     0,    59,    72,    72,    62,
      63,    26,    26,   134,     0,     0,   138,     0,     0,     0,
       0,     0,   109,   114,   115,   116,   117,   118,   119,   123,
     121,   122,   128,   125,   126,   127,     0,   101,   102,   103,
      97,     0,     0,     0,    98,     0,     0,    53,     0,     0,
       0,     0,    41,    55,     0,     0,     0,    70,     0,     0,
       0,   131,   137,   132,     0,     0,     0,   107,   108,   106,
     105,     0,     0,    99,   141,     0,    96,     0,    51,    52,
       0,    47,    49,    48,    61,     0,    78,     0,    74,     0,
       0,     0,    67,    24,    69,   112,     0,     0,     0,   100,
      95,     0,     0,    77,    71,     0,     0,     0,    68,   111,
     110,     0,     0,    54,    73,    75,    76,   104,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,    51,   209,
    -153,  -153,  -153,   196,   -46,  -153,  -153,   166,  -152,  -112,
    -153,  -153,  -153,    25,  -136,  -153,  -153,   130,  -153,   124,
    -153,   134,  -153,    79,  -153,   -22,  -153,  -153,    26,    -6,
     229,  -120,   165,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,    86,  -153,   -20,   204,   -78,   154,   -75,
    -153
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    72,    73,    34,   148,     6,   208,   209,
       8,    15,    18,    19,    74,    21,    49,    50,   150,   151,
     152,   153,   196,   197,    95,    52,    96,    97,   100,   101,
     102,   103,   104,   206,   237,   238,   239,   240,    12,    35,
      16,    36,    37,    38,    39,    40,   223,    41,    42,    43,
     221,    44,   171,   172,    45,   130,    76,    77,    78,   131,
     132
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      91,    13,    75,   204,   198,   235,    81,   187,    83,   189,
     199,    11,    22,   228,   137,   254,    84,   119,    85,    24,
      86,    25,    26,   108,     1,   109,   231,   110,    98,     4,
     154,   122,    27,   164,    87,   255,   167,    99,     5,    28,
     139,   179,   180,   181,   105,     9,   149,    10,   214,    94,
     154,   155,    29,    30,    11,   168,   217,   120,   121,    31,
     198,   140,   154,   230,    14,   133,   170,   135,    17,   236,
      20,    53,    54,    55,    46,    48,    80,    94,   252,    53,
      54,    55,    32,   227,   141,   142,   143,   144,   145,   165,
     146,   123,   124,    51,    79,   246,   247,    88,    90,   253,
     129,   125,   249,    92,    89,    94,   186,   111,   188,   149,
     268,   126,   147,    68,    69,    70,    71,   134,   138,   236,
     169,    68,    69,    70,    71,   170,    11,    22,   157,   258,
     112,   158,   166,    23,    24,   161,    25,    26,   162,   190,
     191,   267,   193,   194,   265,   266,   195,    27,   200,   149,
     201,   203,   202,   205,    28,   233,   113,   114,   115,   116,
     117,   118,   211,   213,   215,   216,   222,    29,    30,   225,
     232,   224,   241,   226,    31,   113,   114,   115,   116,   117,
     118,    11,    22,   261,   149,   251,   234,   256,   242,    24,
     244,    25,    26,   245,   154,   149,   257,    32,   259,    33,
     260,   248,    27,    13,   262,   250,   168,   128,   263,    28,
     149,   149,     7,   210,    47,    93,   149,    11,    22,   106,
     107,   229,    29,    30,   159,    24,   156,    25,    26,    31,
      53,    54,    55,   264,   160,   243,   219,   207,    27,   113,
     114,   115,   116,   117,   118,    28,   113,   114,   115,   116,
     117,   118,    32,   136,    33,   220,    82,   218,    29,    30,
       0,     0,     0,     0,     0,    31,     0,    53,    54,    55,
       0,   169,    68,    69,    70,    71,   182,   183,   184,   185,
     141,   142,   143,   144,   145,     0,   146,     0,    32,   127,
      33,   113,   114,   115,   116,   117,   118,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,   147,    68,
      69,    70,    71,    53,    54,    55,    64,   173,   174,   175,
     176,   177,   178,     0,    65,     0,   113,   114,   115,   116,
     117,   118,     0,    66,   163,     0,     0,     0,    67,    68,
      69,    70,    71,     0,   113,   114,   115,   116,   117,   118,
       0,   192,     0,     0,     0,    68,    69,    70,    71,   113,
     114,   115,   116,   117,   118,   212,     0,     0,     0,     0,
       0,     0,     0,   113,   114,   115,   116,   117,   118
};

static const yytype_int16 yycheck[] =
{
      46,     7,    22,   155,   140,    32,    26,   127,    28,   129,
     146,     5,     6,    12,    89,    55,    54,    21,    56,    13,
      58,    15,    16,    54,    24,    56,    55,    58,    14,    76,
      59,     3,    26,   108,    72,    75,   111,    23,     0,    33,
       4,   119,   120,   121,    64,    75,    92,    58,   168,    76,
      59,    60,    46,    47,     5,    11,    12,    61,    62,    53,
     196,    25,    59,    60,     7,    85,   112,    87,    76,   205,
      30,    35,    36,    37,    69,    76,    78,    76,   230,    35,
      36,    37,    76,   195,    48,    49,    50,    51,    52,   109,
      54,    63,    64,    32,    76,   215,   216,    60,    75,   235,
       9,    73,   222,    69,    54,    76,   126,    54,   128,   155,
     262,    72,    76,    77,    78,    79,    80,    76,    75,   255,
      76,    77,    78,    79,    80,   171,     5,     6,    76,   241,
      20,    76,    76,    12,    13,    75,    15,    16,    75,    55,
      59,   261,    72,    55,   256,   257,    56,    26,    74,   195,
      74,    76,    75,    54,    33,   201,    65,    66,    67,    68,
      69,    70,    55,    55,    60,    60,    11,    46,    47,    72,
      76,   191,    60,   193,    53,    65,    66,    67,    68,    69,
      70,     5,     6,     9,   230,    57,    75,    60,    75,    13,
      75,    15,    16,    75,    59,   241,    60,    76,    75,    78,
      75,   221,    26,   209,    20,   225,    11,    31,    75,    33,
     256,   257,     3,   162,    18,    49,   262,     5,     6,    65,
      66,   196,    46,    47,   100,    13,    96,    15,    16,    53,
      35,    36,    37,   255,   100,   209,    10,   158,    26,    65,
      66,    67,    68,    69,    70,    33,    65,    66,    67,    68,
      69,    70,    76,    88,    78,    29,    27,   171,    46,    47,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    35,    36,    37,
      -1,    76,    77,    78,    79,    80,   122,   123,   124,   125,
      48,    49,    50,    51,    52,    -1,    54,    -1,    76,    28,
      78,    65,    66,    67,    68,    69,    70,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    76,    77,
      78,    79,    80,    35,    36,    37,    54,   113,   114,   115,
     116,   117,   118,    -1,    62,    -1,    65,    66,    67,    68,
      69,    70,    -1,    71,    55,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    -1,    65,    66,    67,    68,    69,    70,
      -1,    57,    -1,    -1,    -1,    77,    78,    79,    80,    65,
      66,    67,    68,    69,    70,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    83,    84,    76,     0,    89,    91,    92,    75,
      58,     5,   120,   121,     7,    93,   122,    76,    94,    95,
      30,    97,     6,    12,    13,    15,    16,    26,    33,    46,
      47,    53,    76,    78,    87,   121,   123,   124,   125,   126,
     127,   129,   130,   131,   133,   136,    69,    95,    76,    98,
      99,    32,   107,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    54,    62,    71,    76,    77,    78,
      79,    80,    85,    86,    96,   137,   138,   139,   140,    76,
      78,   137,   122,   137,    54,    56,    58,    72,    60,    54,
      75,    96,    69,    99,    76,   106,   108,   109,    14,    23,
     110,   111,   112,   113,   114,   137,   140,   140,    54,    56,
      58,    54,    20,    65,    66,    67,    68,    69,    70,    21,
      61,    62,     3,    63,    64,    73,    72,    28,    31,     9,
     137,   141,   142,   137,    76,   137,   124,   141,    75,     4,
      25,    48,    49,    50,    51,    52,    54,    76,    88,    96,
     100,   101,   102,   103,    59,    60,   109,    76,    76,   111,
     113,    75,    75,    55,   141,   137,    76,   141,    11,    76,
      96,   134,   135,   138,   138,   138,   138,   138,   138,   139,
     139,   139,   140,   140,   140,   140,   137,   123,   137,   123,
      55,    59,    57,    72,    55,    56,   104,   105,   106,   106,
      74,    74,    75,    76,   100,    54,   115,   115,    90,    91,
      90,    55,    57,    55,   123,    60,    60,    12,   135,    10,
      29,   132,    11,   128,   137,    72,   137,   101,    12,   105,
      60,    55,    76,    96,    75,    32,   106,   116,   117,   118,
     119,    60,    75,   120,    75,    75,   123,   123,   137,   123,
     137,    57,   100,   106,    55,    75,    60,    60,   101,    75,
      75,     9,    20,    75,   117,   101,   101,   123,   100
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    85,    85,    85,    86,    86,    86,
      86,    86,    86,    86,    86,    87,    87,    87,    88,    88,
      88,    88,    88,    89,    90,    91,    92,    93,    93,    94,
      94,    95,    96,    96,    96,    96,    96,    97,    97,    98,
      98,    99,   100,   100,   100,   101,   101,   101,   101,   101,
     102,   103,   104,   104,   105,   106,   106,   107,   107,   108,
     108,   109,   110,   110,   110,   110,   110,   111,   112,   113,
     114,   115,   115,   116,   116,   117,   117,   118,   119,   120,
     121,   122,   122,   123,   123,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   125,   125,   125,   126,   126,   127,
     128,   128,   129,   130,   131,   132,   132,   133,   134,   134,
     135,   135,   135,   136,   137,   137,   137,   137,   137,   137,
     137,   138,   138,   138,   138,   139,   139,   139,   139,   139,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   141,
     141,   142,   142
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
       3,     3,     0,     3,     1,     3,     3,     2,     1,     1,
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
#line 229 "./src/parser/Parser.yy"
                                {
        (yyval.node_program) = new ASTNode_Program((yyvsp[-2].node_name),(yyvsp[-1].node_routine));
        ASTHandler::setASTHead((yyval.node_program));
    }
#line 1680 "./src/Parser.cc"
    break;

  case 3:
#line 236 "./src/parser/Parser.yy"
                            {
        (yyval.node_name) = (yyvsp[-1].node_name);
    }
#line 1688 "./src/Parser.cc"
    break;

  case 4:
#line 245 "./src/parser/Parser.yy"
              {
        (yyval.node_const) = new ASTNode_ConstBoolean(false);
    }
#line 1696 "./src/Parser.cc"
    break;

  case 5:
#line 248 "./src/parser/Parser.yy"
                {
        (yyval.node_const) = new ASTNode_ConstInteger(INT_MAX);
    }
#line 1704 "./src/Parser.cc"
    break;

  case 6:
#line 251 "./src/parser/Parser.yy"
              {
        (yyval.node_const) = new ASTNode_ConstBoolean(true);
    }
#line 1712 "./src/Parser.cc"
    break;

  case 7:
#line 257 "./src/parser/Parser.yy"
            {
        (yyval.node_name) = new ASTNode_Name("abs");
    }
#line 1720 "./src/Parser.cc"
    break;

  case 8:
#line 260 "./src/parser/Parser.yy"
             {
        (yyval.node_name) = new ASTNode_Name("chr");
    }
#line 1728 "./src/Parser.cc"
    break;

  case 9:
#line 263 "./src/parser/Parser.yy"
             {
        (yyval.node_name) = new ASTNode_Name("odd");
    }
#line 1736 "./src/Parser.cc"
    break;

  case 10:
#line 266 "./src/parser/Parser.yy"
             {
        (yyval.node_name) = new ASTNode_Name("ord");
    }
#line 1744 "./src/Parser.cc"
    break;

  case 11:
#line 269 "./src/parser/Parser.yy"
              {
        (yyval.node_name) = new ASTNode_Name("pred");
    }
#line 1752 "./src/Parser.cc"
    break;

  case 12:
#line 272 "./src/parser/Parser.yy"
             {
        (yyval.node_name) = new ASTNode_Name("sqr");
    }
#line 1760 "./src/Parser.cc"
    break;

  case 13:
#line 275 "./src/parser/Parser.yy"
              {
        (yyval.node_name) = new ASTNode_Name("sqrt");
    }
#line 1768 "./src/Parser.cc"
    break;

  case 14:
#line 278 "./src/parser/Parser.yy"
              {
        (yyval.node_name) = new ASTNode_Name("succ");
    }
#line 1776 "./src/Parser.cc"
    break;

  case 15:
#line 284 "./src/parser/Parser.yy"
              {
        (yyval.node_name) = new ASTNode_Name("write");
    }
#line 1784 "./src/Parser.cc"
    break;

  case 16:
#line 287 "./src/parser/Parser.yy"
                 {
        (yyval.node_name) = new ASTNode_Name("writeln");
    }
#line 1792 "./src/Parser.cc"
    break;

  case 17:
#line 290 "./src/parser/Parser.yy"
              {
        (yyval.node_name) = new ASTNode_Name("read");
    }
#line 1800 "./src/Parser.cc"
    break;

  case 18:
#line 296 "./src/parser/Parser.yy"
                {
        (yyval.node_simple_type) = new ASTNode_SimpleTypePlain("boolean");
    }
#line 1808 "./src/Parser.cc"
    break;

  case 19:
#line 299 "./src/parser/Parser.yy"
              {
        (yyval.node_simple_type) = new ASTNode_SimpleTypePlain("char");
    }
#line 1816 "./src/Parser.cc"
    break;

  case 20:
#line 302 "./src/parser/Parser.yy"
                 {
        (yyval.node_simple_type) = new ASTNode_SimpleTypePlain("integer");
    }
#line 1824 "./src/Parser.cc"
    break;

  case 21:
#line 305 "./src/parser/Parser.yy"
              {
        (yyval.node_simple_type) = new ASTNode_SimpleTypePlain("real");
    }
#line 1832 "./src/Parser.cc"
    break;

  case 22:
#line 308 "./src/parser/Parser.yy"
                {
        (yyval.node_simple_type) = new ASTNode_SimpleTypePlain("string");
    }
#line 1840 "./src/Parser.cc"
    break;

  case 23:
#line 315 "./src/parser/Parser.yy"
                              {
        (yyval.node_routine) = new ASTNode_Routine((yyvsp[-1].node_routine_head),(yyvsp[0].node_stmt_compound));
    }
#line 1848 "./src/Parser.cc"
    break;

  case 24:
#line 321 "./src/parser/Parser.yy"
                              {
        (yyval.node_sub_routine) = new ASTNode_SubRoutine((yyvsp[-1].node_routine_head),(yyvsp[0].node_stmt_compound));
    }
#line 1856 "./src/Parser.cc"
    break;

  case 25:
#line 327 "./src/parser/Parser.yy"
                                                          {
        (yyval.node_routine_head) = new ASTNode_RoutineHead((yyvsp[-3].node_const_decl_list),(yyvsp[-2].node_type_decl_list),(yyvsp[-1].node_var_decl_list),(yyvsp[0].node_routine_part));
    }
#line 1864 "./src/Parser.cc"
    break;

  case 27:
#line 337 "./src/parser/Parser.yy"
                             {
        (yyval.node_const_decl_list) = (yyvsp[0].node_const_decl_list);
    }
#line 1872 "./src/Parser.cc"
    break;

  case 28:
#line 340 "./src/parser/Parser.yy"
             {
        (yyval.node_const_decl_list) = nullptr;
    }
#line 1880 "./src/Parser.cc"
    break;

  case 29:
#line 346 "./src/parser/Parser.yy"
                               {
        (yyval.node_const_decl_list) = (yyvsp[-1].node_const_decl_list);
        (yyval.node_const_decl_list)->append((yyvsp[0].node_const_decl));
    }
#line 1889 "./src/Parser.cc"
    break;

  case 30:
#line 350 "./src/parser/Parser.yy"
                 {
        (yyval.node_const_decl_list) = new ASTNode_ConstDeclList();
        (yyval.node_const_decl_list)->append((yyvsp[0].node_const_decl));
    }
#line 1898 "./src/Parser.cc"
    break;

  case 31:
#line 357 "./src/parser/Parser.yy"
                                      {
        (yyval.node_const_decl) = new ASTNode_ConstDecl((yyvsp[-3].node_name),(yyvsp[-1].node_const));
    }
#line 1906 "./src/Parser.cc"
    break;

  case 32:
#line 363 "./src/parser/Parser.yy"
                  {
        (yyval.node_const) = (yyvsp[0].node_const);
    }
#line 1914 "./src/Parser.cc"
    break;

  case 33:
#line 366 "./src/parser/Parser.yy"
                 {
        (yyval.node_const) = (yyvsp[0].node_const);
    }
#line 1922 "./src/Parser.cc"
    break;

  case 34:
#line 369 "./src/parser/Parser.yy"
                 {
        (yyval.node_const) = (yyvsp[0].node_const);
    }
#line 1930 "./src/Parser.cc"
    break;

  case 35:
#line 372 "./src/parser/Parser.yy"
                   {
        (yyval.node_const) = (yyvsp[0].node_const);
    }
#line 1938 "./src/Parser.cc"
    break;

  case 36:
#line 375 "./src/parser/Parser.yy"
              {
        (yyval.node_const) = (yyvsp[0].node_const);
    }
#line 1946 "./src/Parser.cc"
    break;

  case 37:
#line 381 "./src/parser/Parser.yy"
                           {
        (yyval.node_type_decl_list) = (yyvsp[0].node_type_decl_list);
    }
#line 1954 "./src/Parser.cc"
    break;

  case 38:
#line 384 "./src/parser/Parser.yy"
             {
        (yyval.node_type_decl_list) = nullptr;
    }
#line 1962 "./src/Parser.cc"
    break;

  case 39:
#line 390 "./src/parser/Parser.yy"
                             {
        (yyval.node_type_decl_list) = (yyvsp[-1].node_type_decl_list);
        (yyval.node_type_decl_list)->append((yyvsp[0].node_type_decl));
    }
#line 1971 "./src/Parser.cc"
    break;

  case 40:
#line 394 "./src/parser/Parser.yy"
                {
        (yyval.node_type_decl_list) = new ASTNode_TypeDeclList();
        (yyval.node_type_decl_list)->append((yyvsp[0].node_type_decl));
    }
#line 1980 "./src/Parser.cc"
    break;

  case 41:
#line 401 "./src/parser/Parser.yy"
                               {
        (yyval.node_type_decl) = new ASTNode_TypeDecl((yyvsp[-3].node_name),(yyvsp[-1].node_type));
    }
#line 1988 "./src/Parser.cc"
    break;

  case 42:
#line 407 "./src/parser/Parser.yy"
                {
        (yyval.node_type) = (yyvsp[0].node_simple_type);
    }
#line 1996 "./src/Parser.cc"
    break;

  case 43:
#line 410 "./src/parser/Parser.yy"
                 {
        (yyval.node_type) = (yyvsp[0].node_array_type);
    }
#line 2004 "./src/Parser.cc"
    break;

  case 44:
#line 413 "./src/parser/Parser.yy"
                  {
        (yyval.node_type) = (yyvsp[0].node_record_type);
    }
#line 2012 "./src/Parser.cc"
    break;

  case 45:
#line 419 "./src/parser/Parser.yy"
             {
        (yyval.node_simple_type) = (yyvsp[0].node_simple_type);
    }
#line 2020 "./src/Parser.cc"
    break;

  case 46:
#line 422 "./src/parser/Parser.yy"
           {
        (yyval.node_simple_type) = new ASTNode_SimpleTypePlain((yyvsp[0].node_name));
    }
#line 2028 "./src/Parser.cc"
    break;

  case 47:
#line 425 "./src/parser/Parser.yy"
                            {
        (yyval.node_simple_type) = new ASTNode_SimpleTypeEnumerate((yyvsp[-1].node_name_list));
    }
#line 2036 "./src/Parser.cc"
    break;

  case 48:
#line 428 "./src/parser/Parser.yy"
                                        {
        (yyval.node_simple_type) = new ASTNode_SimpleTypeSubRange((yyvsp[-2].node_const),(yyvsp[0].node_const));
    }
#line 2044 "./src/Parser.cc"
    break;

  case 49:
#line 431 "./src/parser/Parser.yy"
                          {
        (yyval.node_simple_type) = new ASTNode_SimpleTypeSubRange((yyvsp[-2].node_name),(yyvsp[0].node_name));
    }
#line 2052 "./src/Parser.cc"
    break;

  case 50:
#line 437 "./src/parser/Parser.yy"
                                                {
        (yyval.node_array_type) = new ASTNode_ArrayType((yyvsp[-3].node_simple_type),(yyvsp[0].node_type));
    }
#line 2060 "./src/Parser.cc"
    break;

  case 51:
#line 443 "./src/parser/Parser.yy"
                                     {
        (yyval.node_record_type) = new ASTNode_RecordType((yyvsp[-1].node_field_decl_list));
    }
#line 2068 "./src/Parser.cc"
    break;

  case 52:
#line 449 "./src/parser/Parser.yy"
                               {
        (yyval.node_field_decl_list) = (yyvsp[-1].node_field_decl_list);
        (yyval.node_field_decl_list)->append((yyvsp[0].node_field_decl));
    }
#line 2077 "./src/Parser.cc"
    break;

  case 53:
#line 453 "./src/parser/Parser.yy"
                 {
        (yyval.node_field_decl_list) = new ASTNode_FieldDeclList();
        (yyval.node_field_decl_list)->append((yyvsp[0].node_field_decl));
    }
#line 2086 "./src/Parser.cc"
    break;

  case 54:
#line 460 "./src/parser/Parser.yy"
                                    {
        (yyval.node_field_decl) = new ASTNode_FieldDecl((yyvsp[-3].node_name_list),(yyvsp[-1].node_type));
    }
#line 2094 "./src/Parser.cc"
    break;

  case 55:
#line 466 "./src/parser/Parser.yy"
                            {
        (yyval.node_name_list) = (yyvsp[-2].node_name_list);
        (yyval.node_name_list)->insert((yyvsp[0].node_name));
    }
#line 2103 "./src/Parser.cc"
    break;

  case 56:
#line 470 "./src/parser/Parser.yy"
           {
        (yyval.node_name_list) = new ASTNode_NameList();
        (yyval.node_name_list)->insert((yyvsp[0].node_name));
    }
#line 2112 "./src/Parser.cc"
    break;

  case 57:
#line 477 "./src/parser/Parser.yy"
                         {
        (yyval.node_var_decl_list) = (yyvsp[0].node_var_decl_list);
    }
#line 2120 "./src/Parser.cc"
    break;

  case 58:
#line 480 "./src/parser/Parser.yy"
             {
        (yyval.node_var_decl_list) = nullptr;
    }
#line 2128 "./src/Parser.cc"
    break;

  case 59:
#line 486 "./src/parser/Parser.yy"
                           {
        (yyval.node_var_decl_list) = (yyvsp[-1].node_var_decl_list);
        (yyval.node_var_decl_list)->append((yyvsp[0].node_var_decl));
    }
#line 2137 "./src/Parser.cc"
    break;

  case 60:
#line 490 "./src/parser/Parser.yy"
               {
        (yyval.node_var_decl_list) = new ASTNode_VarDeclList();
        (yyval.node_var_decl_list)->append((yyvsp[0].node_var_decl));
    }
#line 2146 "./src/Parser.cc"
    break;

  case 61:
#line 497 "./src/parser/Parser.yy"
                                    {
        (yyval.node_var_decl) = new ASTNode_VarDecl((yyvsp[-3].node_name_list),(yyvsp[-1].node_type));
    }
#line 2154 "./src/Parser.cc"
    break;

  case 62:
#line 503 "./src/parser/Parser.yy"
                               {
        (yyval.node_routine_part) = (yyvsp[-1].node_routine_part);
        (yyval.node_routine_part)->append((yyvsp[0].node_function_decl));
    }
#line 2163 "./src/Parser.cc"
    break;

  case 63:
#line 507 "./src/parser/Parser.yy"
                                  {
        (yyval.node_routine_part) = (yyvsp[-1].node_routine_part);
        (yyval.node_routine_part)->append((yyvsp[0].node_procedure_decl));
    }
#line 2172 "./src/Parser.cc"
    break;

  case 64:
#line 511 "./src/parser/Parser.yy"
                    {
        (yyval.node_routine_part) = new ASTNode_RoutinePart();
        (yyval.node_routine_part)->append((yyvsp[0].node_function_decl));
    }
#line 2181 "./src/Parser.cc"
    break;

  case 65:
#line 515 "./src/parser/Parser.yy"
                     {
        (yyval.node_routine_part) = new ASTNode_RoutinePart();
        (yyval.node_routine_part)->append((yyvsp[0].node_procedure_decl));
    }
#line 2190 "./src/Parser.cc"
    break;

  case 66:
#line 519 "./src/parser/Parser.yy"
                                      {
        (yyval.node_routine_part) = nullptr;
    }
#line 2198 "./src/Parser.cc"
    break;

  case 67:
#line 525 "./src/parser/Parser.yy"
                                              {
        (yyval.node_function_decl) = new ASTNode_FunctionDecl((yyvsp[-3].node_function_head),(yyvsp[-1].node_sub_routine));
    }
#line 2206 "./src/Parser.cc"
    break;

  case 68:
#line 531 "./src/parser/Parser.yy"
                                                     {
        (yyval.node_function_head) = new ASTNode_FunctionHead((yyvsp[-3].node_name),(yyvsp[-2].node_para_decl_list),(yyvsp[0].node_simple_type));
    }
#line 2214 "./src/Parser.cc"
    break;

  case 69:
#line 537 "./src/parser/Parser.yy"
                                               {
        (yyval.node_procedure_decl) = new ASTNode_ProcedureDecl((yyvsp[-3].node_procedure_head),(yyvsp[-1].node_sub_routine));
    }
#line 2222 "./src/Parser.cc"
    break;

  case 70:
#line 543 "./src/parser/Parser.yy"
                                 {
        (yyval.node_procedure_head) = new ASTNode_ProcedureHead((yyvsp[-1].node_name),(yyvsp[0].node_para_decl_list));
    }
#line 2230 "./src/Parser.cc"
    break;

  case 71:
#line 549 "./src/parser/Parser.yy"
                               {
        (yyval.node_para_decl_list) = (yyvsp[-1].node_para_decl_list);
    }
#line 2238 "./src/Parser.cc"
    break;

  case 72:
#line 552 "./src/parser/Parser.yy"
             {
        (yyval.node_para_decl_list) = new ASTNode_ParaDeclList();
    }
#line 2246 "./src/Parser.cc"
    break;

  case 73:
#line 558 "./src/parser/Parser.yy"
                                          {
        (yyval.node_para_decl_list) = (yyvsp[-2].node_para_decl_list);
        (yyval.node_para_decl_list)->append((yyvsp[0].node_para_type_list));
    }
#line 2255 "./src/Parser.cc"
    break;

  case 74:
#line 562 "./src/parser/Parser.yy"
                     {
        (yyval.node_para_decl_list) = new ASTNode_ParaDeclList();
        (yyval.node_para_decl_list)->append((yyvsp[0].node_para_type_list));
    }
#line 2264 "./src/Parser.cc"
    break;

  case 75:
#line 569 "./src/parser/Parser.yy"
                                       {
        (yyval.node_para_type_list) = new ASTNode_ParaTypeList((yyvsp[-2].node_var_para_list),(yyvsp[0].node_simple_type));
    }
#line 2272 "./src/Parser.cc"
    break;

  case 76:
#line 572 "./src/parser/Parser.yy"
                                         {
        (yyval.node_para_type_list) = new ASTNode_ParaTypeList((yyvsp[-2].node_val_para_list),(yyvsp[0].node_simple_type));
        }
#line 2280 "./src/Parser.cc"
    break;

  case 77:
#line 578 "./src/parser/Parser.yy"
                     {
        (yyval.node_var_para_list) = new ASTNode_VarParaList((yyvsp[0].node_name_list));
    }
#line 2288 "./src/Parser.cc"
    break;

  case 78:
#line 584 "./src/parser/Parser.yy"
              {
        (yyval.node_val_para_list) = new ASTNode_ValParaList((yyvsp[0].node_name_list));
    }
#line 2296 "./src/Parser.cc"
    break;

  case 79:
#line 590 "./src/parser/Parser.yy"
                  {
        (yyval.node_stmt_compound) = (yyvsp[0].node_stmt_compound);
    }
#line 2304 "./src/Parser.cc"
    break;

  case 80:
#line 596 "./src/parser/Parser.yy"
                              {
        (yyval.node_stmt_compound) = new ASTNode_StmtCompound((yyvsp[-1].node_stmt_list));
    }
#line 2312 "./src/Parser.cc"
    break;

  case 81:
#line 602 "./src/parser/Parser.yy"
                           {
        (yyval.node_stmt_list) = (yyvsp[-2].node_stmt_list);
        (yyval.node_stmt_list)->append((yyvsp[-1].node_stmt));
    }
#line 2321 "./src/Parser.cc"
    break;

  case 82:
#line 606 "./src/parser/Parser.yy"
             {
        (yyval.node_stmt_list) = new ASTNode_StmtList();
    }
#line 2329 "./src/Parser.cc"
    break;

  case 83:
#line 612 "./src/parser/Parser.yy"
                                          {
        (yyval.node_stmt) = (yyvsp[0].node_stmt);
        (yyval.node_stmt)->setLabel((yyvsp[-2].node_const));
    }
#line 2338 "./src/Parser.cc"
    break;

  case 84:
#line 616 "./src/parser/Parser.yy"
                     {
        (yyval.node_stmt) = (yyvsp[0].node_stmt);
    }
#line 2346 "./src/Parser.cc"
    break;

  case 85:
#line 622 "./src/parser/Parser.yy"
                {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_assign);
    }
#line 2354 "./src/Parser.cc"
    break;

  case 86:
#line 625 "./src/parser/Parser.yy"
                {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_proc);
    }
#line 2362 "./src/Parser.cc"
    break;

  case 87:
#line 628 "./src/parser/Parser.yy"
                    {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_compound);
    }
#line 2370 "./src/Parser.cc"
    break;

  case 88:
#line 631 "./src/parser/Parser.yy"
              {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_if);
    }
#line 2378 "./src/Parser.cc"
    break;

  case 89:
#line 634 "./src/parser/Parser.yy"
                  {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_repeat);
    }
#line 2386 "./src/Parser.cc"
    break;

  case 90:
#line 637 "./src/parser/Parser.yy"
                 {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_while);
    }
#line 2394 "./src/Parser.cc"
    break;

  case 91:
#line 640 "./src/parser/Parser.yy"
               {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_for);
    }
#line 2402 "./src/Parser.cc"
    break;

  case 92:
#line 643 "./src/parser/Parser.yy"
                {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_case);
    }
#line 2410 "./src/Parser.cc"
    break;

  case 93:
#line 646 "./src/parser/Parser.yy"
                {
        (yyval.node_stmt) = (yyvsp[0].node_stmt_goto);
    }
#line 2418 "./src/Parser.cc"
    break;

  case 94:
#line 652 "./src/parser/Parser.yy"
                              {
        (yyval.node_stmt_assign) = new ASTNode_StmtAssignSimpleType((yyvsp[-2].node_name),(yyvsp[0].node_expr));
    }
#line 2426 "./src/Parser.cc"
    break;

  case 95:
#line 655 "./src/parser/Parser.yy"
                                                       {
        (yyval.node_stmt_assign) = new ASTNode_StmtAssignArrayType((yyvsp[-5].node_name),(yyvsp[-3].node_expr),(yyvsp[0].node_expr));
    }
#line 2434 "./src/Parser.cc"
    break;

  case 96:
#line 658 "./src/parser/Parser.yy"
                                            {
        (yyval.node_stmt_assign) = new ASTNode_StmtAssignRecordType((yyvsp[-4].node_name),(yyvsp[-2].node_name),(yyvsp[0].node_expr));
    }
#line 2442 "./src/Parser.cc"
    break;

  case 97:
#line 664 "./src/parser/Parser.yy"
                               {
        (yyval.node_stmt_proc) = new ASTNode_StmtProc((yyvsp[-3].node_name),(yyvsp[-1].node_arg_list));
    }
#line 2450 "./src/Parser.cc"
    break;

  case 98:
#line 667 "./src/parser/Parser.yy"
                                     {
        (yyval.node_stmt_proc) = new ASTNode_StmtSysProc((yyvsp[-3].node_name),(yyvsp[-1].node_arg_list));
    }
#line 2458 "./src/Parser.cc"
    break;

  case 99:
#line 673 "./src/parser/Parser.yy"
                                              {
        (yyval.node_stmt_if) = new ASTNode_StmtIf((yyvsp[-3].node_expr),(yyvsp[-1].node_stmt),(yyvsp[0].node_stmt));
    }
#line 2466 "./src/Parser.cc"
    break;

  case 100:
#line 679 "./src/parser/Parser.yy"
                 {
        (yyval.node_stmt) = (yyvsp[0].node_stmt);
    }
#line 2474 "./src/Parser.cc"
    break;

  case 101:
#line 682 "./src/parser/Parser.yy"
                           {
        (yyval.node_stmt) = nullptr;
    }
#line 2482 "./src/Parser.cc"
    break;

  case 102:
#line 688 "./src/parser/Parser.yy"
                                            {
        (yyval.node_stmt_repeat) = new ASTNode_StmtRepeat((yyvsp[-2].node_stmt_list),(yyvsp[0].node_expr));
    }
#line 2490 "./src/Parser.cc"
    break;

  case 103:
#line 694 "./src/parser/Parser.yy"
                                   {
        (yyval.node_stmt_while) = new ASTNode_StmtWhile((yyvsp[-2].node_expr),(yyvsp[0].node_stmt));
    }
#line 2498 "./src/Parser.cc"
    break;

  case 104:
#line 700 "./src/parser/Parser.yy"
                                                                     {
        (yyval.node_stmt_for) = new ASTNode_StmtFor((yyvsp[-6].node_name),(yyvsp[-3].node_const)->toString() == "true",(yyvsp[-4].node_expr),(yyvsp[-2].node_expr),(yyvsp[0].node_stmt));
    }
#line 2506 "./src/Parser.cc"
    break;

  case 105:
#line 706 "./src/parser/Parser.yy"
          {
        (yyval.node_const) = new ASTNode_ConstBoolean(true);
    }
#line 2514 "./src/Parser.cc"
    break;

  case 106:
#line 709 "./src/parser/Parser.yy"
                {
        (yyval.node_const) = new ASTNode_ConstBoolean(false);
    }
#line 2522 "./src/Parser.cc"
    break;

  case 107:
#line 715 "./src/parser/Parser.yy"
                                                   {
        (yyval.node_stmt_case) = new ASTNode_StmtCase((yyvsp[-3].node_expr),(yyvsp[-1].node_case_expr_list));
    }
#line 2530 "./src/Parser.cc"
    break;

  case 108:
#line 721 "./src/parser/Parser.yy"
                             {
        (yyval.node_case_expr_list) = (yyvsp[-1].node_case_expr_list);
        (yyval.node_case_expr_list)->append((yyvsp[0].node_case_expr));
    }
#line 2539 "./src/Parser.cc"
    break;

  case 109:
#line 725 "./src/parser/Parser.yy"
                {
        (yyval.node_case_expr_list) = new ASTNode_CaseExprList();
        (yyval.node_case_expr_list)->append((yyvsp[0].node_case_expr));
    }
#line 2548 "./src/Parser.cc"
    break;

  case 110:
#line 732 "./src/parser/Parser.yy"
                                      {
        (yyval.node_case_expr) = new ASTNode_CaseExprLiteral((yyvsp[-3].node_const),(yyvsp[-1].node_stmt));
    }
#line 2556 "./src/Parser.cc"
    break;

  case 111:
#line 735 "./src/parser/Parser.yy"
                                 {
        (yyval.node_case_expr) = new ASTNode_CaseExprConstVar((yyvsp[-3].node_name),(yyvsp[-1].node_stmt));
    }
#line 2564 "./src/Parser.cc"
    break;

  case 112:
#line 738 "./src/parser/Parser.yy"
                           {
        (yyval.node_case_expr) = new ASTNode_CaseExprDefault((yyvsp[-1].node_stmt));
    }
#line 2572 "./src/Parser.cc"
    break;

  case 113:
#line 744 "./src/parser/Parser.yy"
                          {
        (yyval.node_stmt_goto) = new ASTNode_StmtGoto((yyvsp[0].node_const));
    }
#line 2580 "./src/Parser.cc"
    break;

  case 114:
#line 750 "./src/parser/Parser.yy"
                          {
        (yyval.node_expr) = new ASTNode_OperatorGE((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2588 "./src/Parser.cc"
    break;

  case 115:
#line 753 "./src/parser/Parser.yy"
                            {
        (yyval.node_expr) = new ASTNode_OperatorGT((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2596 "./src/Parser.cc"
    break;

  case 116:
#line 756 "./src/parser/Parser.yy"
                            {
        (yyval.node_expr) = new ASTNode_OperatorLE((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2604 "./src/Parser.cc"
    break;

  case 117:
#line 759 "./src/parser/Parser.yy"
                            {
        (yyval.node_expr) = new ASTNode_OperatorLT((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2612 "./src/Parser.cc"
    break;

  case 118:
#line 762 "./src/parser/Parser.yy"
                               {
        (yyval.node_expr) = new ASTNode_OperatorEQ((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2620 "./src/Parser.cc"
    break;

  case 119:
#line 765 "./src/parser/Parser.yy"
                                 {
        (yyval.node_expr) = new ASTNode_OperatorNE((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2628 "./src/Parser.cc"
    break;

  case 120:
#line 768 "./src/parser/Parser.yy"
           {
        (yyval.node_expr) = (yyvsp[0].node_expr);
    }
#line 2636 "./src/Parser.cc"
    break;

  case 121:
#line 774 "./src/parser/Parser.yy"
                      {
        (yyval.node_expr) = new ASTNode_OperatorAdd((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2644 "./src/Parser.cc"
    break;

  case 122:
#line 777 "./src/parser/Parser.yy"
                         {
        (yyval.node_expr) = new ASTNode_OperatorSub((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2652 "./src/Parser.cc"
    break;

  case 123:
#line 780 "./src/parser/Parser.yy"
                      {
        (yyval.node_expr) = new ASTNode_OperatorOr((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2660 "./src/Parser.cc"
    break;

  case 124:
#line 783 "./src/parser/Parser.yy"
           {
        (yyval.node_expr) = (yyvsp[0].node_expr);
    }
#line 2668 "./src/Parser.cc"
    break;

  case 125:
#line 789 "./src/parser/Parser.yy"
                       {
        (yyval.node_expr) = new ASTNode_OperatorMul((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2676 "./src/Parser.cc"
    break;

  case 126:
#line 792 "./src/parser/Parser.yy"
                         {
        (yyval.node_expr) = new ASTNode_OperatorDiv((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2684 "./src/Parser.cc"
    break;

  case 127:
#line 795 "./src/parser/Parser.yy"
                         {
        (yyval.node_expr) = new ASTNode_OperatorMod((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2692 "./src/Parser.cc"
    break;

  case 128:
#line 798 "./src/parser/Parser.yy"
                         {
        (yyval.node_expr) = new ASTNode_OperatorAnd((yyvsp[-2].node_expr),(yyvsp[0].node_expr));
    }
#line 2700 "./src/Parser.cc"
    break;

  case 129:
#line 801 "./src/parser/Parser.yy"
             {
        (yyval.node_expr) = (yyvsp[0].node_expr);
    }
#line 2708 "./src/Parser.cc"
    break;

  case 130:
#line 807 "./src/parser/Parser.yy"
         {
        (yyval.node_expr) = new ASTNode_OperandVariable((yyvsp[0].node_name));
    }
#line 2716 "./src/Parser.cc"
    break;

  case 131:
#line 810 "./src/parser/Parser.yy"
                                 {
        (yyval.node_expr) = new ASTNode_OperandFunction((yyvsp[-3].node_name),(yyvsp[-1].node_arg_list));
    }
#line 2724 "./src/Parser.cc"
    break;

  case 132:
#line 813 "./src/parser/Parser.yy"
                                      {
        (yyval.node_expr) = new ASTNode_OperandSystemFunction((yyvsp[-3].node_name),(yyvsp[-1].node_arg_list));
    }
#line 2732 "./src/Parser.cc"
    break;

  case 133:
#line 816 "./src/parser/Parser.yy"
                  {
        (yyval.node_expr) = new ASTNode_OperandLiteral((yyvsp[0].node_const));
    }
#line 2740 "./src/Parser.cc"
    break;

  case 134:
#line 819 "./src/parser/Parser.yy"
                             {
        (yyval.node_expr) = (yyvsp[-1].node_expr);
    }
#line 2748 "./src/Parser.cc"
    break;

  case 135:
#line 822 "./src/parser/Parser.yy"
                    {
        (yyval.node_expr) = new ASTNode_OperatorNot((yyvsp[0].node_expr));
    }
#line 2756 "./src/Parser.cc"
    break;

  case 136:
#line 825 "./src/parser/Parser.yy"
                      {
        (yyval.node_expr) = new ASTNode_OperatorMinus((yyvsp[0].node_expr));
    }
#line 2764 "./src/Parser.cc"
    break;

  case 137:
#line 828 "./src/parser/Parser.yy"
                                  {
        (yyval.node_expr) = new ASTNode_OperandArrayElement((yyvsp[-3].node_name),(yyvsp[-1].node_expr));
    }
#line 2772 "./src/Parser.cc"
    break;

  case 138:
#line 831 "./src/parser/Parser.yy"
                       {
        (yyval.node_expr) = new ASTNode_OperandRecordMember((yyvsp[-2].node_name),(yyvsp[0].node_name));
    }
#line 2780 "./src/Parser.cc"
    break;

  case 139:
#line 837 "./src/parser/Parser.yy"
                        {
        (yyval.node_arg_list) = (yyvsp[0].node_arg_list);
    }
#line 2788 "./src/Parser.cc"
    break;

  case 140:
#line 840 "./src/parser/Parser.yy"
             {
        (yyval.node_arg_list) = new ASTNode_ArgList();
    }
#line 2796 "./src/Parser.cc"
    break;

  case 141:
#line 846 "./src/parser/Parser.yy"
                                            {
        (yyval.node_arg_list) = (yyvsp[-2].node_arg_list);
        (yyval.node_arg_list)->append((yyvsp[0].node_expr));
    }
#line 2805 "./src/Parser.cc"
    break;

  case 142:
#line 850 "./src/parser/Parser.yy"
                 {
        (yyval.node_arg_list) = new ASTNode_ArgList();
        (yyval.node_arg_list)->append((yyvsp[0].node_expr));
    }
#line 2814 "./src/Parser.cc"
    break;


#line 2818 "./src/Parser.cc"

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
#line 856 "./src/parser/Parser.yy"


void yyerror(const char* s)
{
    std::cerr << std::endl << s << std::endl;
    exit(1);
}
