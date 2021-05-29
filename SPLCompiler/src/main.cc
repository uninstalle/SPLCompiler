#include <iostream>
#include "Parser.hh"

int main(int args, char** argv)
{
	if (args > 2)
	{
		std::cout << "Unexpected number of args.\n";
		return 1;
	}
	else if (args == 2) //file
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

	return 0;
}