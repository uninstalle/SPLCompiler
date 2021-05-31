#pragma once
#include "log.hh"
#include <memory>
#include <string>
#include <vector>

class ASTNode;
extern ASTNode *ASTHead;
class ASTHandler;

class ASTNode
{
    friend ASTHandler;
    using pASTNode = std::shared_ptr<ASTNode>;

    pASTNode son = nullptr;
    pASTNode brother = nullptr;

public:
    ASTNode() = default;
    void append(ASTNode *node)
    {
        if (!node)
            return;
        if (!son)
            son = static_cast<pASTNode>(node);
        else
        {
            auto current = son;
            while (current->brother)
                current = current->brother;
            current->brother = static_cast<pASTNode>(node);
        }
    }
    virtual void print() { YaccLogger.println("Node_Base"); }
    virtual ~ASTNode() = default;
};


class ASTNode_Program : public ASTNode
{

    std::string programName;

public:
    ASTNode_Program(std::string name) : programName(name) {}
    void print() override
    {
        YaccLogger.println("Node_Program " + programName);
    }
};

class ASTNode_Routine : public ASTNode
{
};

class ASTNode_RoutineHead : public ASTNode
{
};

class ASTNode_Const : public ASTNode
{
protected:
    union
    {
        const int integer;
        const double real;
        const char character;
        const char *string;
        const bool boolean;
    } value;

public:
    ASTNode_Const(const int val) : value({.integer = val}) {}
    ASTNode_Const(const double val) : value({.real = val}) {}
    ASTNode_Const(const char val) : value({.character = val}) {}
    ASTNode_Const(const char *val) : value({.string = val}) {}
    ASTNode_Const(const bool val) : value({.boolean = val}) {}
    void print() override
    {
        YaccLogger.println("Node_Const");
    }
};

class ASTNode_ConstInteger : public ASTNode_Const
{
    const int &value = ASTNode_Const::value.integer;

public:
    ASTNode_ConstInteger(const int val) : ASTNode_Const(val) {}
    void print() override
    {
        YaccLogger.println("Node_ConstInteger " + std::to_string(value));
    }
};

class ASTNode_ConstReal : public ASTNode_Const
{
    const double &value = ASTNode_Const::value.real;

public:
    ASTNode_ConstReal(const double val) : ASTNode_Const(val) {}
    void print() override
    {
        YaccLogger.println("Node_ConstReal " + std::to_string(value));
    }
};

class ASTNode_ConstCharacter : public ASTNode_Const
{
    const char &value = ASTNode_Const::value.character;

public:
    ASTNode_ConstCharacter(const char val) : ASTNode_Const(val) {}
    void print() override
    {
        YaccLogger.println("Node_ConstCharacter " + std::to_string(value));
    }
};

class ASTNode_ConstString : public ASTNode_Const
{
    const char *&value = ASTNode_Const::value.string;

public:
    ASTNode_ConstString(const char *val) : ASTNode_Const(val) {}
    void print() override
    {
        YaccLogger.print("Node_ConstString ").println(value);
    }
};

class ASTNode_ConstBoolean : public ASTNode_Const
{
    const bool &value = ASTNode_Const::value.boolean;

public:
    ASTNode_ConstBoolean(const bool val) : ASTNode_Const(val) {}
    void print() override
    {
        YaccLogger.print("Node_ConstBoolean " + std::to_string(value));
    }
};

class ASTNode_ConstExpr : public ASTNode
{
    std::string constName;

public:
    ASTNode_ConstExpr(std::string name) : constName(name) {}
};

class ASTNode_ConstExprList : public ASTNode
{
};

class ASTNode_Type : public ASTNode
{
};

class ASTNode_SimpleType : public ASTNode_Type
{
};

class ASTNode_SimpleTypePlain : public ASTNode_SimpleType
{
    std::string typeName;

public:
    ASTNode_SimpleTypePlain(std::string type) : typeName(type) {}
};

class ASTNode_SimpleTypeEnumerate : public ASTNode_SimpleType
{
};

class ASTNode_SimpleTypeSubrange : public ASTNode_SimpleType
{
    std::string begin, end;

public:
    ASTNode_SimpleTypeSubrange() {}
    ASTNode_SimpleTypeSubrange(std::string begin, std::string end) : begin(begin), end(end) {}
};

