#pragma once
#include "ast_base.hh"
#include "ast_const.hh"
#include "ast_type.hh"
#include "ast_variable.hh"
#include "ast_function.hh"
#include "ast_stmt.hh"

// Routine Head
// children:
// [nullable] 1 - ASTNode_ConstDeclList: const part
// [nullable] 2 - ASTNode_TypeDeclList: type part
// [nullable] 3 - ASTNode_VarDeclList: var part
// [nullable] 4 - ASTNode_RoutinePart: routine part
class ASTNode_RoutineHead : public ASTNode
{
public:
	ASTNode_ConstDeclList *const constPart;
	ASTNode_TypeDeclList *const typePart;
	ASTNode_VarDeclList *const varPart;
	ASTNode_RoutinePart *const routinePart;

	ASTNode_RoutineHead(ASTNode_ConstDeclList *constPart, ASTNode_TypeDeclList *typePart, ASTNode_VarDeclList *varPart, ASTNode_RoutinePart *routinePart)
		: constPart(constPart), typePart(typePart), varPart(varPart), routinePart(routinePart)
	{
		append(constPart);
		append(typePart);
		append(varPart);
		append(routinePart);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::RoutineHead; }
	void print() override { YaccLogger.println("RoutineHead"); }
};

// Routine
// children:
// 1 - ASTNode_RoutineHead
// 2 - ASTNode_RoutineBody
class ASTNode_Routine : public ASTNode
{
public:
	ASTNode_RoutineHead *const head;
	ASTNode_StmtCompound *const body;

	ASTNode_Routine(ASTNode_RoutineHead *head, ASTNode_StmtCompound *body)
		: head(head), body(body)
	{
		append(head);
		append(body);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::Routine; }
	void print() override { YaccLogger.println("Routine"); }
};

// Sub Routine (body of function)
// children:
// 1 - ASTNode_RoutineHead
// 2 - ASTNode_RoutineBody
class ASTNode_SubRoutine : public ASTNode
{
public:
	ASTNode_RoutineHead *const head;
	ASTNode_StmtCompound *const body;

	ASTNode_SubRoutine(ASTNode_RoutineHead *head, ASTNode_StmtCompound *body)
		: head(head), body(body)
	{
		append(head);
		append(body);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::SubRoutine; }
	void print() override { YaccLogger.println("SubRoutine"); }
};

// Program
// children:
// 1 - ASTNode_Routine
class ASTNode_Program : public ASTNode
{
	llvm::Function *setupMainFunction();

public:
	std::string name;
	ASTNode_Routine *const routine;

	ASTNode_Program(ASTNode_Name *pName, ASTNode_Routine *routine)
		: name(std::move(pName->name)), routine(routine)
	{
		delete pName;
		append(routine);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::Program; }
	void print() override { YaccLogger.println("Program " + name); }
};
