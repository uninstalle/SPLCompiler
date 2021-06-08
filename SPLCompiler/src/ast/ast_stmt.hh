#pragma once
#include "ast_base.hh"
#include "ast_expr.hh"

// Stmt base class
class ASTNode_Stmt : public ASTNode
{
protected:
	bool hasLabel;
	int label;
	std::string getLabelInfix() const
	{
		if (hasLabel)
			return std::to_string(label) + " ";
		else
			return "";
	}
	void buildLabel();

public:
	ASTNode_Stmt() : hasLabel(false), label(0) {}

	void setLabel(int label)
	{
		hasLabel = true;
		this->label = label;
	}

	void setLabel(ASTNode_Const *pConst)
	{
		hasLabel = true;
		this->label = std::stoi(pConst->toString());
		delete pConst;
	}

	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::Stmt; }
	void print() override { YaccLogger.println(getLabelInfix() + "Stmt"); }
};

// Stmt List
// Children:
// any - ASTNode_Stmt
class ASTNode_StmtList : public ASTNode
{
public:
	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::StmtList; }
	void print() override { YaccLogger.println("StmtList"); }
};

// Compound Stmt
// Children:
// 1 - ASTNode_StmtList: list of stmt inside the compound stmt
class ASTNode_StmtCompound : public ASTNode_Stmt
{
public:
	ASTNode_StmtList *const list;

	ASTNode_StmtCompound(ASTNode_StmtList *list) : list(list)
	{
		append(list);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::StmtCompound; }
	void print() override
	{
		YaccLogger.println(getLabelInfix() + "CompoundStmt");
	}
};

// Assign Stmt base class
class ASTNode_StmtAssign : public ASTNode_Stmt
{
public:
	std::string name;

	ASTNode_StmtAssign(ASTNode_Name *pName) : name(std::move(pName->name))
	{
		delete pName;
	}

	ASTNode_StmtAssign(ASTNode_Name *pNode, ASTNode_Name *member)
		: name(std::move(pNode->name))
	{
		name += "." + std::move(member->name);
		delete pNode;
		delete member;
	}

	llvm::Value *codeGen() override = 0;

	ASTNodeType getType() override { return ASTNodeType::StmtAssign; }
	void print() override { YaccLogger.println(getLabelInfix() + "AssignStmt " + name); }
};

// Assign Stmt for Simple Type
// Children:
// 1 - ASTNode_Expr: rvalue of the assignment
class ASTNode_StmtAssignSimpleType : public ASTNode_StmtAssign
{
public:
	ASTNode_Expr *const value;
	ASTNode_StmtAssignSimpleType(ASTNode_Name *pName, ASTNode_Expr *value)
		: ASTNode_StmtAssign(pName), value(value)
	{
		append(value);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::StmtAssignSimpleType; }
	void print() override
	{
		YaccLogger.println(getLabelInfix() + "AssignStmtSimpleType " + name);
	}
};

// Assign Stmt for Array Type
// Children:
// 1 - ASTNode_Expr: index of the array
// 2 - ASTNode_Expr: rvalue of the assignment
class ASTNode_StmtAssignArrayType : public ASTNode_StmtAssign
{
public:
	ASTNode_Expr *const index;
	ASTNode_Expr *const value;
	ASTNode_StmtAssignArrayType(ASTNode_Name *pName, ASTNode_Expr *index, ASTNode_Expr *value)
		: ASTNode_StmtAssign(pName), index(index), value(value)
	{
		append(index);
		append(value);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::StmtAssignArrayType; }
	void print() override
	{
		YaccLogger.println(getLabelInfix() + "AssignStmtArrayType " + name + "[]");
	}
};

// Assign Stmt for Array Type
// Children:
// 1 - ASTNode_Expr: rvalue of the assignment
class ASTNode_StmtAssignRecordType : public ASTNode_StmtAssign
{
public:
	std::string memberName;
	ASTNode_Expr *const value;

