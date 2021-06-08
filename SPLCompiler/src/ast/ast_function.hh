#pragma once
#include "ast_base.hh"
#include "ast_type.hh"

class ASTNode_SubRoutine;

// Variable Parameter List
// children: none
class ASTNode_VarParaList : public ASTNode_NameList
{
public:
	ASTNode_VarParaList(ASTNode_NameList* pNode) : ASTNode_NameList(std::move(*pNode))
	{
		delete pNode;
	}

	std::string toString() override
	{
		return "var" + ASTNode_NameList::toString();
	}

	llvm::Value* codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::VarParaList; }
	void print() override { YaccLogger.println("VarParaList " + toString()); }
};


// Value Parameter List
// children: none
class ASTNode_ValParaList : public ASTNode_NameList
{
public:
	ASTNode_ValParaList(ASTNode_NameList* pNode) : ASTNode_NameList(std::move(*pNode))
	{
		delete pNode;
	}

	std::string toString() override
	{
		return ASTNode_NameList::toString();
	}

	llvm::Value* codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::ValParaList; }
	void print() override { YaccLogger.print("ValParaList " + toString()); }
};


// Parameter Type List
// children:
// 1 - ASTNode_NameList: parameter names
// 2 - ASTNode_SimpleType: parameter type
class ASTNode_ParaTypeList : public ASTNode
{
public:
	ASTNode_NameList* const list;
	ASTNode_SimpleType* const type;

	ASTNode_ParaTypeList(ASTNode_NameList* paraList, ASTNode_SimpleType* type)
		: list(paraList), type(type)
	{
		append(paraList);
		append(type);
	}

	llvm::Value* codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::ParaTypeList; }
	void print() override { YaccLogger.println("ParaTypeList " + list->toString() + " " + type->toString()); }
};


// Parameter Declaration List
// children:
// any - ASTNode_ParaTypeList
class ASTNode_ParaDeclList : public ASTNode
{
public:
	llvm::Value* codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::ParaDeclList; }
	void print() override { YaccLogger.println("ParaDeclList"); }
};


// Function Head
// children:
// 1 - ASTNode_ParaDeclList: parameters
// [nullable] 2 - ASTNode_SimpleType: return type
class ASTNode_FunctionHead : public ASTNode
{
public:
	std::string name;
	ASTNode_ParaDeclList* const parameters;
	ASTNode_SimpleType* const retType;

	ASTNode_FunctionHead(ASTNode_Name* pName, ASTNode_ParaDeclList* para, ASTNode_SimpleType* type)
		: name(std::move(pName->name)), parameters(para), retType(type)
	{
		delete pName;
		append(para);
		append(type);
	}

	llvm::Value* codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::FunctionHead; }
	void print() override { YaccLogger.println("FuncHead " + name); }
};


// Procedure Head
// children:
// 1 - ASTNode_ParaDeclList: parameters
// [null] 2 - ASTNode_SimpleType
class ASTNode_ProcedureHead : public ASTNode_FunctionHead
{
public:
	ASTNode_ProcedureHead(ASTNode_Name* pName, ASTNode_ParaDeclList* para)
		: ASTNode_FunctionHead(pName, para, nullptr)
	{	}

	// return procedure declaration
	llvm::Value* codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::ProcedureHead; }
	void print() override { YaccLogger.println("ProcHead " + name); }
};


// Function Declaration
// children:
// 1 - ASTNode_FunctionHead
// 2 - ASTNode_SubRoutine: function body
class ASTNode_FunctionDecl : public ASTNode
{
public:
	ASTNode_FunctionHead* const head;
	ASTNode_SubRoutine* const body;

	ASTNode_FunctionDecl(ASTNode_FunctionHead* head, ASTNode_SubRoutine* body)
		:head(head), body(body)
	{
		append(head);
		append(reinterpret_cast<ASTNode*>(body));
	}

	llvm::Value* codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::FunctionDecl; }
	void print() override { YaccLogger.println("FuncDecl"); }
};


// Procedure Declaration
// children:
// 1 - ASTNode_ProcedureHead
// 2 - ASTNode_SubRoutine: procedure body
class ASTNode_ProcedureDecl : public ASTNode_FunctionDecl
{
public:

	ASTNode_ProcedureDecl(ASTNode_ProcedureHead* head, ASTNode_SubRoutine* body)
		:ASTNode_FunctionDecl(head, body)
	{	}

	llvm::Value* codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::ProcedureDecl; }
	void print() override { YaccLogger.println("ProcDecl"); }
};


// Routine Part, or Function Declaration List
// children:
// any - ASTNode_FunctionDecl/ASTNode_ProcedureDecl
class ASTNode_RoutinePart : public ASTNode
{
public:

	llvm::Value* codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::RoutinePart; }
	void print() override { YaccLogger.println("RoutinePart"); }
};