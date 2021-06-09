#pragma once
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>

extern std::unique_ptr<llvm::LLVMContext> IRGenContext;
extern std::unique_ptr<llvm::IRBuilder<>> IRGenBuilder;
extern std::unique_ptr<llvm::Module> IRGenModule;
extern std::unique_ptr<llvm::legacy::FunctionPassManager> IRGenFPM;
extern llvm::Constant* RetValZero;

class ASTNode;

class ASTHandler
{
    static void initializeIRGenerator(const std::string& name, bool optimize);
    static void recursivePrintAST(ASTNode* head, int depth);
    static void printIR();
    static void printAST();

public:
    ASTHandler() = delete;
    static void setASTHead(ASTNode* head);
    static void codeGen(bool optimize);
};
