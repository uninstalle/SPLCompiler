#include "ast_stmt.hh"
#include "ast_variable.hh"
#include "../irgen/generator.hh"
#include "../irgen/table.hh"

void ASTNode_Stmt::buildLabel()
{
    if (!hasLabel)
        return;
    auto fun = IRGenBuilder->GetInsertBlock()->getParent();
    auto bb = llvm::BasicBlock::Create(*IRGenContext, std::to_string(label), fun);
    IRGenBuilder->CreateBr(bb);
    IRGenBuilder->SetInsertPoint(bb);
}

llvm::Value* ASTNode_StmtCompound::codeGen()
{
    buildLabel();
    // empty code block, return
    if (list->children.empty())
        return RetValZero;

    for (auto stmt : list->children)
    {
        // debug info
        CodeGenLogger.print("Compound stmt generating stmt: ");
        CodeGenLogger.println(std::to_string(static_cast<int>(stmt->getType())));

        if (!stmt->codeGen())
            return logAndReturn("Compound stmt has invalid stmt");
    }

    return RetValZero;
}


static void insertExitCode()
{
    std::string name = "exit";
    auto proc = IRGenModule->getFunction("exit");
    if (!proc)
    {
        // not declared yet, declare it
        std::vector<llvm::Type*> args;
        args.push_back(llvm::Type::getInt32Ty(*IRGenContext));
        auto funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(*IRGenContext), args, false);

        proc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "exit", IRGenModule.get());
        proc->setCallingConv(llvm::CallingConv::C);
    }

    std::vector<llvm::Value*> argsToSend;
    argsToSend.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*IRGenContext), 1, true));
    IRGenBuilder->CreateCall(proc, argsToSend);

}

void implicitTypeConversion(llvm::Value*& LHS, llvm::Value*& RHS)
{
    bool LI = LHS->getType()->getPointerElementType()->isIntegerTy(),
        LD = LHS->getType()->getPointerElementType()->isDoubleTy(),
        RI = RHS->getType()->isIntegerTy(),
        RD = RHS->getType()->isDoubleTy();

    if (LI && RD)
        RHS = IRGenBuilder->CreateFPToSI(RHS, LHS->getType()->getPointerElementType(), "fptosi");
    else if (LD && RI)
        RHS = IRGenBuilder->CreateSIToFP(RHS, LHS->getType()->getPointerElementType(), "sitofp");
    else if (LI && RI)
        RHS = IRGenBuilder->CreateSExtOrTrunc(RHS, LHS->getType()->getPointerElementType(), "intcvt");
}

