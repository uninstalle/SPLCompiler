#include "ast_expr.hh"
#include "../irgen/generator.hh"
#include "../irgen/table.hh"

// promote two operands to the same type for computing
// return false if some operand is not computable type (int or real)
bool ASTNode_Operator::intPromotion(llvm::Value*& LHS, llvm::Value*& RHS)
{
    bool LI = isInt(LHS), LD = isDouble(LHS), RI = isInt(RHS), RD = isDouble(RHS);

    // LHS or RHS is of not computable type
    if (!((LI || LD) && (RI || RD)))
        return false;

    // compute between int and double, promote to double
    if (LI && RD)
        LHS = IRGenBuilder->CreateSIToFP(LHS, llvm::Type::getDoubleTy(*IRGenContext), "sitofp");
    else if (LD && RI)
        RHS = IRGenBuilder->CreateSIToFP(RHS, llvm::Type::getDoubleTy(*IRGenContext), "sitofp");
    // compute between int with different bit width, promote to i32
    else if (LI && RI && getIntSize(LHS) != getIntSize(RHS))
    {
        LHS = IRGenBuilder->CreateSExt(LHS, llvm::Type::getInt32Ty(*IRGenContext), "sext");
        RHS = IRGenBuilder->CreateSExt(RHS, llvm::Type::getInt32Ty(*IRGenContext), "sext");
    }
    return true;
}

llvm::Value* ASTNode_OperatorAdd::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in add");

    if (isInt(L))
        return IRGenBuilder->CreateAdd(L, R, "add");
    else if (isDouble(L))
        return IRGenBuilder->CreateFAdd(L, R, "fadd");
    else
        return nullptr;
}

llvm::Value* ASTNode_OperatorSub::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in sub");

    if (isInt(L))
        return IRGenBuilder->CreateSub(L, R, "sub");
    else if (isDouble(L))
        return IRGenBuilder->CreateFSub(L, R, "fsub");
    else
        return nullptr;
}

llvm::Value* ASTNode_OperatorMul::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in mul");

    if (isInt(L))
        return IRGenBuilder->CreateMul(L, R, "mul");
    else if (isDouble(L))
        return IRGenBuilder->CreateFMul(L, R, "fmul");
    else
        return nullptr;
}

llvm::Value* ASTNode_OperatorDiv::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in div");

    if (isInt(L))
    {
        if (getIntSize(L) == 32) // integer
            return IRGenBuilder->CreateSDiv(L, R, "sdiv");
        else // char, boolean
            return IRGenBuilder->CreateUDiv(L, R, "udiv");
    }
    else if (isDouble(L))
        return IRGenBuilder->CreateFDiv(L, R, "fdiv");
    else
        return nullptr;
}

llvm::Value* ASTNode_OperatorMod::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in mod");

    if (isInt(L))
    {
        if (getIntSize(L) == 32) // integer
            return IRGenBuilder->CreateSRem(L, R, "srem");
        else // char, boolean
            return IRGenBuilder->CreateURem(L, R, "urem");
    }
    else if (isDouble(L))
        return IRGenBuilder->CreateFRem(L, R, "frem");
    else
        return nullptr;
}

llvm::Value* ASTNode_OperatorMinus::codeGen()
{
    auto L = LHS->codeGen();
    if (!(isInt(L) || isDouble(L)))
        return logAndReturn("Invalid operand in uminus");

    if (isInt(L)) // -L = 0 - L
        return IRGenBuilder->CreateSub(
            llvm::ConstantInt::get(*IRGenContext, llvm::APInt(L->getType()->getIntegerBitWidth(), 0, true)),
            L, "ineg");
    else if (isDouble(L))
        return IRGenBuilder->CreateFNeg(L, "fneg");
    else
        return nullptr;
}

llvm::Value* ASTNode_OperatorGE::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in ge");

    if (isInt(L))
    {
        if (getIntSize(L) == 32) // integer
            return IRGenBuilder->CreateICmpSGE(L, R, "icmpsge");
        else // char, boolean
            return IRGenBuilder->CreateICmpUGE(L, R, "icmpuge");
    }
    else if (isDouble(L))
        return IRGenBuilder->CreateFCmpOGE(L, R, "fcmpoge");
    else
        return nullptr;
}

llvm::Value* ASTNode_OperatorGT::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in gt");

    if (isInt(L))
    {
        if (getIntSize(L) == 32) // integer
            return IRGenBuilder->CreateICmpSGT(L, R, "icmpsgt");
        else // char, boolean
            return IRGenBuilder->CreateICmpUGT(L, R, "icmpugt");
    }
    else if (isDouble(L))
        return IRGenBuilder->CreateFCmpOGT(L, R, "fcmpogt");
    else
        return nullptr;
}

