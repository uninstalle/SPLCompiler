#pragma once
#include <map>
#include <string>

struct Identifier
{
    std::string literal;
};

union Constant
{
    const int integer;
    const double real;
    const char character;
    const char *string;
    const bool boolean;
};

class IdentifierTable
{
public:
    void insert();
};

class ConstTable
{
};

class VarNameTalbe
{
};