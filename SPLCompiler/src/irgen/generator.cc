#include "generator.hh"
#include "../ast/ast_base.hh"
#include "../logger/log.hh"
#include "table.hh"

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>

std::unique_ptr<llvm::LLVMContext> IRGenContext;
std::unique_ptr<llvm::IRBuilder<>> IRGenBuilder;
std::unique_ptr<llvm::Module> IRGenModule;
std::unique_ptr<llvm::legacy::FunctionPassManager> IRGenFPM;
llvm::Constant* RetValZero; // i32 0
static ASTNode* ASTHead = nullptr;


void ASTHandler::initializeIRGenerator(const std::string& name)
{
	IRGenContext = std::make_unique<llvm::LLVMContext>();
	IRGenBuilder = std::make_unique<llvm::IRBuilder<>>(*IRGenContext);
	IRGenModule = std::make_unique<llvm::Module>(name, *IRGenContext);
	IRGenFPM = std::make_unique<llvm::legacy::FunctionPassManager>(IRGenModule.get());
	RetValZero = llvm::Constant::getNullValue(llvm::Type::getInt32Ty(*IRGenContext));

	IRGenFPM->add(llvm::createInstructionCombiningPass());
	IRGenFPM->add(llvm::createReassociatePass());
	IRGenFPM->add(llvm::createGVNPass());
	IRGenFPM->add(llvm::createCFGSimplificationPass());
	IRGenFPM->doInitialization();
}


void ASTHandler::recursivePrintAST(ASTNode* head, int depth)
{
	std::string spacing(depth, ' ');

	YaccLogger.print(spacing);
	head->print();

	for (auto child : head->children)
		recursivePrintAST(child, depth + 2);
}


void ASTHandler::printIR()
{
	std::error_code errcode;
	llvm::raw_fd_ostream os("out.ll", errcode);

	IRGenModule->print(os, nullptr);

	os.close();
}

void ASTHandler::printAST()
{
	recursivePrintAST(ASTHead, 0);
}

void ASTHandler::setASTHead(ASTNode* head)
{
	ASTHead = head;
}


void ASTHandler::codeGen()
{
	if (!ASTHead)
		return;
	printAST();

	SymbolTable::initialize();
	initializeIRGenerator("what");

	if (ASTHead->codeGen())
	{
		// to file
		IRGenModule->print(llvm::errs(), nullptr);
		// to console
		printIR();
	}
	else
		llvm::errs() << "\nGenerate LLVM IR failed, see codegen.log for information.\n";
}