llvm::Value* ASTNode_OperatorLE::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in le");

    if (isInt(L))
    {
        if (getIntSize(L) == 32) // integer
            return IRGenBuilder->CreateICmpSLE(L, R, "icmpsle");
        else // char, boolean
            return IRGenBuilder->CreateICmpULE(L, R, "icmpule");
    }
    else if (isDouble(L))
        return IRGenBuilder->CreateFCmpOLE(L, R, "fcmpole");
    else
        return nullptr;
}

llvm::Value* ASTNode_OperatorLT::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in lt");

    if (isInt(L))
    {
        if (getIntSize(L) == 32) // integer
            return IRGenBuilder->CreateICmpSLT(L, R, "icmpslt");
        else // char, boolean
            return IRGenBuilder->CreateICmpULT(L, R, "icmpult");
    }
    else if (isDouble(L))
        return IRGenBuilder->CreateFCmpOLT(L, R, "fcmpolt");
    else
        return nullptr;
}

llvm::Value* ASTNode_OperatorEQ::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in eq");

    if (isInt(L))
        return IRGenBuilder->CreateICmpEQ(L, R, "icmpeq");
    else if (isDouble(L))
        return IRGenBuilder->CreateFCmpOEQ(L, R, "fcmpoeq");
    else
        return nullptr;
}

llvm::Value* ASTNode_OperatorNE::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in ne");

    if (isInt(L))
        return IRGenBuilder->CreateICmpNE(L, R, "icmpne");
    else if (isDouble(L))
        return IRGenBuilder->CreateFCmpONE(L, R, "fcmpone");
    else
        return nullptr;
}

llvm::Value* ASTNode_OperatorAnd::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in and");

    return IRGenBuilder->CreateAnd(L, R, "and");
}

llvm::Value* ASTNode_OperatorOr::codeGen()
{
    auto L = LHS->codeGen();
    auto R = RHS->codeGen();
    if (!intPromotion(L, R))
        return logAndReturn("Invalid operand in or");

    return IRGenBuilder->CreateOr(L, R, "or");
}

llvm::Value* ASTNode_OperatorNot::codeGen()
{
    auto L = LHS->codeGen();
    if (!(isInt(L) || isDouble(L)))
        return logAndReturn("Invalid operand in not");

    return IRGenBuilder->CreateNot(L, "not");
}

llvm::Value* ASTNode_OperandLiteral::codeGen()
{
    return literal->codeGen();
}

llvm::Value* ASTNode_OperandVariable::codeGen()
{
    // constant
    auto cSymbol = currentSymbolTable->getConstant(name);
    if (cSymbol)
    {
        // global constant is variable
        if (cSymbol->isGlobal)
            return IRGenBuilder->CreateLoad(cSymbol->raw, name);
        else
            // local constant is value stored in symbol table
            return cSymbol->raw;
    }
    // variable
    auto vSymbol = currentSymbolTable->getVariable(name);
    if (vSymbol)
        return IRGenBuilder->CreateLoad(vSymbol->raw, name);

    // not found
    return logAndReturn("Variable not found: " + name);
}

