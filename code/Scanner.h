/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Jul 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "./Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */ /*to enforce C89 type comments  - to make
                                //comments an warning */

/*#pragma warning(error:4001)*/ /* to enforce C89 comments - to make // comments
                                   an error */

/* Constants */
#define VID_LEN 20 /* variable identifier length */
#define ERR_LEN 40 /* error message length */
#define NUM_LEN 5  /* maximum number of digits for IL */

#define RTE_CODE -1 /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
  ERR_T,  /*  0: Error token */
  MNID_T, /*  1: Method name identifier token (start: !) */
  STR_T,  /*  2: String literal token */
  CH_T,   /*  3: Character token */
  LPR_T,  /*  4: Left parenthesis token */
  RPR_T,  /*  5: Right parenthesis token */
  LBR_T,  /*  6: Left brace token */
  RBR_T,  /*  7: Right brace token */
  KW_T,   /*  8: Keyword token */
  EOS_T,  /*  9: End of statement (semicolon) */
  RTE_T,  /* 10: Run-time error token */
  INL_T,  /* 11: Integer literal token */
  SEOF_T, /* 12: Source end-of-file token */
  COM_T,  /* 13: Comma */
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
  nag_intg codeType;              /* integer attributes accessor */
  AriOperator arithmeticOperator; /* arithmetic operator attribute code */
  RelOperator relationalOperator; /* relational operator attribute code */
  LogOperator logicalOperator;    /* logical operator attribute code */
  EofOperator seofType;           /* source-end-of-file attribute code */
  nag_intg intValue;              /* integer literal attribute (value) */
  nag_intg keywordIndex;          /* keyword index in the keyword table */
  nag_intg
      contentString; /* string literal offset from the beginning of the string
                        literal buffer (stringLiteralTable->content) */
  nag_float floatValue;           /* floating-point literal attribute (value) */
  nag_char characterContent;      /* Character Content from buffer */
  nag_char idLexeme[VID_LEN + 1]; /* variable identifier token attribute */
  nag_char errLexeme[ERR_LEN + 1]; /* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
  nag_byte flags; /* Flags information */
  union {
    nag_intg intValue;       /* Integer value */
    nag_float floatValue;    /* Float value */
    nag_char *stringContent; /* String value */
  } values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
  nag_intg code;            /* token code */
  TokenAttribute attribute; /* token attribute */
  IdAttibutes idAttribute;  /* not used in this scanner implementation - for
                               further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part
 * of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';',
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # ,
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '!'
#define CHRCOL4 '\"'
#define CHRCOL5 '\''

/* These constants will be used on VID / MID function */
#define MNIDPREFIX '!'

/* TO_DO: Error states and illegal state */
#define FS 100   /* Illegal state */
#define ESWR 101 /* Error state with retract */
#define ESNR 102 /* Error state with no retract */

/* TO_DO: State transition table definition */
#define TABLE_COLUMNS 8

// remove errors
static nag_intg transitionTable[][TABLE_COLUMNS] = {
    /*   [A-z] , [0-9],    _,    !,    ",	 ', SEOF, other
               L(0),  D(1), U(2), M(3), Q(4), C(5), E(6),  O(7) */
    {1, ESNR, ESNR, ESNR, 4, 6, ESWR, ESNR},       // S0: NOAS
    {1, 1, 1, 2, 3, 3, 3, 3},                      // S1: NOAS
    {FS, FS, FS, FS, FS, FS, FS, FS},              // S2: ASNR (MVID)
    {FS, FS, FS, FS, FS, FS, FS, FS},              // S3: ASWR (KEY)
    {4, 4, 4, 4, 5, 4, ESWR, 4},                   // S4: NOAS
    {FS, FS, FS, FS, FS, FS, FS, FS},              // S5: ASNR (SL)
    {7, 7, 7, 7, 7, 8, ESWR, 7},                   // S6: NOAS
    {ESNR, ESNR, ESNR, ESNR, ESNR, 8, ESWR, ESNR}, // S7: NOAS
    {FS, FS, FS, FS, FS, FS, FS, FS},              // S8: ASNR (CH)
    {FS, FS, FS, FS, FS, FS, FS, FS},              // S9: ASNR (ES)
    {FS, FS, FS, FS, FS, FS, FS, FS}               // S10: ASWR (ER)
};

/* Define accepting states types */
#define NOFS 0 /* not accepting state */
#define FSNR 1 /* accepting state with no retract */
#define FSWR 2 /* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static nag_intg stateType[] = {
    NOFS, /* 00 */
    NOFS, /* 01 */
    FSNR, /* 02 (MID) - Methods */
    FSWR, /* 03 (KEY) */
    NOFS, /* 04 */
    FSNR, /* 05 (SL) */
    NOFS, /* 06 */
    NOFS, /* 07 */
    FSNR, /* 08 (CH)*/
    FSNR, /* 09 (Err1 - no retract) */
    FSWR  /* 010 (Err2 - retract) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
nag_intg startScanner(ReaderPointer psc_buf);
static nag_intg nextClass(nag_char c);         /* character class function */
static nag_intg nextState(nag_intg, nag_char); /* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token (*PTR_ACCFUN)(nag_char *lexeme);

/* Declare accepting states functions */
Token funcSL(nag_char lexeme[]);
Token funcCH(nag_char lexeme[]);
Token funcID(nag_char lexeme[]);
Token funcKEY(nag_char lexeme[]);
Token funcErr(nag_char lexeme[]);

/*
 * Accepting function (action) callback table (array) definition
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
    NULL,    /* -    [00] */
    NULL,    /* -    [01] */
    funcID,  /* MNID	[02] */
    funcKEY, /* KEY  [03] */
    NULL,    /* -    [04] */
    funcSL,  /* SL   [05] */
    NULL,    /* -    [06] */
    NULL,    /* -    [07] */
    funcCH,  /* CH   [08] */
    funcErr, /* ERR1 [09] */
    funcErr  /* ERR2 [010] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 9

/* TO_DO: Define the list of keywords */
static nag_char *keywordTable[KWT_SIZE] = {
    "main", "int", "string", "char", "float", "if", "else if", "else", "loop"};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t' /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
  nag_char indentationCharType;
  nag_intg indentationCurrentPos;
  /* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and
   * FREE) */
} LanguageAttributes;

#endif
