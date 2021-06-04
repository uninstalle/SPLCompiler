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

llvm::Constant*ASTNode_ConstInteger::codeGen()
{
	return llvm::ConstantInt::get(TheContext, llvm::APInt(32, value, true));
}

llvm::Constant*ASTNode_ConstReal::codeGen()
{
	return llvm::ConstantFP::get(TheContext, llvm::APFloat(value));
}

llvm::Constant*ASTNode_ConstCharacter::codeGen()
{
	return llvm::ConstantInt::get(TheContext, llvm::APInt(8, value, false));
}

llvm::Constant*ASTNode_ConstBoolean::codeGen()
{
	return llvm::ConstantInt::get(TheContext, llvm::APInt(1, value, false));
}

llvm::Constant*ASTNode_ConstString::codeGen()
{
	//TODO
	return nullptr;
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

	CodeGenLogger.println("Unrecognized simple type " + typeName);
	return nullptr;
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
	auto c = GlobalTable.getConstant(name);
	if (c)
		return c;

	// variable
	auto v = GlobalTable.getVariable(name);
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

	auto intPromotion = [&L, &R]()
	{
		// compute with int and double, promote to double
		if (L->getType()->isIntegerTy() && R->getType()->isDoubleTy())
			L = Builder.CreateSIToFP(L, llvm::Type::getDoubleTy(TheContext), "sitofp");
		if (L->getType()->isIntegerTy() && R->getType()->isDoubleTy())
			R = Builder.CreateSIToFP(R, llvm::Type::getDoubleTy(TheContext), "sitofp");
		// compute with int with different bit width, promote to i32
		if (L->getType()->isIntegerTy() && R->getType()->isIntegerTy() &&
			L->getType()->getIntegerBitWidth() != R->getType()->getIntegerBitWidth())
		{
			L = Builder.CreateZExt(L, llvm::Type::getInt32Ty(TheContext), "intext");
			R = Builder.CreateZExt(R, llvm::Type::getInt32Ty(TheContext), "intext");
		}
	};

	if (isUnary)
	{

		if (L->getType()->isIntegerTy())
		{
			// unary int
			switch (op)
			{
			case OPERATOR::MINUS:
				return Builder.CreateSub(llvm::ConstantInt::get(TheContext, llvm::APInt(L->getType()->getIntegerBitWidth(), 0, true)), L, "subtmp");

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

	//TODO
	// set up variable table
	GlobalTable.clearVariable();
	for (auto &arg : fun->args())
		GlobalTable.insertVariable(std::string(arg.getName()), &arg);

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
	GlobalTable.clearVariable();
	for (auto &arg : proc->args())
		GlobalTable.insertVariable(std::string(arg.getName()), &arg);

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

void ASTNode_Routine::scanConstPart(ASTNode *part)
{
	ASTNode *constExpr = part->child;
	while (constExpr)
	{
		ASTNode_ConstExpr *p = dynamic_cast<ASTNode_ConstExpr *>(constExpr);
		auto v = p->value->codeGen();
		GlobalTable.insertConstant(p->constName, v);
		constExpr = constExpr->brother;
	}
}

void ASTNode_Routine::scanTypePart(ASTNode *part)
{
	ASTNode *typeDecl = part->child;
	while (typeDecl)
	{
		ASTNode_TypeDecl *p = dynamic_cast<ASTNode_TypeDecl *>(typeDecl);
		GlobalTable.insertType(p->defName, p->type->codeGen());
		typeDecl = typeDecl->brother;
	}
}

void ASTNode_Routine::scanVarPart(ASTNode *part)
{
	ASTNode *varDecl = part->child;
	while (varDecl)
	{
		ASTNode_VarDecl *p = dynamic_cast<ASTNode_VarDecl *>(varDecl);
		//TODO
		//for (auto& name : p->list->name_list)
		//	GlobalTable.insertVariable(name, p->type->codeGen());

		varDecl = varDecl->brother;
	}
}

void ASTNode_Routine::scanRoutinePart(ASTNode *part)
{
	ASTNode *procDecl = part->child;
	while (procDecl)
	{
		if (procDecl->getType() == ASTNodeType::FunctionDecl)
		{
			ASTNode_FunctionDecl *p = dynamic_cast<ASTNode_FunctionDecl *>(procDecl);
			p->codeGen();
		}
		else if (procDecl->getType() == ASTNodeType::ProcedureDecl)
		{
			ASTNode_ProcedureDecl *p = dynamic_cast<ASTNode_ProcedureDecl *>(procDecl);
			p->codeGen();
		}

		procDecl = procDecl->brother;
	}
}

llvm::Function *ASTNode_Routine::genRoutineHead()
{
	llvm::FunctionType *funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), false);

	auto fun = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", TheModule.get());

	return fun;
}

llvm::Value *ASTNode_Routine::codeGen()
{
	// Routine is the body of program main, thus here we use global table.

	// incomplete Routine without RoutineHead
	if (!child || child->getType() != ASTNodeType::RoutineHead)
		return nullptr;

	ASTNode *routineHead = child;
	ASTNode *headPart = routineHead->child;

	while (headPart)
	{
		if (headPart->getType() == ASTNodeType::ConstExprList)
			scanConstPart(headPart);
		else if (headPart->getType() == ASTNodeType::TypeDeclList)
			scanTypePart(headPart);
		else if (headPart->getType() == ASTNodeType::VarDeclList)
			scanVarPart(headPart);
		else if (headPart->getType() == ASTNodeType::RoutinePart)
			scanRoutinePart(headPart);
		headPart = headPart->brother;
	}

	auto BB = llvm::BasicBlock::Create(TheContext, "main", genRoutineHead());
	Builder.SetInsertPoint(BB);

	dynamic_cast<ASTNode_StmtCompound *>(routineHead->brother)->codeGen();
}

llvm::Value *ASTNode_SubRoutine::codeGen()
{
	// subroutine is a code block surrounded by 'begin' and 'end'

	// TODO
	return nullptr;
}

llvm::Value *ASTNode_StmtIf::codeGen()
{
	// child 1, if-condition expr
	llvm::Value *condV = dynamic_cast<ASTNode_Expr *>(child)->codeGen();
	if (!condV)
	{
		CodeGenLogger.println("If stmt has invalid condition");
		return nullptr;
	}

	if (condV->getType()->isIntegerTy())
		condV = Builder.CreateICmpNE(condV, llvm::ConstantInt::get(TheContext, llvm::APInt(condV->getType()->getIntegerBitWidth(), 0)), "ifcond");
	else if (condV->getType()->isDoubleTy())
		condV = Builder.CreateFCmpONE(condV, llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0)), "ifcond");

	llvm::Function *fun = Builder.GetInsertBlock()->getParent();

	llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(TheContext, "then", fun);
	llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(TheContext, "else");
	llvm::BasicBlock *ifcontBB = llvm::BasicBlock::Create(TheContext, "ifcont");

	Builder.CreateCondBr(condV, thenBB, elseBB);

	Builder.SetInsertPoint(thenBB);

	// child 2, then expr
	llvm::Value *thenV = dynamic_cast<ASTNode_Stmt *>(child->brother)->codeGen();
	if (!thenV)
	{
		CodeGenLogger.println("If stmt has invalid then stmt");
		return nullptr;
	}

	Builder.CreateBr(ifcontBB);
	thenBB = Builder.GetInsertBlock();

	fun->getBasicBlockList().push_back(elseBB);
	Builder.SetInsertPoint(elseBB);

	// child 3, else expr
	llvm::Value *elseV;
	if (child->brother->brother)
	{
		// with else clause
		elseV = dynamic_cast<ASTNode_Stmt *>(child->brother->brother)->codeGen();
		if (!elseV)
		{
			CodeGenLogger.println("If stmt has invalid else stmt");
			return nullptr;
		}
	}
	else
		elseV = llvm::Constant::getNullValue(llvm::Type::getInt1Ty(TheContext));

	Builder.CreateBr(ifcontBB);
	elseBB = Builder.GetInsertBlock();

	fun->getBasicBlockList().push_back(ifcontBB);
	Builder.SetInsertPoint(ifcontBB);
	//TODO: type?
	llvm::PHINode *phiNode =
		Builder.CreatePHI(llvm::Type::getInt1Ty(TheContext), 2, "iftmp");

	phiNode->addIncoming(thenV, thenBB);
	phiNode->addIncoming(elseV, elseBB);
	return phiNode;
}