llvm::Value* ASTNode_OperandFunction::codeGen()
{
    auto symbol = currentSymbolTable->getFunction(name);
    auto fun = symbol->raw;
    if (!fun)
        return logAndReturn("Function not found: " + name);

    // function without args
    if (fun->arg_size() == 0)
        return IRGenBuilder->CreateCall(fun, llvm::None, name + "_ret");

    // function expected args but stmt has no args
    if (args->children.empty())
        return logAndReturn("Function expects args but not provided: " + name);

    // function expects args but provided with different number of args
    if (args->children.size() != fun->arg_size())
        return logAndReturn("Function expects " + std::to_string(fun->arg_size()) + " args but provided " + std::to_string(args->children.size()) + ": " + name);

    auto argNode = args->children.begin();
    auto argIsRef = symbol->isRefArg.begin();
    std::vector<llvm::Value*> argsToSend;

    for (auto& arg : fun->args())
    {
        if (*argIsRef++)
        {
            // if the arg is a ref, it must be a lvalue, thus it only can be:
            // OperandVariable, OperandArrayElement, OperandRecordMember
            auto refArg = *argNode++;

            if (refArg->getType() == ASTNodeType::OperandVariable)
            {
                auto refArgT = dynamic_cast<ASTNode_OperandVariable*>(refArg);
                auto varSymbol = currentSymbolTable->getVariable(refArgT->name);
                if (!varSymbol)
                    return logAndReturn("Unresolved arg: " + refArgT->name + " in function " + name);
                auto var = reinterpret_cast<llvm::AllocaInst*>(varSymbol->raw);
                if (var->getType() != arg.getType())
                    return logAndReturn("Function arg type mismatched: " + name);
                argsToSend.push_back(var);
            }
            else if (refArg->getType() == ASTNodeType::OperandArrayElement)
            {
                auto refArgT = dynamic_cast<ASTNode_OperandArrayElement*>(refArg);
                auto varSymbol = currentSymbolTable->getVariable(refArgT->name);
                if (!varSymbol)
                    return logAndReturn("Unresolved arg in function: " + name);
                // global variable array is not array type, so we can't use isArrayTy() here
                auto typeSymbol = currentSymbolTable->getType(varSymbol->typeName);
                if (typeSymbol->exType != TypeSymbol::ExtraTypeInfo::Array)
                    return logAndReturn("Arg is not an array: " + refArgT->name + " in function " + name);
                auto i = refArgT->index->codeGen();
                auto var = IRGenBuilder->CreateGEP( typeSymbol->raw  , varSymbol->raw, { RetValZero,i });
                if (var->getType() != arg.getType())
                    return logAndReturn("Function arg type mismatched: " + name);
                argsToSend.push_back(var);
            }
            // TODO
            else
                return logAndReturn("Function expects ref arg but provided with constant: " + name);
        }
        else
        {
            auto v = (*argNode++)->codeGen();
            if (!v)
                return logAndReturn("Unresolved arg in function: " + name);
            // type check
            if (v->getType() != arg.getType())
                return logAndReturn("Function arg type mismatched: " + name);
            argsToSend.push_back(v);
        }
    }

    return IRGenBuilder->CreateCall(fun, argsToSend, name + "_ret");
}

llvm::Value* ASTNode_OperandSystemFunction::codeGen()
{
    // System function is unary
    if (args->children.size() != 1)
        return logAndReturn("Sysfunc expects one arg: " + name);

    auto arg = dynamic_cast<ASTNode_Expr*>(args->children[0])->codeGen();

    // abs i32 or fp, 2nd arg indicates whether return poison_value or int_min if is int_min
    if (name == "abs")
        return IRGenBuilder->CreateBinaryIntrinsic(llvm::Intrinsic::abs, arg,
            llvm::ConstantInt::get(*IRGenContext, llvm::APInt(1, 0)),
            nullptr, "abs");
    // chr i32 to i8
    if (name == "chr")
        return IRGenBuilder->CreateTrunc(arg, llvm::Type::getInt8Ty(*IRGenContext), "chr");
    // odd i32 to i1
    if (name == "odd")
    {
        auto tmp = IRGenBuilder->CreateURem(arg, llvm::ConstantInt::get(llvm::Type::getInt32Ty(*IRGenContext), 2), "oddtmp");
        return IRGenBuilder->CreateTrunc(tmp, llvm::Type::getInt1Ty(*IRGenContext), "odd");
    }
    // ord i8 to i32
    if (name == "ord")
        return IRGenBuilder->CreateSExt(arg, llvm::Type::getInt32Ty(*IRGenContext), "ord");
    // pred i32 x = x - 1
    if (name == "pred")
        return IRGenBuilder->CreateSub(arg, llvm::ConstantInt::get(arg->getType(), 1, true), "pred");
    // sqr i32 x = x * x
    if (name == "sqr")
        return IRGenBuilder->CreateMul(arg, arg, "sqr");
    // sqrt i32 or fp return fp
    if (name == "sqrt")
        return IRGenBuilder->CreateUnaryIntrinsic(llvm::Intrinsic::sqrt, arg);
    // succ i32 x = x + 1
    if (name == "succ")
        return IRGenBuilder->CreateAdd(arg, llvm::ConstantInt::get(arg->getType(), 1, true), "succ");

    return logAndReturn("Unrecognized system function " + name);
}

llvm::Value* ASTNode_OperandArrayElement::codeGen()
{
    auto varSymbol = currentSymbolTable->getVariable(name);
    if (!varSymbol)
        return logAndReturn("Unresolved variable: " + name);
    auto i = index->codeGen();
    // type check
    auto typeSymbol = currentSymbolTable->getType(varSymbol->typeName);
    if (typeSymbol->exType != TypeSymbol::ExtraTypeInfo::Array)
        return logAndReturn("Not an array: " + name);

    auto ptrToElement = IRGenBuilder->CreateGEP(typeSymbol->raw, varSymbol->raw, { RetValZero,i });
    return IRGenBuilder->CreateLoad(ptrToElement);
}

llvm::Value* ASTNode_OperandRecordMember::codeGen()
{
    //TODO
}
