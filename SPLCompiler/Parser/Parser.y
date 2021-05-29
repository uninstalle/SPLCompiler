%{
    #include <stdio.h>

    extern int yylex(void);
    extern int yyparse(void);
    void yyerror(const char* s);
    int yydebug = 1;
%}

%union
{
	int integer;
	double real;
	char character;
    char *string;
}

%token
KW_AND
KW_ARRAY
KW_BEGIN
KW_CASE
KW_CONST
KW_DIV
KW_DO
KW_DOWNTO
KW_ELSE
KW_END
KW_FOR
KW_FUNCTION
KW_GOTO
KW_IF
KW_IN
KW_MOD
KW_NOT
KW_OF
KW_OR
KW_PACKED
KW_PROCEDURE
KW_PROGRAM
KW_RECORD
KW_REPEAT
KW_SET
KW_THEN
KW_TO
KW_TYPE
KW_UNTIL
KW_VAR
KW_WHILE
KW_WITH
SYS_FALSE
SYS_MAXINT
SYS_TRUE
SYS_ABS
SYS_CHR
SYS_ODD
SYS_ORD
SYS_PRED
SYS_SQR
SYS_SQRT
SYS_SUCC
SYS_WRITE
SYS_WRITELN
SYS_BOOLEAN
SYS_CHAR
SYS_INTEGER
SYS_REAL
SYS_STRING
SYS_READ
OP_LP
OP_RP
OP_LB
OP_RB
OP_DOT
OP_COMMA
OP_COLON
OP_PLUS
OP_MINUS
OP_MUL
OP_DIV
OP_GE
OP_GT
OP_LE
OP_LT
OP_EQUAL
OP_UNEQUAL
OP_NOT
OP_ASSIGN
OP_MOD
OP_DOTDOT
OP_SEMI

%token <string> NAME
%token <real> CONST_REAL
%token <integer> CONST_INTEGER
%token <character> CONST_CHAR

// fix s/r conflict of routine_part
%precedence EMPTY_ROUTINE_PART
%precedence KW_FUNCTION KW_PROCEDURE

// fix s/r conflict of if then else
%precedence KW_THEN
%precedence KW_ELSE 



%%

program:
    program_head routine OP_DOT
    ;

program_head:
    KW_PROGRAM NAME OP_SEMI
    ;

keywords:
    KW_AND|KW_ARRAY|KW_BEGIN|KW_CASE|KW_CONST|KW_DIV|KW_DO|KW_DOWNTO|KW_ELSE|KW_END|KW_FOR|KW_FUNCTION|KW_GOTO|KW_IF|KW_IN|KW_MOD|KW_NOT|KW_OF|KW_OR|KW_PACKED|KW_PROCEDURE|KW_PROGRAM|KW_RECORD|KW_REPEAT|KW_SET|KW_THEN|KW_TO|KW_TYPE|KW_UNTIL|KW_VAR|KW_WHILE|KW_WITH;

sys_con:
    SYS_FALSE|SYS_MAXINT|SYS_TRUE;

sys_funct:
    SYS_ABS|SYS_CHR|SYS_ODD|SYS_ORD|SYS_PRED|SYS_SQR|SYS_SQRT|SYS_SUCC;

sys_proc:
    SYS_WRITE|SYS_WRITELN|SYS_READ;

sys_type:
    SYS_BOOLEAN|SYS_CHAR|SYS_INTEGER|SYS_REAL;
    

routine:
    routine_head routine_body
    ;

sub_routine:
    routine_head routine_body
    ;

routine_head:
    label_part const_part type_part var_part routine_part
    ;

label_part:
    %empty
    ;

const_part:
    KW_CONST const_expr_list
    | %empty
    ;

const_expr_list:
    const_expr_list NAME OP_EQUAL const_value OP_SEMI
    | NAME OP_EQUAL const_value OP_SEMI
    ;

const_value:
    CONST_INTEGER
    | CONST_REAL
    | CONST_CHAR
    | SYS_STRING
    | sys_con
    ;

type_part:
    KW_TYPE type_decl_list
    | %empty
    ;

type_decl_list:
    type_decl_list type_definition
    | type_definition
    ;

type_definition:
    NAME OP_EQUAL  type_decl OP_SEMI
    ;

type_decl:
    simple_type_decl
    | array_type_decl
    | record_type_decl
    ;

simple_type_decl:
    sys_type
    | NAME
    | OP_LP name_list OP_RP
    | const_value OP_DOTDOT const_value
    | OP_MINUS const_value OP_DOTDOT const_value
    | OP_MINUS const_value OP_DOTDOT OP_MINUS const_value
    | NAME OP_DOTDOT NAME
    ;

