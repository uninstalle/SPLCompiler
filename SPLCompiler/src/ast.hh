#pragma once
#include "log.hh"
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class ASTNode;
class ASTHandler;

class ASTNode
{
    friend ASTHandler;

    ASTNode *son = nullptr;
    ASTNode *brother = nullptr;

public:
    ASTNode() = default;
    void append(ASTNode *node)
    {
        if (!node)
            return;
        if (!son)
            son = node;
        else
        {
            auto current = son;
            while (current->brother)
                current = current->brother;
            current->brother = node;
        }
    }
    virtual void print()
    {
        YaccLogger.print("BaseNode SHOULD NOT OCCURED");
    }
    virtual ~ASTNode() = default;
};

class ASTNode_Name : public ASTNode
{
public:
    std::string name;

    ASTNode_Name(std::string name) : name(name) {}
    virtual void print()
    {
        YaccLogger.print("Name " + name);
    }
};

class ASTNode_Program : public ASTNode
{

    std::string programName;

public:
    ASTNode_Program(ASTNode_Name *pNode) : programName(std::move(pNode->name)) { delete pNode; }
    void print() override
    {
        YaccLogger.println("Program " + programName);
    }
};

class ASTNode_Routine : public ASTNode
{
public:
    void print() override
    {
        YaccLogger.println("Routine");
    }
};

