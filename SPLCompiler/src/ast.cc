#include "ast.hh"
#include "table.hh"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>

const std::string ASTNode_Operator::OperatorString[] = {
	">=",
	">",
	"<=",
	"<",
	"=",
	"<>",

	"+",
	"-",
	"*",
	"/",
	"%",

	"&",
	"!",
	"|",

	"."};

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<llvm::Module> TheModule;
static std::unique_ptr<llvm::legacy::FunctionPassManager> TheFPM;

static ASTNode *ASTHead = nullptr;

// used for return 0
static auto RetValZero = llvm::Constant::getNullValue(llvm::Type::getInt1Ty(TheContext));

// create an IR statement in the beginning of given function, which creating a variable of given type with given name
llvm::AllocaInst *createEntryBlockAlloca(llvm::Function *fun,
										 const std::string &varName, llvm::Type *type)
{
	llvm::IRBuilder<> builder(&fun->getEntryBlock(),
							  fun->getEntryBlock().begin());
	return builder.CreateAlloca(type, nullptr, varName);
}

llvm::Constant *ASTNode_ConstInteger::codeGen()
{
	return llvm::ConstantInt::get(TheContext, llvm::APInt(32, value, true));
}

llvm::Constant *ASTNode_ConstReal::codeGen()
{
	return llvm::ConstantFP::get(TheContext, llvm::APFloat(value));
}

llvm::Constant *ASTNode_ConstCharacter::codeGen()
{
	return llvm::ConstantInt::get(TheContext, llvm::APInt(8, value, false));
}

llvm::Constant *ASTNode_ConstBoolean::codeGen()
{
	return llvm::ConstantInt::get(TheContext, llvm::APInt(1, value, false));
}

llvm::Constant *ASTNode_ConstString::codeGen()
{
	std::vector<llvm::Constant *> charArray;
	for (auto &ch : str)
		charArray.emplace_back(llvm::ConstantInt::get(TheContext, llvm::APInt(8, ch, false)));

	return llvm::ConstantArray::get(llvm::ArrayType::get(llvm::Type::getInt8Ty(TheContext), charArray.size()), charArray);
}

llvm::Type *ASTNode_SimpleTypePlain::codeGen(bool isRef)
{
	if (isRef)
	{
		if (typeName == "integer")
			return llvm::Type::getInt32PtrTy(TheContext);
		if (typeName == "real")
			return llvm::Type::getDoublePtrTy(TheContext);
		if (typeName == "char")
			return llvm::Type::getInt8PtrTy(TheContext);
		if (typeName == "string")
			//TODO: how to get the size of the array?
			//return llvm::ArrayType::get(llvm::Type::getInt8Ty(TheContext), );
			return nullptr;
		if (typeName == "boolean")
			return llvm::Type::getInt1PtrTy(TheContext);
	}
	else
	{
		if (typeName == "integer")
			return llvm::Type::getInt32Ty(TheContext);
		if (typeName == "real")
			return llvm::Type::getDoubleTy(TheContext);
		if (typeName == "char")
			return llvm::Type::getInt8Ty(TheContext);
		if (typeName == "string")
			//TODO: how to get the size of the array?
			//return llvm::ArrayType::get(llvm::Type::getInt8Ty(TheContext), );
			return nullptr;
		if (typeName == "boolean")
			return llvm::Type::getInt1Ty(TheContext);
	}
	if (isRef)
		CodeGenLogger.println("Unrecognized simple type ref " + typeName);
	else
		CodeGenLogger.println("Unrecognized simple type " + typeName);
	return nullptr;
}

llvm::Type *ASTNode_SimpleTypeEnumerate::codeGen(bool isRef)
{
	//TODO
}

llvm::Type *ASTNode_SimpleTypeSubrange::codeGen(bool isRef)
{
	//TODO
}

llvm::Type *ASTNode_ArrayType::codeGen(bool isRef)
{
	//TODO
}

llvm::Type *ASTNode_RecordType::codeGen(bool isRef)
{
	//TODO
}

