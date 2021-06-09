#include "table.hh"

std::shared_ptr<SymbolTable> GlobalTable;
std::shared_ptr<SymbolTable> currentSymbolTable;

std::vector<std::shared_ptr<SymbolTable>> SymbolTable::ARStack;
std::map<std::string, llvm::Constant*> SymbolTable::GlobalStringMap;

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

void SymbolTable::insertGlobalString(const std::string& str, llvm::Constant* gs)
{
    GlobalStringMap.insert(std::make_pair(str, gs));
}

llvm::Constant* SymbolTable::getGlobalString(const std::string& str)
{
    auto res = GlobalStringMap.find(str);
    if (res == GlobalStringMap.end())
        return nullptr;
    else
        return res->second;
}

