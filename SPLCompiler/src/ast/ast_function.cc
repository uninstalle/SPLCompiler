#include "ast_function.hh"
#include "ast_routine.hh"
#include "../irgen/generator.hh"
#include "../irgen/table.hh"
#include <llvm/IR/Verifier.h>

llvm::Value *ASTNode_FunctionHead::codeGen()
{
	llvm::FunctionType *funcType;
	std::vector<bool> isRef;
	bool hasPara = parameters->children.empty() == false;

	if (!hasPara)
		funcType = llvm::FunctionType::get(retType->typeGen(), false);
	else
	{
		std::vector<llvm::Type *> paraTypes;

		for (auto paraDecl : parameters->children)
		{
			auto paraTypeList = dynamic_cast<ASTNode_ParaTypeList *>(paraDecl);
			if (paraTypeList->list->getType() == ASTNodeType::VarParaList)
			{ // ref para, use ptr
				auto type = paraTypeList->type->typeGen()->getPointerTo();
				for (int i = 0; i < paraTypeList->list->list.size(); ++i)
				{
					paraTypes.push_back(type);
					isRef.push_back(true);
				}
			}
			else
			{
				auto type = paraTypeList->type->typeGen();
				for (int i = 0; i < paraTypeList->list->list.size(); ++i)
				{
					paraTypes.push_back(type);
					isRef.push_back(false);
				}
			}
		}
		if (retType)
			funcType = llvm::FunctionType::get(retType->typeGen(), paraTypes, false);
		else // if retType is null, then this is a procedure
			funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(*IRGenContext), paraTypes, false);
	}

	auto fun = llvm::Function::Create(funcType, llvm::Function::InternalLinkage, name, *IRGenModule);

	// set function args' name
	if (hasPara)
	{
		auto iter = fun->args().begin();

		for (auto paraDecl : parameters->children)
		{
			auto paraTypeList = dynamic_cast<ASTNode_ParaTypeList *>(paraDecl);
			for (auto name : paraTypeList->list->list)
			{
				iter->setName(name);
				iter++;
			}
		}
	}

	if (currentSymbolTable == GlobalTable)
	{
		auto symbol = FunctionSymbol(fun);
		symbol.isRefArg = isRef;
		symbol.isGlobal = true;
		GlobalTable->insertFunction(name, symbol);
	}
	else
	{
		auto symbol = FunctionSymbol(fun);
		symbol.isRefArg = isRef;
		currentSymbolTable->insertFunction(name, symbol);
	}
	return fun;
}

llvm::Value *ASTNode_ProcedureHead::codeGen()
{
	return ASTNode_FunctionHead::codeGen();
}

llvm::Value *ASTNode_FunctionDecl::codeGen()
{
	auto fun = currentSymbolTable->getFunction(head->name).raw;
	// check if there's a function declaration with the same name
	if (!fun)
		fun = reinterpret_cast<llvm::Function *>(head->codeGen());
	// check if funcHead generate code successfully
	if (!fun)
		return logAndReturn("Failed to generate function declaration for " + head->name);
	//check if the existed function declaration has been defined
	if (!fun->empty())
		return logAndReturn("Cannot redefine function " + head->name);

	auto symbol = currentSymbolTable->getFunction(head->name);
	auto isRefIter = symbol.isRefArg.begin();

	auto bodyBB = llvm::BasicBlock::Create(*IRGenContext, head->name + "_entry", fun);
	IRGenBuilder->SetInsertPoint(bodyBB);

	// set up a new variable table for this function
	currentSymbolTable->setupNewTable();

	// setup retval variable
	auto retName = head->name;
	llvm::AllocaInst *retVar;
	if (!fun->getReturnType()->isVoidTy())
	{
		retVar = allocInEntryBlock(fun, retName, fun->getReturnType());
		currentSymbolTable->insertVariable(retName, retVar);
	}

	// setup local variables
	for (auto &arg : fun->args())
	{
		if (*isRefIter++)
			// ref arg, don't create a local variable
			currentSymbolTable->insertVariable(std::string(arg.getName()), &arg);
		else
		{
			auto localVar = allocInEntryBlock(fun, std::string(arg.getName()), arg.getType());
			IRGenBuilder->CreateStore(&arg, localVar);
			currentSymbolTable->insertVariable(std::string(arg.getName()), localVar);
		}
	}

	if (body->codeGen())
	{
		// set return val
		if (!fun->getReturnType()->isVoidTy())
		{
			auto retVal = IRGenBuilder->CreateLoad(retVar, retName);
			IRGenBuilder->CreateRet(retVal);
		}
		else
			IRGenBuilder->CreateRet(nullptr);

		llvm::verifyFunction(*fun);
		IRGenFPM->run(*fun);
		currentSymbolTable->removeCurrentTable();
		return fun;
	}
	else
	{
		// revert function generation
		fun->eraseFromParent();
		currentSymbolTable->removeCurrentTable();
		return logAndReturn("Failed to generate function body for " + head->name);
	}
}

llvm::Value *ASTNode_ProcedureDecl::codeGen()
{
	return ASTNode_FunctionDecl::codeGen();
}

llvm::Value *ASTNode_RoutinePart::codeGen()
{
	for (auto funcDecl : children)
	{
		if (!funcDecl->codeGen())
			return nullptr;
	}
	return RetValZero;
}
