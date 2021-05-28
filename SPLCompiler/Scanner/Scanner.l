%{
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
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
op_mod MOD
op_dotdot ".."
op_semi ";"


/* NAME: ID except keywords and system used tokens */
name [a-zA-Z][_a-zA-Z0-9]*

/* constants */
const_real [0-9]+(.[0-9]+)?
const_int [0-9]+
const_char '.*'

/* white space */
ws [ \t]+
newline \n

/* exception */
unrecognized .


%%



{const_real} {
    yylval = atof(yytext);
    return CONST_REAL
}
{const_int} {
    yylval = atoi(yytext);
    return CONST_INT;
}

{ws} ;
{newline} ;

{unrecognized} {
    printf("Unrecognized symbol: %s\n",yytext);
    exit(1);
}


%%
