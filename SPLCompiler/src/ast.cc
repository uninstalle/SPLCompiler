#include "ast.hh"
#include "table.hh"
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

const std::string ASTNode_Operator::OperatorString[] = {
		">=",
		">",
		"<=",
		"<",
		"=",
		"<>",
		"+",
		"-",
		"|",
		"*",
		"/",
		"&",
		"!",
		"-",
		"."
};

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<llvm::Module> TheModule;
static std::map<std::string, llvm::Value*> NamedValues;

ASTNode* ASTHead = nullptr;

llvm::Value* ASTNode_ConstInteger::codeGen()
{
	return llvm::ConstantInt::get(TheContext, llvm::APSInt(value));
}


llvm::Value* ASTNode_ConstReal::codeGen()
{
	return llvm::ConstantFP::get(TheContext, llvm::APFloat(value));
}

llvm::Value* ASTNode_ConstCharacter::codeGen()
{
	return llvm::ConstantInt::get(TheContext, llvm::APSInt(value));
}

llvm::Value* ASTNode_ConstBoolean::codeGen()
{
	return llvm::ConstantInt::get(TheContext, llvm::APSInt(value));
}

llvm::Value* ASTNode_ConstString::codeGen()
{
	//TODO
}

llvm::Type* ASTNode_SimpleTypePlain::codeGen()
{
	//TODO
}

llvm::Type* ASTNode_SimpleTypeEnumerate::codeGen()
{
	//TODO
}

llvm::Type* ASTNode_SimpleTypeSubrange::codeGen()
{
	//TODO
}

llvm::Type* ASTNode_ArrayType::codeGen()
{
	//TODO
}

llvm::Type* ASTNode_RecordType::codeGen()
{
	//TODO
}


llvm::Value* ASTNode_Operand::codeGen()
{
	//TODO
}


llvm::Value* ASTNode_Operator::codeGen()
{
	bool isUnary = false;
	llvm::Value* L = dynamic_cast<ASTNode_Expr*>(child)->codeGen();
	llvm::Value* R = nullptr;
	if (!L)
		return nullptr;
	if (child->brother)
		R = dynamic_cast<ASTNode_Expr*>(child->brother)->codeGen();
	else
		isUnary = true;

	// int promotion
	auto intPromotion = [&L, &R]() {
		if (L->getType()->isIntegerTy() && R->getType()->isFloatingPointTy())
			L = Builder.CreateSIToFP(L, llvm::Type::getDoubleTy(TheContext), "sitofp");
		if (L->getType()->isIntegerTy() && R->getType()->isFloatingPointTy())
			R = Builder.CreateSIToFP(R, llvm::Type::getDoubleTy(TheContext), "sitofp");
	};

	if (isUnary)
	{

		if (L->getType()->isIntegerTy())
		{
			// unary int
			switch (op)
			{
			case OPERATOR::MINUS:
				return Builder.CreateSub(llvm::ConstantInt::get(TheContext, llvm::APSInt(0)), L, "subtmp");

			case OPERATOR::NOT:
				return Builder.CreateNot(L, "nottmp");

			default:
				CodeGenLogger.println("Invalid int unary operator" + stringOf(op));
				return nullptr;
			}
		}
		else if (L->getType()->isFloatingPointTy())
		{
			// unary float
			switch (op)
			{
			case OPERATOR::MINUS:
				return Builder.CreateFNeg(L, "fnegtmp");

			case OPERATOR::NOT:
				return Builder.CreateNot(L, "nottmp");

			default:
				CodeGenLogger.println("Invalid float unary operator" + stringOf(op));
				return nullptr;
			}
		}
		else
		{
			CodeGenLogger.println("Invalid type for operator " + stringOf(op));
			return nullptr;
		}
	}
	else
	{
		intPromotion();

		if (L->getType()->isIntegerTy() && R->getType()->isIntegerTy())
		{
			// binary int
			switch (op)
			{
			case OPERATOR::PLUS:
				return Builder.CreateAdd(L, R, "addtmp");
			case OPERATOR::MINUS:
				return Builder.CreateSub(L, R, "subtmp");
			case OPERATOR::MUL:
				return Builder.CreateMul(L, R, "multmp");
			case OPERATOR::DIV:
				return Builder.CreateSDiv(L, R, "divtmp");
			case OPERATOR::MOD:
				return Builder.CreateSRem(L, R, "divtmp");

			case OPERATOR::GE:
				return Builder.CreateICmpSGE(L, R, "cmpgetmp");
			case OPERATOR::GT:
				return Builder.CreateICmpSGT(L, R, "cmpgttmp");
			case OPERATOR::LE:
				return Builder.CreateICmpSLE(L, R, "cmpletmp");
			case OPERATOR::LT:
				return Builder.CreateICmpSLT(L, R, "cmplttmp");
			case OPERATOR::EQUAL:
				return Builder.CreateICmpEQ(L, R, "cmpeqtmp");
			case OPERATOR::UNEQUAL:
				return Builder.CreateICmpNE(L, R, "cmpnetmp");

			case OPERATOR::AND:
				return Builder.CreateAnd(L, R, "andtmp");
			case OPERATOR::OR:
				return Builder.CreateOr(L, R, "ortmp");

			default:
				CodeGenLogger.println("Invalid int binary operator" + stringOf(op));
				return nullptr;

			}
		}
		else if (L->getType()->isFloatingPointTy() && R->getType()->isFloatingPointTy())
		{
			// binary float
			switch (op)
			{
			case OPERATOR::PLUS:
				return Builder.CreateFAdd(L, R, "addtmp");
			case OPERATOR::MINUS:
				return Builder.CreateFSub(L, R, "subtmp");
			case OPERATOR::MUL:
				return Builder.CreateFMul(L, R, "multmp");
			case OPERATOR::DIV:
				return Builder.CreateFDiv(L, R, "divtmp");
			case OPERATOR::MOD:
				return Builder.CreateFRem(L, R, "divtmp");

			case OPERATOR::GE:
				return Builder.CreateFCmpUGE(L, R, "cmpgetmp");
			case OPERATOR::GT:
				return Builder.CreateFCmpUGT(L, R, "cmpgttmp");
			case OPERATOR::LE:
				return Builder.CreateFCmpULE(L, R, "cmpletmp");
			case OPERATOR::LT:
				return Builder.CreateFCmpULT(L, R, "cmplttmp");
			case OPERATOR::EQUAL:
				return Builder.CreateFCmpUEQ(L, R, "cmpeqtmp");
			case OPERATOR::UNEQUAL:
				return Builder.CreateFCmpUNE(L, R, "cmpnetmp");


			case OPERATOR::AND:
				return Builder.CreateAnd(L, R, "andtmp");
			case OPERATOR::OR:
				return Builder.CreateOr(L, R, "ortmp");

			default:
				CodeGenLogger.println("Invalid float binary operator" + stringOf(op));
				return nullptr;
			}
		}
		else
		{
			CodeGenLogger.println("Invalid type for operator " + stringOf(op));
			return nullptr;
		}
	}

}

