#include "table.hh"

SymbolTable GlobalTable;
SymbolTable *currentSymbolTable = &GlobalTable;
std::vector<SymbolTable *> SymbolTable::ARStack;

SymbolTable *SymbolTable::setupNewTable()
{
	auto t = new SymbolTable;
	t->prev = &GlobalTable;
	ARStack.push_back(t);
	currentSymbolTable = t;
	return t;
}

SymbolTable *SymbolTable::removeCurrentTable()
{
	if (currentSymbolTable == &GlobalTable)
	{
		llvm::errs() << "Trying to delete global symbol table, exitting\n";
		exit(1);
	}
	auto t = currentSymbolTable;
	ARStack.pop_back();
	currentSymbolTable = ARStack.back();
	delete t;
	return currentSymbolTable;
}

void SymbolTable::initialize()
{
	ARStack.push_back(&GlobalTable);
}