%{
#include "bc.hpp"
char* yyfile = nullptr;
%}

%option noyywrap yylineno

%%
. {yyerror("");} // lexer error on any undetected char
