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
	"."};

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<llvm::Module> TheModule = std::make_unique<llvm::Module>("jit", TheContext);

ASTNode *ASTHead = nullptr;

llvm::Value *ASTNode_ConstInteger::codeGen()
{
	return llvm::ConstantInt::get(TheContext, llvm::APSInt(value));
}

llvm::Value *ASTNode_ConstReal::codeGen()
{
	return llvm::ConstantFP::get(TheContext, llvm::APFloat(value));
}

llvm::Value *ASTNode_ConstCharacter::codeGen()
{
	return llvm::ConstantInt::get(TheContext, llvm::APSInt(value));
}

llvm::Value *ASTNode_ConstBoolean::codeGen()
{
	return llvm::ConstantInt::get(TheContext, llvm::APSInt(value));
}

llvm::Value *ASTNode_ConstString::codeGen()
{
	//TODO
}

llvm::Type *ASTNode_SimpleTypePlain::codeGen()
{
	if (typeName == "integer")
		return llvm::Type::getInt32Ty(TheContext);
	if (typeName == "real")
		return llvm::Type::getDoubleTy(TheContext);
	if (typeName == "char")
		return llvm::Type::getInt8Ty(TheContext);
	if (typeName == "string")
	//TODO
		return nullptr;
	if (typeName == "boolean")
		return llvm::Type::getInt1Ty(TheContext);
}

llvm::Type *ASTNode_SimpleTypeEnumerate::codeGen()
{
	//TODO
}

llvm::Type *ASTNode_SimpleTypeSubrange::codeGen()
{
	//TODO
}

llvm::Type *ASTNode_ArrayType::codeGen()
{
	//TODO
}

llvm::Type *ASTNode_RecordType::codeGen()
{
	//TODO
}

llvm::Value *ASTNode_Operand::codeGen()
{
	// literal
	if (name == "const")
		return dynamic_cast<ASTNode_Const *>(child)->codeGen();

	// const
	auto c = GlobalTable::getConstant(name);
	if (c)
		return c;

	// variable
	auto v = GlobalTable::getVariable(name);
	if (v)
		return v;

	// function
	auto f = TheModule->getFunction(name);
	if (f)
	{
		auto argList = dynamic_cast<ASTNode_ArgList *>(child);
		if (argList->count == f->arg_size())
		{
			std::vector<llvm::Value *> args;
			auto argNode = dynamic_cast<ASTNode_Expr *>(argList->child);
			while (argNode->brother)
			{
				args.push_back(argNode->codeGen());
				argNode = dynamic_cast<ASTNode_Expr *>(argNode->brother);
			}
			return Builder.CreateCall(f, args, "calltmp");
		}
	}

	CodeGenLogger.println("Unrecognized expression " + name);
	return nullptr;
}

llvm::Value *ASTNode_Operator::codeGen()
{
	bool isUnary = false;
	llvm::Value *L = dynamic_cast<ASTNode_Expr *>(child)->codeGen();
	llvm::Value *R = nullptr;
	if (!L)
		return nullptr;
	if (child->brother)
		R = dynamic_cast<ASTNode_Expr *>(child->brother)->codeGen();
	else
		isUnary = true;

	// int promotion
	auto intPromotion = [&L, &R]()
	{
		if (L->getType()->isIntegerTy() && R->getType()->isDoubleTy())
			L = Builder.CreateSIToFP(L, llvm::Type::getDoubleTy(TheContext), "sitofp");
		if (L->getType()->isIntegerTy() && R->getType()->isDoubleTy())
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
		else if (L->getType()->isDoubleTy())
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
		else if (L->getType()->isDoubleTy() && R->getType()->isDoubleTy())
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

llvm::Function *ASTNode_FunctionHead::codeGen()
{
	llvm::FunctionType *funcType;

	if (child->getType() == ASTNodeType::ParaDeclList)
	{
		// with para
		std::vector<llvm::Type *> paraTypes;

		auto paraDecl = dynamic_cast<ASTNode_ParaTypeList *>(child->child);

		while (paraDecl)
		{
			if (paraDecl->paraList->getType() == ASTNodeType::VarParaList)
			{
				// TODO: reference variable
			}
			else if (paraDecl->paraList->getType() == ASTNodeType::ValParaList)
				for (int i = 0; i < paraDecl->paraList->name_list.size(); ++i)
					paraTypes.push_back(paraDecl->type->codeGen());
			paraDecl = dynamic_cast<ASTNode_ParaTypeList *>(paraDecl->brother);
		}

		funcType = llvm::FunctionType::get(dynamic_cast<ASTNode_Type *>(child->brother)->codeGen(), paraTypes, false);
	}
	else
		// no para
		funcType = llvm::FunctionType::get(dynamic_cast<ASTNode_Type *>(child)->codeGen(), false);

	auto fun = llvm::Function::Create(funcType, llvm::Function::InternalLinkage, functionName, TheModule.get());

	// set args' name

	auto iter = fun->args().begin();
	auto paraDecl = dynamic_cast<ASTNode_ParaTypeList *>(child->child);

	while (paraDecl)
	{
		for (auto &name : paraDecl->paraList->name_list)
		{
			iter->setName(name);
			iter++;
		}
		paraDecl = dynamic_cast<ASTNode_ParaTypeList *>(paraDecl->brother);
	}

	return fun;
}

llvm::Function *ASTNode_FunctionDecl::codeGen()
{
	auto funcHead = dynamic_cast<ASTNode_FunctionHead *>(child);

	auto fun = TheModule->getFunction(funcHead->functionName);

	if (!fun)
		fun = funcHead->codeGen();
	if (!fun)
		return nullptr;
	if (!fun->empty())
	{
		CodeGenLogger.println("Cannot redefine function " + funcHead->functionName);
		return nullptr;
	}
	
	auto BB = llvm::BasicBlock::Create(TheContext, "entry", fun);
	Builder.SetInsertPoint(BB);

	// set up variable table
	GlobalTable::clearVariable();
	for (auto &arg : fun->args())
		GlobalTable::insertVariable(std::string(arg.getName()), &arg);

	auto routine = dynamic_cast<ASTNode_SubRoutine *>(funcHead->brother);

	auto retVal = routine->codeGen();
	if (retVal)
	{
		Builder.CreateRet(retVal);
		llvm::verifyFunction(*fun);
		return fun;
	}
	else
	{
		fun->eraseFromParent();
		return nullptr;
	}
}

llvm::Function *ASTNode_ProcedureHead::codeGen()
{
	llvm::FunctionType *procType;
	if (child)
	{
		// with para
		std::vector<llvm::Type *> paraTypes;

		auto paraDecl = dynamic_cast<ASTNode_ParaTypeList *>(child->child);

		while (paraDecl)
		{
			if (paraDecl->paraList->getType() == ASTNodeType::VarParaList)
			{
				// TODO: reference variable
			}
			else if (paraDecl->paraList->getType() == ASTNodeType::ValParaList)
				for (int i = 0; i < paraDecl->paraList->name_list.size(); ++i)
					paraTypes.push_back(paraDecl->type->codeGen());
			paraDecl = dynamic_cast<ASTNode_ParaTypeList *>(paraDecl->brother);
		}

		procType = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), paraTypes, false);
	}
	else
		// no para
		procType = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), false);

	auto proc = llvm::Function::Create(procType, llvm::Function::InternalLinkage, procedureName, TheModule.get());

	// set args' name

	auto iter = proc->args().begin();
	auto paraDecl = dynamic_cast<ASTNode_ParaTypeList *>(child->child);

	while (paraDecl)
	{
		for (auto &name : paraDecl->paraList->name_list)
		{
			iter->setName(name);
			iter++;
		}
		paraDecl = dynamic_cast<ASTNode_ParaTypeList *>(paraDecl->brother);
	}

	return proc;
}

