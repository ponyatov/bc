%{
    #include "bc.hpp"
%}

%defines %union { Object *o; }

%type  <o> ex
%token <o> SYM NUM STR OP
%token <o> LP RP LQ RQ
%%

REPL :
REPL : REPL ex  { cout << $2->dump(); }

ex : SYM
ex : NUM
ex : STR
ex : OP
ex : LP
ex : RP
ex : LQ
ex : RQ