	ASTNode_StmtAssignRecordType(ASTNode_Name *pName, ASTNode_Name *pMember, ASTNode_Expr *value)
		: ASTNode_StmtAssign(pName), memberName(std::move(pMember->name)), value(value)
	{
		delete pMember;
		append(value);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::StmtAssignRecordType; }
	void print() override
	{
		YaccLogger.println(getLabelInfix() + "AssignStmtRecordType " + name + "." + memberName);
	}
};

// Procedure Stmt
// Children:
// 1 - ASTNode_ArgList: args to call the procedure
class ASTNode_StmtProc : public ASTNode_Stmt
{
public:
	std::string name;
	ASTNode_ArgList *const args;

	ASTNode_StmtProc(ASTNode_Name *pNode, ASTNode_ArgList *args)
		: name(std::move(pNode->name)), args(args)
	{
		delete pNode;
		append(args);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::StmtProc; }
	void print() override
	{
		YaccLogger.println(getLabelInfix() + "ProcStmt " + name);
	}
};

// System Procedure Stmt
// Children:
// 1 - ASTNode_ArgList: args to call the procedure
class ASTNode_StmtSysProc : public ASTNode_StmtProc
{
	llvm::Value *sysWrite(bool ln = false);
	llvm::Value *sysRead();

public:
	ASTNode_StmtSysProc(ASTNode_Name *pNode, ASTNode_ArgList *args)
		: ASTNode_StmtProc(pNode, args) {}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::StmtSysProc; }
	void print() override
	{
		YaccLogger.println(getLabelInfix() + "SysProcStmt " + name);
	}
};

// If Stmt
// Children:
// 1 - ASTNode_Expr: if condition
// 2 - ASTNode_Stmt: then stmt
// [nullable] 3 - ASTNode_Stmt: else stmt
class ASTNode_StmtIf : public ASTNode_Stmt
{
public:
	ASTNode_Expr *const cond;
	ASTNode_Stmt *const thenStmt;
	ASTNode_Stmt *const elseStmt;

	ASTNode_StmtIf(ASTNode_Expr *cond, ASTNode_Stmt *then, ASTNode_Stmt *els)
		: cond(cond), thenStmt(then), elseStmt(els)
	{
		append(cond);
		append(then);
		append(els);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::StmtIf; }
	void print() override
	{
		YaccLogger.println(getLabelInfix() + "IfStmt");
	}
};

// Repeat Stmt
// Children:
// 1 - ASTNode_StmtList: loop body
// 2 - ASTNode_Expr: loop cond
class ASTNode_StmtRepeat : public ASTNode_Stmt
{
public:
	ASTNode_StmtList *const body;
	ASTNode_Expr *const cond;

	ASTNode_StmtRepeat(ASTNode_StmtList *list, ASTNode_Expr *cond)
		: body(list), cond(cond)
	{
		append(list);
		append(cond);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::StmtRepeat; }
	void print() override
	{
		YaccLogger.println(getLabelInfix() + "RepeatStmt");
	}
};

// While Stmt
// Children:
// 1 - ASTNode_Expr: loop cond
// 2 - ASTNode_Stmt: loop body
class ASTNode_StmtWhile : public ASTNode_Stmt
{
public:
	ASTNode_Expr *const cond;
	ASTNode_Stmt *const body;

	ASTNode_StmtWhile(ASTNode_Expr *cond, ASTNode_Stmt *stmt)
		: cond(cond), body(stmt)
	{
		append(cond);
		append(stmt);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::StmtWhile; }
	void print() override
	{
		YaccLogger.println("WhileStmt " + (hasLabel ? std::to_string(label) : std::string()));
	}
};

