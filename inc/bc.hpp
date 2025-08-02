#pragma once

/// @defgroup core core

/// @defgroup config config
/// @ingroup core
/// @{

/// @ref M size, bytes
#define Msz 0x10000
/// @ref R size, @ref addr esses
#define Rsz 0x100
/// @ref D size, @ref cell s
#define Dsz 0x10
/// @}

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include <map>
#include <vector>
#include <string>

/// @defgroup main main
/// @ingroup core
/// @{
extern int main(int argc, char *argv[]);
extern void arg(int argc, char *argv);
/// @}

/// @defgroup vm vm
/// @ingroup core

/// @defgroup types types
/// @ingroup vm
/// @{
typedef uint8_t byte;   ///< byte type
typedef uint16_t addr;  ///< memory address limited to 64K
typedef int32_t cell;   ///< VM integer
/// @}

/// @defgroup memory memory
/// @ingroup vm
/// @{
extern byte M[Msz];  ///< main memory
extern addr Cp;      ///< compiler pointer (@ref M)
extern addr Ip;      ///< interpreter pointer (@ref M)

extern addr R[Rsz];  ///< return stack
extern byte Rp;      ///< @ref R pointer (@ref R)

extern cell D[Dsz];  ///< data stack
extern byte Dp;      ///< @ref D pointer (@ref D)
/// @}

extern std::map<std::string, addr> label;                 ///< known labels
extern std::map<std::string, std::vector<addr>> forward;  ///< forward refs

extern int yylex();
extern int yylineno;
extern char *yytext;
extern char *yyfile;
extern FILE *yyin;
extern int yyparse();
extern void yyerror(const char *msg);
#include "bc.yacc.hpp"
