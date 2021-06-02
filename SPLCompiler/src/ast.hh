#pragma once
#include "log.hh"
#include <llvm/IR/BasicBlock.h>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class ASTHandler;
class CodeGenerator;

class ASTNode
{
public:
	friend ASTHandler;
	friend CodeGenerator;

	ASTNode *child = nullptr;
	ASTNode *brother = nullptr;

	enum class ASTNodeType
	{
		Base,
		Name,
		Program,
		Routine,
		SubRoutine,
		RoutineHead,
		Const,
		ConstInteger,
		ConstReal,
		ConstCharacter,
		ConstString,
		ConstBoolean,
		ConstExpr,
		ConstExprList,
		Type,
		SimpleTypePlain,
		NameList,
		SimpleType,
		SimpleTypeEnumerate,
		SimpleTypeSubrange,
		ArrayType,
		RecordType,
		TypeDecl,
		TypeDeclList,
		FieldDecl,
		FieldDeclList,
		VarDeclList,
		VarDecl,
		RoutinePart,
		FunctionDecl,
		FunctionHead,
		ProcedureDecl,
		ProcedureHead,
		ParaDeclList,
		ParaTypeList,
		VarParaList,
		ValParaList,
		StmtList,
		Stmt,
		Expr,
		StmtAssign,
		StmtProc,
		StmtCompound,
		StmtIf,
		StmtRepeat,
		StmtWhile,
		StmtFor,
		StmtCase,
		StmtGoto,
		CaseExpr,
		CaseExprList,
		ExprList,
		Operator,
		Operand,
		ArgList
	};

	ASTNode() = default;
	ASTNode(const ASTNode &node) = delete;
	ASTNode(ASTNode &&node) = delete;

	void append(ASTNode *node)
	{
		if (!node)
			return;
		if (!child)
			child = node;
		else
		{
			auto current = child;
			while (current->brother)
				current = current->brother;
			current->brother = node;
		}
	}

	virtual void print()
	{
		YaccLogger.print("BaseNode SHOULD NOT OCCURRED");
	}

	virtual ASTNodeType getType()
	{
		return ASTNodeType::Base;
	}

	virtual ~ASTNode()
	{
		if (child)
		{
			auto current = child;
			while (current->brother)
			{
				auto prev = current;
				current = current->brother;
				delete prev;
			}
			delete current;
		}
	}
};

class ASTNode_Name : public ASTNode
{
public:
	std::string name;

	ASTNode_Name(std::string name) : name(std::move(name)) {}

	ASTNodeType getType() override
	{
		return ASTNodeType::Name;
	}

	void print() override
	{
		YaccLogger.print("Name " + name);
	}
};

class ASTNode_Program : public ASTNode
{
public:
	std::string programName;

	ASTNode_Program(ASTNode_Name *pNode) : programName(std::move(pNode->name)) { delete pNode; }

	ASTNodeType getType() override
	{
		return ASTNodeType::Program;
	}

	void print() override
	{
		YaccLogger.println("Program " + programName);
	}
};

class ASTNode_Routine : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::Routine;
	}

	void print() override
	{
		YaccLogger.println("Routine");
	}
};

class ASTNode_SubRoutine : public ASTNode
{
public:
	llvm::Value *codeGen();

	void print() override
	{
		YaccLogger.println("SubRoutine");
	}
};

class ASTNode_RoutineHead : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::RoutineHead;
	}

	void print() override
	{
		YaccLogger.println("RoutineHead");
	}
};

class ASTNode_Const : public ASTNode
{
protected:
	union
	{
		const int integer;
		const double real;
		const char character;
		const char *string;
		const bool boolean;
	} value;

public:
	ASTNode_Const(const int val) : value({.integer = val}) {}
	ASTNode_Const(const double val) : value({.real = val}) {}
	ASTNode_Const(const char val) : value({.character = val}) {}
	ASTNode_Const(const char *val) : value({.string = val}) {}
	ASTNode_Const(const bool val) : value({.boolean = val}) {}

	virtual std::string get() = 0;

