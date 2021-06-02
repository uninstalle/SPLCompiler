#pragma once
#include <map>
#include <string>
#include <llvm/IR/BasicBlock.h>

class GlobalTable
{
	static std::map<std::string, llvm::Value*> constant;
	static std::map<std::string, llvm::Type*> type;
	static std::map<std::string, llvm::Value*> variable;
	static std::map<std::string, llvm::Function*> function;

public:

	GlobalTable() = delete;


	static void insertConstant(const std::string& name, llvm::Value* value)
	{
		constant.insert(std::make_pair(name, value));
	}
	static llvm::Value* getConstant(const std::string& name)
	{
		auto res = constant.find(name);
		if (res == constant.end())
			return nullptr;
		else return res->second;
	}

	static void insertType(const std::string& name, llvm::Type* value)
	{
		type.insert(std::make_pair(name, value));
	}
	static llvm::Type* getType(const std::string& name)
	{
		auto res = type.find(name);
		if (res == type.end())
			return nullptr;
		else return res->second;
	}

	static void insertVariable(const std::string& name, llvm::Value* value)
	{
		variable.insert(std::make_pair(name, value));
	}
	static llvm::Value* getVariable(const std::string& name)
	{
		auto res = variable.find(name);
		if (res == variable.end())
			return nullptr;
		else return res->second;
	}
	static void clearVariable()
	{
		variable.clear();
	}
	

	static void insertFunction(const std::string& name, llvm::Function* value)
	{
		function.insert(std::make_pair(name, value));
	}
	static llvm::Function* getFunction(const std::string& name)
	{
		auto res = function.find(name);
		if (res == function.end())
			return nullptr;
		else return res->second;
	}
};