llvm::Value *ASTNode_StmtFor::codeGen()
{
	// child 1, start value expr
	auto startValue = dynamic_cast<ASTNode_Expr *>(child)->codeGen();
	if (!startValue)
		return nullptr;
	// only supports integer as stepping value
	if (!startValue->getType()->isIntegerTy())
		return nullptr;

	auto fun = Builder.GetInsertBlock()->getParent();
	auto prevBB = Builder.GetInsertBlock();
	auto loopBB = llvm::BasicBlock::Create(TheContext, "forloop", fun);

	Builder.CreateBr(loopBB);

	Builder.SetInsertPoint(loopBB);
	llvm::PHINode *variable = Builder.CreatePHI(llvm::Type::getInt1Ty(TheContext),
												2, varName);
	variable->addIncoming(startValue, prevBB);
	// save shadowed value if existed
	// TODO: replace it with a hierarchy variable table
	auto shadowedVar = GlobalTable.getVariable(varName);
	GlobalTable.insertVariable(varName, variable);

	// child 2, end value expr
	auto endValue = dynamic_cast<ASTNode_Expr *>(child->brother)->codeGen();
	if (!endValue)
		return nullptr;
	// only supports integer as stepping value
	if (!endValue->getType()->isIntegerTy())
		return nullptr;

	// child 3, for body
	auto body = dynamic_cast<ASTNode_Stmt *>(child->brother->brother)->codeGen();
	if (!body)
		return nullptr;

	auto stepping = this->isPositive ? llvm::ConstantInt::get(TheContext, llvm::APInt(32, 1, true))
									 : llvm::ConstantInt::get(TheContext, llvm::APInt(32, -1, true));

	auto nextVar = Builder.CreateAdd(variable, stepping, "stepping");

	auto loopCond = Builder.CreateICmpSLE(endValue, nextVar, "forloopcond");

	llvm::BasicBlock *loopEndBB = Builder.GetInsertBlock();
	llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(TheContext, "afterforloop", fun);

	// test if the loop is end
	Builder.CreateCondBr(loopCond, loopBB, afterBB);

	Builder.SetInsertPoint(afterBB);
	variable->addIncoming(nextVar, loopEndBB);

	if (shadowedVar)
		GlobalTable.insertVariable(varName, shadowedVar);
	else
		GlobalTable.removeVariable(varName);

	// return 0
	return llvm::Constant::getNullValue(llvm::Type::getInt1Ty(TheContext));
}