llvm::Value* ASTNode_StmtAssignSimpleType::codeGen()
{
    buildLabel();

    auto varSymbol = currentSymbolTable->getVariable(name);
    if (!varSymbol)
        return logAndReturn("Unresolved variable: " + name);
    llvm::Value* rvalue;
    // type check
    auto typeSymbol = currentSymbolTable->getType(varSymbol->typeName);
    // we can only handle simple type assignment,
    // thus array and record type(not their element types) are regarded as error
    switch (typeSymbol->exType)
    {
    case TypeSymbol::ExtraTypeInfo::Base:
        rvalue = value->codeGen();
        implicitTypeConversion(varSymbol->raw, rvalue);
        break;
    case TypeSymbol::ExtraTypeInfo::Enumerate:
    {
        // rvalue will be taken as variable operand when parsing
        // thus we just get the name and compare it to the type attribute
        auto enumTag = reinterpret_cast<ASTNode_OperandVariable*>(value)->name;
        int actualValue;
        for (actualValue = 0; actualValue < typeSymbol->attributes.size(); ++actualValue)
            if (typeSymbol->attributes[actualValue] == enumTag) break;
        // tag not found
        if (actualValue == typeSymbol->attributes.size())
            return logAndReturn("Invalid enumerate tag in assignment of variable: " + name);
        rvalue = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*IRGenContext), actualValue, true);
        break;
    }
    case TypeSymbol::ExtraTypeInfo::SubRange:
    {
        // A idea to optimize:
        // Do a constant check in compile time, to do that we need to
        // add a constant mark in expr nodes, this can also help implement
        // constant folding.

        rvalue = value->codeGen();
        implicitTypeConversion(varSymbol->raw, rvalue);
        // runtime check
        // maybe should not?
        auto upperBound = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*IRGenContext),
            std::stoi(typeSymbol->attributes[0]), true);
        auto lowerBound = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*IRGenContext),
            std::stoi(typeSymbol->attributes[1]), true);
        auto exitBB = llvm::BasicBlock::Create(*IRGenContext, "sbrngchkexit");
        auto contBB = llvm::BasicBlock::Create(*IRGenContext, "sbrngchkcont");
        auto lbcond = IRGenBuilder->CreateICmpSLE(rvalue, lowerBound, "sbrnglbchk");
        auto ubcond = IRGenBuilder->CreateICmpSGE(rvalue, upperBound, "sbrngubchk");
        auto cond = IRGenBuilder->CreateAnd(lbcond, ubcond, "sbrngchk");
        IRGenBuilder->CreateCondBr(cond, contBB, exitBB);
        IRGenBuilder->GetInsertBlock()->getParent()->getBasicBlockList().push_back(exitBB);
        IRGenBuilder->SetInsertPoint(exitBB);
        // call c stdlib.h exit(), not the best way
        insertExitCode();
        // never reach it though
        IRGenBuilder->CreateBr(contBB);
        // continue part
        IRGenBuilder->GetInsertBlock()->getParent()->getBasicBlockList().push_back(contBB);
        IRGenBuilder->SetInsertPoint(contBB);
        break;
    }
    case TypeSymbol::ExtraTypeInfo::Array:
        return logAndReturn("Trying to assign an array");
    case TypeSymbol::ExtraTypeInfo::String:
        // TODO may be i will add string type one day
        return logAndReturn("Trying to assign a string");
    case  TypeSymbol::ExtraTypeInfo::Record:
        return logAndReturn("Trying to assign a record");
    }
    // implicit type conversion
    IRGenBuilder->CreateStore(rvalue, varSymbol->raw);
    return rvalue;
}

llvm::Value* ASTNode_StmtAssignArrayType::codeGen()
{
    buildLabel();
    //TODO
}

llvm::Value* ASTNode_StmtAssignRecordType::codeGen()
{
    buildLabel();
    //TODO
}

llvm::Value* ASTNode_StmtProc::codeGen()
{
    buildLabel();

    auto symbol = currentSymbolTable->getFunction(name);
    if (!symbol)
        return logAndReturn("Procedure not found: " + name);
    auto proc = symbol->raw;

    // function without args
    if (proc->arg_size() == 0)
        return IRGenBuilder->CreateCall(proc, llvm::None);

    // function expected args but stmt has no args
    if (args->children.empty())
        return logAndReturn("Procedure expects args but not provided: " + name);

    auto argNode = args->children.begin();
    auto argIsRef = symbol->isRefArg.begin();
    std::vector<llvm::Value*> argsToSend;

    for (auto& arg : proc->args())
    {
        if (*argIsRef++)
        {
            // if the arg is a ref, it must be a lvalue, thus it only can be:
            // OperandVariable, OperandArrayElement, OperandRecordMember
            auto refArg = *argNode++;

            if (refArg->getType() == ASTNodeType::OperandVariable)
            {
                auto refArgT = dynamic_cast<ASTNode_OperandVariable*>(refArg);
                auto symbol = currentSymbolTable->getVariable(refArgT->name);
                if (!symbol)
                    return logAndReturn("Unresolved arg in function: " + name);
                auto var = reinterpret_cast<llvm::AllocaInst*>(symbol->raw);
                if (var->getType() != arg.getType())
                    return logAndReturn("Procedure arg type mismatched: " + name);
                argsToSend.push_back(var);
            }
            // TODO
            else
                return logAndReturn("Procedure expects ref arg but provided with constant: " + name);
        }
        else
        {
            auto v = (*argNode++)->codeGen();
            // type check
            if (v->getType() != arg.getType())
                return logAndReturn("Procedure arg type mismatched: " + name);

            argsToSend.push_back(v);
        }
    }

    return IRGenBuilder->CreateCall(proc, argsToSend, name + "_call");
}

