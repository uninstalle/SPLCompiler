#include "Parser.hh"
#include "ast/ast.hh"
#include "irgen/generator.hh"
#include <iostream>

int main(int args, char** argv)
{
    if (args > 3)
    {
        std::cout << "Unexpected number of args.\n";
        return 1;
    }
    else if (args > 1) //file
    {
        extern FILE* yyin;
        yyin = fopen(argv[1], "r");
        if (!yyin)
        {
            std::cout << "Unable to open file " << argv[1] << std::endl;
            return 1;
        }
        yyparse();
        fclose(yyin);
    }
    else //stdin
    {
        yyparse();
    }

    ASTHandler::codeGen(argv[1], args == 3);

    return 0;
}