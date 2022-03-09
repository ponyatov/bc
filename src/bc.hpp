#ifndef _BC_H
#define _BC_H

#include <assert.h>

#include <iostream>
#include <sstream>
using namespace std;

class Object {
    string value;

   public:
    Object(string V);
    ~Object();
    string dump(int depth = 0, string prefix = "");
    string pad(int depth);
    string head(string prefix = "");
};

class Primitive : public Object {
   public:
    Primitive(string V);
};

class Sym : public Primitive {
   public:
    Sym(string V);
};

class Num : public Primitive {
   public:
    Num(string V);
};

class Str : public Primitive {
   public:
    Str(string V);
};

class Active : public Object {
   public:
    Active(string V);
};

class Op : public Active {
   public:
    Op(string V);
};

extern int yylex();
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
extern int yyparse();
extern void yyerror(string);
#define TOKEN(C, X)               \
    {                             \
        yylval.o = new C(yytext); \
        return X;                 \
    }
#include "bc.parser.hpp"

#endif  // _BC_H
