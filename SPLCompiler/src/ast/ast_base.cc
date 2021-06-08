#include "ast_base.hh"
#include "../logger/log.hh"

llvm::Value* ASTNode::logAndReturn(const std::string& msg)
{
	CodeGenLogger.println(msg);
	return nullptr;
}
