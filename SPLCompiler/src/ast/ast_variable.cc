#include "ast_variable.hh"
#include "../irgen/generator.hh"
#include "../irgen/table.hh"



llvm::AllocaInst* allocInEntryBlock(llvm::Function* fun, const std::string& varName, llvm::Type* type)
{
	llvm::IRBuilder<> builder(&fun->getEntryBlock(), fun->getEntryBlock().begin());
	return builder.CreateAlloca(type, nullptr, varName);
}


llvm::Value* ASTNode_VarDecl::codeGen()
{
	auto t = type->codeGen();

	if (!t)
		return logAndReturn("Variable declaration has invalid type: " + list->toString());


	auto v = llvm::Constant::getNullValue(t);

	for (auto name : list->list)
	{
		if (currentSymbolTable == GlobalTable)
		{
			// if it is defined in global table, then it is a global variable
			auto gv = new llvm::GlobalVariable(
				*IRGenModule,
				t,
				false,
				llvm::GlobalValue::InternalLinkage,
				v,
				name);
			// store the global value in the symbol table
			auto symbol = VariableSymbol(gv);
			symbol.isGlobal = true;
			GlobalTable->insertVariable(name, symbol);
		}
		else
		{
			auto ptr = allocInEntryBlock(IRGenBuilder->GetInsertBlock()->getParent(), name, t);
			currentSymbolTable->insertVariable(name, ptr);
		}
	}
	return v;
}


llvm::Value* ASTNode_VarDeclList::codeGen()
{
	for (auto varDecl : children)
	{
		if (!varDecl->codeGen())
			return nullptr;
	}
	return RetValZero;
}