	ASTNodeType getType() override
	{
		return ASTNodeType::Const;
	}

	virtual llvm::Value *codeGen() = 0;

	void print() override
	{
		YaccLogger.println("Const SHOULD NOT OCCURRED");
	}
};

class ASTNode_ConstInteger : public ASTNode_Const
{
	const int &value = ASTNode_Const::value.integer;

public:
	ASTNode_ConstInteger(const int val) : ASTNode_Const(val) {}

	std::string get() override
	{
		return std::to_string(value);
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::ConstInteger;
	}

	llvm::Value *codeGen() override;

	void print() override
	{
		YaccLogger.println("ConstInteger " + std::to_string(value));
	}
};

class ASTNode_ConstReal : public ASTNode_Const
{
	const double &value = ASTNode_Const::value.real;

public:
	ASTNode_ConstReal(const double val) : ASTNode_Const(val) {}

	std::string get() override
	{
		return std::to_string(value);
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::ConstReal;
	}

	llvm::Value *codeGen() override;

	void print() override
	{
		YaccLogger.println("ConstReal " + std::to_string(value));
	}
};

class ASTNode_ConstCharacter : public ASTNode_Const
{
	const char &value = ASTNode_Const::value.character;

public:
	ASTNode_ConstCharacter(const char val) : ASTNode_Const(val) {}

	std::string get() override
	{
		return std::to_string(value);
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::ConstCharacter;
	}

	llvm::Value *codeGen() override;

	void print() override
	{
		YaccLogger.println("ConstCharacter " + std::to_string(value));
	}
};

class ASTNode_ConstString : public ASTNode_Const
{
	const char *&value = ASTNode_Const::value.string;

public:
	ASTNode_ConstString(const char *val) : ASTNode_Const(val) {}

	std::string get() override
	{
		return value;
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::ConstString;
	}

	llvm::Value *codeGen() override;

	void print() override
	{
		YaccLogger.print("ConstString ").println(value);
	}
};

class ASTNode_ConstBoolean : public ASTNode_Const
{
	const bool &value = ASTNode_Const::value.boolean;

public:
	ASTNode_ConstBoolean(const bool val) : ASTNode_Const(val) {}

	std::string get() override
	{
		return value ? "true" : "false";
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::ConstBoolean;
	}

	llvm::Value *codeGen() override;

	void print() override
	{
		YaccLogger.print("ConstBoolean " + std::to_string(value));
	}
};

class ASTNode_ConstExpr : public ASTNode
{
public:
	std::string constName;
	ASTNode_Const *value;

	ASTNode_ConstExpr(ASTNode_Name *pNode, ASTNode_Const *value) : constName(std::move(pNode->name)), value(value) { delete pNode; }

	ASTNodeType getType() override
	{
		return ASTNodeType::ConstExpr;
	}

	void print() override
	{
		YaccLogger.print("ConstExpr " + constName + " ").println(value->get());
	}

	~ASTNode_ConstExpr() override
	{
		delete value;
	}
};

class ASTNode_ConstExprList : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::ConstExprList;
	}

	void print() override
	{
		YaccLogger.println("ConstExprList");
	}
};

class ASTNode_Type : public ASTNode
{
public:
	virtual std::string get() = 0;

	ASTNodeType getType() override
	{
		return ASTNodeType::Type;
	}

	virtual llvm::Type *codeGen() = 0;

	void print() override
	{
		YaccLogger.println("Type");
	}
};

class ASTNode_SimpleType : public ASTNode_Type
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::SimpleType;
	}

	void print() override
	{
		YaccLogger.println("SimpleType");
	}
};

class ASTNode_SimpleTypePlain : public ASTNode_SimpleType
{
	std::string typeName;

public:
	ASTNode_SimpleTypePlain(std::string type) : typeName(std::move(type)) {}
	ASTNode_SimpleTypePlain(ASTNode_Name *pNode) : typeName(std::move(pNode->name)) { delete pNode; }

	std::string get() override
	{
		return typeName;
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::SimpleTypePlain;
	}

