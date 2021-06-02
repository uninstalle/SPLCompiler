#pragma once
#include "ast.hh"
#include "log.hh"

class CodeGenerator
{
public:
	static void generateCode(ASTNode* head);
};