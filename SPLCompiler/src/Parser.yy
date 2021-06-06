%{
    #include <iostream>
    #include <limits.h>
    #include "ast.hh"
    extern int yylex(void);
    void yyerror(const char* s);
%}

%union
{
    class ASTNode* node;
    class ASTNode_Name* node_name;
    class ASTNode_Program* node_program;
    class ASTNode_Routine* node_routine;
    class ASTNode_SubRoutine* node_sub_routine;
    class ASTNode_RoutineHead* node_routine_head;

    class ASTNode_Const* node_const;
    class ASTNode_ConstExpr* node_const_expr;
    class ASTNode_ConstExprList* node_const_expr_list;

    class ASTNode_Type* node_type;
    class ASTNode_SimpleType* node_simple_type;
    class ASTNode_ArrayType* node_array_type;
    class ASTNode_RecordType* node_record_type;
    class ASTNode_TypeDecl* node_type_decl;
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

    class ASTNode_Expr* node_expr;
    class ASTNode_ExprList* node_expr_list;
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

%token <node_name> NAME
%token <node_const> CONST_REAL
%token <node_const> CONST_INTEGER
%token <node_const> CONST_CHAR
%token <node_const> CONST_STRING

%type <node_program> program
%type <node_name> program_head
%type <node_routine> routine
%type <node_sub_routine> sub_routine
%type <node_routine_head> routine_head

%type <node_name> sys_funct
%type <node_const> sys_con
%type <node_const> const_value
%type <node_const_expr> const_expr
%type <node_const_expr_list> const_expr_list
%type <node_const_expr_list> const_part

%type <node_type> type
%type <node_simple_type> sys_type
%type <node_simple_type> simple_type_decl
%type <node_array_type> array_type_decl
%type <node_record_type> record_type_decl
%type <node_type_decl> type_decl
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

%type <node_stmt_compound> routine_body
%type <node_stmt_compound> compound_stmt
%type <node_stmt_list> stmt_list
%type <node_stmt> stmt
%type <node_stmt> non_label_stmt

%type <node_stmt_assign> assign_stmt
%type <node_stmt_proc> proc_stmt
%type <node_name> sys_proc
%type <node_stmt_if> if_stmt
%type <node_stmt> else_clause
%type <node_stmt_repeat> repeat_stmt
%type <node_stmt_while> while_stmt
%type <node_stmt_for> for_stmt
%type <node_const> direction
%type <node_stmt_case> case_stmt
%type <node_stmt_goto> goto_stmt
%type <node_case_expr> case_expr
%type <node_case_expr_list> case_expr_list

%type <node_expr> expression
%type <node_expr> expr
%type <node_expr> term
%type <node_expr> factor
%type <node_arg_list> args_list
%type <node_arg_list> args

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
        ASTHandler::setASTHead($$);
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
        $$ = new ASTNode_Name("abs");
    }
    |SYS_CHR {
        $$ = new ASTNode_Name("chr");
    }
    |SYS_ODD {
        $$ = new ASTNode_Name("odd");
    }
    |SYS_ORD {
        $$ = new ASTNode_Name("ord");
    }
    |SYS_PRED {
        $$ = new ASTNode_Name("pred");
    }
    |SYS_SQR {
        $$ = new ASTNode_Name("sqr");
    }
    |SYS_SQRT {
        $$ = new ASTNode_Name("sqrt");
    }
    |SYS_SUCC {
        $$ = new ASTNode_Name("succ");
    }
    ;

sys_proc:
    SYS_WRITE {
        $$ = new ASTNode_Name("write");
    }
    |SYS_WRITELN {
        $$ = new ASTNode_Name("writeln");
    }
    |SYS_READ {
        $$ = new ASTNode_Name("read");
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
        $$ = new ASTNode_SubRoutine();
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
        $$ = new ASTNode_ConstExpr($1,$3);
    }
    ;