llvm::Value *ASTNode_Operand::codeGen()
{
	if (type == OperandType::Literal)
		return dynamic_cast<ASTNode_Const *>(child)->codeGen();

	if (type == OperandType::Variable)
	{
		// constant
		auto c = currentSymbolTable->getConstant(name);
		if (c)
			return c;
		// variable
		auto v = currentSymbolTable->getVariable(name);
		if (v)
			return Builder.CreateLoad(v, name);
		// not found
		CodeGenLogger.println("Variable not found: " + name);
		return nullptr;
	}

	if (type == OperandType::Function)
	{
		auto fun = TheModule->getFunction(name);
		if (fun)
		{
			// function without args
			if (fun->arg_size() == 0)
			{
				std::vector<llvm::Value *> args;
				return Builder.CreateCall(fun, llvm::None, name + "_call");
			}
			else
			{
				// function expected args but stmt has no args
				if (!child)
				{
					CodeGenLogger.println("Function expects args but not provided: " + name);
					return nullptr;
				}

				auto argList = dynamic_cast<ASTNode_ArgList *>(child);
				if (argList->count == fun->arg_size())
				{
					std::vector<llvm::Value *> args;
					auto argNode = dynamic_cast<ASTNode_Expr *>(argList->child);

					// TODO: type check

					for (auto &arg : fun->args())
					{
						if (arg.getType()->isPointerTy())
						{
							auto v = argNode->codeGen();
							auto alloca = createEntryBlockAlloca(fun, std::string(arg.getName()), arg.getType());
							Builder.CreateStore(v, alloca);
							args.push_back(alloca);
						}
						else
						{
							args.push_back(argNode->codeGen());
						}
						argNode = dynamic_cast<ASTNode_Expr *>(argNode->brother);
					}

					return Builder.CreateCall(fun, args, name + "_call");
				}
				// function expects args but provided with different number of args
				CodeGenLogger.println("Function expects " + std::to_string(fun->arg_size()) + " args but provided " + std::to_string(argList->count) + ": " + name);
				return nullptr;
			}
		}
		CodeGenLogger.println("Unrecognized expression " + name);
		return nullptr;
	}

	if (type == OperandType::ArrayElement)
		// TODO
		return nullptr;

	if (type == OperandType::RecordMember)
		// TODO
		return nullptr;

	return nullptr;
}

static void intPromotion(llvm::Value *&L, llvm::Value *&R)
{
	// compute with int and double, promote to double
	if (L->getType()->isIntegerTy() && R->getType()->isDoubleTy())
		L = Builder.CreateSIToFP(L, llvm::Type::getDoubleTy(TheContext), "sitofp");
	if (L->getType()->isDoubleTy() && R->getType()->isIntegerTy())
		R = Builder.CreateSIToFP(R, llvm::Type::getDoubleTy(TheContext), "sitofp");

	// compute with int with different bit width, promote to i32
	if (L->getType()->isIntegerTy() && R->getType()->isIntegerTy() &&
		L->getType()->getIntegerBitWidth() != R->getType()->getIntegerBitWidth())
	{
		L = Builder.CreateZExt(L, llvm::Type::getInt32Ty(TheContext), "intzext");
		R = Builder.CreateZExt(R, llvm::Type::getInt32Ty(TheContext), "intzext");
	}
}

