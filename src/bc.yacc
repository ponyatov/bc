%{
#include "bc.hpp"
%}

%defines %union { char c; std::string* s; int n; float f; }

%token<s> LABEL

%%
syntax: | label syntax

label: LABEL    { label[*$1] = Cp; }

%%
void yyerror(const char *msg) {
    fprintf(stderr, "\n\n%s:%i %s [%s]\n\n", yyfile, yylineno, msg, yytext);
    exit(-1);
}
