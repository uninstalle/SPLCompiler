#pragma once
#include <map>
#include <string>
#include <llvm/IR/BasicBlock.h>

class GlobalTable
{
	static std::map<std::string, llvm::Value*> constant;
	static std::map<std::string, llvm::Type*> type;
	static std::map<std::string, llvm::Type*> variable;
	static std::map<std::string, llvm::Function*> function;

public:

	GlobalTable() = delete;


	static void insertConstant(const std::string& name, llvm::Value* value)
	{
		constant.insert(std::make_pair(name, value));
	}
	static llvm::Value* getConstant(const std::string& name)
	{
		return constant.find(name)->second;
	}
	
	static void insertType(const std::string& name, llvm::Type* value)
	{
		type.insert(std::make_pair(name, value));
	}
	static llvm::Type* getType(const std::string& name)
	{
		return type.find(name)->second;
	}

	static void insertVariable(const std::string& name, llvm::Type* value)
	{
		variable.insert(std::make_pair(name, value));
	}
	static llvm::Type* getVariable(const std::string& name)
	{
		return variable.find(name)->second;
	}
	
	static void insertFunction(const std::string& name, llvm::Function* value)
	{
		function.insert(std::make_pair(name, value));
	}
	static llvm::Function* getFunction(const std::string& name)
	{
		return function.find(name)->second;
	}
};
