#pragma once
#include "ast_base.hh"
#include <llvm/IR/Constants.h>

// Const base class
class ASTNode_Const : public ASTNode
{
public:
    virtual std::string toString() = 0;

    llvm::Constant* codeGen() override = 0;

    ASTNodeType getType() override { return ASTNodeType::Const; }
    void print() override { YaccLogger.println("ConstBase"); }
};

// Const Integer :i32 signed
// children: none
class ASTNode_ConstInteger : public ASTNode_Const
{
public:
    const int value;

    ASTNode_ConstInteger(const int val) : value(val) {}

    std::string toString() override
    {
        return std::to_string(value);
    }

    llvm::Constant* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::ConstInteger; }
    void print() override { YaccLogger.println("ConstInteger " + toString()); }
};

// Const Real :double
// children: none
class ASTNode_ConstReal : public ASTNode_Const
{
public:
    const double value;

    ASTNode_ConstReal(const double val) : value(val) {}

    std::string toString() override
    {
        return std::to_string(value);
    }

    llvm::Constant* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::ConstReal; }
    void print() override { YaccLogger.println("ConstReal " + toString()); }
};

// Const Character :i8 unsigned
// children: none
class ASTNode_ConstCharacter : public ASTNode_Const
{
public:
    const char value;

    ASTNode_ConstCharacter(const char val) : value(val) {}

    std::string toString() override
    {
        return std::to_string(value);
    }

    llvm::Constant* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::ConstCharacter; }
    void print() override { YaccLogger.println("ConstCharacter " + toString()); }
};

// Const String
// children: none
class ASTNode_ConstString : public ASTNode_Const
{
public:
    std::string value;

    ASTNode_ConstString(const char* val) : value(val) {}

    std::string toString() override
    {
        return value;
    }

    llvm::Constant* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::ConstString; }
    void print() override { YaccLogger.println("ConstString " + toString()); }
};

// Const Boolean :i1 unsigned
// children: none
class ASTNode_ConstBoolean : public ASTNode_Const
{
public:
    const bool value;

    ASTNode_ConstBoolean(const bool val) : value(val) {}

    std::string toString() override
    {
        return value ? "true" : "false";
    }

    llvm::Constant* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::ConstBoolean; }
    void print() override { YaccLogger.println("ConstBoolean " + toString()); }
};

// Constant Declaration
// children:
// 1 - ASTNode_Const: the value of constant declaration
class ASTNode_ConstDecl : public ASTNode
{
public:
    std::string name;
    ASTNode_Const* const value;

    ASTNode_ConstDecl(ASTNode_Name* pName, ASTNode_Const* value)
        : name(std::move(pName->name)), value(value)
    {
        delete pName;
        append(value);
    }

    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::ConstDecl; }
    void print() override { YaccLogger.println("ConstDecl " + name + " " + value->toString()); }
};

// Constant Declaration List
// children:
// any - ASTNode_ConstDecl
class ASTNode_ConstDeclList : public ASTNode
{
public:
    llvm::Value* codeGen() override;

    ASTNodeType getType() override { return ASTNodeType::ConstDeclList; }
    void print() override { YaccLogger.println("ConstExprList size " + std::to_string(children.size())); }
};