llvm::Value *ASTNode_Operator::codeGen()
{
	bool isUnary = false;
	llvm::Value *L = dynamic_cast<ASTNode_Expr *>(child)->codeGen();
	llvm::Value *R = nullptr;
	if (!L)
	{
		CodeGenLogger.println("Unresolved expr value");
		return nullptr;
	}
	if (child->brother)
	{
		R = dynamic_cast<ASTNode_Expr *>(child->brother)->codeGen();
		if (!R)
		{
			CodeGenLogger.println("Unresolved expr value");
			return nullptr;
		}
	}
	else
		isUnary = true;

	if (isUnary)
	{
		if (L->getType()->isIntegerTy())
		{
			// unary int
			switch (type)
			{
			case OperatorType::MINUS:
				// -L = 0 - L
				return Builder.CreateSub(llvm::ConstantInt::get(TheContext, llvm::APInt(L->getType()->getIntegerBitWidth(), 0)), L, "intuminus");

			case OperatorType::NOT:
				return Builder.CreateNot(L, "intnot");

			default:
				CodeGenLogger.println("Invalid int unary operator" + stringOf(type));
				return nullptr;
			}
		}
		else if (L->getType()->isDoubleTy())
		{
			// unary float
			switch (type)
			{
			case OperatorType::MINUS:
				return Builder.CreateFNeg(L, "fpfneg");

			case OperatorType::NOT:
				return Builder.CreateNot(L, "fpnot");

			default:
				CodeGenLogger.println("Invalid float unary operator" + stringOf(type));
				return nullptr;
			}
		}
		else
		{
			CodeGenLogger.println("Invalid unary operator " + stringOf(type));
			return nullptr;
		}
	}
	else
	{
		intPromotion(L, R);

		if (L->getType()->isIntegerTy() && R->getType()->isIntegerTy())
		{
			// binary int
			switch (type)
			{
			case OperatorType::PLUS:
				return Builder.CreateAdd(L, R, "intadd");
			case OperatorType::MINUS:
				return Builder.CreateSub(L, R, "intsub");
			case OperatorType::MUL:
				return Builder.CreateMul(L, R, "intmul");
			case OperatorType::DIV:
				return Builder.CreateSDiv(L, R, "intdiv");
			case OperatorType::MOD:
				return Builder.CreateSRem(L, R, "intdiv");

			case OperatorType::GE:
				return Builder.CreateICmpSGE(L, R, "intcmpge");
			case OperatorType::GT:
				return Builder.CreateICmpSGT(L, R, "intcmpgt");
			case OperatorType::LE:
				return Builder.CreateICmpSLE(L, R, "intcmple");
			case OperatorType::LT:
				return Builder.CreateICmpSLT(L, R, "intcmplt");
			case OperatorType::EQUAL:
				return Builder.CreateICmpEQ(L, R, "intcmpeq");
			case OperatorType::UNEQUAL:
				return Builder.CreateICmpNE(L, R, "intcmpne");

			case OperatorType::AND:
				return Builder.CreateAnd(L, R, "intand");
			case OperatorType::OR:
				return Builder.CreateOr(L, R, "intor");

			default:
				CodeGenLogger.println("Invalid int binary operator" + stringOf(type));
				return nullptr;
			}
		}
		else if (L->getType()->isDoubleTy() && R->getType()->isDoubleTy())
		{
			// binary float
			switch (type)
			{
			case OperatorType::PLUS:
				return Builder.CreateFAdd(L, R, "fpadd");
			case OperatorType::MINUS:
				return Builder.CreateFSub(L, R, "fpsub");
			case OperatorType::MUL:
				return Builder.CreateFMul(L, R, "fpmul");
			case OperatorType::DIV:
				return Builder.CreateFDiv(L, R, "fpdiv");
			case OperatorType::MOD:
				return Builder.CreateFRem(L, R, "fpdiv");

			case OperatorType::GE:
				return Builder.CreateFCmpUGE(L, R, "fpcmpge");
			case OperatorType::GT:
				return Builder.CreateFCmpUGT(L, R, "fpcmpgt");
			case OperatorType::LE:
				return Builder.CreateFCmpULE(L, R, "fpcmple");
			case OperatorType::LT:
				return Builder.CreateFCmpULT(L, R, "fpcmplt");
			case OperatorType::EQUAL:
				return Builder.CreateFCmpUEQ(L, R, "fpcmpeq");
			case OperatorType::UNEQUAL:
				return Builder.CreateFCmpUNE(L, R, "fpcmpne");

			case OperatorType::AND:
				return Builder.CreateAnd(L, R, "fpand");
			case OperatorType::OR:
				return Builder.CreateOr(L, R, "fpor");

			default:
				CodeGenLogger.println("Invalid float binary operator" + stringOf(type));
				return nullptr;
			}
		}
		else
		{
			CodeGenLogger.println("Invalid binary operator " + stringOf(type));
			return nullptr;
		}
	}
}

llvm::Function *ASTNode_FunctionHead::codeGen()
{
	llvm::FunctionType *funcType;
	bool hasPara = child->getType() == ASTNodeType::ParaDeclList;

	if (hasPara)
	{
		// with para
		std::vector<llvm::Type *> paraTypes;
		auto paraDecl = dynamic_cast<ASTNode_ParaTypeList *>(child->child);

		while (paraDecl)
		{
			if (paraDecl->paraList->getType() == ASTNodeType::VarParaList)
			{ // ref para, the type is ptr
				auto type = paraDecl->type->codeGen(true);
				for (int i = 0; i < paraDecl->paraList->name_list.size(); ++i)
					paraTypes.push_back(type);
			}
			else if (paraDecl->paraList->getType() == ASTNodeType::ValParaList)
			{ // value para
				auto type = paraDecl->type->codeGen();
				for (int i = 0; i < paraDecl->paraList->name_list.size(); ++i)
					paraTypes.push_back(type);
			}
			paraDecl = dynamic_cast<ASTNode_ParaTypeList *>(paraDecl->brother);
		}

		funcType = llvm::FunctionType::get(dynamic_cast<ASTNode_Type *>(child->brother)->codeGen(), paraTypes, false);
	}
	else
		// no para
		funcType = llvm::FunctionType::get(dynamic_cast<ASTNode_Type *>(child)->codeGen(), false);

	auto fun = llvm::Function::Create(funcType, llvm::Function::InternalLinkage, functionName, TheModule.get());

	// set function args' name
	if (hasPara)
	{
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
	}

	return fun;
}

