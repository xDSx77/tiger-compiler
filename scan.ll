%option debug nounput

%{
#include <iostream>

static int nb_digits = 0;
static int nb_ids = 0;
static int nb_other = 0;
%}

digit [0-9]+
id [a-z][a-z0-9]*

%%

<<EOF>>         yywrap(); yyterminate();
{digit}         ++nb_digits;
{id}            ++nb_ids;
.               ++nb_other;

%%
int yywrap()
{
    std::cout << "number of digits: " << nb_digits << '\n' <<
        "number of ids: " << nb_ids << '\n' << "other: " << nb_other << '\n';
    return 1;
}

int main()
{
    yylex();
    return 0;
}
