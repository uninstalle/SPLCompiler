%{
    #include <iostream>
    #include <limits.h>
    #include "ast.hh"
    extern int yylex(void);
    void yyerror(const char* s);
%}

%union
{
	int integer;
	double real;
	char character;
    char *string;
    bool boolean;

    class ASTNode* node;

    class ASTNode_Program* node_program;
    class ASTNode_Routine* node_routine;
    class ASTNode_RoutineHead* node_routine_head;

    class ASTNode_Const* node_const;
    class ASTNode_ConstExpr* node_const_expr;
    class ASTNode_ConstExprList* node_const_expr_list;

    class ASTNode_Type* node_type;
    class ASTNode_SimpleType* node_simple_type;
    class ASTNode_ArrayType* node_array_type;
    class ASTNode_RecordType* node_record_type;
    class ASTNode_TypeDef* node_type_def;
    class ASTNode_TypeDeclList* node_type_decl_list;

    class ASTNode_NameList* node_name_list;

    class ASTNode_FieldDecl* node_field_decl;
    class ASTNode_FieldDeclList* node_field_decl_list;

    class ASTNode_VarDecl* node_var_decl;
    class ASTNode_VarDeclList* node_var_decl_list;

    class ASTNode_RoutinePart* node_routine_part;
    class ASTNode_FunctionDecl* node_function_decl;
    class ASTNode_FunctionHead* node_function_head;
    class ASTNode_ProcedureDecl* node_procedure_decl;
    class ASTNode_ProcedureHead* node_procedure_head;

    class ASTNode_ParaDeclList* node_para_decl_list;
    class ASTNode_ParaTypeList* node_para_type_list;
    class ASTNode_VarParaList* node_var_para_list;
    class ASTNode_ValParaList* node_val_para_list;

    class ASTNode_StmtList* node_stmt_list;
    class ASTNode_Stmt* node_stmt;
    class ASTNode_Stmt_Assign* node_stmt_assign;
    class ASTNode_Stmt_Proc* node_stmt_proc;
    class ASTNode_Stmt_If* node_stmt_if;
    class ASTNode_Stmt_Repeat* node_stmt_repeat;
    class ASTNode_Stmt_While* node_stmt_while;
    class ASTNode_Stmt_For* node_stmt_for;
    class ASTNode_Stmt_Case* node_stmt_case;
    class ASTNode_Stmt_Goto* node_stmt_goto;
    class ASTNode_Case_Expr* node_case_expr;
    class ASTNode_Case_Expr_List* node_case_expr_list;

    class ASTNode_Expr* node_expr;
    class ASTNode_Expr_List* node_expr_list;
    class ASTNode_Operator* node_operator;
    class ASTNode_operand* node_operand;
    class ASTNode_ArgList* node_arg_list;
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
%token <string> CONST_STRING

%type <node_program> program
%type <string> program_head
%type <node_routine> routine
%type <node_routine> sub_routine
%type <node_routine_head> routine_head

%type <string> sys_funct
%type <node_const> sys_con
%type <node_const> const_value
%type <node_const_expr> const_expr
%type <node_const_expr_list> const_expr_list
%type <node_const_expr_list> const_part

%type <node_type> type_decl
%type <node_simple_type> sys_type
%type <node_simple_type> simple_type_decl
%type <node_array_type> array_type_decl
%type <node_record_type> record_type_decl
%type <node_type_def> type_def
%type <node_type_decl_list> type_decl_list
%type <node_type_decl_list> type_part

%type <node_name_list> name_list
%type <node_field_decl> field_decl
%type <node_field_decl_list> field_decl_list

%type <node_var_decl> var_decl
%type <node_var_decl_list> var_decl_list
%type <node_var_decl_list> var_part

%type <node_routine_part> routine_part
%type <node_function_decl> function_decl
%type <node_function_head> function_head
%type <node_procedure_decl> procedure_decl
%type <node_procedure_head> procedure_head

%type <node_para_decl_list> parameters
%type <node_para_decl_list> para_decl_list
%type <node_para_type_list> para_type_list
%type <node_var_para_list> var_para_list
%type <node_val_para_list> val_para_list

%type <node_stmt_list> routine_body
%type <node_stmt_list> compound_stmt
%type <node_stmt_list> stmt_list
%type <node_stmt> stmt
%type <node_stmt> non_label_stmt

%type <node_stmt_assign> assign_stmt
%type <node_stmt_proc> proc_stmt
%type <node_stmt_proc> sys_proc
%type <node_stmt_if> if_stmt
%type <node_stmt> else_clause
%type <node_stmt_repeat> repeat_stmt
%type <node_stmt_while> while_stmt
%type <node_stmt_for> for_stmt
%type <boolean> direction
%type <node_stmt_case> case_stmt
%type <node_stmt_goto> goto_stmt
%type <node_case_expr> case_expr
%type <node_case_expr_list> case_expr_list

%type <node_expr> expression
%type <node_expr> expr
%type <node_expr> term
%type <node_expr> factor
%type <node_expr_list> expression_list
%type <node_arg_list> args_list

// fix s/r conflict of routine_part
%precedence EMPTY_ROUTINE_PART
%precedence KW_FUNCTION KW_PROCEDURE

// fix s/r conflict of if then else
%precedence KW_THEN
%precedence KW_ELSE 



%%

program:
    program_head routine OP_DOT {
        $$ = new ASTNode_Program($1);
        ASTHead = $$;
        $$->append($2);
    }
    ;

program_head:
    KW_PROGRAM NAME OP_SEMI {
        $$ = $2;
    }
    ;

keywords:
    KW_AND|KW_ARRAY|KW_BEGIN|KW_CASE|KW_CONST|KW_DIV|KW_DO|KW_DOWNTO|KW_ELSE|KW_END|KW_FOR|KW_FUNCTION|KW_GOTO|KW_IF|KW_IN|KW_MOD|KW_NOT|KW_OF|KW_OR|KW_PACKED|KW_PROCEDURE|KW_PROGRAM|KW_RECORD|KW_REPEAT|KW_SET|KW_THEN|KW_TO|KW_TYPE|KW_UNTIL|KW_VAR|KW_WHILE|KW_WITH;

sys_con:
    SYS_FALSE {
        $$ = new ASTNode_ConstBoolean(false);
    }
    |SYS_MAXINT {
        $$ = new ASTNode_ConstInteger(INT_MAX);
    }
    |SYS_TRUE {
        $$ = new ASTNode_ConstBoolean(true);
    }
    ;

sys_funct:
    SYS_ABS {
        $$ = "abs";
    }
    |SYS_CHR {
        $$ = "chr";
    }
    |SYS_ODD {
        $$ = "odd";
    }
    |SYS_ORD {
        $$ = "ord";
    }
    |SYS_PRED {
        $$ = "pred";
    }
    |SYS_SQR {
        $$ = "sqr";
    }
    |SYS_SQRT {
        $$ = "sqrt";
    }
    |SYS_SUCC {
        $$ = "succ";
    }
    ;

sys_proc:
    SYS_WRITE {
        $$ = new ASTNode_Stmt_Proc("write");
    }
    |SYS_WRITELN {
        $$ = new ASTNode_Stmt_Proc("writeln");
    }
    |SYS_READ {
        $$ = new ASTNode_Stmt_Proc("read");
    }
    ;

sys_type:
    SYS_BOOLEAN {
        $$ = new ASTNode_SimpleTypePlain("boolean");
    }
    |SYS_CHAR {
        $$ = new ASTNode_SimpleTypePlain("char");
    }
    |SYS_INTEGER {
        $$ = new ASTNode_SimpleTypePlain("integer");
    }
    |SYS_REAL {
        $$ = new ASTNode_SimpleTypePlain("real");
    }
    |SYS_STRING {
        $$ = new ASTNode_SimpleTypePlain("string");
    }
    ;
    

routine:
    routine_head routine_body {
        $$ = new ASTNode_Routine();
        $$->append($1);
        $$->append($2);
    }
    ;

sub_routine:
    routine_head routine_body {
        $$ = new ASTNode_Routine();
        $$->append($1);
        $$->append($2);
    }
    ;

routine_head:
    label_part const_part type_part var_part routine_part {
        $$ = new ASTNode_RoutineHead();
        $$->append($2);
        $$->append($3);
        $$->append($4);
        $$->append($5);
    }
    ;

label_part:
    %empty
    ;

const_part:
    KW_CONST const_expr_list {
        $$ = $2;
    }
    | %empty {
        $$ = nullptr;
    }
    ;

const_expr_list:
    const_expr_list const_expr {
        $$ = $1;
        $$->append($2);
    }
    | const_expr {
        $$ = new ASTNode_ConstExprList();
        $$->append($1);
    }
    ;

const_expr:
    NAME OP_EQUAL const_value OP_SEMI {
        $$ = new ASTNode_ConstExpr($1);
        $$->append($3);
    }
    ;

const_value:
    CONST_INTEGER {
        $$ = new ASTNode_ConstInteger($1);
    }
    | CONST_REAL {
        $$ = new ASTNode_ConstReal($1);
    }
    | CONST_CHAR {
        $$ = new ASTNode_ConstCharacter($1);
    }
    | CONST_STRING {
        $$ = new ASTNode_ConstString($1);
    }
    | sys_con {
        $$ = $1;
    }
    ;

type_part:
    KW_TYPE type_decl_list {
        $$ = $2;
    }
    | %empty {
        $$ = nullptr;
    }
    ;

type_decl_list:
    type_decl_list type_def {
        $$ = $1;
        $$->append($2);
    }
    | type_def {
        $$ = new ASTNode_TypeDeclList();
        $$->append($1);
    }
    ;

type_def:
    NAME OP_EQUAL type_decl OP_SEMI {
        $$ = new ASTNode_TypeDef($1);
        $$->append($3);
    }
    ;

type_decl:
    simple_type_decl {
        $$ = $1;
    }
    | array_type_decl {
        $$ = $1;
    }
    | record_type_decl {
        $$ = $1;
    }
    ;

simple_type_decl:
    sys_type {
        $$ = $1;
    }
    | NAME {
        $$ = new ASTNode_SimpleTypePlain($1);
    }
    | OP_LP name_list OP_RP {
        $$ = new ASTNode_SimpleTypeEnumerate();
        $$->append($2);
    }
    | const_value OP_DOTDOT const_value {
        $$ = new ASTNode_SimpleTypeSubrange();
        $$->append($1);
        $$->append($3);
    }
    | OP_MINUS const_value OP_DOTDOT const_value {
        //TODO: is this OP_MINUS necessary? check it
        $$ = new ASTNode_SimpleTypeSubrange();
        $$->append($2);
        $$->append($4);
    }
    | OP_MINUS const_value OP_DOTDOT OP_MINUS const_value {
        $$ = new ASTNode_SimpleTypeSubrange();
        $$->append($2);
        $$->append($5);
    }
    | NAME OP_DOTDOT NAME {
        $$ = new ASTNode_SimpleTypeSubrange($1,$3);
    }
    ;

array_type_decl:
    KW_ARRAY OP_LB simple_type_decl OP_RB KW_OF type_decl {
        $$ = new ASTNode_ArrayType();
        $$->append($3);
        $$->append($6);
    }
    ;

record_type_decl:
    KW_RECORD field_decl_list KW_END {
        $$ = new ASTNode_RecordType();
        $$->append($2);
    }
    ;

field_decl_list:
    field_decl_list field_decl {
        $$ = $1;
        $$->append($2);
    }
    | field_decl {
        $$ = new ASTNode_FieldDeclList();
        $$->append($1);
    }
    ;

field_decl:
    name_list OP_COLON type_decl OP_SEMI {
        $$ = new ASTNode_FieldDecl();
        $$->append($1);
        $$->append($3);
    }
    ;

name_list:
    name_list OP_COMMA NAME {
        $$ = $1;
        $$->insert($3);
    }
    | NAME {
        $$ = new ASTNode_NameList();
        $$->insert($1);
    }
    ;

var_part:
    KW_VAR var_decl_list {
        $$ = $2;
    }
    | %empty {
        $$ = nullptr;
    }
    ;

var_decl_list:
    var_decl_list var_decl {
        $$ = $1;
        $$->append($2);
    }
    | var_decl {
        $$ = new ASTNode_VarDeclList();
        $$->append($1);
    }
    ;

var_decl:
    name_list OP_COLON type_decl OP_SEMI {
        $$ = new ASTNode_VarDecl();
        $$->append($1);
        $$->append($3);
    }
    ;

routine_part:
    routine_part function_decl {
        $$ = $1;
        $$->append($2);
    }
    | routine_part procedure_decl {
        $$ = $1;
        $$->append($2);
    }
    | function_decl {
        $$ = new ASTNode_RoutinePart();
        $$->append($1);
    }
    | procedure_decl {
        $$ = new ASTNode_RoutinePart();
        $$->append($1);
    }
    | %empty %prec EMPTY_ROUTINE_PART {
        $$ = nullptr;
    }
    ;

function_decl:
    function_head OP_SEMI sub_routine OP_SEMI {
        $$ = new ASTNode_FunctionDecl();
        $$->append($1);
        $$->append($3);
    }
    ;

function_head:
    KW_FUNCTION NAME parameters OP_COLON simple_type_decl {
        $$ = new ASTNode_FunctionHead($2);
        $$->append($3);
        $$->append($5);
    }
    ;

procedure_decl:
    procedure_head OP_SEMI sub_routine OP_SEMI {
        $$ = new ASTNode_ProcedureDecl();
        $$->append($1);
        $$->append($3);
    }
    ;

procedure_head:
    KW_PROCEDURE NAME parameters {
        $$ = new ASTNode_ProcedureHead($2);
        $$->append($3);
    }
    ;

parameters:
    OP_LP para_decl_list OP_RP {
        $$ = $2;
    }
    | %empty {
        $$ = nullptr;
    }
    ;

para_decl_list:
    para_decl_list OP_SEMI para_type_list {
        $$ = $1;
        $$->append($3);
    }
    | para_type_list {
        $$ = new ASTNode_ParaDeclList();
        $$->append($1);
    }
    ;

para_type_list:
    var_para_list OP_COLON simple_type_decl {
        $$ = new ASTNode_ParaTypeList();
        $$->append($1);
        $$->append($3);
    }
    | val_para_list OP_COLON simple_type_decl {
        $$ = new ASTNode_ParaTypeList();
        $$->append($1);
        $$->append($3);
        }
    ;

var_para_list:
    KW_VAR name_list {
        $$ = new ASTNode_VarParaList();
        $$->append($2);
    }
    ;

val_para_list:
    name_list {
        $$ = new ASTNode_ValParaList();
        $$->append($1);
    }
    ;

routine_body:
    compound_stmt {
        $$ = $1;
    }
    ;

compound_stmt:
    KW_BEGIN stmt_list KW_END {
        $$ = $2;
    }
    ;

stmt_list:
    stmt_list stmt OP_SEMI {
        $$ = $1;
        $$->append($2);
    }
    | %empty {
        $$ = new ASTNode_StmtList();
    }
    ;

stmt:
    CONST_INTEGER OP_COLON non_label_stmt {
        $$ = $3;
        $$->setLabel($1);
    }
    | non_label_stmt {
        $$ = $1;
    }
    ;

non_label_stmt:
    assign_stmt {
        $$ = $1;
    }
    | proc_stmt {
        $$ = $1;
    }
    | compound_stmt {
        //TODO: fix recursive definition
        $$ = new ASTNode_Stmt_Compound();
        $$->append($1);
    }
    | if_stmt {
        $$ = $1;
    }
    | repeat_stmt {
        $$ = $1;
    }
    | while_stmt {
        $$ = $1;
    }
    | for_stmt {
        $$ = $1;
    }
    | case_stmt {
        $$ = $1;
    }
    | goto_stmt {
        $$ = $1;
    }
    ;

assign_stmt:
    NAME OP_ASSIGN expression {
        $$ = new ASTNode_Stmt_Assign($1);
        $$->append($3);
    }
    | NAME OP_LB expression OP_RB OP_ASSIGN expression {
        //TODO: array
        $$ = new ASTNode_Stmt_Assign($1);
        $$->append($6);
    }
    | NAME OP_DOT NAME OP_ASSIGN expression {
        //TODO: member
        $$ = new ASTNode_Stmt_Assign($1);
        $$->append($5);
    }
    ;

proc_stmt:
    NAME {
        $$ = new ASTNode_Stmt_Proc($1);
    }
    | NAME OP_LP args_list OP_RP {
        $$ = new ASTNode_Stmt_Proc($1);
        $$->append($3);
    }
    | sys_proc {
        $$ = $1;
    }
    | sys_proc OP_LP expression_list OP_RP {
        $$ = $1;
        $$->append($3);
    }
    ;

if_stmt:
    KW_IF expression KW_THEN stmt else_clause {
        $$ = new ASTNode_Stmt_If();
        $$->append($2);
        $$->append($4);
        $$->append($5);
    }
    ;

else_clause: 
    KW_ELSE stmt {
        $$ = $2;
    }
    | %empty %prec KW_THEN {
        $$ = nullptr;
    }
    ;

repeat_stmt:
    KW_REPEAT stmt_list KW_UNTIL expression {
        $$ = new ASTNode_Stmt_Repeat();
        $$->append($2);
        $$->append($4);
    }
    ;

while_stmt:
    KW_WHILE expression KW_DO stmt {
        $$ = new ASTNode_Stmt_While();
        $$->append($2);
        $$->append($4);
    }
    ;

for_stmt:
    KW_FOR NAME OP_ASSIGN expression direction expression KW_DO stmt {
        $$ = new ASTNode_Stmt_For($5);
        auto var = new ASTNode_Stmt_Assign($2);
        var->append($4);
        $$->append(var);
        $$->append($6);
        $$->append($8);
    }
    ;

direction:
    KW_TO {
        $$ = false;
    }
    | KW_DOWNTO {
        $$ = true;
    }
    ;

case_stmt:
    KW_CASE expression KW_OF case_expr_list KW_END {
        $$ = new ASTNode_Stmt_Case();
        $$->append($2);
        $$->append($4);
    }
    ;

case_expr_list:
    case_expr_list case_expr {
        $$ = $1;
        $$->append($2);
    }
    | case_expr {
        $$ = new ASTNode_Case_Expr_List();
        $$->append($1);
    }
    ;

case_expr:
    const_value OP_COLON stmt OP_SEMI {
        $$ = new ASTNode_Case_Expr();
        $$->append($1);
        $$->append($3);
    }
    | NAME OP_COLON stmt OP_SEMI {
        $$ = new ASTNode_Case_Expr($1);
        $$->append($3);
    }
    ;

goto_stmt:
    KW_GOTO CONST_INTEGER {
        $$ = new ASTNode_Stmt_Goto($2);
    }
    ;

expression_list:
    expression_list OP_COMMA expression {
        $$ = $1;
        $$->append($3);
    }
    | expression {
        $$ = new ASTNode_Expr_List();
        $$->append($1);
    }
    ;

expression:
    expression OP_GE expr {
        $$ = new ASTNode_Operator(">=");
        $$->append($1);
        $$->append($3);
    }
    | expression OP_GT expr {
        $$ = new ASTNode_Operator(">");
        $$->append($1);
        $$->append($3);
    }
    | expression OP_LE expr {
        $$ = new ASTNode_Operator("<=");
        $$->append($1);
        $$->append($3);
    }
    | expression OP_LT expr {
        $$ = new ASTNode_Operator("<");
        $$->append($1);
        $$->append($3);
    }
    | expression OP_EQUAL expr {
        $$ = new ASTNode_Operator("=");
        $$->append($1);
        $$->append($3);
    }
    | expression OP_UNEQUAL expr {
        $$ = new ASTNode_Operator("<>");
        $$->append($1);
        $$->append($3);
    }
    | expr {
        $$ = $1;
    }
    ;

expr:
    expr OP_PLUS term {
        $$ = new ASTNode_Operator("+");
        $$->append($1);
        $$->append($3);
    }
    | expr OP_MINUS term {
        $$ = new ASTNode_Operator("-");
        $$->append($1);
        $$->append($3);
    }
    | expr KW_OR term {
        $$ = new ASTNode_Operator("|");
        $$->append($1);
        $$->append($3);
    }
    | term {
        $$ = $1;
    }
    ;

term:
    term OP_MUL factor {
        $$ = new ASTNode_Operator("*");
        $$->append($1);
        $$->append($3);
    }
    | term OP_DIV factor {
        $$ = new ASTNode_Operator("/");
        $$->append($1);
        $$->append($3);
    }
    | term OP_MOD factor {
        $$ = new ASTNode_Operator("%");
        $$->append($1);
        $$->append($3);
    }
    | term KW_AND factor {
        $$ = new ASTNode_Operator("&");
        $$->append($1);
        $$->append($3);
    }
    | factor {
        $$ = $1;
    }
    ;

factor:
    NAME {
        $$ = new ASTNode_Operand($1);
    }
    | NAME OP_LP args_list OP_RP {
        //TODO: FUNCTION
        $$ = new ASTNode_Operand($1);
        $$->append($3);
    }
    | sys_funct {
        $$ = new ASTNode_Operand($1);
    }
    | sys_funct OP_LP args_list OP_RP {
        $$ = new ASTNode_Operand($1);
        $$->append($3);
    }
    | const_value {
        $$ = new ASTNode_Operand();
        $$->append($1);
    }
    | OP_LP expression OP_RP {
        $$ = new ASTNode_Operand();
        $$->append($2);
    }
    | OP_NOT factor {
        $$ = new ASTNode_Operator("!");
        $$->append($2);
    }
    | OP_MINUS factor {
        $$ = new ASTNode_Operator("--");
        $$->append($2);
    }
    | NAME OP_LB expression OP_RB {
        $$ = new ASTNode_Operand($1);
        $$->append($3);
    }
    | NAME OP_DOT NAME {
        //TODO: member
        $$ = new ASTNode_Operand($1);
    }
    ;

args_list:
    args_list OP_COMMA expression {
        $$ = $1;
        $$->append($3);
    }
    | expression {
        $$ = new ASTNode_ArgList();
        $$->append($1);
    }
    ;

%%

void yyerror(const char* s)
{
    std::cerr << std::endl << s << std::endl;
}