llvm::Function *ASTNode_FunctionDecl::codeGen()
{
	auto funcHead = dynamic_cast<ASTNode_FunctionHead *>(child);

	auto fun = TheModule->getFunction(funcHead->functionName);
	// check if there's a function declaration with the same name
	if (!fun)
		fun = funcHead->codeGen();
	// check if funcHead generate code successfully
	if (!fun)
	{
		CodeGenLogger.println("Failed to generate function declaration for " + funcHead->functionName);
		return nullptr;
	}
	//check if the existed function declaration has been defined
	if (!fun->empty())
	{
		CodeGenLogger.println("Cannot redefine function " + funcHead->functionName);
		return nullptr;
	}

	auto BB = llvm::BasicBlock::Create(TheContext, funcHead->functionName + "_entry", fun);
	Builder.SetInsertPoint(BB);

	// set up a new variable table for this function
	currentSymbolTable->setupNewTable();

	// setup retval
	auto retName = funcHead->functionName;
	auto alloca = createEntryBlockAlloca(fun, retName, fun->getReturnType());
	currentSymbolTable->insertVariable(retName, alloca);

	for (auto &arg : fun->args())
	{
		if (arg.getType()->isPointerTy())
		{
			// ref arg
			currentSymbolTable->insertVariable(std::string(arg.getName()), reinterpret_cast<llvm::AllocaInst *>(&arg));
		}
		else
		{
			// val arg
			auto alloca = createEntryBlockAlloca(fun, std::string(arg.getName()), arg.getType());
			Builder.CreateStore(&arg, alloca);
			currentSymbolTable->insertVariable(std::string(arg.getName()), alloca);
		}
	}

	auto routine = dynamic_cast<ASTNode_SubRoutine *>(funcHead->brother);

	auto genBody = routine->codeGen(fun);
	if (genBody)
	{
		auto retVal = Builder.CreateLoad(alloca, retName);
		Builder.CreateRet(retVal);
		llvm::verifyFunction(*fun);
		TheFPM->run(*fun);
		currentSymbolTable->removeCurrentTable();
		return fun;
	}
	else
	{
		// revert function generation
		fun->eraseFromParent();
		currentSymbolTable->removeCurrentTable();
		CodeGenLogger.println("Failed to generate function body for " + funcHead->functionName);
		return nullptr;
	}
}

llvm::Function *ASTNode_ProcedureHead::codeGen()
{
	// procedure is almost the same as function, except that it has no return value
	llvm::FunctionType *procType;
	bool hasPara = child->getType() == ASTNodeType::ParaDeclList;

	if (hasPara)
	{
		// with para
		std::vector<llvm::Type *> paraTypes;
		auto paraDecl = dynamic_cast<ASTNode_ParaTypeList *>(child->child);

		while (paraDecl)
		{
			if (paraDecl->paraList->getType() == ASTNodeType::VarParaList)
			{ // ref para, the type is ptr
				auto type = paraDecl->type->codeGen(true);
				for (int i = 0; i < paraDecl->paraList->name_list.size(); ++i)
					paraTypes.push_back(type);
			}
			else if (paraDecl->paraList->getType() == ASTNodeType::ValParaList)
			{ // value para
				auto type = paraDecl->type->codeGen();
				for (int i = 0; i < paraDecl->paraList->name_list.size(); ++i)
					paraTypes.push_back(type);
			}
			paraDecl = dynamic_cast<ASTNode_ParaTypeList *>(paraDecl->brother);
		}

		procType = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), paraTypes, false);
	}
	else
		// no para
		procType = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), false);

	auto proc = llvm::Function::Create(procType, llvm::Function::InternalLinkage, procedureName, TheModule.get());

	// set procedure args' name
	if (hasPara)
	{
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
	}

	return proc;
}

