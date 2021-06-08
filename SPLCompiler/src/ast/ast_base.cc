#include "ast_base.hh"

llvm::Value *ASTNode::logAndReturn(const std::string &msg)
{
	CodeGenLogger.println(msg);
	return nullptr;
}
