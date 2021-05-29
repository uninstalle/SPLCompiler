%{
    #include "Parser.h"
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
    return KW_AND;
}

{kw_array} {
    return KW_ARRAY;
}

{kw_begin} {
    return KW_BEGIN;
}

{kw_case} {
    return KW_CASE;
}

{kw_const} {
    return KW_CONST;
}

{kw_div} {
    return KW_DIV;
}

{kw_do} {
    return KW_DO;
}

{kw_downto} {
    return KW_DOWNTO;
}

{kw_else} {
    return KW_ELSE;
}

{kw_end} {
    return KW_END;
}

{kw_for} {
    return KW_FOR;
}

{kw_function} {
    return KW_FUNCTION;
}

{kw_goto} {
    return KW_GOTO;
}

{kw_if} {
    return KW_IF;
}

{kw_in} {
    return KW_IN;
}

{kw_mod} {
    return KW_MOD;
}

{kw_not} {
    return KW_NOT;
}

{kw_of} {
    return KW_OF;
}

{kw_or} {
    return KW_OR;
}

{kw_packed} {
    return KW_PACKED;
}

{kw_procedure} {
    return KW_PROCEDURE;
}

{kw_program} {
    return KW_PROGRAM;
}

{kw_record} {
    return KW_RECORD;
}

{kw_repeat} {
    return KW_REPEAT;
}

{kw_set} {
    return KW_SET;
}

{kw_then} {
    return KW_THEN;
}

{kw_to} {
    return KW_TO;
}

{kw_type} {
    return KW_TYPE;
}

{kw_until} {
    return KW_UNTIL;
}

{kw_var} {
    return KW_VAR;
}

{kw_while} {
    return KW_WHILE;
}

{kw_with} {
    return KW_WITH;
}


%{
/* SYS_CON */
%}

{sys_false} {
    return SYS_FALSE;
}

{sys_maxint} {
    return SYS_MAXINT;
}

{sys_true} {
    return SYS_TRUE;
}


%{
/* SYS_FUNCT */
%}

{sys_abs} {
    return SYS_ABS;
}

{sys_chr} {
    return SYS_CHR;
}

{sys_odd} {
    return SYS_ODD;
}

{sys_ord} {
    return SYS_ORD;
}

{sys_pred} {
    return SYS_PRED;
}

{sys_sqr} {
    return SYS_SQR;
}

{sys_sqrt} {
    return SYS_SQRT;
}

{sys_succ} {
    return SYS_SUCC;
}


%{
/* SYS_PROC */
%}

{sys_write} {
    return SYS_WRITE;
}

{sys_writeln} {
    return SYS_WRITELN;
}


%{
/* SYS_TYPE */
%}

{sys_boolean} {
    return SYS_BOOLEAN;
}

{sys_char} {
    return SYS_CHAR;
}

{sys_integer} {
    return SYS_INTEGER;
}

{sys_real} {
    return SYS_REAL;
}

{sys_string} {
    return SYS_STRING;
}


%{
/* READ */
%}

{sys_read} {
    return SYS_READ;
}


%{
/* operator */
%}

{op_lp} {
    return OP_LP;
}

{op_rp} {
    return OP_RP;
}

{op_lb} {
    return OP_LB;
}

{op_rb} {
    return OP_RB;
}

{op_dot} {
    return OP_DOT;
}

{op_comma} {
    return OP_COMMA;
}

{op_colon} {
    return OP_COLON;
}

{op_plus} {
    return OP_PLUS;
}

{op_minus} {
    return OP_MINUS;
}

{op_mul} {
    return OP_MUL;
}

{op_div} {
    return OP_DIV;
}

{op_ge} {
    return OP_GE;
}

{op_gt} {
    return OP_GT;
}

{op_le} {
    return OP_LE;
}

{op_lt} {
    return OP_LT;
}

{op_equal} {
    return OP_EQUAL;
}

{op_unequal} {
    return OP_UNEQUAL;
}

{op_not} {
    return OP_NOT;
}

{op_assign} {
    return OP_ASSIGN;
}

{op_mod} {
    return OP_MOD;
}

{op_dotdot} {
    return OP_DOTDOT;
}

{op_semi} {
    return OP_SEMI;
}


%{
/* NAME: ID except keywords and system used tokens */
%}

{name} {
    // TODO: copy the value
    yylval.string = yytext;
    return NAME;
}

{const_real} {
    yylval.real = atof(yytext);
    return CONST_REAL;
}

{const_integer} {
    yylval.integer = atoi(yytext);
    return CONST_INTEGER;
}

{const_char} {
    yylval.character = yytext[1];
    return CONST_CHAR;
}

{ws} ;
{newline} ;

{unrecognized} {
    printf("\nUnrecognized symbol: %s\n",yytext);
}


%%