llvm::Value* ASTNode_StmtSysProc::sysWrite(bool ln)
{
    auto proc = IRGenModule->getFunction("printf");
    if (!proc)
    {
        // not declared yet, declare it
        std::vector<llvm::Type*> args;
        args.push_back(llvm::Type::getInt8PtrTy(*IRGenContext));
        auto funcType = llvm::FunctionType::get(llvm::IntegerType::get(*IRGenContext, 32), args, true);

        proc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "printf", IRGenModule.get());
        proc->setCallingConv(llvm::CallingConv::C);
    }

    std::vector<llvm::Value*> argsToSend;
    std::string format;

    for (auto expr : args->children)
    {
        auto v = expr->codeGen();
        if (v->getType()->isDoubleTy())
            format += "%lf";
        if (v->getType()->isIntegerTy())
        {
            if (v->getType()->getIntegerBitWidth() == 32)
                format += "%d";
            else if (v->getType()->getIntegerBitWidth() == 8)
                format += "%c";
            else if (v->getType()->getIntegerBitWidth() == 1)
                format += "%u";
        }
        argsToSend.push_back(v);
    }

    if (ln)
        format += "\n";

    auto globalstr = SymbolTable::getGlobalString(format);
    if (!globalstr)
    {
        globalstr = IRGenBuilder->CreateGlobalStringPtr(format);
        SymbolTable::insertGlobalString(format, globalstr);
    }
    argsToSend.insert(argsToSend.begin(), globalstr);
    IRGenBuilder->CreateCall(proc, argsToSend);

    return RetValZero;
}

llvm::Value* ASTNode_StmtSysProc::sysRead()
{
    auto proc = IRGenModule->getFunction("scanf");
    if (!proc)
    {
        // not declared yet, declare it
        std::vector<llvm::Type*> args;
        args.push_back(llvm::Type::getInt8PtrTy(*IRGenContext));
        auto funcType = llvm::FunctionType::get(llvm::IntegerType::get(*IRGenContext, 32), args, true);

        proc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "scanf", IRGenModule.get());
        proc->setCallingConv(llvm::CallingConv::C);
    }

    std::vector<llvm::Value*> argsToSend;
    std::string format;

    for (auto expr : args->children)
    {
        // if the arg is a ref, it must be a lvalue, thus it only can be:
        // OperandVariable, OperandArrayElement, OperandRecordMember
        if (expr->getType() == ASTNodeType::OperandVariable)
        {
            auto arg = dynamic_cast<ASTNode_OperandVariable*>(expr);
            auto symbol = currentSymbolTable->getVariable(arg->name);
            if (!symbol)
                logAndReturn("Unresolved arg in sysproc read");
            auto v = symbol->raw;

            if (v->getType()->getPointerElementType()->isDoubleTy())
                format += "%lf";
            if (v->getType()->getPointerElementType()->isIntegerTy())
            {
                if (v->getType()->getPointerElementType()->getIntegerBitWidth() == 32)
                    format += "%d";
                else if (v->getType()->getPointerElementType()->getIntegerBitWidth() == 8)
                    format += "%c";
                else if (v->getType()->getPointerElementType()->getIntegerBitWidth() == 1)
                    format += "%u";
            }
            argsToSend.push_back(v);
        }
        // TODO
        else
            return logAndReturn("Sysproc expects ref arg but provided with constant: read");
    }

    auto globalstr = SymbolTable::getGlobalString(format);
    if (!globalstr)
    {
        globalstr = IRGenBuilder->CreateGlobalStringPtr(format);
        SymbolTable::insertGlobalString(format, globalstr);
    }
    argsToSend.insert(argsToSend.begin(), globalstr);
    IRGenBuilder->CreateCall(proc, argsToSend);

    return RetValZero;
}

