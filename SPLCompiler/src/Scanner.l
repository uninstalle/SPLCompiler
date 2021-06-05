%{
    #include <iostream>
    #include "Parser.hh"
    #include "log.hh"
    #include "ast.hh"
    int lineno = 1;
    int colno = 1;
%}


/* keywords */
kw_and and
kw_array array
kw_begin begin
kw_case case
kw_const const
kw_div div
kw_do do
kw_downto downto
kw_else else
kw_end end
kw_for for
kw_function function
kw_goto goto
kw_if if
kw_in in
kw_mod mod
kw_not not
kw_of of
kw_or or
kw_packed packed
kw_procedure procedure
kw_program program
kw_record record
kw_repeat repeat
kw_set set
kw_then then
kw_to to
kw_type type
kw_until until
kw_var var
kw_while while
kw_with with

/* SYS_CON */
sys_false false
sys_maxint maxint
sys_true true

/* SYS_FUNCT */
sys_abs abs
sys_chr chr
sys_odd odd
sys_ord ord
sys_pred pred
sys_sqr sqr
sys_sqrt sqrt
sys_succ succ

/* SYS_PROC */
sys_write write
sys_writeln writeln

/* SYS_TYPE */
sys_boolean boolean
sys_char char
sys_integer integer
sys_real real
sys_string string

/* READ */
sys_read read

/* operator */
op_lp "("
op_rp ")"
op_lb "["
op_rb "]"
op_dot "."
op_comma ","
op_colon ":"
op_plus "+"
op_minus "-"
op_mul "*"
op_div "/"
op_ge ">="
op_gt ">"
op_le "<="
op_lt "<"
op_equal "="
op_unequal "<>"
op_not NOT
op_assign ":="
op_mod MOD|"%"
op_dotdot ".."
op_semi ";"


/* NAME: ID except keywords and system used tokens */
name [a-zA-Z][_a-zA-Z0-9]*

/* constants */
const_real -?[0-9]+("."[0-9]+|e-?[0-9]+)
const_integer -?[0-9]+
const_char '.'
const_string '.{0,255}'

/* white space */
ws [ \t]+
newline \n

/* exception */
unrecognized .


%%

%{
/* keywords */
%}

{kw_and} {
    colno += yyleng;
    return KW_AND;
}

{kw_array} {
    colno += yyleng;
    return KW_ARRAY;
}

{kw_begin} {
    colno += yyleng;
    return KW_BEGIN;
}

{kw_case} {
    colno += yyleng;
    return KW_CASE;
}

{kw_const} {
    colno += yyleng;
    return KW_CONST;
}

{kw_div} {
    colno += yyleng;
    return KW_DIV;
}

{kw_do} {
    colno += yyleng;
    return KW_DO;
}

{kw_downto} {
    colno += yyleng;
    return KW_DOWNTO;
}

{kw_else} {
    colno += yyleng;
    return KW_ELSE;
}

{kw_end} {
    colno += yyleng;
    return KW_END;
}

{kw_for} {
    colno += yyleng;
    return KW_FOR;
}

{kw_function} {
    colno += yyleng;
    return KW_FUNCTION;
}

{kw_goto} {
    colno += yyleng;
    return KW_GOTO;
}

{kw_if} {
    colno += yyleng;
    return KW_IF;
}

{kw_in} {
    colno += yyleng;
    return KW_IN;
}

{kw_mod} {
    colno += yyleng;
    return KW_MOD;
}

{kw_not} {
    colno += yyleng;
    return KW_NOT;
}

{kw_of} {
    colno += yyleng;
    return KW_OF;
}

{kw_or} {
    colno += yyleng;
    return KW_OR;
}

{kw_packed} {
    colno += yyleng;
    return KW_PACKED;
}

{kw_procedure} {
    colno += yyleng;
    return KW_PROCEDURE;
}

{kw_program} {
    colno += yyleng;
    return KW_PROGRAM;
}

{kw_record} {
    colno += yyleng;
    return KW_RECORD;
}

{kw_repeat} {
    colno += yyleng;
    return KW_REPEAT;
}

{kw_set} {
    colno += yyleng;
    return KW_SET;
}

{kw_then} {
    colno += yyleng;
    return KW_THEN;
}

{kw_to} {
    colno += yyleng;
    return KW_TO;
}

{kw_type} {
    colno += yyleng;
    return KW_TYPE;
}

{kw_until} {
    colno += yyleng;
    return KW_UNTIL;
}

{kw_var} {
    colno += yyleng;
    return KW_VAR;
}

{kw_while} {
    colno += yyleng;
    return KW_WHILE;
}

{kw_with} {
    colno += yyleng;
    return KW_WITH;
}


%{
/* SYS_CON */
%}

{sys_false} {
    colno += yyleng;
    LexLogger.print("SYS_CONST:").println(yytext);
    return SYS_FALSE;
}

{sys_maxint} {
    colno += yyleng;
    LexLogger.print("SYS_CONST:").println(yytext);
    return SYS_MAXINT;
}