const_value:
    CONST_INTEGER {
        $$ = $1;
    }
    | CONST_REAL {
        $$ = $1;
    }
    | CONST_CHAR {
        $$ = $1;
    }
    | CONST_STRING {
        $$ = $1;
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
    type_decl_list type_decl {
        $$ = $1;
        $$->append($2);
    }
    | type_decl {
        $$ = new ASTNode_TypeDeclList();
        $$->append($1);
    }
    ;

type_decl:
    NAME OP_EQUAL type OP_SEMI {
        $$ = new ASTNode_TypeDecl($1,$3);
    }
    ;

type:
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
        $$ = new ASTNode_SimpleTypeEnumerate($2);
    }
    | const_value OP_DOTDOT const_value {
        $$ = new ASTNode_SimpleTypeSubrange($1,$3);
    }
    | OP_MINUS const_value OP_DOTDOT const_value {
        //TODO: is this OP_MINUS necessary? check it
        $$ = new ASTNode_SimpleTypeSubrange($2,$4);
    }
    | OP_MINUS const_value OP_DOTDOT OP_MINUS const_value {
        //TODO: is this OP_MINUS necessary? check it
        $$ = new ASTNode_SimpleTypeSubrange($2,$5);
    }
    | NAME OP_DOTDOT NAME {
        $$ = new ASTNode_SimpleTypeSubrange($1,$3);
    }
    ;

array_type_decl:
    KW_ARRAY OP_LB simple_type_decl OP_RB KW_OF type {
        $$ = new ASTNode_ArrayType($3,$6);
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
    name_list OP_COLON type OP_SEMI {
        $$ = new ASTNode_FieldDecl($1,$3);
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
    name_list OP_COLON type OP_SEMI {
        $$ = new ASTNode_VarDecl($1,$3);
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
        $$ = new ASTNode_ParaTypeList($1,$3);
    }
    | val_para_list OP_COLON simple_type_decl {
        $$ = new ASTNode_ParaTypeList($1,$3);
        }
    ;

var_para_list:
    KW_VAR name_list {
        $$ = new ASTNode_VarParaList($2);
    }
    ;

val_para_list:
    name_list {
        $$ = new ASTNode_ValParaList($1);
    }
    ;

routine_body:
    compound_stmt {
        $$ = $1;
    }
    ;

compound_stmt:
    KW_BEGIN stmt_list KW_END {
        $$ = new ASTNode_StmtCompound();
        $$->append($2);
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
        $$ = $1;
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
        $$ = new ASTNode_StmtAssign($1);
        $$->append($3);
    }
    | NAME OP_LB expression OP_RB OP_ASSIGN expression {
        $$ = new ASTNode_StmtAssign($1,$3);
        $$->append($3);
        $$->append($6);
    }
    | NAME OP_DOT NAME OP_ASSIGN expression {
        $$ = new ASTNode_StmtAssign($1,$3);
        $$->append($5);
    }
    ;

proc_stmt:
    NAME OP_LP args_list OP_RP {
        $$ = new ASTNode_StmtProc($1,false);
        $$->append($3);
    }
    | sys_proc OP_LP args_list OP_RP {
        $$ = new ASTNode_StmtProc($1,true);
        $$->append($3);
    }
    ;

if_stmt:
    KW_IF expression KW_THEN stmt else_clause {
        $$ = new ASTNode_StmtIf();
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
        $$ = new ASTNode_StmtRepeat();
        $$->append($2);
        $$->append($4);
    }
    ;

while_stmt:
    KW_WHILE expression KW_DO stmt {
        $$ = new ASTNode_StmtWhile();
        $$->append($2);
        $$->append($4);
    }
    ;

for_stmt:
    KW_FOR NAME OP_ASSIGN expression direction expression KW_DO stmt {
        $$ = new ASTNode_StmtFor($2,$5->get() == "true");
        $$->append($4);
        $$->append($6);
        $$->append($8);
    }
    ;

direction:
    KW_TO {
        $$ = new ASTNode_ConstBoolean(true);
    }
    | KW_DOWNTO {
        $$ = new ASTNode_ConstBoolean(false);
    }
    ;

case_stmt:
    KW_CASE expression KW_OF case_expr_list KW_END {
        $$ = new ASTNode_StmtCase();
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
        $$ = new ASTNode_CaseExprList();
        $$->append($1);
    }
    ;

case_expr:
    const_value OP_COLON stmt OP_SEMI {
        $$ = new ASTNode_CaseExpr();
        $$->append($1);
        $$->append($3);
    }
    | NAME OP_COLON stmt OP_SEMI {
        $$ = new ASTNode_CaseExpr();
        $$->append($1);
        $$->append($3);
    }
    | KW_ELSE stmt OP_SEMI {
        $$ = new ASTNode_CaseExpr();
        $$->append($2);
    }
    ;

goto_stmt:
    KW_GOTO CONST_INTEGER {
        $$ = new ASTNode_StmtGoto($2);
    }
    ;

expression:
    expression OP_GE expr {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::GE);
        $$->append($1);
        $$->append($3);
    }
    | expression OP_GT expr {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::GT);
        $$->append($1);
        $$->append($3);
    }
    | expression OP_LE expr {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::LE);
        $$->append($1);
        $$->append($3);
    }
    | expression OP_LT expr {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::LT);
        $$->append($1);
        $$->append($3);
    }
    | expression OP_EQUAL expr {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::EQUAL);
        $$->append($1);
        $$->append($3);
    }
    | expression OP_UNEQUAL expr {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::UNEQUAL);
        $$->append($1);
        $$->append($3);
    }
    | expr {
        $$ = $1;
    }
    ;