// For Stmt
// Children:
// 1 - ASTNode_Expr: for begin value
// 2 - ASTNode_Expr: for end value
// 3 - ASTNode_Stmt: loop body
class ASTNode_StmtFor : public ASTNode_Stmt
{
	std::string name;
	bool isPositive;
	ASTNode_Expr *const begin;
	ASTNode_Expr *const end;
	ASTNode_Stmt *const body;

public:
	ASTNode_StmtFor(ASTNode_Name *pNode, bool dir, ASTNode_Expr *begin, ASTNode_Expr *end, ASTNode_Stmt *stmt)
		: name(std::move(pNode->name)), isPositive(dir), begin(begin), end(end), body(stmt)
	{
		delete pNode;
		append(begin);
		append(end);
		append(stmt);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::StmtFor; }
	void print() override
	{
		YaccLogger.println(getLabelInfix() + "ForStmt " + name + (isPositive ? " to" : " downto"));
	}
};

// Case Expr base class
class ASTNode_CaseExpr : public ASTNode
{
public:
	llvm::Value *codeGen() override = 0;

	ASTNodeType getType() override { return ASTNodeType::CaseExpr; }
	void print() override { YaccLogger.println("CaseExpr"); }
};

// Case Expr Literal
// Children:
// 1 - ASTNode_Const: case clause entry
// 2 - ASTNode_Stmt: case clause stmt
class ASTNode_CaseExprLiteral : public ASTNode_CaseExpr
{
public:
	ASTNode_Const *value;
	ASTNode_Stmt *body;

	ASTNode_CaseExprLiteral(ASTNode_Const *value, ASTNode_Stmt *stmt)
		: value(value), body(stmt)
	{
		append(value);
		append(body);
	}

	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::CaseExprLiteral; }
	void print() override { YaccLogger.println("CaseExprLiteral"); }
};

// Case Expr Const Variable
// Children:
// 1 - ASTNode_Stmt: case clause stmt
class ASTNode_CaseExprConstVar : public ASTNode_CaseExpr
{
public:
	std::string name;
	ASTNode_Stmt *body;

	ASTNode_CaseExprConstVar(ASTNode_Name *pName, ASTNode_Stmt *stmt)
		: name(std::move(pName->name)), body(stmt)
	{
		delete pName;
		append(body);
	}

	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::CaseExprConstVar; }
	void print() override { YaccLogger.println("CaseExprConstVar"); }
};

// Case Expr Default
// Children:
// 1 - ASTNode_Stmt: case clause stmt
class ASTNode_CaseExprDefault : public ASTNode_CaseExpr
{
public:
	ASTNode_Stmt *body;

	ASTNode_CaseExprDefault(ASTNode_Stmt *stmt) : body(stmt)
	{
		append(body);
	}

	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::CaseExprDefault; }
	void print() override { YaccLogger.println("CaseExprDefault"); }
};

// Case Expr List
// Children:
// any - ASTNode_CaseExpr
class ASTNode_CaseExprList : public ASTNode
{
public:
	llvm::Value *codeGen() override { return nullptr; }

	ASTNodeType getType() override { return ASTNodeType::CaseExprList; }
	void print() override { YaccLogger.println("CaseExprList"); }
};

// Case Stmt
// Children:
// 1 - ASTNode_Expr: case condition
// 2 - ASTNode_CaseExprList: case clause list
class ASTNode_StmtCase : public ASTNode_Stmt
{
public:
	ASTNode_Expr *const cond;
	ASTNode_CaseExprList *caseList;

	ASTNode_StmtCase(ASTNode_Expr *cond, ASTNode_CaseExprList *caseList)
		: cond(cond), caseList(caseList)
	{
		append(cond);
		append(caseList);
	}

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::StmtCase; }
	void print() override
	{
		YaccLogger.println("CaseStmt " + (hasLabel ? std::to_string(label) : std::string()));
	}
};

// Goto Stmt
class ASTNode_StmtGoto : public ASTNode_Stmt
{
	std::string gotoLabel;

public:
	ASTNode_StmtGoto(ASTNode_Const *pNode) : gotoLabel(pNode->toString()) { delete pNode; }

	llvm::Value *codeGen() override;

	ASTNodeType getType() override { return ASTNodeType::StmtGoto; }
	void print() override
	{
		YaccLogger.println(getLabelInfix() + "GotoStmt " + gotoLabel);
	}
};
