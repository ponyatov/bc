%{
    #include "bc.hpp"
    ostringstream ostr;
%}

%option yylineno noyywrap

%x string

%%
#.*             {}              // line comment

"'"         { ostr.clear(); BEGIN(string); }
<string>"'" { BEGIN(INITIAL); yylval.o = new Str(ostr.str()); return STR; }
<string>.   { ostr << yytext; }

[a-zA-Z_][a-zA-Z_0-9]*  TOKEN(Sym,SYM)
[0-9]+                  TOKEN(Num,NUM)
!?=                     TOKEN(Op,OP)
[\+\-\*\/]              TOKEN(Op,OP)
[<>:.,]                 TOKEN(Op,OP)
"["                     TOKEN(Op,LQ)
"]"                     TOKEN(Op,RQ)
"("                     TOKEN(Op,LP)
")"                     TOKEN(Op,RP)

[ \t\r\n]+      {}              // drop spaces
.               {yyerror("");}  // any undetected char
