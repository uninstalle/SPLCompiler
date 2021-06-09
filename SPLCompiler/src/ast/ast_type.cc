#include "ast_type.hh"
#include "../irgen/generator.hh"
#include "../irgen/table.hh"


std::string ASTNode_Type::getSimpleTypeName(llvm::Type* type)
{
    if (type->isIntegerTy())
    {
        if (type->getIntegerBitWidth() == 32)
            return "integer";
        else if (type->getIntegerBitWidth() == 8)
            return "char";
        else if (type->getIntegerBitWidth() == 1)
            return "boolean";
        else
            return "i" + std::to_string(type->getIntegerBitWidth());
    }
    else if (type->isDoubleTy())
        return "real";
    else if (type->isPointerTy())
        // recursively get pointer's final element type
        return "pointer" + getSimpleTypeName(type->getPointerElementType());
    else
        return "unrecognized";
}


std::shared_ptr<TypeSymbol> ASTNode_SimpleTypePlain::typeGen()
{
    auto t = currentSymbolTable->getType(name);
    if (t)
        return t;
    else
        CodeGenLogger.println("Unrecognized simple type " + name);
    return nullptr;
}

std::shared_ptr<TypeSymbol> ASTNode_SimpleTypeEnumerate::typeGen()
{
    // enum is implemented as integer
    auto enumSymbol = std::make_shared<TypeSymbol>(llvm::Type::getInt32Ty(*IRGenContext),
        TypeSymbol::ExtraTypeInfo::Enumerate);
    // copy the name list to symbol attribute
    enumSymbol->attributes = list->list;
    return enumSymbol;
}

std::shared_ptr<TypeSymbol> ASTNode_SimpleTypeSubRange::typeGen()
{
    // sub range is implemented as integer
    auto subRangeSymbol = std::make_shared<TypeSymbol>(llvm::Type::getInt32Ty(*IRGenContext),
        TypeSymbol::ExtraTypeInfo::SubRange);
    // copy the bounds of sub range to symbol attribute
    subRangeSymbol->attributes.push_back(begin);
    subRangeSymbol->attributes.push_back(end);
    return subRangeSymbol;
}

std::shared_ptr<TypeSymbol> ASTNode_ArrayType::typeGen()
{
    auto indexSymbol = indexType->typeGen();
    if (!indexSymbol)
    {
        logAndReturn("Array declaration has invalid index type");
        return nullptr;
    }
    auto elementSymbol = elementType->typeGen();
    if (!elementSymbol)
    {
        logAndReturn("Array declaration has invalid element type");
        return nullptr;
    }

    int size;
    // only supports enum and sub range, other types have a too large range
    if (indexSymbol->exType == TypeSymbol::ExtraTypeInfo::Enumerate)
    {
        size = indexSymbol->attributes.size();
    }
    else if (indexSymbol->exType == TypeSymbol::ExtraTypeInfo::SubRange)
    {
        size = std::stoi(indexSymbol->attributes[1]) - std::stoi(indexSymbol->attributes[0]) + 1;
    }
    else
    {
        logAndReturn("Array declaration has unsupported index type");
        return nullptr;
    }

    auto t = llvm::ArrayType::get(elementSymbol->raw, size);
    auto arraySymbol = std::make_shared<TypeSymbol>(t, TypeSymbol::ExtraTypeInfo::Array);
    arraySymbol->attributes = indexSymbol->attributes;
    arraySymbol->attributes.insert(arraySymbol->attributes.begin(), std::to_string(size));
    return arraySymbol;
}

std::shared_ptr<TypeSymbol> ASTNode_RecordType::typeGen()
{
    //TODO
}

llvm::Value* ASTNode_TypeDecl::codeGen()
{
    auto t = currentSymbolTable->getType(name);
    if (t)
        return logAndReturn("Type has been defined: " + name);
    t = type->typeGen();
    if (!t)
        return logAndReturn("Type declaration is invalid: " + name);

    if (currentSymbolTable == GlobalTable)
    {
        t->isGlobal = true;
        GlobalTable->insertType(name, *t);
    }
    else
        currentSymbolTable->insertType(name, *t);

    return RetValZero;
}

llvm::Value* ASTNode_TypeDeclList::codeGen()
{
    for (auto typeDecl : children)
    {
        if (!typeDecl->codeGen())
            return nullptr;
    }
    return RetValZero;
}
