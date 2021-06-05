#pragma once
#include <map>
#include <string>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instructions.h>

class SymbolTable
{
	std::map<std::string, llvm::Constant*> constant;
	std::map<std::string, llvm::Type*> type;
	std::map<std::string, llvm::AllocaInst*> variable;
	std::map<std::string, llvm::Function*> function;

	SymbolTable* prev = nullptr;

public:


	void insertConstant(const std::string& name, llvm::Constant* value)
	{
		constant.insert(std::make_pair(name, value));
	}
	llvm::Constant* getConstant(const std::string& name)
	{
		auto res = constant.find(name);
		if (res == constant.end())
		{
			if (prev)
				return prev->getConstant(name);
			else
				return nullptr;
		}
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
		{
			if (prev)
				return prev->getType(name);
			else
			return nullptr;
		}
		else return res->second;
	}

	void insertVariable(const std::string& name, llvm::AllocaInst* value)
	{
		variable.insert(std::make_pair(name, value));
	}
	llvm::AllocaInst* getVariable(const std::string& name)
	{
		auto res = variable.find(name);
		if (res == variable.end())
		{
			if (prev)
				return prev->getVariable(name);
			else
				return nullptr;
		}
		else return res->second;
	}
	

	void insertFunction(const std::string& name, llvm::Function* value)
	{
		function.insert(std::make_pair(name, value));
	}
	llvm::Function* getFunction(const std::string& name)
	{
		auto res = function.find(name);
		if (res == function.end())
		{
			if (prev)
				return prev->getFunction(name);
			else
				return nullptr;
		}
		else return res->second;
	}

	static SymbolTable* setupNewTable();

	static SymbolTable* removeCurrentTable();
};

extern SymbolTable GlobalTable;
extern SymbolTable* currentSymbolTable;