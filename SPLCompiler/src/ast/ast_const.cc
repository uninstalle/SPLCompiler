#include "ast_const.hh"
#include "../irgen/generator.hh"
#include "../irgen/table.hh"

llvm::Constant *ASTNode_ConstInteger::codeGen()
{
	return llvm::ConstantInt::get(*IRGenContext, llvm::APInt(32, value, true));
}

llvm::Constant *ASTNode_ConstReal::codeGen()
{
	return llvm::ConstantFP::get(*IRGenContext, llvm::APFloat(value));
}

llvm::Constant *ASTNode_ConstCharacter::codeGen()
{
	return llvm::ConstantInt::get(*IRGenContext, llvm::APInt(8, value, false));
}

llvm::Constant *ASTNode_ConstString::codeGen()
{
	std::vector<llvm::Constant *> charArray;
	for (auto &ch : value)
		charArray.emplace_back(llvm::ConstantInt::get(*IRGenContext, llvm::APInt(8, ch, false)));

	return llvm::ConstantArray::get(llvm::ArrayType::get(llvm::Type::getInt8Ty(*IRGenContext), charArray.size()), charArray);
}

llvm::Constant *ASTNode_ConstBoolean::codeGen()
{
	return llvm::ConstantInt::get(*IRGenContext, llvm::APInt(1, value, false));
}

llvm::Value *ASTNode_ConstDecl::codeGen()
{
	auto v = value->codeGen();

	if (!v)
		return logAndReturn("Const declaration has invalid rvalue: " + name);

	if (currentSymbolTable == GlobalTable)
	{
		// if it is defined in global table, then it is a global variable
		auto gv = new llvm::GlobalVariable(
			*IRGenModule, v->getType(), true,
			llvm::GlobalValue::InternalLinkage, v, name);
		// store the global value in the symbol table
		auto symbol = ConstantSymbol(gv);
		symbol.isGlobal = true;
		GlobalTable->insertConstant(name, symbol);
	}
	else
		// if not, just store the name as an alias of const value in the symbol table
		currentSymbolTable->insertConstant(name, v);

	return v;
}

llvm::Value *ASTNode_ConstDeclList::codeGen()
{
	for (auto constDecl : children)
	{
		if (!constDecl->codeGen())
			return nullptr;
	}
	return RetValZero;
}