llvm::Value* ASTNode_StmtSysProc::codeGen()
{
    buildLabel();

    // function expected args but stmt has no args
    if (args->children.empty())
        return logAndReturn("SysProc expects args but not provided: " + name);

    if (name == "write")
        return sysWrite();
    if (name == "writeln")
        return sysWrite(true);
    if (name == "read")
        return sysRead();

    return logAndReturn("SysProc not found: " + name);
}

llvm::Value* ASTNode_StmtIf::codeGen()
{
    buildLabel();

    auto condV = cond->codeGen();
    if (!condV)
        return logAndReturn("If stmt has invalid condition");

    if (condV->getType()->isIntegerTy())
        condV = IRGenBuilder->CreateICmpNE(condV, llvm::ConstantInt::get(*IRGenContext, llvm::APInt(condV->getType()->getIntegerBitWidth(), 0)), "ifcond");
    else if (condV->getType()->isDoubleTy())
        condV = IRGenBuilder->CreateFCmpONE(condV, llvm::ConstantFP::get(*IRGenContext, llvm::APFloat(0.0)), "ifcond");

    // get current function that the if stmt belonged to
    auto fun = IRGenBuilder->GetInsertBlock()->getParent();
    // attach then BB
    auto thenBB = llvm::BasicBlock::Create(*IRGenContext, "then", fun);
    // not attached yet
    auto elseBB = llvm::BasicBlock::Create(*IRGenContext, "else");
    auto ifcontBB = llvm::BasicBlock::Create(*IRGenContext, "ifcont");

    IRGenBuilder->CreateCondBr(condV, thenBB, elseBB);

    IRGenBuilder->SetInsertPoint(thenBB);
    if (!thenStmt->codeGen())
        return logAndReturn("If stmt has invalid then stmt");
    IRGenBuilder->CreateBr(ifcontBB);

    // attach else BB to the function
    fun->getBasicBlockList().push_back(elseBB);
    IRGenBuilder->SetInsertPoint(elseBB);
    if (elseStmt)
        if (!elseStmt->codeGen())
            return logAndReturn("If stmt has invalid else stmt");
    IRGenBuilder->CreateBr(ifcontBB);

    // attach ifcont BB to the function
    fun->getBasicBlockList().push_back(ifcontBB);
    IRGenBuilder->SetInsertPoint(ifcontBB);

    return RetValZero;
}

llvm::Value* ASTNode_StmtRepeat::codeGen()
{
    buildLabel();

    // get current function that the if stmt belonged to
    auto fun = IRGenBuilder->GetInsertBlock()->getParent();
    auto loopBB = llvm::BasicBlock::Create(*IRGenContext, "repeat", fun);

    IRGenBuilder->CreateBr(loopBB);
    IRGenBuilder->SetInsertPoint(loopBB);

    for (auto stmt : body->children)
        if (!stmt->codeGen())
            return logAndReturn("Repeat stmt has invalid stmt");

    auto curVal = cond->codeGen();
    if (!curVal)
        return logAndReturn("Repeat stmt has invalid condition expr");

    // if end value == false, loopCond = true
    auto loopCond = IRGenBuilder->CreateICmpEQ(
        curVal,
        llvm::ConstantInt::get(
            *IRGenContext,
            llvm::APInt(curVal->getType()->getIntegerBitWidth(), 0)),
        "repeatcond");

    llvm::BasicBlock* contBB = llvm::BasicBlock::Create(*IRGenContext, "repeatcont", fun);
    IRGenBuilder->CreateCondBr(loopCond, loopBB, contBB);
    IRGenBuilder->SetInsertPoint(contBB);

    return RetValZero;
}