llvm::Value *ASTNode_StmtCompound::codeGen()
{
	auto stmtList = child;
	auto stmt = stmtList->child;
	// empty code block
	if (!stmt)
		return llvm::Constant::getNullValue(llvm::Type::getInt1Ty(TheContext));

	while (stmt)
	{
		// debug info
		CodeGenLogger.print("Compound stmt generating stmt: ");
		CodeGenLogger.println(std::to_string(static_cast<int>(stmt->getType())));

		auto res = dynamic_cast<ASTNode_Stmt *>(stmt)->codeGen();
		if (!res)
		{
			CodeGenLogger.println("Compound stmt has invalid stmt");
			return nullptr;
		}
		stmt = stmt->brother;
	}

	return llvm::Constant::getNullValue(llvm::Type::getInt1Ty(TheContext));
}

llvm::Value *ASTNode_StmtRepeat::codeGen()
{
	auto fun = Builder.GetInsertBlock()->getParent();
	auto loopBB = llvm::BasicBlock::Create(TheContext, "repeatloop", fun);

	Builder.CreateBr(loopBB);

	Builder.SetInsertPoint(loopBB);

	// child 1, loop body stmt_list
	auto stmtList = dynamic_cast<ASTNode_Stmt *>(child);
	auto stmt = stmtList->child;
	while (stmt)
	{
		auto res = dynamic_cast<ASTNode_Stmt *>(stmt)->codeGen();
		stmt = stmt->brother;
		if (!res)
		{
			CodeGenLogger.println("Repeat stmt has invalid stmt");
			return nullptr;
		}
	}

	// child 2, end cond
	auto endValue = dynamic_cast<ASTNode_Expr *>(child->brother)->codeGen();
	if (!endValue)
	{
		CodeGenLogger.println("Repeat stmt has invalid end expression");
		return nullptr;
	}

	auto loopCond = Builder.CreateICmpNE(endValue, llvm::ConstantInt::get(TheContext, llvm::APInt(1, 1)), "repeatloopcond");

	llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(TheContext, "afterrepeatloop", fun);

	// test if the loop is end
	Builder.CreateCondBr(loopCond, loopBB, afterBB);

	Builder.SetInsertPoint(afterBB);

	// return 0
	return llvm::Constant::getNullValue(llvm::Type::getInt1Ty(TheContext));
}

