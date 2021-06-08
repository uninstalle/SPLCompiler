#pragma once
#include <map>
#include <string>
#include <llvm/IR/Instructions.h>

struct ConstantSymbol
{
    llvm::Constant* raw;
    bool isGlobal;

    ConstantSymbol(llvm::Constant* p, bool isGlobal = false)
        : raw(p), isGlobal(isGlobal) {}

    llvm::Constant* operator->() const
    {
        return raw;
    }
};

struct TypeSymbol
{
    enum class ExtraTypeInfo
    {
        Base,
        Enumerate,
        SubRange,
        Array,
        String,
        Record
    };

    llvm::Type* raw;
    ExtraTypeInfo exType;
    bool isGlobal;
    std::vector<std::string> attributes;

    TypeSymbol(llvm::Type* t, ExtraTypeInfo ex = ExtraTypeInfo::Base, bool isGlobal = false)
        :raw(t), exType(ex), isGlobal(isGlobal) {}

    llvm::Type* operator->() const
    {
        return raw;
    }
};

struct VariableSymbol
{
    llvm::Value* raw;
    std::string typeName;
    bool isGlobal;

    VariableSymbol(llvm::Value* p, std::string type, bool isGlobal = false)
        : raw(p), typeName(type), isGlobal(isGlobal) {}

    llvm::Value* operator->() const
    {
        return raw;
    }
};

struct FunctionSymbol
{
    llvm::Function* raw;
    bool isGlobal;

    std::vector<bool> isRefArg;

    FunctionSymbol(llvm::Function* p, bool isGlobal = false)
        : raw(p), isGlobal(isGlobal) {}

    llvm::Function* operator->() const
    {
        return raw;
    }
};

class SymbolTable
{
    std::map<std::string, std::shared_ptr<ConstantSymbol>> constant;
    std::map<std::string, std::shared_ptr<TypeSymbol>> type;
    std::map<std::string, std::shared_ptr<VariableSymbol>> variable;
    std::map<std::string, std::shared_ptr<FunctionSymbol>> function;

    static std::vector<std::shared_ptr<SymbolTable>> ARStack;

    std::shared_ptr<SymbolTable> prev = nullptr;

public:
    void insertConstant(const std::string& name, ConstantSymbol value)
    {
        constant.insert(std::make_pair(name, std::make_shared<ConstantSymbol>(value)));
    }
    std::shared_ptr<ConstantSymbol> getConstant(const std::string& name)
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
        type.insert(std::make_pair(name, std::make_shared<TypeSymbol>(value)));
    }
    std::shared_ptr<TypeSymbol> getType(const std::string& name)
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
        variable.insert(std::make_pair(name, std::make_shared<VariableSymbol>(value)));
    }
    std::shared_ptr<VariableSymbol> getVariable(const std::string& name)
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
        function.insert(std::make_pair(name, std::make_shared<FunctionSymbol>(value)));
    }
    std::shared_ptr<FunctionSymbol> getFunction(const std::string& name)
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