expr:
    expr OP_PLUS term {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::PLUS);
        $$->append($1);
        $$->append($3);
    }
    | expr OP_MINUS term {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::MINUS);
        $$->append($1);
        $$->append($3);
    }
    | expr KW_OR term {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::OR);
        $$->append($1);
        $$->append($3);
    }
    | term {
        $$ = $1;
    }
    ;

term:
    term OP_MUL factor {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::MUL);
        $$->append($1);
        $$->append($3);
    }
    | term OP_DIV factor {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::DIV);
        $$->append($1);
        $$->append($3);
    }
    | term OP_MOD factor {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::MOD);
        $$->append($1);
        $$->append($3);
    }
    | term KW_AND factor {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::AND);
        $$->append($1);
        $$->append($3);
    }
    | factor {
        $$ = $1;
    }
    ;

factor:
    NAME {
        $$ = new ASTNode_Operand($1,ASTNode_Operand::OperandType::Variable);
    }
    | NAME OP_LP args_list OP_RP {
        $$ = new ASTNode_Operand($1,ASTNode_Operand::OperandType::Function);
        $$->append($3);
    }
    | sys_funct OP_LP args_list OP_RP {
        $$ = new ASTNode_Operand($1,ASTNode_Operand::OperandType::SystemFunction);
        $$->append($3);
    }
    | const_value {
        $$ = new ASTNode_Operand("const",ASTNode_Operand::OperandType::Literal);
        $$->append($1);
    }
    | OP_LP expression OP_RP {
        $$ = $2;
    }
    | OP_NOT factor {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::NOT);
        $$->append($2);
    }
    | OP_MINUS factor {
        $$ = new ASTNode_Operator(ASTNode_Operator::OperatorType::UMINUS);
        $$->append($2);
    }
    | NAME OP_LB expression OP_RB {
        $$ = new ASTNode_Operand($1,ASTNode_Operand::OperandType::ArrayElement);
        $$->append($3);
    }
    | NAME OP_DOT NAME {
        $$ = new ASTNode_Operand($1,ASTNode_Operand::OperandType::RecordMember);
        $$->append($3);
    }
    ;

args_list:
    args {
        $$ = $1;
    }
    | %empty {
        $$ = new ASTNode_ArgList();
    }
    ;

args:
    args_list OP_COMMA expression {
        $$ = $1;
        $$->append($3);
        $$->count++;
    }
    | expression {
        $$ = new ASTNode_ArgList();
        $$->append($1);
        $$->count++;
    }
    ;

%%

void yyerror(const char* s)
{
    std::cerr << std::endl << s << std::endl;
    exit(1);
}