llvm::Function *ASTNode_ProcedureDecl::codeGen()
{
	auto procHead = dynamic_cast<ASTNode_ProcedureHead *>(child);

	auto proc = TheModule->getFunction(procHead->procedureName);

	if (!proc)
		proc = procHead->codeGen();
	if (!proc)
		return nullptr;
	if (!proc->empty())
	{
		CodeGenLogger.println("Cannot redefine procedure " + procHead->procedureName);
		return nullptr;
	}

	auto BB = llvm::BasicBlock::Create(TheContext, "entry", proc);
	Builder.SetInsertPoint(BB);

	// set up variable table
	GlobalTable::clearVariable();
	for (auto &arg : proc->args())
		GlobalTable::insertVariable(std::string(arg.getName()), &arg);

	auto routine = dynamic_cast<ASTNode_SubRoutine *>(procHead->brother);

	auto retVal = routine->codeGen();
	if (retVal)
	{
		Builder.CreateRet(retVal);
		llvm::verifyFunction(*proc);
		return proc;
	}
	else
	{
		proc->eraseFromParent();
		return nullptr;
	}
}

llvm::Value *ASTNode_SubRoutine::codeGen()
{
	// TODO
	
}

void ASTHandler::recursivePrint(ASTNode *head, int depth)
{
	ASTNode *current = head;
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
	ASTNode *routineHead = ASTHead->child->child;
	ASTNode *headPart = routineHead->child;

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
	TheModule->print(llvm::errs(), nullptr);
}

void ASTHandler::scanConstPart(ASTNode *part)
{
	ASTNode *constExpr = part->child;
	while (constExpr)
	{
		ASTNode_ConstExpr *p = dynamic_cast<ASTNode_ConstExpr *>(constExpr);
		GlobalTable::insertConstant(p->constName, p->value->codeGen());
		constExpr = constExpr->brother;
	}
}

void ASTHandler::scanTypePart(ASTNode *part)
{
	ASTNode *typeDecl = part->child;
	while (typeDecl)
	{
		ASTNode_TypeDecl *p = dynamic_cast<ASTNode_TypeDecl *>(typeDecl);
		GlobalTable::insertType(p->defName, p->type->codeGen());
		typeDecl = typeDecl->brother;
	}
}

void ASTHandler::scanVarPart(ASTNode *part)
{
	ASTNode *varDecl = part->child;
	while (varDecl)
	{
		ASTNode_VarDecl *p = dynamic_cast<ASTNode_VarDecl *>(varDecl);
		//for (auto& name : p->list->name_list)
		//	GlobalTable::insertVariable(name, p->type->codeGen());

		varDecl = varDecl->brother;
	}
}

void ASTHandler::scanRoutinePart(ASTNode *part)
{
	ASTNode *procDecl = part->child;
	while (procDecl)
	{
		if (procDecl->getType() == ASTNode::ASTNodeType::FunctionDecl)
		{
			ASTNode_FunctionDecl *p = dynamic_cast<ASTNode_FunctionDecl *>(procDecl);
			p->codeGen();
		}
		else if (procDecl->getType() == ASTNode::ASTNodeType::ProcedureDecl)
		{
			ASTNode_ProcedureDecl *p = dynamic_cast<ASTNode_ProcedureDecl *>(procDecl);
			p->codeGen();
		}

		procDecl = procDecl->brother;
	}
}
