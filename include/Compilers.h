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
* File name: compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12, A22, A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 1

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/* Logical constants - adapt for your language */
#define TRUE 1
#define FALSE 0

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
                but they can be necessary for conversions.
------------------------------------------------------------
*/
/* TODO: Define your typedefs */

typedef char *string;
typedef unsigned char bool;
typedef unsigned char byte;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS { PGM_READER = 'R', PGM_SCANNER = 'S', PGM_PARSER = 'P' };

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
int mainReader(int argc, string *argv);
int mainScanner(int argc, string *argv);
int mainParser(int argc, string *argv);
void printLogo();

#endif