llvm::Function *ASTNode_ProcedureDecl::codeGen()
{
	auto procHead = dynamic_cast<ASTNode_ProcedureHead *>(child);

	auto proc = TheModule->getFunction(procHead->procedureName);
	// check if there's a procedure declaration with the same name
	if (!proc)
		proc = procHead->codeGen();
	// check if funcHead generate code successfully
	if (!proc)
	{
		CodeGenLogger.println("Failed to generate procedure declaration for " + procHead->procedureName);
		return nullptr;
	}
	//check if the existed procedure declaration has been defined
	if (!proc->empty())
	{
		CodeGenLogger.println("Cannot redefine function " + procHead->procedureName);
		return nullptr;
	}

	auto BB = llvm::BasicBlock::Create(TheContext, procHead->procedureName + "_entry", proc);
	Builder.SetInsertPoint(BB);

	// set up variable table
	currentSymbolTable->setupNewTable();

	// setup retval
	auto retName = procHead->procedureName + "_ret";
	auto alloca = createEntryBlockAlloca(proc, retName, proc->getReturnType());
	currentSymbolTable->insertVariable(retName, alloca);

	for (auto &arg : proc->args())
	{
		if (arg.getType()->isPointerTy())
		{
			// ref arg
			currentSymbolTable->insertVariable(std::string(arg.getName()), reinterpret_cast<llvm::AllocaInst *>(&arg));
		}
		else
		{
			// val arg
			auto alloca = createEntryBlockAlloca(proc, std::string(arg.getName()), arg.getType());
			Builder.CreateStore(&arg, alloca);
			currentSymbolTable->insertVariable(std::string(arg.getName()), alloca);
		}
	}

	auto routine = dynamic_cast<ASTNode_SubRoutine *>(procHead->brother);

	auto genBody = routine->codeGen(proc);
	if (genBody)
	{
		auto retVal = Builder.CreateLoad(alloca, retName);
		Builder.CreateRet(retVal);
		llvm::verifyFunction(*proc);
		TheFPM->run(*proc);
		currentSymbolTable->removeCurrentTable();
		return proc;
	}
	else
	{
		// revert function generation
		proc->eraseFromParent();
		currentSymbolTable->removeCurrentTable();
		CodeGenLogger.println("Failed to generate function body for " + procHead->procedureName);
		return nullptr;
	}
}

void ASTNode_Routine::scanConstPart(ASTNode *part)
{
	ASTNode *constExpr = part->child;
	while (constExpr)
	{
		auto p = dynamic_cast<ASTNode_ConstExpr *>(constExpr);
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
		auto p = dynamic_cast<ASTNode_TypeDecl *>(typeDecl);
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

		auto type = p->type->codeGen();
		for (auto &name : p->list->name_list)
		{
			auto ptr = createEntryBlockAlloca(Builder.GetInsertBlock()->getParent(), name, type);
			GlobalTable.insertVariable(name, ptr);
		}

		varDecl = varDecl->brother;
	}
}

void ASTNode_Routine::scanRoutinePart(ASTNode *part)
{
	//TODO: add visibility?
	ASTNode *procDecl = part->child;
	while (procDecl)
	{
		if (procDecl->getType() == ASTNodeType::FunctionDecl)
		{
			auto p = dynamic_cast<ASTNode_FunctionDecl *>(procDecl);
			p->codeGen();
		}
		else if (procDecl->getType() == ASTNodeType::ProcedureDecl)
		{
			auto p = dynamic_cast<ASTNode_ProcedureDecl *>(procDecl);
			p->codeGen();
		}

		procDecl = procDecl->brother;
	}
}

llvm::Function *ASTNode_Routine::genRoutineHead()
{
	llvm::FunctionType *funcType = llvm::FunctionType::get(llvm::Type::getInt32Ty(TheContext), false);

	auto fun = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", TheModule.get());

	return fun;
}

llvm::Value *ASTNode_Routine::codeGen()
{
	// Routine is the body of program main, thus here we use global table.

	// incomplete routine without RoutineHead
	if (!child || child->getType() != ASTNodeType::RoutineHead)
	{
		CodeGenLogger.println("Incomplete main program without routine head");
		return nullptr;
	}

	ASTNode *routineHead = child;
	ASTNode *headPart = routineHead->child;

	auto mainFun = genRoutineHead();

	auto BB = llvm::BasicBlock::Create(TheContext, "entry", mainFun);
	Builder.SetInsertPoint(BB);

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

	// Routine Part will change insert point
	Builder.SetInsertPoint(BB);
	if (dynamic_cast<ASTNode_StmtCompound *>(routineHead->brother)->codeGen())
	{
		Builder.CreateRet(llvm::Constant::getNullValue(llvm::Type::getInt32Ty(TheContext)));
		llvm::verifyFunction(*mainFun);
		TheFPM->run(*mainFun);
		return RetValZero;
	}
	else
	{
		CodeGenLogger.println("Main has invalid stmt");
		return nullptr;
	}
}

