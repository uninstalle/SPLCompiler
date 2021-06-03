#pragma once
#include <map>
#include <string>
#include <llvm/IR/BasicBlock.h>

class SymbolTable
{
	std::map<std::string, llvm::Value*> constant;
	std::map<std::string, llvm::Type*> type;
	std::map<std::string, llvm::Value*> variable;
	std::map<std::string, llvm::Function*> function;

public:


	void insertConstant(const std::string& name, llvm::Value* value)
	{
		constant.insert(std::make_pair(name, value));
	}
	llvm::Value* getConstant(const std::string& name)
	{
		auto res = constant.find(name);
		if (res == constant.end())
			return nullptr;
		else return res->second;
	}

	void insertType(const std::string& name, llvm::Type* value)
	{
		type.insert(std::make_pair(name, value));
	}
	llvm::Type* getType(const std::string& name)
	{
		auto res = type.find(name);
		if (res == type.end())
			return nullptr;
		else return res->second;
	}

	void insertVariable(const std::string& name, llvm::Value* value)
	{
		variable.insert(std::make_pair(name, value));
	}
	llvm::Value* getVariable(const std::string& name)
	{
		auto res = variable.find(name);
		if (res == variable.end())
			return nullptr;
		else return res->second;
	}
	void removeVariable(const std::string &name)
	{
		variable.erase(name);
	}
	void clearVariable()
	{
		variable.clear();
	}
	

	void insertFunction(const std::string& name, llvm::Function* value)
	{
		function.insert(std::make_pair(name, value));
	}
	llvm::Function* getFunction(const std::string& name)
	{
		auto res = function.find(name);
		if (res == function.end())
			return nullptr;
		else return res->second;
	}
};

extern SymbolTable GlobalTable;