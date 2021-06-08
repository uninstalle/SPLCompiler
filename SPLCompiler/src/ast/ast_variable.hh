#pragma once
#include "ast_base.hh"
#include "ast_type.hh"
#include <llvm/IR/Instructions.h>



// Variable Declaration
// children:
// 1 - ASTNode_NameList: variable names
// 2 - ASTNode_Type: type
class ASTNode_VarDecl : public ASTNode
{
public:
	ASTNode_NameList* const list;
	ASTNode_Type* const type;

	ASTNode_VarDecl(ASTNode_NameList* list, ASTNode_Type* type) : list(list), type(type)
	{
		append(list);
		append(type);
	}

	std::string toString() const
	{
		return list->toString() + " " + type->toString();
	}

	llvm::Value* codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::VarDecl; }
	void print() override { YaccLogger.println("VarDecl " + toString()); }
};


// Variable Declaration List
// children:
// any - ASTNode_VarDecl
class ASTNode_VarDeclList : public ASTNode
{
public:

	llvm::Value* codeGen() override;
	
	ASTNodeType getType() override { return ASTNodeType::VarDeclList; }
	void print() override { YaccLogger.println("VarDeclList"); }
};




// create an IR code that creates a variable of given type with given name,
// in the entry block of given function
llvm::AllocaInst* allocInEntryBlock(llvm::Function* fun, const std::string& varName, llvm::Type* type);
