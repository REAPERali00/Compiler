// /*
// ************************************************************
// * COMPILERS COURSE - Algonquin College
// * Code version: Fall, 2022
// * Author: Svillen Ranev - Paulo Sousa
// * Professors: Paulo Sousa
// ************************************************************
//  _________________________________
// |                                 |
// | ........ nag LANGUAGE ......... |
// |     __    __    __    __        |
// |    /  \  /  \  /  \  /  \       |
// | __/  __\/  __\/  __\/  __\__    |
// | _/  /__/  /__/  /__/  /_____|   |
// |  \_/ \   / \   / \   / \  \___  |
// |       \_/   \_/   \_/   \___o_> |
// |                                 |
// | .. ALGONQUIN COLLEGE - 2022F .. |
// |_________________________________|
//
// */
//
// /*
// ************************************************************
// * File name: parser.h
// * Compiler: MS Visual Studio 2022
// * Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
// * Assignment: A32.
// * Date: Sep 01 2022
// * Professor: Paulo Sousa
// * Purpose: This file is the main header for Parser (.h)
// *************************************************************/
//
// #ifndef PARSER_H_
// #define PARSER_H_
//
// /* Inclusion section */
// #include <stdarg.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
// #ifndef COMPILERS_H_
// #include "Compilers.h"
// #endif
// #ifndef READER_H_
// #include "Reader.h"
// #endif
// #ifndef SCANNER_H_
// #include "Scanner.h"
// #endif
//
// /* Global vars */
// static Token lookahead;
// extern BufferReader *stringLiteralTable;
// extern nag_i line;
// extern Token tokenizer();
// extern nag_ch *keywordTable[];
// nag_i syntaxErrorNumber = 0;
//
// #define STR_LANGNAME "Nagini"
// #define LANG_WRTE "print!"
// #define LANG_READ "input!"
// #define LANG_MAIN "main!"
//
// /* TO_DO: Create ALL constants for keywords (sequence given in table.h) */
//
// /* Constants */
// enum KEYWORDS {
//   NO_ATTR = -1,
//   KW_data,
//   KW_code,
//   KW_int,
//   KW_string,
//   KW_char,
//   KW_float,
//   KW_if,
//   KW_elseIf,
//   KW_else,
//   KW_loop
// };
//
// /* Function definitions */
// nag_v startParser();
// nag_v matchToken(nag_i, nag_i);
// nag_v syncErrorHandler(nag_i);
// nag_v printError();
//
// /* TO_DO: Place ALL non-terminal function declarations */
// nag_v program();
// nag_v dataSession();
// nag_v codeSession();
// nag_v optVarListDeclarations();
// nag_v optionalStatements();
// nag_v outputVariableList();
// nag_v outputStatement();
// nag_v statement();
// nag_v statements();
// nag_v statementsPrime();
//
// nag_v varListDeclarations();
// nag_v varListDeclaration();
// nag_v varListDeclarationsPrime();
//
// #endif
