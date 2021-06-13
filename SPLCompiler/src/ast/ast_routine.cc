#include "ast_routine.hh"
#include "../irgen/generator.hh"
#include "../irgen/table.hh"
#include <llvm/IR/Verifier.h>

llvm::Value* ASTNode_RoutineHead::codeGen()
{
    if (constPart)
        if (!constPart->codeGen())
            return logAndReturn("Const part generate failed");
    if (typePart)
        if (!typePart->codeGen())
            return logAndReturn("Type part generate failed");
    if (varPart)
        if (!varPart->codeGen())
            return logAndReturn("Var part generate failed");
    if (routinePart)
        if (!routinePart->codeGen())
            return logAndReturn("Routine part generate failed");

    return RetValZero;
}

llvm::Value* ASTNode_Routine::codeGen()
{
    auto main = IRGenBuilder->GetInsertBlock()->getParent();

    if (!head->codeGen())
        return logAndReturn("Main head generate failed");

    // Routine Part may change the insert point when creating functions
    IRGenBuilder->SetInsertPoint(&main->getBasicBlockList().back());

    // This will decide if the definition part of main is global or not.
    // To make them global, delete this.
    SymbolTable::setupNewTable();

    if (body->codeGen())
        return RetValZero;
    else
        return logAndReturn("Main body has invalid stmt");
}

llvm::Value* ASTNode_SubRoutine::codeGen()
{
    auto fun = IRGenBuilder->GetInsertBlock()->getParent();

    if (!head->codeGen())
        return logAndReturn("Function head generate failed");

    // Routine Part may change the insert point when creating functions
    IRGenBuilder->SetInsertPoint(&fun->getEntryBlock());

    if (body->codeGen())
        return RetValZero;
    else
        return logAndReturn("Function " + std::string(fun->getName()) + "'s body has invalid stmt");
}

void ASTNode_Program::setupSystemType()
{
    GlobalTable->insertType("integer", llvm::Type::getInt32Ty(*IRGenContext));
    GlobalTable->insertType("real", llvm::Type::getDoubleTy(*IRGenContext));
    GlobalTable->insertType("char", llvm::Type::getInt8Ty(*IRGenContext));
    GlobalTable->insertType("boolean", llvm::Type::getInt1Ty(*IRGenContext));

}


// i32 main(void)
llvm::Function* ASTNode_Program::setupMainFunction()
{
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*IRGenContext), false);

    return llvm::Function::Create(
        funcType, llvm::Function::ExternalLinkage,
        "main",
        IRGenModule.get());
}

llvm::Value* ASTNode_Program::codeGen()
{
    setupSystemType();
    auto main = setupMainFunction();
    auto mainBB = llvm::BasicBlock::Create(*IRGenContext, "entry", main);
    IRGenBuilder->SetInsertPoint(mainBB);

    if (routine->codeGen())
    {
        IRGenBuilder->CreateRet(RetValZero);
        llvm::verifyFunction(*main);
        SymbolTable::removeCurrentTable();
        IRGenFPM->run(*main);
        return RetValZero;
    }
    else
        return logAndReturn("Create main failed");
}