class ASTNode_RoutineHead : public ASTNode
{
public:
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
    void print() override
    {
        YaccLogger.println("Const");
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
    void print() override
    {
        YaccLogger.print("ConstBoolean " + std::to_string(value));
    }
};

class ASTNode_ConstExpr : public ASTNode
{
    std::string constName;
    ASTNode_Const *value;

public:
    ASTNode_ConstExpr(ASTNode_Name *pNode, ASTNode_Const *value) : constName(std::move(pNode->name)), value(value) { delete pNode; }
    void print() override
    {
        YaccLogger.print("ConstExpr " + constName + " ").println(value->get());
    }
    ~ASTNode_ConstExpr()
    {
        delete value;
    }
};

class ASTNode_ConstExprList : public ASTNode
{
public:
    void print() override
    {
        YaccLogger.println("ConstExprList");
    }
};

class ASTNode_Type : public ASTNode
{
public:
    virtual std::string get() = 0;
    void print() override
    {
        YaccLogger.println("Type");
    }
};

class ASTNode_SimpleType : public ASTNode_Type
{
public:
    void print() override
    {
        YaccLogger.println("SimpleType");
    }
};

class ASTNode_SimpleTypePlain : public ASTNode_SimpleType
{
    std::string typeName;

public:
    ASTNode_SimpleTypePlain(std::string type) : typeName(type) {}
    ASTNode_SimpleTypePlain(ASTNode_Name *pNode) : typeName(std::move(pNode->name)) { delete pNode; }
    std::string get() override
    {
        return typeName;
    }
    void print() override
    {
        YaccLogger.println("SympleTypePlain " + typeName);
    }
};

class ASTNode_NameList : public ASTNode
{
public:
    std::vector<std::string> name_list;
    void insert(const std::string &name)
    {
        name_list.push_back(name);
    }
    void insert(ASTNode_Name *pNode)
    {
        name_list.push_back(std::move(pNode->name));
        delete pNode;
    }
    std::string get()
    {
        std::stringstream ss;
        ss << "(";
        for (auto &i : name_list)
            ss << i << ",";
        ss << ")";
        return ss.str();
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
    void print() override
    {
        YaccLogger.println("SimpleTypeEnum " + list->get());
    }
    ~ASTNode_SimpleTypeEnumerate()
    {
        delete list;
    }
};

class ASTNode_SimpleTypeSubrange : public ASTNode_SimpleType
{
    std::string begin, end;

public:
    ASTNode_SimpleTypeSubrange(ASTNode_Const *begin, ASTNode_Const *end) : begin(std::move(begin->get())), end(std::move(end->get()))
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
    void print() override
    {
        YaccLogger.println("SympleTypeSubrange " + begin + "..." + end);
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
    void print() override
    {
        YaccLogger.println("ArrayType [" + indexType->get() + "] of " + elementType->get());
    }
    ~ASTNode_ArrayType()
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
    void print() override
    {
        YaccLogger.println("RecordType");
    }
};

class ASTNode_TypeDecl : public ASTNode
{
    std::string defName;
    ASTNode_Type *type;

public:
    ASTNode_TypeDecl(ASTNode_Name *pNode, ASTNode_Type *type) : defName(std::move(pNode->name)), type(type) { delete pNode; }
    void print() override
    {
        YaccLogger.println("TypeDecl " + defName + " " + type->get());
    }
    ~ASTNode_TypeDecl()
    {
        delete type;
    }
};

class ASTNode_TypeDeclList : public ASTNode
{
public:
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
    void print() override
    {
        YaccLogger.println("FieldDecl " + list->get() + " " + type->get());
    }
    ~ASTNode_FieldDecl()
    {
        delete list;
        delete type;
    }
};

class ASTNode_FieldDeclList : public ASTNode
{
public:
    void print() override
    {
        YaccLogger.println("FieldDeclList");
    }
};

class ASTNode_VarDeclList : public ASTNode
{
public:
    void print() override
    {
        YaccLogger.println("VarDeclList");
    }
};

class ASTNode_VarDecl : public ASTNode
{
    ASTNode_NameList *list;
    ASTNode_Type *type;

public:
    ASTNode_VarDecl(ASTNode_NameList *list, ASTNode_Type *type) : list(list), type(type) {}
    std::string get()
    {
        return list->get() + " " + type->get();
    }
    void print() override
    {
        YaccLogger.println("VarDecl " + list->get() + " " + type->get());
    }
    ~ASTNode_VarDecl()
    {
        delete list;
        delete type;
    }
};

class ASTNode_RoutinePart : public ASTNode
{
public:
    void print() override
    {
        YaccLogger.println("RoutinePart");
    }
};

class ASTNode_FunctionDecl : public ASTNode
{
public:
    void print() override
    {
        YaccLogger.println("FuncDecl");
    }
};

class ASTNode_FunctionHead : public ASTNode
{
    std::string functionName;

public:
    ASTNode_FunctionHead(ASTNode_Name *pNode) : functionName(std::move(pNode->name)) { delete pNode; }
    void print() override
    {
        YaccLogger.println("FuncHead " + functionName);
    }
};

class ASTNode_ProcedureDecl : public ASTNode
{
public:
    void print() override
    {
        YaccLogger.println("ProcDecl");
    }
};

class ASTNode_ProcedureHead : public ASTNode
{
    std::string procedureName;

public:
    ASTNode_ProcedureHead(ASTNode_Name *pNode) : procedureName(std::move(pNode->name)) { delete pNode; }
    void print() override
    {
        YaccLogger.println("ProcHead " + procedureName);
    }
};

class ASTNode_ParaDeclList : public ASTNode
{
public:
    void print() override
    {
        YaccLogger.println("ParaDeclList");
    }
};

class ASTNode_ParaTypeList : public ASTNode
{
    ASTNode_NameList *paraList;
    ASTNode_SimpleType *type;

public:
    ASTNode_ParaTypeList(ASTNode_NameList *paraList, ASTNode_SimpleType *type) : paraList(paraList), type(type) {}
    void print() override
    {
        YaccLogger.println("ParaTypeList " + paraList->get() + " " + type->get());
    }
    ~ASTNode_ParaTypeList()
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
    std::string get()
    {
        std::stringstream ss("var(");
        for (auto &i : name_list)
            ss << i << ",";
        ss << ")";
        return ss.str();
    }
    void print() override
    {
        YaccLogger.print("VarParaList (");
        for (auto &i : name_list)
            YaccLogger.print(i).print(" ");
        YaccLogger.println(")");
    }
};

class ASTNode_ValParaList : public ASTNode_NameList
{
public:
    ASTNode_ValParaList(ASTNode_NameList *pNode) : ASTNode_NameList(std::move(*pNode))
    {
        delete pNode;
    }
    std::string get()
    {
        std::stringstream ss("(");
        for (auto &i : name_list)
            ss << i << ",";
        ss << ")";
        return ss.str();
    }
    void print() override
    {
        YaccLogger.print("ValParaList (");
        for (auto &i : name_list)
            YaccLogger.print(i).print(" ");
        YaccLogger.println(")");
    }
};

class ASTNode_StmtList : public ASTNode
{
public:
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
    void print() override
    {
        YaccLogger.println("Expr");
    }
};

class ASTNode_StmtAssign : public ASTNode_Stmt
{
    std::string lvalueName;
    ASTNode_Expr *expr = nullptr;

public:
    ASTNode_StmtAssign(ASTNode_Name *pNode) : lvalueName(std::move(pNode->name)) { delete pNode; }
    ASTNode_StmtAssign(ASTNode_Name *pNode, ASTNode_Expr *expr) : lvalueName(std::move(pNode->name)), expr(expr)
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
    void print() override
    {
        YaccLogger.println("ProcStmt " + (hasLabel ? (std::to_string(label) + " ") : std::string()) + procName);
    }
};

class ASTNode_StmtCompound : public ASTNode_Stmt
{
public:
    void print() override
    {
        YaccLogger.println("CompoundStmt " + (hasLabel ? std::to_string(label) : std::string()));
    }
};

class ASTNode_StmtIf : public ASTNode_Stmt
{
public:
    void print() override
    {
        YaccLogger.println("IfStmt " + (hasLabel ? std::to_string(label) : std::string()));
    }
};

class ASTNode_StmtRepeat : public ASTNode_Stmt
{
public:
    void print() override
    {
        YaccLogger.println("RepeatStmt " + (hasLabel ? std::to_string(label) : std::string()));
    }
};

class ASTNode_StmtWhile : public ASTNode_Stmt
{
public:
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
    void print() override
    {
        YaccLogger.println("ForStmt " + (hasLabel ? (std::to_string(label) + " ") : std::string()) + varName + (isPositive ? " to" : " downto"));
    }
};

class ASTNode_StmtCase : public ASTNode_Stmt
{
public:
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
    void print() override
    {
        YaccLogger.println("CaseExpr " + caseVar);
    }
};

class ASTNode_CaseExprList : public ASTNode
{
public:
    void print() override
    {
        YaccLogger.println("CaseExprList");
    }
};

class ASTNode_ExprList : public ASTNode
{
public:
    void print() override
    {
        YaccLogger.println("ExprList");
    }
};

class ASTNode_Operator : public ASTNode_Expr
{
    std::string op;

public:
    ASTNode_Operator(std::string op) : op(op) {}
    void print() override
    {
        YaccLogger.println("Operator " + op);
    }
};

class ASTNode_Operand : public ASTNode_Expr
{
    std::string name;

public:
    ASTNode_Operand() {}
    ASTNode_Operand(std::string name) : name(name) {}
    ASTNode_Operand(ASTNode_Name *pNode) : name(std::move(pNode->name)) { delete pNode; }

    void print() override
    {
        YaccLogger.println("Operand " + name);
    }
};

class ASTNode_ArgList : public ASTNode
{
public:
    void print() override
    {
        YaccLogger.println("ArgList");
    }
};

extern ASTNode *ASTHead;

class ASTHandler
{
    static void recursivePrint(ASTNode *head, int depth)
    {
        ASTNode *current = head;
        std::string prefix(depth, ' ');
        YaccLogger.print(prefix);
        current->print();
        if (current->son)
            current = current->son;
        else
            return;
        do
        {
            ASTHandler::recursivePrint(current, depth + 2);
            current = current->brother;
        } while (current);
    }

public:
    static void print()
    {
        recursivePrint(ASTHead, 0);
    }
};