	llvm::Type *codeGen() override;

	void print() override
	{
		YaccLogger.println("SimpleTypePlain " + typeName);
	}
};

class ASTNode_NameList : public ASTNode
{
public:
	std::vector<std::string> name_list;

	ASTNode_NameList() = default;
	ASTNode_NameList(ASTNode_NameList &&node) noexcept : name_list(std::move(node.name_list)) {}

	void insert(const std::string &name)
	{
		name_list.push_back(name);
	}

	void insert(ASTNode_Name *pNode)
	{
		name_list.push_back(std::move(pNode->name));
		delete pNode;
	}

	virtual std::string get()
	{
		std::stringstream ss;
		ss << "(";
		for (auto &i : name_list)
			ss << i << ",";
		ss << ")";
		return ss.str();
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::NameList;
	}

	void print() override
	{
		YaccLogger.print("NameList (");
		for (auto &i : name_list)
			YaccLogger.print(i).print(" ");
		YaccLogger.println(")");
	}
};

class ASTNode_SimpleTypeEnumerate : public ASTNode_SimpleType
{
	ASTNode_NameList *list;

public:
	ASTNode_SimpleTypeEnumerate(ASTNode_NameList *list) : list(list) {}

	std::string get() override
	{
		return list->get();
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::SimpleTypeEnumerate;
	}

	void print() override
	{
		YaccLogger.println("SimpleTypeEnum " + list->get());
	}

	llvm::Type *codeGen() override;

	~ASTNode_SimpleTypeEnumerate() override
	{
		delete list;
	}
};

class ASTNode_SimpleTypeSubrange : public ASTNode_SimpleType
{
	std::string begin, end;

public:
	ASTNode_SimpleTypeSubrange(ASTNode_Const *begin, ASTNode_Const *end) : begin(begin->get()), end(end->get())
	{
		delete begin;
		delete end;
	}

	ASTNode_SimpleTypeSubrange(ASTNode_Name *begin, ASTNode_Name *end) : begin(std::move(begin->name)), end(std::move(end->name))
	{
		delete begin;
		delete end;
	}

	std::string get() override
	{
		return begin + "..." + end;
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::SimpleTypeSubrange;
	}

	llvm::Type *codeGen() override;

	void print() override
	{
		YaccLogger.println("SimpleTypeSubrange " + begin + "..." + end);
	}
};

class ASTNode_ArrayType : public ASTNode_Type
{
	ASTNode_SimpleType *indexType;
	ASTNode_Type *elementType;

public:
	ASTNode_ArrayType(ASTNode_SimpleType *indexType, ASTNode_Type *elementType) : indexType(indexType), elementType(elementType) {}

	std::string get() override
	{
		return "[" + indexType->get() + "] of " + elementType->get();
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::ArrayType;
	}

	llvm::Type *codeGen() override;

	void print() override
	{
		YaccLogger.println("ArrayType [" + indexType->get() + "] of " + elementType->get());
	}

	~ASTNode_ArrayType() override
	{
		delete indexType;
		delete elementType;
	}
};

class ASTNode_RecordType : public ASTNode_Type
{
public:
	std::string get() override
	{
		//TODO: better string representation of record
		return "RECORD";
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::RecordType;
	}

	llvm::Type *codeGen() override;

	void print() override
	{
		YaccLogger.println("RecordType");
	}
};

class ASTNode_TypeDecl : public ASTNode
{
public:
	std::string defName;
	ASTNode_Type *type;

	ASTNode_TypeDecl(ASTNode_Name *pNode, ASTNode_Type *type) : defName(std::move(pNode->name)), type(type) { delete pNode; }

	ASTNodeType getType() override
	{
		return ASTNodeType::TypeDecl;
	}

	void print() override
	{
		YaccLogger.println("TypeDecl " + defName + " " + type->get());
	}

	~ASTNode_TypeDecl() override
	{
		delete type;
	}
};

class ASTNode_TypeDeclList : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::TypeDeclList;
	}

	void print() override
	{
		YaccLogger.println("TypeDeclList");
	}
};