array_type_decl:
    KW_ARRAY OP_LB simple_type_decl OP_RB KW_OF type_decl
    ;

record_type_decl:
    KW_RECORD field_decl_list KW_END
    ;

field_decl_list:
    field_decl_list field_decl 
    | field_decl
    ;

field_decl:
    name_list OP_COLON type_decl OP_SEMI
    ;

name_list:
    name_list OP_COMMA NAME
    | NAME
    ;

var_part:
    KW_VAR var_decl_list
    | %empty
    ;

var_decl_list:
    var_decl_list var_decl
    | var_decl
    ;

var_decl:
    name_list OP_COLON type_decl OP_SEMI
    ;

routine_part:
    routine_part function_decl
    | routine_part procedure_decl
    | function_decl
    | procedure_decl
    | %empty %prec EMPTY_ROUTINE_PART
    ;

function_decl:
    function_head OP_SEMI sub_routine OP_SEMI
    ;

function_head:
    KW_FUNCTION NAME parameters OP_COLON simple_type_decl
    ;

procedure_decl:
    procedure_head OP_SEMI sub_routine OP_SEMI
    ;

procedure_head:
    KW_PROCEDURE NAME parameters
    ;

parameters:
    OP_LP para_decl_list OP_RP
    | %empty
    ;

para_decl_list:
    para_decl_list OP_SEMI para_type_list
    | para_type_list
    ;

para_type_list:
    var_para_list OP_COLON simple_type_decl  
    | val_para_list OP_COLON simple_type_decl
    ;

var_para_list:
    KW_VAR name_list
    ;

val_para_list:
    name_list
    ;

routine_body:
    compound_stmt
    ;

compound_stmt:
    KW_BEGIN stmt_list KW_END
    ;

stmt_list:
    stmt_list stmt OP_SEMI 
    | %empty
    ;

stmt:
    CONST_INTEGER OP_COLON non_label_stmt 
    | non_label_stmt
    ;

non_label_stmt:
    assign_stmt
    | proc_stmt
    | compound_stmt
    | if_stmt
    | repeat_stmt
    | while_stmt
    | for_stmt
    | case_stmt
    | goto_stmt
    ;

assign_stmt:
    NAME OP_ASSIGN expression
    | NAME OP_LB expression OP_RB OP_ASSIGN expression
    | NAME OP_DOT NAME OP_ASSIGN expression
    ;

proc_stmt:
    NAME
    | NAME OP_LP args_list OP_RP
    | sys_proc
    | sys_proc OP_LP expression_list OP_RP
    ;

if_stmt:
    KW_IF expression KW_THEN stmt else_clause
    ;

else_clause: 
    KW_ELSE stmt
    | %empty %prec KW_THEN
    ;

repeat_stmt:
    KW_REPEAT stmt_list KW_UNTIL expression
    ;

while_stmt:
    KW_WHILE expression KW_DO stmt
    ;

for_stmt:
    KW_FOR NAME OP_ASSIGN expression direction expression KW_DO stmt
    ;

direction:
    KW_TO
    | KW_DOWNTO
    ;

case_stmt:
    KW_CASE expression KW_OF case_expr_list KW_END
    ;

case_expr_list:
    case_expr_list case_expr
    | case_expr
    ;

case_expr:
    const_value OP_COLON stmt OP_SEMI
    | NAME OP_COLON stmt OP_SEMI
    ;

goto_stmt:
    KW_GOTO CONST_INTEGER
    ;

expression_list:
    expression_list OP_COMMA expression
    | expression
    ;

expression:
    expression OP_GE expr
    | expression OP_GT expr
    | expression OP_LE expr
    | expression OP_LT expr
    | expression OP_EQUAL expr
    | expression OP_UNEQUAL expr
    | expr
    ;

expr:
    expr OP_PLUS term
    | expr OP_MINUS term
    | expr KW_OR term
    | term
    ;

term:
    term OP_MUL factor
    | term OP_DIV factor
    | term OP_MOD factor 
    | term KW_AND factor
    | factor
    ;

factor:
    NAME
    | NAME OP_LP args_list OP_RP
    | sys_funct
    | sys_funct OP_LP args_list OP_RP
    | const_value
    | OP_LP expression  OP_RP
    | OP_NOT factor 
    | OP_MINUS factor
    | NAME OP_LB expression OP_RB
    | NAME OP_DOT NAME
    ;

args_list:
    args_list OP_COMMA expression 
    | expression
    ;

%%

