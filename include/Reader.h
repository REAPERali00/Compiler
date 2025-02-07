/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
 _________________________________
|                                 |
| ........ nag LANGUAGE ......... |
|     __    __    __    __        |
|    /  \  /  \  /  \  /  \       |
| __/  __\/  __\/  __\/  __\__    |
| _/  /__/  /__/  /__/  /_____|   |
|  \_/ \   / \   / \   / \  \___  |
|       \_/   \_/   \_/   \___o_> |
|                                 |
| .. ALGONQUIN COLLEGE - 2022F .. |
|_________________________________|

*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary
 * .......................................*/
/*#pragma warning(1:4001) */    /*to enforce C89 type comments  - to make
                                   //comments an warning */
/*#pragma warning(error:4001)*/ /* to enforce C89 comments - to make // comments
                                   an error */

/* standard header files */
#include <limits.h> /* implementation-defined data type ranges and limits */
#include <malloc.h> /* for dynamic memory allocation*/
#include <stdio.h>  /* standard input/output */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT)
 * .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
  MODE_FIXED = 'f', /* Fixed mode (constant size) */
  MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
  MODE_MULTI =
      'm' /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)      /* General error message */
#define READER_TERMINATOR '\0' /* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA)
 * .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE INT_MAX - 1 /* maximum capacity */

#define READER_DEFAULT_SIZE 250     /* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT 10 /* default increment factor */

/* Add your bit-masks constant definitions here - Defined for nag */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 /* (0000.0000)_2 = (000)_10 */

#define READER_FUL_FLAG 0x08
#define READER_EMP_FLAG 0x04
#define READER_REL_FLAG 0x02
#define READER_END_FLAG 0x01

#define NCHAR 128 /* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA)
 * .................................. */

/* Offset declaration */
typedef struct position {
  nag_i mark; /* the offset to the mark position (in chars) */
  nag_i read; /* the offset to the get a char position (in chars) */
  nag_i wrte; /* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
  nag_ch *content; /* pointer to the beginning of character array (character
                      buffer) */
  nag_i size; /* current dynamic memory size (in bytes) allocated to character
                 buffer */
  nag_i increment; /* character array increment factor */
  nag_i mode;      /* operational mode indicator */
  nag_bt flags; /* contains character array floatlocation flag and end-of-buffer
                   flag */
  Position position;      /* Offset / position field */
  nag_i histogram[NCHAR]; /* Statistics of chars */
} BufferReader, *ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer readerCreate(nag_i, nag_i, nag_i);
ReaderPointer readerAddChar(ReaderPointer const, nag_ch);
nag_bl readerClear(ReaderPointer const);
nag_bl readerFree(ReaderPointer const);
nag_bl readerIsFull(ReaderPointer const);
nag_bl readerIsEmpty(ReaderPointer const);
nag_bl readerSetMark(ReaderPointer const, nag_i);
nag_i readerPrint(ReaderPointer const);
nag_i readerLoad(ReaderPointer const, FILE *const);
nag_bl readerRecover(ReaderPointer const);
nag_bl readerRetract(ReaderPointer const);
nag_bl readerRestore(ReaderPointer const);
/* Getters */
nag_ch readerGetChar(ReaderPointer const);
nag_ch *readerGetContent(ReaderPointer const, nag_i);
nag_i readerGetPosRead(ReaderPointer const);
nag_i readerGetPosWrte(ReaderPointer const);
nag_i readerGetPosMark(ReaderPointer const);
nag_i readerGetSize(ReaderPointer const);
nag_i readerGetInc(ReaderPointer const);
nag_i readerGetMode(ReaderPointer const);
nag_bt readerGetFlags(ReaderPointer const);
nag_i readerShowStat(ReaderPointer const);

#endif
