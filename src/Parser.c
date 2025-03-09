﻿// /*
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
// * File name: mainBuffer.c
// * Compiler: MS Visual Studio 2022
// * Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
// * Assignment: A32.
// * Date: Sep 01 2022
// * Purpose: This file contains all functionalities from Parser.
// * Function list: (...).
// ************************************************************
// */
//
// /* TODO: Adjust the function header */
//
// #ifndef COMPILERS_H_
// #include "Compilers.h"
// #endif
//
// #ifndef PARSER_H_
// #include "Parser.h"
// #endif
//
// /*
// ************************************************************
//  * Process Parser
//  ***********************************************************
//  */
// /* TODO: This is the function to start the parser - check your program
// definition */
//
// nag_v startParser() {
// 	lookahead = tokenizer();
// 	if (lookahead.code != SEOF_T) {
// 		program();
// 	}
// 	matchToken(SEOF_T, NO_ATTR);
// 	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
// }
//
//
// /*
//  ************************************************************
//  * Match Token
//  ***********************************************************
//  */
// /* TODO: This is the main code for match - check your definition */
// nag_v matchToken(nag_i tokenCode, nag_i tokenAttribute) {
// 	nag_i matchFlag = 1;
// 	switch (lookahead.code) {
// 	case KW_T:
// 		if (lookahead.attribute.codeType != tokenAttribute)
// 			matchFlag = 0;
// 	default:
// 		if (lookahead.code != tokenCode)
// 			matchFlag = 0;
// 	}
// 	if (matchFlag && lookahead.code == SEOF_T)
// 		return;
// 	if (matchFlag) {
// 		lookahead = tokenizer();
// 		if (lookahead.code == ERR_T) {
// 			printError();
// 			lookahead = tokenizer();
// 			syntaxErrorNumber++;
// 		}
// 	}
// 	else
// 		syncErrorHandler(tokenCode);
// }
//
// /*
//  ************************************************************
//  * Syncronize Error Handler
//  ***********************************************************
//  */
// /* TODO: This is the function to handler error - adjust basically datatypes
// */ nag_v syncErrorHandler(nag_i syncTokenCode) { 	printError();
// 	syntaxErrorNumber++;
// 	while (lookahead.code != syncTokenCode) {
// 		if (lookahead.code == SEOF_T)
// 			exit(syntaxErrorNumber);
// 		lookahead = tokenizer();
// 	}
// 	if (lookahead.code != SEOF_T)
// 		lookahead = tokenizer();
// }
//
// /*
//  ************************************************************
//  * Print Error
//  ***********************************************************
//  */
// /* TODO: This is the function to error printing - adjust basically datatypes
// */ nag_v printError() { 	Token t = lookahead; 	printf("%s%s%3d\n",
// STR_LANGNAME, ": Syntax error:  Line:", line); 	printf("*****  Token code:%3d
// Attribute: ", t.code); 	switch (t.code) { 	case ERR_T: 		printf("*ERROR*: %s\n",
// t.attribute.errLexeme); 		break; 	case SEOF_T: 		printf("SEOF_T\t\t%d\t\n",
// t.attribute.seofType); 		break; 	case MNID_T: 		printf("MNID_T:\t\t%s\t\n",
// t.attribute.idLexeme); 		break; 	case STR_T: 		printf("STR_T: %s\n",
// readerGetContent(stringLiteralTable, t.attribute.contentString)); 		break; 	case
// KW_T: 		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]); 		break; 	case
// LPR_T: 		printf("LPR_T\n"); 		break; 	case RPR_T: 		printf("RPR_T\n"); 		break; 	case
// LBR_T: 		printf("LBR_T\n"); 		break; 	case RBR_T: 		printf("RBR_T\n"); 		break; 	case
// EOS_T: 		printf("NA\n"); 		break; 	default: 		printf("%s%s%d\n", STR_LANGNAME, ":
// Scanner error: invalid token code: ", t.code);
// 	}
// }
//
// /*
//  ************************************************************
//  * Program statement
//  * BNF: <program> -> main& { <opt_statements> }
//  * FIRST(<program>)= {MNID_T (main&)}.
//  ***********************************************************
//  */
// nag_v program() {
// 	switch (lookahead.code) {
// 	case MNID_T:
// 		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
// 			matchToken(MNID_T, NO_ATTR);
// 			matchToken(LBR_T, NO_ATTR);
// 			dataSession();
// 			codeSession();
// 			matchToken(RBR_T, NO_ATTR);
// 			break;
// 		}
// 		else {
// 			printError();
// 		}
// 	case SEOF_T:
// 		; // Empty
// 		break;
// 	default:
// 		printError();
// 	}
// 	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
// }
//
//
// /*
//  ************************************************************
//  * dataSession
//  * BNF: <dataSession> -> data { <opt_varlist_declarations> }
//  * FIRST(<program>)= {KW_T (KW_data)}.
//  ***********************************************************
//  */
// nag_v dataSession() {
// 	matchToken(KW_T, KW_data);
// 	matchToken(LBR_T, NO_ATTR);
// 	optVarListDeclarations();
// 	matchToken(RBR_T, NO_ATTR);
// 	printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
// }
//
//
//
//
// /*
//  ************************************************************
//  * Optional Var List Declarations
//  * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
//  * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T
//  (KW_float),KW_T (KW_char), KW_T (KW_string)}.
//  ***********************************************************
//  */
// nag_v optVarListDeclarations() {
// 	switch (lookahead.code) {
// 	case KW_T:
// 		varListDeclarations();
// 		break;
// 	default:
// 		; // Empty
// 	}
// 	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations
// parsed");
// }
//
// /*
//  ************************************************************
//  * Var List Declarations
//  * BNF: <varlist_declarations> -> <varlist_declaration>
//  <varlist_declarationsPrime>
//  * FIRST(<varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_float),KW_T
//  (KW_char), KW_T (KW_string)}.
//  ***********************************************************
//  */
// nag_v varListDeclarations() {
//
// 	varListDeclaration();
// 	varListDeclarationsPrime();
//
// 	printf("%s%s\n", STR_LANGNAME, ": Variable List Declarations parsed");
// }
//
// /*
//  ************************************************************
//  * Var List Declarations Prime
//  * BNF: <varlist_declarations> -> <varlist_declarationsPrime> ->
//  <varlist_declaration> <varlist_declarationsPrime> | ϵ
//  * FIRST(<varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_float),KW_T
//  (KW_char), KW_T (KW_string)}.
//  ***********************************************************
//  */
// nag_v varListDeclarationsPrime() {
// 	switch (lookahead.code) {
// 	case KW_T:
// 		varListDeclaration();
// 		varListDeclarationsPrime();
// 	default:
// 		; // Empty
// 	}
// 	printf("%s%s\n", STR_LANGNAME, ": Variable List Declarations Prime
// parsed");
// }
//
//
// /*
//  ************************************************************
//  * Var List Declaration
//  * BNF: <varlist_declaration> -> <integer_varlist_declaration>
// 								|
// <float_varlist_declaration> 								| <char_varlist_declaration> 								|
// <string_varlist_declaration>
//
//  * FIRST(<varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_float),KW_T
//  (KW_char), KW_T (KW_string)}.
//  ***********************************************************
//  */
// nag_v varListDeclaration() {
//
// 		switch (lookahead.attribute.codeType) {
// 		case KW_int:
// 			matchToken(KW_T, KW_int);
// 			matchToken(IVAR_T, NO_ATTR);
// 			matchToken(EOS_T, NO_ATTR);
// 			printf("%s%s\n", STR_LANGNAME, ": Integer Variable List
// parsed"); 			break; 		case KW_float: 			matchToken(KW_T, KW_float);
// 			matchToken(FVAR_T, NO_ATTR);
// 			matchToken(EOS_T, NO_ATTR);
// 			printf("%s%s\n", STR_LANGNAME, ": Float Variable List
// parsed"); 			break; 		case KW_char: 			matchToken(KW_T, KW_char); 			matchToken(CVAR_T,
// NO_ATTR); 			matchToken(EOS_T, NO_ATTR); 			printf("%s%s\n", STR_LANGNAME, ":
// Character Variable List parsed"); 			break; 		case KW_string: 			matchToken(KW_T,
// KW_string); 			matchToken(SVAR_T, NO_ATTR); 			matchToken(EOS_T, NO_ATTR);
// 			printf("%s%s\n", STR_LANGNAME, ": String Variable List
// parsed"); 			break;
// 		}
//
//
// 	printf("%s%s\n", STR_LANGNAME, ": Variable List Declaration parsed");
// }
//
//
//
// /*
//  ************************************************************
//  * codeSession statement
//  * BNF: <codeSession> -> code { <opt_statements> }
//  * FIRST(<codeSession>)= {KW_T (KW_code)}.
//  ***********************************************************
//  */
// nag_v codeSession() {
// 	matchToken(KW_T, KW_code);
// 	matchToken(LBR_T, NO_ATTR);
// 	optionalStatements();
// 	matchToken(RBR_T, NO_ATTR);
// 	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
// }
//
//
//
// /* TODO: Continue the development (all non-terminal functions) */
//
// /*
//  ************************************************************
//  * Optional statement
//  * BNF: <opt_statements> -> <statements> | ϵ
//  * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
//  *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
//  ***********************************************************
//  */
// nag_v optionalStatements() {
// 	switch (lookahead.code) {
// 	case MNID_T:
// 		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0)
// || 			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
// 			statements();
// 			break;
// 		}
// 	default:
// 		; // Empty
// 	}
// 	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
// }
//
// /*
//  ************************************************************
//  * Statements
//  * BNF: <statements> -> <statement><statementsPrime>
//  * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
//  *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
//  ***********************************************************
//  */
// nag_v statements() {
// 	statement();
// 	statementsPrime();
// 	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
// }
//
// /*
//  ************************************************************
//  * Statements Prime
//  * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
//  * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T,
//  *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
//  ***********************************************************
//  */
// nag_v statementsPrime() {
// 	switch (lookahead.code) {
// 	case MNID_T:
// 		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
// 			statement();
// 			break;
// 		}
// 	default:
// 		; //empty string
// 	}
// }
//
// /*
//  ************************************************************
//  * Single statement
//  * BNF: <statement> -> <assignment statement> | <selection statement> |
//  *	<iteration statement> | <input statement> | <output statement>
//  * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
//  KW_T(KW_while), *			MNID_T(input&), MNID_T(print&) }
//  ***********************************************************
//  */
// nag_v statement() {
// 	switch (lookahead.code) {
// 	case KW_T:
// 		switch (lookahead.attribute.codeType) {
// 		default:
// 			printError();
// 		}
// 		break;
// 	case MNID_T:
// 		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
// 			outputStatement();
// 		}
// 		break;
// 	default:
// 		printError();
// 	}
// 	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
// }
//
// /*
//  ************************************************************
//  * Output Statement
//  * BNF: <output statement> -> print& (<output statementPrime>);
//  * FIRST(<output statement>) = { MNID_T(print&) }
//  ***********************************************************
//  */
// nag_v outputStatement() {
// 	matchToken(MNID_T, NO_ATTR);
// 	matchToken(LPR_T, NO_ATTR);
// 	outputVariableList();
// 	matchToken(RPR_T, NO_ATTR);
// 	matchToken(EOS_T, NO_ATTR);
// 	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
// }
//
// /*
//  ************************************************************
//  * Output Variable List
//  * BNF: <opt_variable list> -> <variable list> | ϵ
//  * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
//  ***********************************************************
//  */
// nag_v outputVariableList() {
// 	switch (lookahead.code) {
// 	case STR_T:
// 		matchToken(STR_T, NO_ATTR);
// 		break;
// 	default:
// 		;
// 	}
// 	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
// }