class ASTNode_FieldDecl : public ASTNode
{
	ASTNode_NameList *list;
	ASTNode_Type *type;

public:
	ASTNode_FieldDecl(ASTNode_NameList *list, ASTNode_Type *type) : list(list), type(type) {}

	std::string get()
	{
		return list->get() + " " + type->get();
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::FieldDecl;
	}

	void print() override
	{
		YaccLogger.println("FieldDecl " + list->get() + " " + type->get());
	}
	~ASTNode_FieldDecl() override
	{
		delete list;
		delete type;
	}
};

class ASTNode_FieldDeclList : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::FieldDeclList;
	}

	void print() override
	{
		YaccLogger.println("FieldDeclList");
	}
};

class ASTNode_VarDeclList : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::VarDeclList;
	}

	void print() override
	{
		YaccLogger.println("VarDeclList");
	}
};

class ASTNode_VarDecl : public ASTNode
{
public:
	ASTNode_NameList *list;
	ASTNode_Type *type;

	ASTNode_VarDecl(ASTNode_NameList *list, ASTNode_Type *type) : list(list), type(type) {}

	std::string get()
	{
		return list->get() + " " + type->get();
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::VarDecl;
	}

	void print() override
	{
		YaccLogger.println("VarDecl " + list->get() + " " + type->get());
	}

	~ASTNode_VarDecl() override
	{
		delete list;
		delete type;
	}
};

class ASTNode_RoutinePart : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::RoutinePart;
	}

	void print() override
	{
		YaccLogger.println("RoutinePart");
	}
};

class ASTNode_FunctionDecl : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::FunctionDecl;
	}

	llvm::Function *codeGen();

	void print() override
	{
		YaccLogger.println("FuncDecl");
	}
};

class ASTNode_FunctionHead : public ASTNode
{
public:
	std::string functionName;

	ASTNode_FunctionHead(ASTNode_Name *pNode) : functionName(std::move(pNode->name)) { delete pNode; }

	ASTNodeType getType() override
	{
		return ASTNodeType::FunctionHead;
	}

	// return function declaration
	llvm::Function *codeGen();

	void print() override
	{
		YaccLogger.println("FuncHead " + functionName);
	}
};

class ASTNode_ProcedureDecl : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::ProcedureDecl;
	}

	llvm::Function *codeGen();

	void print() override
	{
		YaccLogger.println("ProcDecl");
	}
};

class ASTNode_ProcedureHead : public ASTNode
{
public:
	std::string procedureName;
	ASTNode_ProcedureHead(ASTNode_Name *pNode) : procedureName(std::move(pNode->name)) { delete pNode; }

	ASTNodeType getType() override
	{
		return ASTNodeType::ProcedureHead;
	}

	// return procedure declaration
	llvm::Function *codeGen();

	void print() override
	{
		YaccLogger.println("ProcHead " + procedureName);
	}
};

class ASTNode_ParaDeclList : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::ParaDeclList;
	}

	void print() override
	{
		YaccLogger.println("ParaDeclList");
	}
};

class ASTNode_ParaTypeList : public ASTNode
{
public:
	ASTNode_NameList *paraList;
	ASTNode_SimpleType *type;

	ASTNode_ParaTypeList(ASTNode_NameList *paraList, ASTNode_SimpleType *type) : paraList(paraList), type(type) {}

	ASTNodeType getType() override
	{
		return ASTNodeType::ParaTypeList;
	}

	void print() override
	{
		YaccLogger.println("ParaTypeList " + paraList->get() + " " + type->get());
	}

	~ASTNode_ParaTypeList() override
	{
		delete paraList;
		delete type;
	}
};

class ASTNode_VarParaList : public ASTNode_NameList
{
public:
	ASTNode_VarParaList(ASTNode_NameList *pNode) : ASTNode_NameList(std::move(*pNode))
	{
		delete pNode;
	}

	std::string get() override
	{
		return "var" + ASTNode_NameList::get();
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::VarParaList;
	}

