#include <stdio.h>

extern "C" {
#include "Parser.h"
}



int main(int args, char** argv)
{
	if (args > 2)
	{
		printf("Unexpected number of args.\n");
		return 1;
	}
	else if (args == 2) //file
	{
		extern FILE* yyin;
		yyin = fopen(argv[1], "r");
		if (!yyin)
		{
			printf("Unable to open file %s\n", argv[1]);
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