class ASTNode_ArrayType : public ASTNode_Type
{
};

class ASTNode_RecordType : public ASTNode_Type
{
};

class ASTNode_TypeDef : public ASTNode
{
    std::string defName;

public:
    ASTNode_TypeDef(std::string name) : defName(name) {}
};

class ASTNode_TypeDeclList : public ASTNode
{
};

class ASTNode_NameList : public ASTNode
{
    std::vector<std::string> name_list;

public:
    void insert(std::string name)
    {
        name_list.push_back(name);
    }
};

class ASTNode_FieldDecl : public ASTNode
{
};

class ASTNode_FieldDeclList : public ASTNode
{
};

class ASTNode_VarDeclList : public ASTNode
{
};

class ASTNode_VarDecl : public ASTNode
{
};

class ASTNode_RoutinePart : public ASTNode
{
};

class ASTNode_FunctionDecl : public ASTNode
{
};

class ASTNode_FunctionHead : public ASTNode
{
    std::string functionName;

public:
    ASTNode_FunctionHead(std::string name) : functionName(name) {}
};

class ASTNode_ProcedureDecl : public ASTNode
{
};

class ASTNode_ProcedureHead : public ASTNode
{
    std::string procedureName;

public:
    ASTNode_ProcedureHead(std::string name) : procedureName(name) {}
};

class ASTNode_ParaDeclList : public ASTNode
{
};

class ASTNode_ParaTypeList : public ASTNode
{
};

class ASTNode_VarParaList : public ASTNode_NameList
{
};

class ASTNode_ValParaList : public ASTNode_NameList
{
};

class ASTNode_StmtList : public ASTNode
{
};

class ASTNode_Stmt : public ASTNode
{
    bool hasLabel;
    int label;

public:
    ASTNode_Stmt() : hasLabel(false), label(0) {}
    void setLabel(int label)
    {
        hasLabel = true;
        this->label = label;
    }
};

class ASTNode_Stmt_Assign : public ASTNode_Stmt
{
    std::string lvalueName;

public:
    ASTNode_Stmt_Assign(std::string name) : lvalueName(name) {}
};

class ASTNode_Stmt_Proc : public ASTNode_Stmt
{
    std::string procName;

public:
    ASTNode_Stmt_Proc(std::string name) : procName(name) {}
};

class ASTNode_Stmt_Compound : public ASTNode_Stmt
{
};

class ASTNode_Stmt_If : public ASTNode_Stmt
{
};

class ASTNode_Stmt_Repeat : public ASTNode_Stmt
{
};

class ASTNode_Stmt_While : public ASTNode_Stmt
{
};

class ASTNode_Stmt_For : public ASTNode_Stmt
{
    bool direction;

public:
    ASTNode_Stmt_For(bool dir) : direction(dir) {}
};

class ASTNode_Stmt_Case : public ASTNode_Stmt
{
};

class ASTNode_Stmt_Goto : public ASTNode_Stmt
{
    int gotoLabel;

public:
    ASTNode_Stmt_Goto(int label) : gotoLabel(label) {}
};

class ASTNode_Case_Expr : public ASTNode
{
    std::string caseVar;

public:
    ASTNode_Case_Expr() {}
    ASTNode_Case_Expr(std::string name) : caseVar(name) {}
};

class ASTNode_Case_Expr_List : public ASTNode
{
};

class ASTNode_Expr_List : public ASTNode
{
};

class ASTNode_Expr : public ASTNode
{
};

class ASTNode_Operator : public ASTNode_Expr
{
    std::string op;

public:
    ASTNode_Operator(std::string op) : op(op) {}
};

class ASTNode_Operand : public ASTNode_Expr
{
    std::string name;

public:
    ASTNode_Operand() {}
    ASTNode_Operand(std::string name) : name(name) {}
};

class ASTNode_ArgList : public ASTNode
{
};

class ASTHandler
{
public:
    static void print(ASTNode *head)
    {
        ASTNode *current = head;
        current->print();
        if (current->son)
            current = current->son.get();
        do
        {
            ASTHandler::print(current);
        } while (current->brother);
    }
};