	void print() override
	{
		YaccLogger.print("VarParaList " + ASTNode_NameList::get());
	}
};

class ASTNode_ValParaList : public ASTNode_NameList
{
public:
	ASTNode_ValParaList(ASTNode_NameList *pNode) : ASTNode_NameList(std::move(*pNode))
	{
		delete pNode;
	}

	std::string get() override
	{
		return ASTNode_NameList::get();
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::ValParaList;
	}

	void print() override
	{
		YaccLogger.print("ValParaList " + ASTNode_NameList::get());
	}
};

class ASTNode_StmtList : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::StmtList;
	}

	void print() override
	{
		YaccLogger.println("StmtList");
	}
};

class ASTNode_Stmt : public ASTNode
{
protected:
	bool hasLabel;
	int label;

public:
	ASTNode_Stmt() : hasLabel(false), label(0) {}

	ASTNodeType getType() override
	{
		return ASTNodeType::Stmt;
	}

	void setLabel(int label)
	{
		hasLabel = true;
		this->label = label;
	}

	void setLabel(ASTNode_Const *pNode)
	{
		hasLabel = true;
		this->label = std::stoi(pNode->get());
		delete pNode;
	}

	void print() override
	{
		YaccLogger.println("Stmt " + (hasLabel ? std::to_string(label) : std::string()));
	}
};

class ASTNode_Expr : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::Expr;
	}

	virtual llvm::Value *codeGen() = 0;

	void print() override
	{
		YaccLogger.println("Expr");
	}
};

class ASTNode_StmtAssign : public ASTNode_Stmt
{
	std::string lvalueName;

public:
	ASTNode_StmtAssign(ASTNode_Name *pNode) : lvalueName(std::move(pNode->name)) { delete pNode; }

	ASTNode_StmtAssign(ASTNode_Name *pNode, ASTNode_Expr *expr) : lvalueName(std::move(pNode->name))
	{
		lvalueName += "[]";
		delete pNode;
	}

	ASTNode_StmtAssign(ASTNode_Name *pNode, ASTNode_Name *member) : lvalueName(std::move(pNode->name))
	{
		lvalueName += "." + std::move(member->name);
		delete pNode;
		delete member;
	}

	ASTNodeType getType() override
	{
		return ASTNodeType::StmtAssign;
	}

	void print() override
	{
		YaccLogger.println("AssignStmt " + (hasLabel ? (std::to_string(label) + " ") : std::string()) + lvalueName);
	}
};

class ASTNode_StmtProc : public ASTNode_Stmt
{
	std::string procName;

public:
	ASTNode_StmtProc(ASTNode_Name *pNode) : procName(std::move(pNode->name)) {}

	ASTNodeType getType() override
	{
		return ASTNodeType::StmtProc;
	}

	void print() override
	{
		YaccLogger.println("ProcStmt " + (hasLabel ? (std::to_string(label) + " ") : std::string()) + procName);
	}
};

class ASTNode_StmtCompound : public ASTNode_Stmt
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::StmtCompound;
	}

	void print() override
	{
		YaccLogger.println("CompoundStmt " + (hasLabel ? std::to_string(label) : std::string()));
	}
};

class ASTNode_StmtIf : public ASTNode_Stmt
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::StmtIf;
	}

	void print() override
	{
		YaccLogger.println("IfStmt " + (hasLabel ? std::to_string(label) : std::string()));
	}
};

class ASTNode_StmtRepeat : public ASTNode_Stmt
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::StmtRepeat;
	}

	void print() override
	{
		YaccLogger.println("RepeatStmt " + (hasLabel ? std::to_string(label) : std::string()));
	}
};

class ASTNode_StmtWhile : public ASTNode_Stmt
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::StmtWhile;
	}

	void print() override
	{
		YaccLogger.println("WhileStmt " + (hasLabel ? std::to_string(label) : std::string()));
	}
};

class ASTNode_StmtFor : public ASTNode_Stmt
{
	std::string varName;
	bool isPositive;

public:
	ASTNode_StmtFor(ASTNode_Name *pNode, bool dir) : varName(std::move(pNode->name)), isPositive(dir) { delete pNode; }