void ASTNode_SubRoutine::scanConstPart(ASTNode *part)
{
	ASTNode *constExpr = part->child;
	while (constExpr)
	{
		auto p = dynamic_cast<ASTNode_ConstExpr *>(constExpr);
		auto v = p->value->codeGen();
		currentSymbolTable->insertConstant(p->constName, v);
		constExpr = constExpr->brother;
	}
}

void ASTNode_SubRoutine::scanTypePart(ASTNode *part)
{
	ASTNode *typeDecl = part->child;
	while (typeDecl)
	{
		auto p = dynamic_cast<ASTNode_TypeDecl *>(typeDecl);
		currentSymbolTable->insertType(p->defName, p->type->codeGen());
		typeDecl = typeDecl->brother;
	}
}

void ASTNode_SubRoutine::scanVarPart(ASTNode *part)
{
	ASTNode *varDecl = part->child;
	while (varDecl)
	{
		ASTNode_VarDecl *p = dynamic_cast<ASTNode_VarDecl *>(varDecl);

		auto type = p->type->codeGen();
		for (auto &name : p->list->name_list)
		{
			auto ptr = createEntryBlockAlloca(Builder.GetInsertBlock()->getParent(), name, type);
			currentSymbolTable->insertVariable(name, ptr);
		}

		varDecl = varDecl->brother;
	}
}

void ASTNode_SubRoutine::scanRoutinePart(ASTNode *part)
{
	ASTNode *procDecl = part->child;
	while (procDecl)
	{
		if (procDecl->getType() == ASTNodeType::FunctionDecl)
		{
			auto p = dynamic_cast<ASTNode_FunctionDecl *>(procDecl);
			p->codeGen();
		}
		else if (procDecl->getType() == ASTNodeType::ProcedureDecl)
		{
			auto p = dynamic_cast<ASTNode_ProcedureDecl *>(procDecl);
			p->codeGen();
		}

		procDecl = procDecl->brother;
	}
}

llvm::Value *ASTNode_SubRoutine::codeGen(llvm::Function *head)
{
	// subroutine is a code block surrounded by 'begin' and 'end'

	// incomplete subroutine without RoutineHead
	if (!child || child->getType() != ASTNodeType::RoutineHead)
	{
		CodeGenLogger.println("Incomplete function body without routine head: " + std::string(head->getName()));
		return nullptr;
	}

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

	// Routine Part will change insert point
	Builder.SetInsertPoint(&head->getEntryBlock());

	if (dynamic_cast<ASTNode_StmtCompound *>(routineHead->brother)->codeGen())
		return RetValZero;
	else
	{
		CodeGenLogger.println("function " + std::string(head->getName()) + "'s body has invalid stmt");
		return nullptr;
	}
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

	// get current function that the if stmt belonged to
	llvm::Function *fun = Builder.GetInsertBlock()->getParent();

	// attach then BB
	llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(TheContext, "then", fun);
	// not attached yet
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

	// update thenBB since then clause may change the current block, used by PHI
	thenBB = Builder.GetInsertBlock();

	// attach else BB to the function
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
		// without else clause, empty else BB
		elseV = llvm::Constant::getNullValue(llvm::Type::getInt1Ty(TheContext));

	Builder.CreateBr(ifcontBB);

	// update elseBB since else clause may change the current block, used by PHI
	elseBB = Builder.GetInsertBlock();

	// attach ifcont BB to the function
	fun->getBasicBlockList().push_back(ifcontBB);
	Builder.SetInsertPoint(ifcontBB);

	// stmt returns a bool
	llvm::PHINode *phiNode =
		Builder.CreatePHI(llvm::Type::getInt1Ty(TheContext), 2, "ifphi");

	phiNode->addIncoming(thenV, thenBB);
	phiNode->addIncoming(elseV, elseBB);
	// TODO: review, do we really need to return a phi node?
	return phiNode;
}

