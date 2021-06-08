#pragma once
#include "ast_base.hh"
#include "ast_const.hh"

// Type base class
class ASTNode_Type : public ASTNode
{
public:
	virtual std::string toString() = 0;

	virtual llvm::Type *typeGen() = 0;

	llvm::Value *codeGen() override = 0;

	ASTNodeType getType() override { return ASTNodeType::Type; }
	void print() override { YaccLogger.println("TypeBase"); }
};

// Simple Type base class
class ASTNode_SimpleType : public ASTNode_Type
{
public:
	llvm::Type *typeGen() override = 0;

	llvm::Value *codeGen() override = 0;

	ASTNodeType getType() override { return ASTNodeType::SimpleType; }
	void print() override { YaccLogger.println("SimpleType"); }
};

// Simple Type Plain(single value)
// children: none
class ASTNode_SimpleTypePlain : public ASTNode_SimpleType
{
public:
	std::string name;
	ASTNode_SimpleTypePlain(std::string typeName) : name(std::move(typeName)) {}
	ASTNode_SimpleTypePlain(ASTNode_Name *pName) : name(std::move(pName->name))
	{
		delete pName;
	}

	std::string toString() override
	{
		return name;
	}

	llvm::Type *typeGen() override;

	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::SimpleTypePlain; }
	void print() override { YaccLogger.println("SimpleTypePlain " + name); }
};

// Name List
// children: none
class ASTNode_NameList : public ASTNode
{
public:
	std::vector<std::string> list;

	ASTNode_NameList() = default;
	ASTNode_NameList(ASTNode_NameList &&node) noexcept : list(std::move(node.list)) {}

	void insert(const std::string &name)
	{
		list.push_back(name);
	}

	void insert(ASTNode_Name *pName)
	{
		list.push_back(std::move(pName->name));
		delete pName;
	}

	virtual std::string toString()
	{
		std::string str = "(";
		for (auto &i : list)
			str += i + ",";
		str += ")";
		return str;
	}

	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::NameList; }

	void print() override
	{
		YaccLogger.print("NameList ( ");
		for (auto &i : list)
			YaccLogger.print(i).print(" ");
		YaccLogger.println(")");
	}
};

// Simple Type Enumerate
// children:
// 1 - ASTNode_NameList: enum members
class ASTNode_SimpleTypeEnumerate : public ASTNode_SimpleType
{
public:
	ASTNode_NameList *const list;

	ASTNode_SimpleTypeEnumerate(ASTNode_NameList *list) : list(list)
	{
		append(list);
	}

	std::string toString() override
	{
		return list->toString();
	}

	llvm::Type *typeGen() override;

	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::SimpleTypeEnumerate; }
	void print() override { YaccLogger.println("SimpleTypeEnum " + toString()); }
};

// Simple Type Sub Range
// children: none
class ASTNode_SimpleTypeSubRange : public ASTNode_SimpleType
{
public:
	std::string begin, end;
	bool isEnumRange;

	ASTNode_SimpleTypeSubRange(ASTNode_Const *begin, ASTNode_Const *end) : begin(begin->toString()), end(end->toString()), isEnumRange(false)
	{
		delete begin;
		delete end;
	}

	ASTNode_SimpleTypeSubRange(ASTNode_Name *begin, ASTNode_Name *end) : begin(std::move(begin->name)), end(std::move(end->name)), isEnumRange(true)
	{
		delete begin;
		delete end;
	}

	std::string toString() override
	{
		return begin + "..." + end;
	}

	llvm::Type *typeGen() override;

	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::SimpleTypeSubRange; }
	void print() override { YaccLogger.println("SimpleTypeSubRange " + toString()); }
};

// Array Type
// children:
// 1 - ASTNode_SimpleType: index type
// 2 - ASTNode_Type: element type
class ASTNode_ArrayType : public ASTNode_Type
{
public:
	ASTNode_SimpleType *const indexType;
	ASTNode_Type *const elementType;

	ASTNode_ArrayType(ASTNode_SimpleType *indexType, ASTNode_Type *elementType)
		: indexType(indexType), elementType(elementType)
	{
		append(indexType);
		append(elementType);
	}

	std::string toString() override
	{
		return "[" + indexType->toString() + "] of " + elementType->toString();
	}

	llvm::Type *typeGen() override;

	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::ArrayType; }
	void print() override { YaccLogger.println("ArrayType " + toString()); }
};

// Field Declaration
// children: 1 - ASTNode_NameList: field name
// children: 2 - ASTNode_Type: field type
class ASTNode_FieldDecl : public ASTNode
{
public:
	ASTNode_NameList *const list;
	ASTNode_Type *const type;

	ASTNode_FieldDecl(ASTNode_NameList *list, ASTNode_Type *type) : list(list), type(type)
	{
		append(list);
		append(type);
	}

	std::string toString() const
	{
		return list->toString() + " " + type->toString();
	}

	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::FieldDecl; }
	void print() override { YaccLogger.println("FieldDecl " + toString()); }
};

// Field Declaration List
// children:
// any - ASTNode_FieldDecl
class ASTNode_FieldDeclList : public ASTNode
{
public:
	std::string toString() const
	{
		std::string str = "{";
		for (auto &i : children)
			str += dynamic_cast<ASTNode_FieldDecl *>(i)->toString() + ",";
		str += "}";
		return str;
	}

	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::FieldDeclList; }
	void print() override { YaccLogger.println("FieldDeclList"); }
};

// Record Type
// children:
// 1 - ASTNode_FieldDeclList
class ASTNode_RecordType : public ASTNode_Type
{
public:
	ASTNode_FieldDeclList *const list;

	ASTNode_RecordType(ASTNode_FieldDeclList *list) : list(list)
	{
		append(list);
	}

	std::string toString() override { return list->toString(); }

	llvm::Type *typeGen() override;

	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::RecordType; }
	void print() override { YaccLogger.println("RecordType" + toString()); }
};

// Type Declaration
// children:
// 1 - ASTNode_Type: type
class ASTNode_TypeDecl : public ASTNode
{
public:
	std::string name;
	ASTNode_Type *const type;

	ASTNode_TypeDecl(ASTNode_Name *pName, ASTNode_Type *type)
		: name(std::move(pName->name)), type(type)
	{
		delete pName;
		append(type);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::TypeDecl; }
	void print() override { YaccLogger.println("TypeDecl " + name + " " + type->toString()); }
};

// Type Declaration List
// children:
// any - ASTNode_TypeDecl
class ASTNode_TypeDeclList : public ASTNode
{
public:
	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::TypeDeclList; }
	void print() override { YaccLogger.println("TypeDeclList"); }
};