	ASTNodeType getType() override
	{
		return ASTNodeType::StmtFor;
	}

	void print() override
	{
		YaccLogger.println("ForStmt " + (hasLabel ? (std::to_string(label) + " ") : std::string()) + varName + (isPositive ? " to" : " downto"));
	}
};

class ASTNode_StmtCase : public ASTNode_Stmt
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::StmtCase;
	}

	void print() override
	{
		YaccLogger.println("CaseStmt " + (hasLabel ? std::to_string(label) : std::string()));
	}
};

class ASTNode_StmtGoto : public ASTNode_Stmt
{
	std::string gotoLabel;

public:
	ASTNode_StmtGoto(ASTNode_Const *pNode) : gotoLabel(pNode->get()) { delete pNode; }

	ASTNodeType getType() override
	{
		return ASTNodeType::StmtGoto;
	}

	void print() override
	{
		YaccLogger.println("GotoStmt " + (hasLabel ? (std::to_string(label) + " ") : std::string()) + "to " + gotoLabel);
	}
};

class ASTNode_CaseExpr : public ASTNode
{
	std::string caseVar;

public:
	ASTNode_CaseExpr(ASTNode_Const *pNode) : caseVar(pNode->get()) { delete pNode; }

	ASTNode_CaseExpr(ASTNode_Name *pNode) : caseVar(std::move(pNode->name)) { delete pNode; }

	ASTNodeType getType() override
	{
		return ASTNodeType::CaseExpr;
	}

	void print() override
	{
		YaccLogger.println("CaseExpr " + caseVar);
	}
};

class ASTNode_CaseExprList : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::CaseExprList;
	}

	void print() override
	{
		YaccLogger.println("CaseExprList");
	}
};

class ASTNode_ExprList : public ASTNode
{
public:
	ASTNodeType getType() override
	{
		return ASTNodeType::ExprList;
	}

	void print() override
	{
		YaccLogger.println("ExprList");
	}
};

class ASTNode_Operator : public ASTNode_Expr
{
public:
	enum class OPERATOR
	{
		GE,
		GT,
		LE,
		LT,
		EQUAL,
		UNEQUAL,

		PLUS,
		MINUS,
		MUL,
		DIV,
		MOD,
		UMINUS,

		AND,
		OR,
		NOT,

		DOT
	};

private:
	static const std::string OperatorString[15];

	OPERATOR op;

	static const std::string &stringOf(OPERATOR op)
	{
		return OperatorString[static_cast<int>(op)];
	}

public:
	ASTNode_Operator(OPERATOR op) : op(op) {}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override
	{
		return ASTNodeType::Operator;
	}

	void print() override
	{
		YaccLogger.println("Operator " + stringOf(op));
	}
};

class ASTNode_Operand : public ASTNode_Expr
{
	std::string name;

public:
	ASTNode_Operand() = default;

	ASTNode_Operand(std::string name) : name(std::move(name)) {}

	ASTNode_Operand(ASTNode_Name *pNode) : name(std::move(pNode->name)) { delete pNode; }

	llvm::Value *codeGen() override;

	ASTNodeType getType() override
	{
		return ASTNodeType::Operand;
	}

	void print() override
	{
		YaccLogger.println("Operand " + name);
	}
};

class ASTNode_ArgList : public ASTNode
{
public:
	int count = 0;

	ASTNodeType getType() override
	{
		return ASTNodeType::ArgList;
	}

	void print() override
	{
		YaccLogger.println("ArgList " + std::to_string(count));
	}
};

extern ASTNode *ASTHead;

class ASTHandler
{
	static void recursivePrint(ASTNode *head, int depth);
	static void scanConstPart(ASTNode *part);
	static void scanTypePart(ASTNode *part);
	static void scanVarPart(ASTNode *part);
	static void scanRoutinePart(ASTNode *part);

public:
	ASTHandler() = delete;

	static void print();
	static void scanProgramHead();
};