llvm::Value *ASTNode_StmtFor::codeGen()
{
	// child 1, start value expr
	auto startValue = dynamic_cast<ASTNode_Expr *>(child)->codeGen();
	if (!startValue)
	{
		CodeGenLogger.println("For stmt has invalid start value");
		return nullptr;
	}
	// only supports integer as stepping value
	if (!startValue->getType()->isIntegerTy())
	{
		CodeGenLogger.println("For stmt only supports integer for stepping");
		return nullptr;
	}

	// get current function that the for stmt belonged to
	auto fun = Builder.GetInsertBlock()->getParent();
	auto loopBB = llvm::BasicBlock::Create(TheContext, "forloop", fun);

	Builder.CreateBr(loopBB);

	Builder.SetInsertPoint(loopBB);

	// stepping value should be i32
	auto alloca = createEntryBlockAlloca(fun, varName, llvm::Type::getInt32Ty(TheContext));

	Builder.CreateStore(startValue, alloca);
	currentSymbolTable->insertVariable(varName, alloca);

	// child 2, end value expr
	auto endValue = dynamic_cast<ASTNode_Expr *>(child->brother)->codeGen();
	if (!endValue)
	{
		CodeGenLogger.println("Unresolved end value in for stmt");
		return nullptr;
	}
	// only supports integer as stepping value
	if (!endValue->getType()->isIntegerTy())
	{
		CodeGenLogger.println("For stmt only supports integer for stepping");
		return nullptr;
	}

	// child 3, for body
	auto body = dynamic_cast<ASTNode_Stmt *>(child->brother->brother)->codeGen();
	if (!body)
	{
		CodeGenLogger.println("Unresolved body in for stmt");
		return nullptr;
	}

	// to: ++, downto: --
	auto stepping = this->isPositive ? llvm::ConstantInt::get(TheContext, llvm::APInt(32, 1, true))
									 : llvm::ConstantInt::get(TheContext, llvm::APInt(32, -1, true));

	auto curVal = Builder.CreateLoad(alloca, varName);
	auto nextVar = Builder.CreateAdd(curVal, stepping, "stepping");
	Builder.CreateStore(curVal, alloca);

	// if stepping++, check if end value <= stepping
	// if stepping--, check if end value >= stepping
	// if loopCond is true, loop again
	auto loopCond = this->isPositive ? Builder.CreateICmpSLE(endValue, nextVar, "forloopcond") : Builder.CreateICmpSGE(endValue, nextVar, "forloopcond");

	llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(TheContext, "afterforloop", fun);

	Builder.CreateCondBr(loopCond, loopBB, afterBB);

	Builder.SetInsertPoint(afterBB);

	return RetValZero;
}

llvm::Value *ASTNode_StmtCompound::codeGen()
{
	auto stmtList = child;
	auto stmt = stmtList->child;

	// empty code block, return
	if (!stmt)
		return RetValZero;

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

	return RetValZero;
}

llvm::Value *ASTNode_StmtRepeat::codeGen()
{
	// get current function that the repeat stmt belonged to
	auto fun = Builder.GetInsertBlock()->getParent();
	auto loopBB = llvm::BasicBlock::Create(TheContext, "repeatloop", fun);

	Builder.CreateBr(loopBB);

	Builder.SetInsertPoint(loopBB);

	// child 1, loop body stmtList
	auto stmtList = dynamic_cast<ASTNode_StmtList *>(child);
	auto stmt = stmtList->child;
	while (stmt)
	{
		auto res = dynamic_cast<ASTNode_Stmt *>(stmt)->codeGen();
		if (!res)
		{
			CodeGenLogger.println("Repeat stmt has invalid stmt");
			return nullptr;
		}
		stmt = stmt->brother;
	}

	// child 2, end cond until
	auto curVal = dynamic_cast<ASTNode_Expr *>(child->brother)->codeGen();
	if (!curVal)
	{
		CodeGenLogger.println("Repeat stmt has invalid end expression");
		return nullptr;
	}

	// if end value == false, loopCond = true
	auto loopCond = Builder.CreateICmpEQ(curVal, llvm::ConstantInt::get(TheContext, llvm::APInt(curVal->getType()->getIntegerBitWidth(), 0)), "repeatloopcond");

	llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(TheContext, "afterrepeatloop", fun);

	Builder.CreateCondBr(loopCond, loopBB, afterBB);

	Builder.SetInsertPoint(afterBB);

	return RetValZero;
}

