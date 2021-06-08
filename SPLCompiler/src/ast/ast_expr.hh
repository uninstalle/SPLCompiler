#pragma once
#include "ast_base.hh"
#include "ast_const.hh"

// Expr base class
class ASTNode_Expr : public ASTNode
{
public:
    llvm::Value* codeGen() override = 0;

    ASTNodeType getType() override { return ASTNodeType::Expr; }
    void print() override { YaccLogger.println("ExprBase"); }
};

// Arguments List
// children:
// any - ASTNode_Expr
class ASTNode_ArgList : public ASTNode
{
public:
    llvm::Value* codeGen() override { return nullptr; }

    ASTNodeType getType() override { return ASTNodeType::ArgList; }
    void print() override { YaccLogger.println("ArgList size " + std::to_string(children.size())); }
};

// Operator base class
class ASTNode_Operator : public ASTNode_Expr
{
protected:
    static bool intPromotion(llvm::Value*& LHS, llvm::Value*& RHS);
    static bool isInt(llvm::Value* val) { return val->getType()->isIntegerTy(); }
    static bool isDouble(llvm::Value* val) { return val->getType()->isDoubleTy(); }
    static unsigned getIntSize(llvm::Value* val) { return val->getType()->getIntegerBitWidth(); }

public:
    llvm::Value* codeGen() override = 0;

    ASTNodeType getType() override { return ASTNodeType::Operator; }
    void print() override { YaccLogger.println("OperatorBase"); }
};

// Operator Add
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorAdd : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorAdd(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorAdd; }
    void print() override { YaccLogger.println("Operator +"); }
};

// Operator Sub
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorSub : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorSub(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorSub; }
    void print() override { YaccLogger.println("Operator -"); }
};

// Operator Mul
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorMul : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorMul(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorMul; }
    void print() override { YaccLogger.println("Operator *"); }
};

// Operator Div
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorDiv : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorDiv(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorDiv; }
    void print() override { YaccLogger.println("Operator /"); }
};

// Operator Mod
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorMod : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorMod(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorMod; }
    void print() override { YaccLogger.println("Operator %"); }
};

// Operator Minus
// children:
// 1 - ASTNode_Expr: LHS
class ASTNode_OperatorMinus : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;

public:
    ASTNode_OperatorMinus(ASTNode_Expr* LHS) : LHS(LHS)
    {
        append(LHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorMinus; }
    void print() override { YaccLogger.println("Operator unary -"); }
};

// Operator Greater or equal
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorGE : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorGE(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorGE; }
    void print() override { YaccLogger.println("Operator >="); }
};

// Operator Greater than
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorGT : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorGT(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorGT; }
    void print() override { YaccLogger.println("Operator >"); }
};

// Operator Less or equal
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorLE : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorLE(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorLE; }
    void print() override { YaccLogger.println("Operator <="); }
};

// Operator Less than
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorLT : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorLT(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorLT; }
    void print() override { YaccLogger.println("Operator <"); }
};

// Operator Equal
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorEQ : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorEQ(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorEQ; }
    void print() override { YaccLogger.println("Operator =="); }
};

// Operator Not equal
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorNE : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorNE(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorNE; }
    void print() override { YaccLogger.println("Operator !="); }
};

// Operator And
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorAnd : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorAnd(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorAnd; }
    void print() override { YaccLogger.println("Operator &"); }
};

// Operator Or
// children:
// 1 - ASTNode_Expr: LHS
// 2 - ASTNode_Expr: RHS
class ASTNode_OperatorOr : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;
    ASTNode_Expr* const RHS;

public:
    ASTNode_OperatorOr(ASTNode_Expr* LHS, ASTNode_Expr* RHS) : LHS(LHS), RHS(RHS)
    {
        append(LHS);
        append(RHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorOr; }
    void print() override { YaccLogger.println("Operator |"); }
};

// Operator Not
// children:
// 1 - ASTNode_Expr: LHS
class ASTNode_OperatorNot : public ASTNode_Operator
{
    ASTNode_Expr* const LHS;

public:
    ASTNode_OperatorNot(ASTNode_Expr* LHS) : LHS(LHS)
    {
        append(LHS);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperatorNot; }
    void print() override { YaccLogger.println("Operator !"); }
};

// Operand base class
class ASTNode_Operand : public ASTNode_Expr
{
public:
    llvm::Value* codeGen() override = 0;

    ASTNodeType getType() override { return ASTNodeType::Operand; }
    void print() override { YaccLogger.println("OperandBase"); }
};

// Operand Literal
// children:
// 1 - ASTNode_Const: literal
class ASTNode_OperandLiteral : public ASTNode_Operand
{
public:
    ASTNode_Const* const literal;

    ASTNode_OperandLiteral(ASTNode_Const* node) : literal(node)
    {
        append(node);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperandLiteral; }
    void print() override { YaccLogger.println("Operand Literal " + literal->toString()); }
};

// Operand Variable
// children: none
class ASTNode_OperandVariable : public ASTNode_Operand
{
public:
    std::string name;

    ASTNode_OperandVariable(ASTNode_Name* pName) : name(std::move(pName->name))
    {
        delete pName;
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperandVariable; }
    void print() override { YaccLogger.println("Operand Variable " + name); }
};

// Operand Function
// children:
// 1 - ASTNode_ArgList: args to call the function
class ASTNode_OperandFunction : public ASTNode_Operand
{
public:
    std::string name;
    ASTNode_ArgList* const args;

    ASTNode_OperandFunction(ASTNode_Name* pName, ASTNode_ArgList* args)
        : name(std::move(pName->name)), args(args)
    {
        delete pName;
        append(args);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperandFunction; }
    void print() override { YaccLogger.println("Operand Function " + name); }
};

// Operand System Function
// children:
// 1 - ASTNode_ArgList: args to call the function
class ASTNode_OperandSystemFunction : public ASTNode_Operand
{
public:
    std::string name;
    ASTNode_ArgList* const args;

    ASTNode_OperandSystemFunction(ASTNode_Name* pName, ASTNode_ArgList* args)
        : name(std::move(pName->name)), args(args)
    {
        delete pName;
        append(args);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperandSystemFunction; }
    void print() override { YaccLogger.println("Operand System Function " + name); }
};

// Operand Array Element
// children:
// 1 - ASTNode_Expr: index of the array element
class ASTNode_OperandArrayElement : public ASTNode_Operand
{
public:
    std::string name;
    ASTNode_Expr* const index;

    ASTNode_OperandArrayElement(ASTNode_Name* pName, ASTNode_Expr* index)
        : name(std::move(pName->name)), index(index)
    {
        delete pName;
        append(index);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperandArrayElement; }
    void print() override { YaccLogger.println("Operand Array Element " + name + "[]"); }
};

// Operand Record Member
// children:
// 1 - ASTNode_Expr: index of the array element
class ASTNode_OperandRecordMember : public ASTNode_Operand
{
public:
    std::string name;
    std::string memberName;

    ASTNode_OperandRecordMember(ASTNode_Name* pName, ASTNode_Name* pMember)
        : name(std::move(pName->name)), memberName(std::move(pName->name))
    {
        delete pName;
        delete pMember;
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::OperandRecordMember; }
    void print() override { YaccLogger.println("Operand Record Member " + name + "." + memberName); }
};
