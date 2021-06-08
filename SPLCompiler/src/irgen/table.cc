#include "table.hh"

std::shared_ptr<SymbolTable> GlobalTable;
std::shared_ptr<SymbolTable> currentSymbolTable;

std::vector<std::shared_ptr<SymbolTable>> SymbolTable::ARStack;

void SymbolTable::setupNewTable()
{
	auto t = std::make_shared<SymbolTable>();
	t->prev = GlobalTable;
	ARStack.push_back(t);
	currentSymbolTable = t;
}

void SymbolTable::removeCurrentTable()
{
	if (currentSymbolTable == GlobalTable)
	{
		llvm::errs() << "Trying to delete global symbol table, exiting\n";
		exit(1);
	}
	ARStack.pop_back();
	currentSymbolTable = ARStack.back();
}

void SymbolTable::initialize()
{
	GlobalTable = std::make_shared<SymbolTable>();
	currentSymbolTable = GlobalTable;
	ARStack.push_back(GlobalTable);
}