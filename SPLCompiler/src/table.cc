#include "table.hh"

std::map<std::string, llvm::Value *> GlobalTable::constant;
std::map<std::string, llvm::Type *> GlobalTable::type;
std::map<std::string, llvm::Value *> GlobalTable::variable;
std::map<std::string, llvm::Function *> GlobalTable::function;