llvm::Value *ASTNode_StmtWhile::codeGen()
{
	auto fun = Builder.GetInsertBlock()->getParent();
	auto loopBB = llvm::BasicBlock::Create(TheContext, "whileloop", fun);

	Builder.CreateBr(loopBB);

	Builder.SetInsertPoint(loopBB);

	// child 1, end cond
	auto endValue = dynamic_cast<ASTNode_Expr *>(child)->codeGen();
	if (!endValue)
	{
		CodeGenLogger.println("While stmt has invalid end expression");
		return nullptr;
	}

	// child 2, loop body stmt
	auto body = dynamic_cast<ASTNode_Stmt *>(child->brother)->codeGen();
	if (!body)
	{
		CodeGenLogger.println("While stmt has invalid stmt");
		return nullptr;
	}

	auto loopCond = Builder.CreateICmpEQ(endValue, llvm::ConstantInt::get(TheContext, llvm::APInt(1, 1)), "whileloopcond");

	llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(TheContext, "afterwhileloop", fun);

	// test if the loop is end
	Builder.CreateCondBr(loopCond, loopBB, afterBB);

	Builder.SetInsertPoint(afterBB);

	// return 0
	return llvm::Constant::getNullValue(llvm::Type::getInt1Ty(TheContext));
}

llvm::Value *ASTNode_StmtProc::codeGen()
{
	auto f = TheModule->getFunction(procName);
	if (f)
	{
		if (f->arg_size() == 0)
		{
			std::vector<llvm::Value *> args;
			return Builder.CreateCall(f, llvm::None, "calltmp");
		}
		else
		{
			// function expected args but stmt has no args
			if (!child)
			{
				CodeGenLogger.println("Function expects args but not provided: " + procName);
				return nullptr;
			}

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
			CodeGenLogger.println("Function expects " + std::to_string(f->arg_size()) + " args but provided " + std::to_string(argList->count) + ": " + procName);
			return nullptr;
		}
	}
	CodeGenLogger.println("Function not found in symbol table: " + procName);
	return nullptr;
}

llvm::Value *ASTNode_StmtAssign::codeGen()
{
	//TODO
	return llvm::Constant::getNullValue(llvm::Type::getInt1Ty(TheContext));
}

