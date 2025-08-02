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
extern int main(int argc, char *argv[]);  ///< system entry point
extern void arg(int argc, char *argv);    ///< print command line argument
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

/// @defgroup command command
/// @ingroup vm
/// @{

/// @brief command opcode (single byte)
enum class Op {
    nop = 0x00,   ///< 0x00 `( -- )` do nothing
    halt = 0xFF,  ///< 0xFF `( -- )` stop system

    jmp = 0x01,   ///< 0x01 `( -- )` unconditional jump
    jnz = 0x02,   ///< 0x02 `( -- )` conditional jump
    call = 0x03,  ///< 0x03 `(R: -- addr )` nested call
    ret = 0x04,   ///< 0x04 `(R: addr -- )` return from @ref Op::call
    let = 0x05,   ///< 0x05 `( -- n )` @ref cell literal
};

extern void nop();   ///< @ref Op::nop
extern void halt();  ///< @ref Op::halt

/// @}

/// @defgroup compiler compiler
/// @ingroup core
/// @{
extern std::map<std::string, addr> label;                 ///< known labels
extern std::map<std::string, std::vector<addr>> forward;  ///< forward refs
/// @}

/// @defgroup parser parser
/// @ingroup compiler
/// @{
extern int yylex();                    ///< lexer (flex)
extern int yylineno;                   ///< current line
extern char *yytext;                   ///< lexeme value
extern char *yyfile;                   ///< current file name
extern FILE *yyin;                     ///< current file handler
extern int yyparse();                  ///< syntax parser (bison)
extern void yyerror(const char *msg);  ///< syntax error callback
#include "bc.yacc.hpp"
/// @}
