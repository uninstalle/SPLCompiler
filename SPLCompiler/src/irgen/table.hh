#pragma once
#include <map>
#include <string>
#include <llvm/IR/Instructions.h>

struct ConstantSymbol
{
	llvm::Constant* raw;

	bool isGlobal = false;

	ConstantSymbol(llvm::Constant* p) :raw(p) {}

	llvm::Constant* operator->() const
	{
		return raw;
	}
};

struct TypeSymbol
{
	llvm::Type* raw;

	bool isGlobal = false;

	TypeSymbol(llvm::Type* p) :raw(p) {}

	llvm::Type* operator->() const
	{
		return raw;
	}
};

struct VariableSymbol
{
	llvm::Value* raw;

	bool isGlobal = false;

	VariableSymbol(llvm::Value* p) :raw(p) {}

	llvm::Value* operator->() const
	{
		return raw;
	}
};

struct FunctionSymbol
{
	llvm::Function* raw;

	bool isGlobal = false;

	std::vector<bool> isRefArg;

	FunctionSymbol(llvm::Function* p) : raw(p) {}

	llvm::Function* operator->() const
	{
		return raw;
	}
};

class SymbolTable
{
	std::map<std::string, ConstantSymbol> constant;
	std::map<std::string, TypeSymbol> type;
	std::map<std::string, VariableSymbol> variable;
	std::map<std::string, FunctionSymbol> function;

	static std::vector<std::shared_ptr<SymbolTable>> ARStack;

	std::shared_ptr<SymbolTable> prev = nullptr;

public:
	void insertConstant(const std::string& name, ConstantSymbol value)
	{
		constant.insert(std::make_pair(name, value));
	}
	ConstantSymbol getConstant(const std::string& name)
	{
		auto res = constant.find(name);
		if (res == constant.end())
		{
			if (prev)
				return prev->getConstant(name);
			else
				return nullptr;
		}
		else
			return res->second;
	}

	void insertType(const std::string& name, TypeSymbol value)
	{
		type.insert(std::make_pair(name, value));
	}
	TypeSymbol getType(const std::string& name)
	{
		auto res = type.find(name);
		if (res == type.end())
		{
			if (prev)
				return prev->getType(name);
			else
				return nullptr;
		}
		else
			return res->second;
	}

	void insertVariable(const std::string& name, VariableSymbol value)
	{
		variable.insert(std::make_pair(name, value));
	}
	VariableSymbol getVariable(const std::string& name)
	{
		auto res = variable.find(name);
		if (res == variable.end())
		{
			if (prev)
				return prev->getVariable(name);
			else
				return nullptr;
		}
		else
			return res->second;
	}

	void insertFunction(const std::string& name, FunctionSymbol value)
	{
		function.insert(std::make_pair(name, value));
	}
	FunctionSymbol getFunction(const std::string& name)
	{
		auto res = function.find(name);
		if (res == function.end())
		{
			if (prev)
				return prev->getFunction(name);
			else
				return nullptr;
		}
		else
			return res->second;
	}

	static void setupNewTable();

	static void removeCurrentTable();

	static void initialize();
};

extern std::shared_ptr<SymbolTable> GlobalTable;
extern std::shared_ptr<SymbolTable> currentSymbolTable;