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
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */ /*to enforce C89 type comments  - to make
                                //comments an warning */

/*#pragma warning(error:4001)*/ /* to enforce C89 comments - to make //
comments
                                   an error */

/* Constants */
#define VID_LEN 20 /* variable identifier length */
#define ERR_LEN 40 /* error message length */
#define NUM_LEN 5  /* maximum number of digits for IL */

#define RTE_CODE 1 /* Value for run-time error */

/* TODO: Define the number of tokens */
#define NUM_TOKENS 13

/* TODO: Define Token codes - Create your token classes */
enum TOKENS {
  ERR_T,   /*  0: Error token */
  MNID_T,  /*  1: Method name identifier token (start: &) */
  INL_T,   /*  1: Integer literal token */
  FLTL_T,  /*  1: Float literal token */
  CHRL_T,  /*  1: Character literal token */
  BOOLL_T, /*  1: Character literal token */
  STRL_T,  /*  1: String literal token */
  LPR_T,   /*  1: Left parenthesis token */
  RPR_T,   /*  1: Right parenthesis token */
  LBR_T,   /*  1: Left brace token */
  RBR_T,   /*  1: Right brace token */
  KW_T,    /*  1: Keyword token */
  EOS_T,   /*  1: End of statement (semicolon) */
  RTE_T,   /*  1: Run-time error token */
  SEOF_T,  /*  1: Source end-of-file token */
  CMT_T    /*  1: Comment token */
};

/* TODO: Define the list of keywords */
static string tokenStrTable[NUM_TOKENS] = {
    "ERR_T", "MNID_T", "INL_T", "STR_T", "LPR_T",  "RPR_T", "LBR_T",
    "RBR_T", "KW_T",   "EOS_T", "RTE_T", "SEOF_T", "CMT_T"};

/* TODO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TODO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
  int codeType;                   /* integer attributes accessor */
  AriOperator arithmeticOperator; /* arithmetic operator attribute code */
  RelOperator relationalOperator; /* relational operator attribute code */
  LogOperator logicalOperator;    /* logical operator attribute code */
  EofOperator seofType;           /* source-end-of-file attribute code */
  int intValue;                   /* integer literal attribute (value) */
  int keywordIndex;               /* keyword index in the keyword table */
  int contentString;          /* string literal offset from the beginning of the
           string
                                   literal buffer (stringLiteralTable->content) */
  float floatValue;           /* floating-point literal attribute (value) */
  char idLexeme[VID_LEN + 1]; /* variable identifier token attribute */
  char errLexeme[ERR_LEN + 1]; /* error token attribite */
} TokenAttribute;

/* TODO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
  byte flags; /* Flags information */
  union {
    int intValue;         /* Integer value */
    float floatValue;     /* Float value */
    string stringContent; /* String value */
    char charContent;
    bool boolValue;
    byte byteValue;
  } values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
  int code;                 /* token code */
  TokenAttribute attribute; /* token attribute */
  IdAttibutes idAttribute;  /* not used in this scanner implementation - for
                               further use */
} Token;

/* Scanner */
typedef struct scannerData {
  int scanHistogram[NUM_TOKENS]; /* Statistics of chars */
} ScannerData, *pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven
part
 * of the scanner: LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special
 chars
 * used for tokenis include _, & and ' */

/* TODO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL0 '#'
#define CHRCOL1 '{'
#define CHRCOL2 '}'
#define CHRCOL3 '$'
#define CHRCOL4 '%'
#define CHRCOL5 ';'
#define CHRCOL6 '+'
#define CHRCOL7 '-'
#define CHRCOL8 '*'
#define CHRCOL9 '('
#define CHRCOL10 ')'
#define CHRCOL11 '!'
#define CHRCOL12 '\"'
#define CHRCOL13 '&'
#define CHRCOL14 '<'
#define CHRCOL15 '>'
#define CHRCOL16 '^'

// Multi-character symbols like '==', '<>', and '=' cannot be directly
// defined
// as a macro value in this context.

/* These constants will be used on VID / MID function */
#define MNID_SUF '&'
#define COMM_SYM '#'

/* TODO: Error states and illegal state */
#define ESNR 100 /* Error state with no retract */
#define ESWR 100 /* Error state with retract */
#define FS 100   /* Illegal state */
#define ES 100   /* Error state */

/* Expanded State transition table definition */
#define NUM_STATES 16   // Updated number of states
#define CHAR_CLASSES 10 // Updated number of character classes