llvm::Value *ASTNode_StmtCase::codeGen()
{
	//TODO

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

	// child 2, then expr
	auto caseExprList = child->brother;
	auto caseExpr = caseExprList->child;

	int caseCount = 0;
	std::vector<std::pair<llvm::Constant*, llvm::BasicBlock*>> cases;
	 llvm::BasicBlock* defaultBB = nullptr;

	 auto createCaseBB = [] {
		 auto fun = Builder.GetInsertBlock()->getParent();
		 auto caseBB = llvm::BasicBlock::Create(TheContext, "case", fun);
		 return caseBB;
	 };
	
	while (caseExpr)
	{
		caseCount++;
		auto caseVar = caseExpr->child;
		auto caseStmt = caseVar->brother;
		
		if (caseVar->getType() == ASTNodeType::Const) 
		{
			// const literal case
			auto v = dynamic_cast<ASTNode_Const*>(caseVar)->codeGen();
			if(!v->getType()->isIntegerTy())
			{
				CodeGenLogger.println("Case stmt expects integer");
				return nullptr;
			}
			
			auto bb = createCaseBB();
			Builder.SetInsertPoint(bb);
			auto caseV = dynamic_cast<ASTNode_Stmt*>(caseStmt)->codeGen();
			if (!caseV)
			{
				CodeGenLogger.println("case has invalid stmt");
				return nullptr;
			}
			cases.push_back(std::make_pair(v, bb));
		}
		else if (caseVar->getType() == ASTNodeType::Name)
		{
			auto name = dynamic_cast<ASTNode_Name*>(caseVar)->name;
			if (name == "else")
			{
				// default case
				auto fun = Builder.GetInsertBlock()->getParent();
				defaultBB = llvm::BasicBlock::Create(TheContext, "default",fun);
				
				Builder.SetInsertPoint(defaultBB);
				auto caseV = dynamic_cast<ASTNode_Stmt*>(caseStmt)->codeGen();
				if (!caseV)
				{
					CodeGenLogger.println("case has invalid stmt");
					return nullptr;
				}
				
			}
			else
			{
				// const variable case
				auto v = GlobalTable.getConstant(name);
				if (!v->getType()->isIntegerTy())
				{
					CodeGenLogger.println("Case stmt expects integer");
					return nullptr;
				}
				auto bb = createCaseBB();
				Builder.SetInsertPoint(bb);
				auto caseV = dynamic_cast<ASTNode_Stmt*>(caseStmt)->codeGen();
				if (!caseV)
				{
					CodeGenLogger.println("case has invalid stmt");
					return nullptr;
				}
				cases.emplace_back(std::make_pair(v, bb));
			}
		}
		

		caseExpr = caseExpr->brother;
	}

	if(!defaultBB)
	{
		auto fun = Builder.GetInsertBlock()->getParent();
		defaultBB = llvm::BasicBlock::Create(TheContext, "default", fun);
	}

	auto sw = Builder.CreateSwitch(condV, defaultBB,caseCount);

	for(auto &c :cases)
		sw->addCase(reinterpret_cast<llvm::ConstantInt*>(c.first), c.second);

	Builder.SetInsertPoint(defaultBB);
	
}

llvm::Value *ASTNode_StmtGoto::codeGen()
{
	// only look for labels in the same parent block.
	// still, this may not reach labels after it.
	// should use a jump table to store all labelled basic blocks pointers.
	llvm::Function *fun = Builder.GetInsertBlock()->getParent();
	llvm::BasicBlock *gotoBB = nullptr;
	for (auto &bb : fun->getBasicBlockList())
	{
		if (bb.getName() == std::to_string(label))
		{
			gotoBB = &bb;
			break;
		}
	}

	if (gotoBB)
	{
		Builder.CreateBr(gotoBB);
		return llvm::Constant::getNullValue(llvm::Type::getInt1Ty(TheContext));
	}
	else
	{
		CodeGenLogger.println("Invalid label in goto stmt: " + std::to_string(label));
		return nullptr;
	}
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

void ASTHandler::setASTHead(ASTNode *head)
{
	ASTHead = head;
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

	auto routine = dynamic_cast<ASTNode_Routine *>(ASTHead->child);
	routine->codeGen();
	TheModule->print(llvm::errs(), nullptr);
}
