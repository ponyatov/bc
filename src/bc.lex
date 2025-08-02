%{
#include "bc.hpp"
char* yyfile = nullptr;
%}

%option noyywrap yylineno

alpha [a-zA-Z_]
alnum [a-zA-Z_0-9]

%%
#![^\n]*            {}              // shebang
"//"[^\n]*          {}              // line comment
"/*".+?"*/"         {}              // block comment

:{alpha}{alnum}*    {yylval.s = new std::string(&yytext[1]); return LABEL; }

.                   {yyerror("");}  // lexer error on any undetected char