void ASTHandler::recursivePrint(ASTNode* head, int depth)
{
	ASTNode* current = head;
	std::string prefix(depth, ' ');
	YaccLogger.print(prefix);
	current->print();
	if (current->child)
		current = current->child;
	else
		return;
	do
	{
		recursivePrint(current, depth + 2);
		current = current->brother;
	} while (current);
}

void ASTHandler::print()
{
	recursivePrint(ASTHead, 0);
}

void ASTHandler::scanProgramHead()
{
	// incomplete AST without Routine
	if (!ASTHead || !ASTHead->child || ASTHead->child->getType() != ASTNode::ASTNodeType::Routine)
		return;
	// incomplete AST without RoutineHead
	if (!ASTHead->child->child || ASTHead->child->child->getType() != ASTNode::ASTNodeType::RoutineHead)
		return;
	ASTNode* routineHead = ASTHead->child->child;
	ASTNode* headPart = routineHead->child;

	while (headPart)
	{
		if (headPart->getType() == ASTNode::ASTNodeType::ConstExprList)
			scanConstPart(headPart);
		else if (headPart->getType() == ASTNode::ASTNodeType::TypeDeclList)
			scanTypePart(headPart);
		else if (headPart->getType() == ASTNode::ASTNodeType::VarDeclList)
			scanVarPart(headPart);
		else if (headPart->getType() == ASTNode::ASTNodeType::RoutinePart)
			scanRoutinePart(headPart);
		headPart = headPart->brother;
	}
}

void ASTHandler::scanConstPart(ASTNode* part)
{
	ASTNode* constExpr = part->child;
	while (constExpr)
	{
		ASTNode_ConstExpr* p = dynamic_cast<ASTNode_ConstExpr*>(constExpr);
		GlobalTable::insertConstant(p->constName, p->value->codeGen());
		constExpr = constExpr->brother;
	}
}

void ASTHandler::scanTypePart(ASTNode* part)
{
	ASTNode* typeDecl = part->child;
	while (typeDecl)
	{
		ASTNode_TypeDecl* p = dynamic_cast<ASTNode_TypeDecl*>(typeDecl);
		GlobalTable::insertType(p->defName, p->type->codeGen());
		typeDecl = typeDecl->brother;
	}
}

void ASTHandler::scanVarPart(ASTNode* part)
{
	ASTNode* varDecl = part->child;
	while (varDecl)
	{
		ASTNode_VarDecl* p = dynamic_cast<ASTNode_VarDecl*>(varDecl);
		for (auto& name : p->list->name_list)
			GlobalTable::insertVariable(name, p->type->codeGen());

		varDecl = varDecl->brother;
	}
}

void ASTHandler::scanRoutinePart(ASTNode* part)
{
	ASTNode* procDecl = part->child;
	while (procDecl)
	{
		if(procDecl->getType() == ASTNode::ASTNodeType::FunctionDecl)
		{
			ASTNode_FunctionDecl* p = dynamic_cast<ASTNode_FunctionDecl*>(procDecl);
			
		}
		else if (procDecl->getType() == ASTNode::ASTNodeType::ProcedureDecl)
		{
			ASTNode_ProcedureDecl* p = dynamic_cast<ASTNode_ProcedureDecl*>(procDecl);

		}

		procDecl = procDecl->brother;
	}
}