llvm::Value* ASTNode_StmtWhile::codeGen()
{
    buildLabel();

    // get current function that the if stmt belonged to
    auto fun = IRGenBuilder->GetInsertBlock()->getParent();
    auto condBB = llvm::BasicBlock::Create(*IRGenContext, "whilecond", fun);
    auto loopBB = llvm::BasicBlock::Create(*IRGenContext, "while");
    auto contBB = llvm::BasicBlock::Create(*IRGenContext, "whilecont");

    IRGenBuilder->CreateBr(condBB);
    IRGenBuilder->SetInsertPoint(condBB);

    auto curVal = cond->codeGen();
    if (!curVal)
        return logAndReturn("While stmt has invalid condition expr");

    // if end == false, loopCond = true
    auto loopCond = IRGenBuilder->CreateICmpNE(
        curVal,
        llvm::ConstantInt::get(
            *IRGenContext,
            llvm::APInt(curVal->getType()->getIntegerBitWidth(), 0)),
        "whilecond");

    IRGenBuilder->CreateCondBr(loopCond, loopBB, contBB);

    fun->getBasicBlockList().push_back(loopBB);
    IRGenBuilder->SetInsertPoint(loopBB);

    if (!body->codeGen())
        return logAndReturn("While stmt has invalid stmt");

    IRGenBuilder->CreateBr(condBB);

    fun->getBasicBlockList().push_back(contBB);
    IRGenBuilder->SetInsertPoint(contBB);

    return RetValZero;
}

llvm::Value* ASTNode_StmtFor::codeGen()
{
    buildLabel();

    auto beginV = begin->codeGen();
    if (!beginV)
        return logAndReturn("For stmt has invalid begin value");
    // only supports integer as stepping value
    if (!beginV->getType()->isIntegerTy())
        return logAndReturn("For stmt only supports begin value of integer");

    auto fun = IRGenBuilder->GetInsertBlock()->getParent();
    auto stepVar = allocInEntryBlock(fun, name, beginV->getType());
    IRGenBuilder->CreateStore(beginV, stepVar);
    currentSymbolTable->insertVariable(name, { stepVar,"integer" });

    auto condBB = llvm::BasicBlock::Create(*IRGenContext, "forcond", fun);
    auto loopBB = llvm::BasicBlock::Create(*IRGenContext, "for");
    auto contBB = llvm::BasicBlock::Create(*IRGenContext, "forcont");
    IRGenBuilder->CreateBr(condBB);
    IRGenBuilder->SetInsertPoint(condBB);

    auto endV = end->codeGen();
    if (!endV)
        return logAndReturn("For stmt has invalid end value");
    // only supports integer as stepping value
    if (!endV->getType()->isIntegerTy())
        return logAndReturn("For stmt only supports end value of integer");

    auto curVal = IRGenBuilder->CreateLoad(stepVar, name);

    // if stepping++, check if end value <= stepping
    // if stepping--, check if end value >= stepping
    // if loopCond is true, loop again
    auto loopCond = this->isPositive ?
        IRGenBuilder->CreateICmpSLE(curVal, endV, "forcond") :
        IRGenBuilder->CreateICmpSGE(curVal, endV, "forcond");

    IRGenBuilder->CreateCondBr(loopCond, loopBB, contBB);

    fun->getBasicBlockList().push_back(loopBB);
    IRGenBuilder->SetInsertPoint(loopBB);

    if (!body->codeGen())
        return logAndReturn("For stmt has invalid stmt");

    auto nextVal = this->isPositive ?
        IRGenBuilder->CreateAdd(curVal, llvm::ConstantInt::get(curVal->getType(), 1), "stepping") :
        IRGenBuilder->CreateSub(curVal, llvm::ConstantInt::get(curVal->getType(), 1), "stepping");
    IRGenBuilder->CreateStore(nextVal, stepVar);

    IRGenBuilder->CreateBr(condBB);

    fun->getBasicBlockList().push_back(contBB);
    IRGenBuilder->SetInsertPoint(contBB);
    currentSymbolTable->removeVariable(name);

    return RetValZero;
}

