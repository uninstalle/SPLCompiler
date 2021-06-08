#include "ast.hh"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>


llvm::Value *ASTNode_StmtCase::codeGen()
{
	// child 1, case condition expr
	llvm::Value *condV = dynamic_cast<ASTNode_Expr *>(child)->codeGen();
	if (!condV)
	{
		CodeGenLogger.println("Case stmt has invalid condition");
		return nullptr;
	}
	if (!condV->getType()->isIntegerTy())
	{
		CodeGenLogger.println("Case stmt expects integer condition");
		return nullptr;
	}

	// child 2, case expr list
	auto caseExprList = child->brother;
	auto caseExpr = caseExprList->child;

	int caseCount = 0;
	std::vector<std::pair<llvm::Constant *, llvm::BasicBlock *>> cases;
	auto fun = Builder.GetInsertBlock()->getParent();

	// create an empty case BB
	auto createCaseBB = [fun]
	{
		auto caseBB = llvm::BasicBlock::Create(TheContext, "case", fun);
		return caseBB;
	};

	ASTNode *defaultCaseStmt = nullptr;

	auto sw = Builder.CreateSwitch(condV, nullptr, caseCount);
	auto endBB = llvm::BasicBlock::Create(TheContext, "endcase");

	while (caseExpr)
	{
		caseCount++;
		auto caseVar = caseExpr->child;
		auto caseStmt = caseVar->brother;

		if (caseVar->getType() == ASTNodeType::ConstInteger ||
			caseVar->getType() == ASTNodeType::ConstCharacter ||
			caseVar->getType() == ASTNodeType::ConstBoolean)
		{
			// const literal
			auto v = dynamic_cast<ASTNode_Const *>(caseVar)->codeGen();

			auto bb = createCaseBB();
			Builder.SetInsertPoint(bb);
			auto caseV = dynamic_cast<ASTNode_Stmt *>(caseStmt)->codeGen();
			if (!caseV)
			{
				CodeGenLogger.println("case clause has invalid stmt");
				return nullptr;
			}
			Builder.CreateBr(endBB);
			cases.emplace_back(std::make_pair(v, bb));
		}
		else if (caseVar->getType() == ASTNodeType::Name)
		{
			auto name = dynamic_cast<ASTNode_Name *>(caseVar)->name;
			// const variable
			auto v = currentSymbolTable->getConstant(name);
			if (!v)
			{
				CodeGenLogger.println("Case clause const variable not found");
			}
			if (!v->getType()->isIntegerTy())
			{
				CodeGenLogger.println("Case clause expects integer");
				return nullptr;
			}
			auto bb = createCaseBB();
			Builder.SetInsertPoint(bb);
			auto caseV = dynamic_cast<ASTNode_Stmt *>(caseStmt)->codeGen();
			if (!caseV)
			{
				CodeGenLogger.println("case clause has invalid stmt");
				return nullptr;
			}
			Builder.CreateBr(endBB);
			cases.emplace_back(std::make_pair(v, bb));
		}
		else if (!caseStmt)
		{
			// only one child node, default branch, child 1 is stmt
			defaultCaseStmt = caseVar;
		}
		else
		{
			CodeGenLogger.println("case clause has invalid expr");
			return nullptr;
		}
		caseExpr = caseExpr->brother;
	}

	auto defaultBB = llvm::BasicBlock::Create(TheContext, "default", fun);
	Builder.SetInsertPoint(defaultBB);
	if (defaultCaseStmt)
	{
		auto caseV = dynamic_cast<ASTNode_Stmt *>(defaultCaseStmt)->codeGen();
		if (!caseV)
		{
			CodeGenLogger.println("case has invalid stmt");
			return nullptr;
		}
		Builder.CreateBr(endBB);
	}

	for (auto &c : cases)
		sw->addCase(reinterpret_cast<llvm::ConstantInt *>(c.first), c.second);
	sw->setDefaultDest(defaultBB);

	fun->getBasicBlockList().push_back(endBB);
	Builder.SetInsertPoint(endBB);

	return RetValZero;
}
