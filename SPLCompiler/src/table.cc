#include "table.hh"

SymbolTable GlobalTable;
SymbolTable* currentSymbolTable = &GlobalTable;

SymbolTable* SymbolTable::setupNewTable()
{
	auto t = new SymbolTable;
	t->prev = currentSymbolTable;
	currentSymbolTable = t;
	return t;
}

SymbolTable* SymbolTable::removeCurrentTable()
{
	auto t = currentSymbolTable;
	currentSymbolTable = currentSymbolTable->prev;
	delete t;
	return currentSymbolTable;
}