{sys_true} {
    colno += yyleng;
    LexLogger.print("SYS_CONST:").println(yytext);
    return SYS_TRUE;
}


%{
/* SYS_FUNCT */
%}

{sys_abs} {
    colno += yyleng;
    return SYS_ABS;
}

{sys_chr} {
    colno += yyleng;
    return SYS_CHR;
}

{sys_odd} {
    colno += yyleng;
    return SYS_ODD;
}

{sys_ord} {
    colno += yyleng;
    return SYS_ORD;
}

{sys_pred} {
    colno += yyleng;
    return SYS_PRED;
}

{sys_sqr} {
    colno += yyleng;
    return SYS_SQR;
}

{sys_sqrt} {
    colno += yyleng;
    return SYS_SQRT;
}

{sys_succ} {
    colno += yyleng;
    return SYS_SUCC;
}


%{
/* SYS_PROC */
%}

{sys_write} {
    colno += yyleng;
    return SYS_WRITE;
}

{sys_writeln} {
    colno += yyleng;
    return SYS_WRITELN;
}


%{
/* SYS_TYPE */
%}

{sys_boolean} {
    colno += yyleng;
    return SYS_BOOLEAN;
}

{sys_char} {
    colno += yyleng;
    return SYS_CHAR;
}

{sys_integer} {
    colno += yyleng;
    return SYS_INTEGER;
}

{sys_real} {
    colno += yyleng;
    return SYS_REAL;
}

{sys_string} {
    colno += yyleng;
    return SYS_STRING;
}


%{
/* READ */
%}

{sys_read} {
    colno += yyleng;
    return SYS_READ;
}


%{
/* operator */
%}

{op_lp} {
    colno += yyleng;
    return OP_LP;
}

{op_rp} {
    colno += yyleng;
    return OP_RP;
}

{op_lb} {
    colno += yyleng;
    return OP_LB;
}

{op_rb} {
    colno += yyleng;
    return OP_RB;
}

{op_dot} {
    colno += yyleng;
    return OP_DOT;
}

{op_comma} {
    colno += yyleng;
    return OP_COMMA;
}

{op_colon} {
    colno += yyleng;
    return OP_COLON;
}

{op_plus} {
    colno += yyleng;
    return OP_PLUS;
}

{op_minus} {
    colno += yyleng;
    return OP_MINUS;
}

{op_mul} {
    colno += yyleng;
    return OP_MUL;
}

{op_div} {
    colno += yyleng;
    return OP_DIV;
}

{op_ge} {
    colno += yyleng;
    return OP_GE;
}

{op_gt} {
    colno += yyleng;
    return OP_GT;
}

{op_le} {
    colno += yyleng;
    return OP_LE;
}

{op_lt} {
    colno += yyleng;
    return OP_LT;
}

{op_equal} {
    colno += yyleng;
    return OP_EQUAL;
}

{op_unequal} {
    colno += yyleng;
    return OP_UNEQUAL;
}

{op_not} {
    colno += yyleng;
    return OP_NOT;
}

{op_assign} {
    colno += yyleng;
    return OP_ASSIGN;
}

{op_mod} {
    colno += yyleng;
    return OP_MOD;
}

{op_dotdot} {
    colno += yyleng;
    return OP_DOTDOT;
}

{op_semi} {
    colno += yyleng;
    return OP_SEMI;
}


%{
/* NAME: ID except keywords and system used tokens */
%}

{name} {
   yylval.node_name = new ASTNode_Name(yytext);
    colno += yyleng;
    LexLogger.print("NAME:").println(yytext);
    return NAME;
}

{const_real} {
    yylval.node_const = new ASTNode_ConstReal(atof(yytext));
    colno += yyleng;
    LexLogger.print("REAL:").println(yytext);
    return CONST_REAL;
}

{const_integer} {
    yylval.node_const = new ASTNode_ConstInteger(atoi(yytext));
    colno += yyleng;
    LexLogger.print("INTEGER:").println(yytext);
    return CONST_INTEGER;
}

{const_char} {
    yylval.node_const = new ASTNode_ConstCharacter(yytext[1]);
    colno += yyleng;
    LexLogger.print("CHAR:").println(yytext);
    return CONST_CHAR;
}

{const_string} {
    yylval.node_const = new ASTNode_ConstString(yytext);
    colno += yyleng;
    LexLogger.print("STRING:").println(yytext);
    return CONST_STRING;
}

{ws} {
    colno++;
}
{newline} {
    lineno++;
    colno = 1;
}

{unrecognized} {
    std::cerr << "Unrecognized symbol: \'" << yytext << "\' at line " << lineno << " col " << colno << std::endl;
    LexLogger.print("Unrecognized symbol: \'").print(yytext).print("\' at line ").print(std::to_string(lineno)).print(" col ").println(std::to_string(colno));
    exit(1);
}


%%

int yywrap()
{
    return 1;
}