llvm::Value* ASTNode_StmtCase::codeGen()
{
    buildLabel();

    auto condV = cond->codeGen();
    if (!condV)
        return logAndReturn("Case stmt has invalid condition");
    if (!condV->getType()->isIntegerTy())
        return logAndReturn("Case stmt expects integer condition");

    auto fun = IRGenBuilder->GetInsertBlock()->getParent();
    std::vector<std::pair<llvm::Constant*, llvm::BasicBlock*>> cases;
    auto endBB = llvm::BasicBlock::Create(*IRGenContext, "endcase");
    auto sw = IRGenBuilder->CreateSwitch(condV, nullptr, caseList->children.size());

    auto buildCaseBody = [&fun, &endBB](ASTNode* body) -> llvm::BasicBlock*
    {
        auto bb = llvm::BasicBlock::Create(*IRGenContext, "case", fun);
        IRGenBuilder->SetInsertPoint(bb);
        if (!body->codeGen())
        {
            CodeGenLogger.println("Case clause has invalid stmt");
            return nullptr;
        }
        IRGenBuilder->CreateBr(endBB);
        return bb;
    };

    for (auto caseExpr : caseList->children)
    {
        if (caseExpr->getType() == ASTNodeType::CaseExprLiteral)
        {
            auto c = dynamic_cast<ASTNode_CaseExprLiteral*>(caseExpr);
            auto v = c->value->codeGen();
            auto bb = buildCaseBody(c->body);
            cases.emplace_back(v, bb);
        }
        else if (caseExpr->getType() == ASTNodeType::CaseExprConstVar)
        {
            auto c = dynamic_cast<ASTNode_CaseExprConstVar*>(caseExpr);
            auto symbol = currentSymbolTable->getConstant(c->name);
            if (!symbol)
                return logAndReturn("Case clause const variable not found");
            if (!symbol->raw->getType()->isIntegerTy())
                return logAndReturn("Case clause expects integer");
            auto bb = buildCaseBody(c->body);
            cases.emplace_back(symbol->raw, bb);
        }
        else if (caseExpr->getType() == ASTNodeType::CaseExprDefault)
        {
            auto c = dynamic_cast<ASTNode_CaseExprDefault*>(caseExpr);
            auto bb = llvm::BasicBlock::Create(*IRGenContext, "default", fun);
            IRGenBuilder->SetInsertPoint(bb);
            if (!c->body->codeGen())
                return logAndReturn("Case default clause has invalid stmt");
            IRGenBuilder->CreateBr(endBB);
            sw->setDefaultDest(bb);
        }
    }

    for (auto& c : cases)
        sw->addCase(reinterpret_cast<llvm::ConstantInt*>(c.first), c.second);

    fun->getBasicBlockList().push_back(endBB);
    IRGenBuilder->SetInsertPoint(endBB);

    return RetValZero;
}

llvm::Value* ASTNode_StmtGoto::codeGen()
{
    buildLabel();

    // only look for labels in the function body located in.
    // still, this may not reach labels after it.
    // should use a jump table to store all labeled basic blocks pointers.
    auto fun = IRGenBuilder->GetInsertBlock()->getParent();
    llvm::BasicBlock* gotoBB = nullptr;
    for (auto& bb : fun->getBasicBlockList())
        if (bb.getName() == gotoLabel)
        {
            gotoBB = &bb;
            break;
        }

    if (gotoBB)
    {
        IRGenBuilder->CreateBr(gotoBB);
        return RetValZero;
    }
    else
        return logAndReturn("Invalid label in goto stmt: " + gotoLabel);
}
