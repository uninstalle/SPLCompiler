%{
#include <stdio.h>
#include <math.h>

#define YYSTYPE int

extern int yylex(void);
extern int yyparse(void);
void yyerror(const char* s);
%}

%token INTEGER ADD SUB MUL DIV POW LP RP EXPEND

%%

commands: /* %empty */
    |commands command
    ;

command:
    exp EXPEND {printf("%d\n",$1);}
    ;

exp:
    exp ADD term {$$ = $1 + $3;}
	|exp SUB term {$$ = $1 - $3;}
	|term {$$ = $1;}
	;
term:
    term MUL factor {$$ = $1 * $3;}
	|term DIV factor {$$ = $1 / $3;}
	|factor {$$ = $1;}
	;
factor:
    SUB power {$$ = -$2;}
    |power {$$ = $1;}
	;
power:
    power POW num {$$ = pow($1, $3);}
    | num {$$ = $1;}
    ;
num:
    INTEGER {$$ = $1;}
    |LP exp RP {$$ = $2;}
    ;

%%

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
        yyin = fopen(argv[1],"r");
        if(!yyin) 
        {
            printf("Unable to open file %s\n",argv[1]);
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

int yywrap()
{
	return 1;
}

void yyerror(const char* s)
{
	fprintf(stderr,"\n%s\n",s);
}