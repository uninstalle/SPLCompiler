#pragma once
#include "../logger/logger.hh"
#include <vector>
#include <llvm/IR/Value.h>

enum class ASTNodeType
{
    Base,
    Name,

    Const,
    ConstInteger,
    ConstReal,
    ConstCharacter,
    ConstString,
    ConstBoolean,
    ConstDecl,
    ConstDeclList,

    Expr,
    ArgList,
    Operator,
    OperatorAdd,
    OperatorSub,
    OperatorMul,
    OperatorDiv,
    OperatorMod,
    OperatorMinus,
    OperatorGE,
    OperatorGT,
    OperatorLE,
    OperatorLT,
    OperatorEQ,
    OperatorNE,
    OperatorAnd,
    OperatorOr,
    OperatorNot,

    Operand,
    OperandLiteral,
    OperandVariable,
    OperandFunction,
    OperandSystemFunction,
    OperandArrayElement,
    OperandRecordMember,

    Type,
    SimpleType,
    SimpleTypePlain,
    NameList,
    SimpleTypeEnumerate,
    SimpleTypeSubRange,
    ArrayType,
    FieldDecl,
    FieldDeclList,
    RecordType,
    TypeDecl,
    TypeDeclList,

    VarParaList,
    ValParaList,
    ParaTypeList,
    ParaDeclList,
    FunctionHead,
    ProcedureHead,
    FunctionDecl,
    ProcedureDecl,

    VarDecl,
    VarDeclList,

    Stmt,
    StmtList,
    StmtCompound,
    StmtAssign,
    StmtAssignSimpleType,
    StmtAssignArrayType,
    StmtAssignRecordType,
    StmtProc,
    StmtSysProc,
    StmtIf,
    StmtRepeat,
    StmtWhile,
    StmtFor,
    CaseExpr,
    CaseExprLiteral,
    CaseExprConstVar,
    CaseExprDefault,
    CaseExprList,
    StmtCase,
    StmtGoto,

    RoutinePart,
    RoutineHead,
    Routine,
    SubRoutine,
    Program
};

// Node base class
// Free all memory of its children nodes when get deleted.
// This leads to a cascading delete of AST. Thus it doesn't
// support copy construction or assignment.
class ASTNode
{
public:
    std::vector<ASTNode*> children;

    ASTNode() = default;
    ASTNode(const ASTNode& node) = delete;
    ASTNode(ASTNode&& node) = delete;
    ASTNode& operator=(const ASTNode& node) = delete;
    ASTNode& operator=(ASTNode&& node) = delete;

    // send msg to CodeGenLogger and return nullptr
    static llvm::Value* logAndReturn(const std::string& msg);

    void append(ASTNode* node)
    {
        if (node)
            children.push_back(node);
    }

    virtual llvm::Value* codeGen() = 0;
    virtual ASTNodeType getType() { return ASTNodeType::Base; }
    virtual void print() { YaccLogger.print("BaseNode"); }

    virtual ~ASTNode()
    {
        for (auto node : children)
            delete node;
    }
};

// Name
// Simply a wrapper of a name string. Normally it should not
// exist as a node in AST. AST nodes that use Name node as
// a parameter of constructor will delete the node after
// the construction.
class ASTNode_Name : public ASTNode
{
public:
    std::string name;

    ASTNode_Name(std::string name) : name(std::move(name)) {}

    llvm::Value* codeGen() override { return nullptr; }
    ASTNodeType getType() override { return ASTNodeType::Name; }
    void print() override { YaccLogger.println("Name " + name); }
};