/* Expanded Transition table - type of states defined in a separate table */
static int transitionTable[NUM_STATES][CHAR_CLASSES] = {
    /*     L(0),  D(1),  U(2), B1(3),  Q(4), QQ(5),  S(6),  P(7), V_id(8),
    O(9)
     */
    /* S0 */ {1, 11, ES, ES, 8, 4, 6, ES, ES, ES},
    /* S1 */ {1, 1, 1, 2, 3, 3, 3, 3, 5, 3},
    /* S2 */ {FS, FS, FS, FS, FS, FS, FS, FS, FS, FS},
    /* S3 */ {FS, FS, FS, FS, FS, FS, FS, FS, FS, FS},
    /* S4 */ {4, 4, 4, 4, 4, 15, 4, 4, 4, 4},
    /* S5 */ {FS, FS, FS, FS, FS, FS, FS, FS, FS, FS},
    /* S6 */ {6, 6, 6, 6, 6, 6, 7, 6, 6, 6},
    /* S7 */ {FS, FS, FS, FS, FS, FS, FS, FS, FS, FS},
    /* S8 */ {9, 9, 9, 9, ES, 9, 9, 9, 9, 9},
    /* S9 */ {ES, ES, ES, ES, 10, ES, ES, ES, ES, ES},
    /* S10 */ {FS, FS, FS, FS, FS, FS, FS, FS, FS, FS},
    /* S11 */ {ES, 11, ES, 12, ES, ES, 12, 13, ES, 12},
    /* S12 */ {FS, FS, FS, FS, FS, FS, FS, FS, FS, FS},
    /* S13 */ {ES, 13, ES, 14, ES, ES, 14, ES, ES, 14},
    /* S14 */ {FS, FS, FS, FS, FS, FS, FS, FS, FS, FS},
    /* S15 */ {FS, FS, FS, FS, FS, FS, FS, FS, FS, FS}};

/* Define accepting states types */
#define NOFS 0 /* not accepting state */
#define FSNR 1 /* accepting state with no retract */
#define FSWR 2 /* accepting state with retract */

/* TODO: Define list of acceptable states */
static int stateType[NUM_STATES] = {
    NOFS, /* 00 */
    NOFS, /* 01 */
    FSNR, /* 02 (MID) - Methods */
    FSWR, /* 03 (KEY) */
    NOFS, /* 04 */
    FSNR, /* 05 (SL) */
    NOFS, /* 06 */
    FSNR, /* 07 (COM) */
    FSNR, /* 08 (Err1 - no retract) */
    FSWR  /* 09 (Err2 - retract) */
};

/*
-------------------------------------------------
TODO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
int startScanner(ReaderPointer psc_buf);
static int nextClass(char c);    /* character class function */
static int nextState(int, char); /* state machine function */
void printScannerData(ScannerData scData);
Token tokenizer(void);

/*se
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TODO: Pointer to function (of one string  argument) returning Token */
typedef Token (*PTR_ACCFUN)(string lexeme);

/* Declare accepting states functions */
Token funcSL(string lexeme);
Token funcIL(string lexeme);
Token funcID(string lexeme);
Token funcCMT(string lexeme);
Token funcKEY(string lexeme);
Token funcErr(string lexeme);

/*
 * Accepting function (action) callback table (array) definition
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TODO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
    NULL,    /* -    [00] */
    NULL,    /* -    [01] */
    funcID,  /* MNID	[02] */
    funcKEY, /* KEY  [03] */
    NULL,    /* -    [04] */
    funcSL,  /* SL   [05] */
    NULL,    /* -    [06] */
    funcCMT, /* COM  [07] */
    funcErr, /* ERR1 [06] */
    funcErr  /* ERR2 [07] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TODO: Define the number of Keywords from the language */
#define KWT_SIZE 16

/* TODO: Define the list of keywords */
static string keywordTable[KWT_SIZE] = {
    "main", /* KW00 */
    "if",     "else", "elif",  "for",    "while", "continue", "break", "def",
    "return", "int",  "float", "string", "char",  "bool",     "class"};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t' /* Tabulation */

/* TODO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
  char indentationCharType;
  int indentationCurrentPos;
  /* TODO: Include any extra attribute to be used in your scanner (OPTIONAL
  and
   * FREE) */
} LanguageAttributes;

/* Number of errors */
int numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
