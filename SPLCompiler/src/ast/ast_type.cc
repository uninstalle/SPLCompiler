#include "ast_type.hh"
#include "../irgen/generator.hh"
#include "../irgen/table.hh"

llvm::Type *ASTNode_SimpleTypePlain::typeGen()
{
	if (name == "integer")
		return llvm::Type::getInt32Ty(*IRGenContext);
	if (name == "real")
		return llvm::Type::getDoubleTy(*IRGenContext);
	if (name == "char")
		return llvm::Type::getInt8Ty(*IRGenContext);
	if (name == "boolean")
		return llvm::Type::getInt1Ty(*IRGenContext);

	CodeGenLogger.println("Unrecognized simple type " + name);
	return nullptr;
}

llvm::Type *ASTNode_SimpleTypeEnumerate::typeGen()
{
	//TODO
}

llvm::Type *ASTNode_SimpleTypeSubRange::typeGen()
{
	//TODO
}

llvm::Type *ASTNode_ArrayType::typeGen()
{
	//TODO
}

llvm::Type *ASTNode_RecordType::typeGen()
{
	//TODO
}

llvm::Value *ASTNode_TypeDecl::codeGen()
{
	auto t = type->typeGen();
	if (!t)
		return logAndReturn("Type declaration is invalid: " + name);

	if (currentSymbolTable == GlobalTable)
	{
		// if it is defined in global table, then it is a global variable
		//
		// store the global value in the symbol table
		auto symbol = TypeSymbol(t);
		symbol.isGlobal = true;
		GlobalTable->insertType(name, symbol);
	}
	else
		// if not, just store the name as an alias of const value in the symbol table
		currentSymbolTable->insertType(name, t);

	return RetValZero;
}

llvm::Value *ASTNode_TypeDeclList::codeGen()
{
	for (auto typeDecl : children)
	{
		if (!typeDecl->codeGen())
			return nullptr;
	}
	return RetValZero;
}
