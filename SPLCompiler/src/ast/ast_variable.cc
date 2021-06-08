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
    auto t = type->typeGen();
    // if this is a declared type, then its name in symbol table can be got from this method
    // if not, use the return value of toString method as a type name
    auto typeName = type->toString();
    if (!currentSymbolTable->getType(typeName))
        currentSymbolTable->insertType(typeName, *t);

    if (!t)
        return logAndReturn("Variable declaration has invalid type: " + list->toString());


    for (auto name : list->list)
    {
        if (currentSymbolTable == GlobalTable)
        {
            // set global variable's initial value to zero
            auto v = llvm::Constant::getNullValue(t->raw);
            auto gv = new llvm::GlobalVariable(
                *IRGenModule,
                t->raw,
                false,
                llvm::GlobalValue::InternalLinkage,
                v,
                name);
            // store the global value in the symbol table
            GlobalTable->insertVariable(name, { gv,typeName,true });
        }
        else
        {
            auto ptr = allocInEntryBlock(IRGenBuilder->GetInsertBlock()->getParent(), name, t->raw);
            currentSymbolTable->insertVariable(name, { ptr,typeName });
        }
    }
    return RetValZero;
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
