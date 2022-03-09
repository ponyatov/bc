#include "bc.hpp"

int main(int argc, char *argv[]) {
    printf("\n%s: compile\n", argv[0]);
    for (int i = 1; i < argc; i++) {
        printf("argv[%i] = <%s>\n", i, argv[i]);
        assert(yyin = fopen(argv[i], "r"));
        yyparse();
        fclose(yyin);
    }
    printf("\n");
    return 0;
}

#define YYERR "\n\n" << yylineno << ":" << msg << "[" << yytext << "]\n\n"
void yyerror(string msg) {
    cerr << YYERR;
    exit(-1);
}

Object::Object(string V) { value = V; }
Object::~Object() {}

string Object::pad(int depth) {
    ostringstream ret;
    ret << '\n';
    for (uint i = 0; i < depth; i++) ret << '\t';
    return ret.str();
}

string Object::dump(int depth, string prefix) {
    ostringstream ret;
    ret << pad(depth) << head(prefix);
    return ret.str();
}

string Object::head(string prefix) {
    ostringstream ret;
    return ret.str();
}

Primitive::Primitive(string V) : Object(V) {}
Sym::Sym(string V) : Primitive(V) {}
Num::Num(string V) : Primitive(V) {}
Str::Str(string V) : Primitive(V) {}

Active::Active(string V) : Object(V) {}
Op::Op(string V) : Active(V) {}