llvm::Value *ASTNode_StmtWhile::codeGen()
{
	// get current function that the while stmt belonged to
	auto fun = Builder.GetInsertBlock()->getParent();
	auto loopBB = llvm::BasicBlock::Create(TheContext, "whileloop", fun);
	auto bodyBB = llvm::BasicBlock::Create(TheContext, "whileloopbody");
	llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(TheContext, "afterwhileloop");

	Builder.CreateBr(loopBB);

	Builder.SetInsertPoint(loopBB);

	// child 1, end cond
	auto curVal = dynamic_cast<ASTNode_Expr *>(child)->codeGen();
	if (!curVal)
	{
		CodeGenLogger.println("While stmt has invalid end expression");
		return nullptr;
	}

	// if end == false, loopCond = true
	auto loopCond = Builder.CreateICmpNE(curVal, llvm::ConstantInt::get(TheContext, llvm::APInt(curVal->getType()->getIntegerBitWidth(), 0)), "whileloopcond");

	Builder.CreateCondBr(loopCond, bodyBB, afterBB);

	fun->getBasicBlockList().push_back(bodyBB);
	Builder.SetInsertPoint(bodyBB);

	// child 2, loop body stmt
	auto body = dynamic_cast<ASTNode_Stmt *>(child->brother)->codeGen();
	if (!body)
	{
		CodeGenLogger.println("While stmt has invalid stmt");
		return nullptr;
	}

	Builder.CreateBr(loopBB);

	fun->getBasicBlockList().push_back(afterBB);
	Builder.SetInsertPoint(afterBB);

	return RetValZero;
}

llvm::Value *ASTNode_StmtProc::codeGen()
{
	auto proc = TheModule->getFunction(procName);
	if (proc)
	{
		// function without args
		if (proc->arg_size() == 0)
		{
			std::vector<llvm::Value *> args;
			return Builder.CreateCall(proc, llvm::None, procName + "_call");
		}
		else
		{
			// function expected args but stmt has no args
			if (!child)
			{
				CodeGenLogger.println("Procedure expects args but not provided: " + procName);
				return nullptr;
			}

			auto argList = dynamic_cast<ASTNode_ArgList *>(child);
			if (argList->count == proc->arg_size())
			{
				std::vector<llvm::Value *> args;
				auto argNode = dynamic_cast<ASTNode_Expr *>(argList->child);

				// TODO: type check

				for (auto &arg : proc->args())
				{
					if (arg.getType()->isPointerTy())
					{
						auto v = argNode->codeGen();
						auto alloca = createEntryBlockAlloca(proc, std::string(arg.getName()), arg.getType());
						Builder.CreateStore(v, alloca);
						args.push_back(alloca);
					}
					else
					{
						args.push_back(argNode->codeGen());
					}
					argNode = dynamic_cast<ASTNode_Expr *>(argNode->brother);
				}
				Builder.CreateCall(proc, args, procName + "_call");
				// procedure doesn't have return value
				return RetValZero;
			}
			// function expects args but provided with different number of args
			CodeGenLogger.println("Procedure expects " + std::to_string(proc->arg_size()) + " args but provided " + std::to_string(argList->count) + ": " + procName);
			return nullptr;
		}
	}
	CodeGenLogger.println("Procedure not found in symbol table: " + procName);
	return nullptr;
}

llvm::Value *ASTNode_StmtAssign::codeGen()
{
	// declaration is done in routine head
	// TODO: only support single value yet
	auto alloca = currentSymbolTable->getVariable(lvalueName);
	auto v = dynamic_cast<ASTNode_Expr *>(child)->codeGen();
	Builder.CreateStore(v, alloca);
	return v;
}

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

llvm::Value *ASTNode_StmtGoto::codeGen()
{
	// only look for labels in the same parent block.
	// still, this may not reach labels after it.
	// should use a jump table to store all labeled basic blocks pointers.
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
		return RetValZero;
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
	auto head = dynamic_cast<ASTNode_Program *>(ASTHead);
	initializeIRBuilder(head->programName);

	auto routine = dynamic_cast<ASTNode_Routine *>(ASTHead->child);
	if (routine->codeGen())
	{
		TheModule->print(llvm::errs(), nullptr);
		printIR();
	}
	else
		llvm::errs() << "\nGenerate LLVM IR failed, see codegen.log for information.\n";
}

void ASTHandler::initializeIRBuilder(const std::string &programName)
{
	TheModule = std::make_unique<llvm::Module>(programName, TheContext);

	TheFPM = std::make_unique<llvm::legacy::FunctionPassManager>(TheModule.get());

	TheFPM->add(llvm::createInstructionCombiningPass());
	TheFPM->add(llvm::createReassociatePass());
	TheFPM->add(llvm::createGVNPass());
	TheFPM->add(llvm::createCFGSimplificationPass());
	TheFPM->doInitialization();
}

void ASTHandler::printIR()
{
	std::error_code errcode;
	llvm::raw_fd_ostream os("out.ll", errcode);

	TheModule->print(os, nullptr);

	os.close();
}