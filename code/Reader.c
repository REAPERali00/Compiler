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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif
#include <string.h>

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
        factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

ReaderPointer readerCreate(nag_i size, nag_i increment, nag_i mode) {
  ReaderPointer readerPointer;

  // possible error: if only one is null, all will reset to default. if not the
  // goal, change later
  if (size == NULL || increment == NULL || mode == NULL) {
    size = READER_DEFAULT_SIZE;
    increment = READER_DEFAULT_INCREMENT;
    mode = MODE_FIXED;
  }

  readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
  if (!readerPointer)
    return NULL;

  readerPointer->content = (nag_ch *)malloc(size);
  if (!readerPointer->content)
    return NULL;

  readerPointer->size = size;
  readerPointer->increment = increment;
  readerPointer->mode = mode;
  readerPointer->flags = READER_EMP_FLAG;

  return readerPointer;
}

/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, nag_ch ch) {
  nag_ch *tempReader = NULL;
  nag_i newSize = 0;

  if (!readerPointer || ch > NCHAR)
    return NULL;

  /* TO_DO: Reset realocation */

  if (readerPointer->position.wrte * (nag_i)sizeof(nag_ch) >=
      readerPointer->size) {

    readerPointer->flags = readerPointer->flags | READER_FUL_FLAG;

    switch (readerPointer->mode) {
    case MODE_FIXED:
      return NULL;
    case MODE_ADDIT:
      newSize = readerPointer->size + readerPointer->increment;
      break;
    case MODE_MULTI:
      newSize = readerPointer->size * readerPointer->increment;
      break;
    default:
      return NULL;
    }

    if (newSize < 0 || newSize > READER_MAX_SIZE)
      return NULL;

    tempReader = (char *)realloc(tempReader, newSize);
    if (!tempReader)
      return NULL;
    strcpy(tempReader, readerPointer->content);
    readerPointer->content = tempReader;

    readerPointer->flags = readerPointer->flags & ~READER_FUL_FLAG;
    readerPointer->flags = readerPointer->flags | READER_REL_FLAG;
  }

  /* TO_DO: Add the char */
  readerPointer->content[readerPointer->position.wrte++] = ch;
  /* TO_DO: Updates histogram */
  readerPointer->histogram[ch % NCHAR]++;

  readerPointer->flags = readerPointer->flags & ~READER_EMP_FLAG;

  return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_bl readerClear(ReaderPointer const readerPointer) {
  /* TO_DO: Defensive programming */
  /* TO_DO: Adjust flags original */
  if (!readerPointer)
    return nag_FALSE;

  // reset position conditions?
  readerPointer->position.mark = 0;
  readerPointer->position.read = 0;
  readerPointer->position.wrte = 0;

  readerPointer->flags = READER_EMP_FLAG;

  for (int i = 0; i < NCHAR; i++)
    readerPointer->histogram[i] = 0;

  return nag_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_bl readerFree(ReaderPointer const readerPointer) {
  if (!readerPointer)
    return nag_FALSE;
  /* TO_DO: Free pointers */
  free(readerPointer->content);
  free(readerPointer);

  return nag_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_bl readerIsFull(ReaderPointer const readerPointer) {
  /* TO_DO: Defensive programming */
  /* TO_DO: Check flag if buffer is FUL */
  if (!readerPointer)
    return nag_FALSE;

  if (readerPointer->flags & READER_FUL_FLAG)
    return nag_TRUE;

  return nag_FALSE;
}

/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_bl readerIsEmpty(ReaderPointer const readerPointer) {
  /* TO_DO: Defensive programming */
  /* TO_DO: Check flag if buffer is EMP */
  if (!readerPointer)
    return nag_FALSE;

  if (readerPointer->flags & READER_EMP_FLAG)
    return nag_TRUE;

  return nag_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_bl readerSetMark(ReaderPointer const readerPointer, nag_i mark) {
  /* TO_DO: Defensive programming */
  if (!readerPointer || mark < 0 || mark > readerPointer->position.wrte)
    return nag_FALSE;
  /* TO_DO: Adjust mark */
  readerPointer->position.mark = mark;
  return nag_TRUE;
}

/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_i readerPrint(ReaderPointer const readerPointer) {
  nag_i cont = 0;
  nag_ch c;
  if (!readerPointer)
    return cont;
  /* TO_DO: Defensive programming (including invalid chars) */
  c = readerGetChar(readerPointer);

  /* TO_DO: Check flag if buffer EOB has achieved */
  while (cont < readerPointer->position.wrte &&
         !(readerPointer->flags & READER_END_FLAG)) {
    cont++;
    printf("%c", c);
    c = readerGetChar(readerPointer);
  }
  return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
        an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_i readerLoad(ReaderPointer const readerPointer,
                 FILE *const fileDescriptor) {
  nag_i size = 0;
  nag_ch c;
  /* TO_DO: Defensive programming */
  if (!readerPointer || !fileDescriptor)
    return READER_ERROR;

  c = (nag_ch)fgetc(fileDescriptor);
  while (!feof(fileDescriptor)) {
    if (!readerAddChar(readerPointer, c)) {
      ungetc(c, fileDescriptor);
      return READER_ERROR;
    }
    c = (char)fgetc(fileDescriptor);
    size++;
  }
  /* TO_DO: Defensive programming */
  return size;
}

/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_bl readerRecover(ReaderPointer const readerPointer) {
  /* TO_DO: Defensive programming */
  if (!readerPointer)
    return nag_FALSE;

  /* TO_DO: Recover positions */
  readerPointer->position.mark = 0;
  readerPointer->position.read = 0;

  return nag_TRUE;
}

/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_bl readerRetract(ReaderPointer const readerPointer) {
  /* TO_DO: Defensive programming */
  if (!readerPointer)
    return nag_FALSE;

  /* TO_DO: Retract (return 1 pos read) */
  if (!readerPointer->position.read)
    readerPointer->position.read--;

  return nag_TRUE;
}

/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_bl readerRestore(ReaderPointer const readerPointer) {
  /* TO_DO: Defensive programming */
  if (!readerPointer)
    return nag_FALSE;

  readerPointer->position.read = readerPointer->position.mark;
  return nag_TRUE;
}

/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_ch readerGetChar(ReaderPointer const readerPointer) {
  /* TO_DO: Defensive programming */
  if (!readerPointer)
    return NULL;

  /* TO_DO: Check condition to read/wrte */

  /* TO_DO: Set EOB flag */
  if (readerPointer->position.read == readerPointer->position.wrte)
    readerPointer->flags = readerPointer->flags | READER_END_FLAG;
  /* TO_DO: Reset EOB flag */
  else if (readerPointer->position.read < readerPointer->position.wrte)
    readerPointer->flags = readerPointer->flags & ~READER_END_FLAG;
  else
    return NULL;

  return readerPointer->content[readerPointer->position.read++];
}

/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_ch *readerGetContent(ReaderPointer const readerPointer, nag_i pos) {
  /* TO_DO: Defensive programming */
  if (!readerPointer)
    return NULL;
  if (pos > readerPointer->position.wrte)
    return NULL;
  /* TO_DO: Return content (string) */
  return readerPointer->content + pos;
}

/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_i readerGetPosRead(ReaderPointer const readerPointer) {
  /* TO_DO: Defensive programming */
  if (!readerPointer)
    return NULL;
  /* TO_DO: Return read */
  return readerPointer->position.read;
}

/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_i readerGetPosWrte(ReaderPointer const readerPointer) {
  if (!readerPointer)
    return NULL;
  /* TO_DO: Return read */
  return readerPointer->position.wrte;
}

/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_i readerGetPosMark(ReaderPointer const readerPointer) {
  if (!readerPointer)
    return NULL;
  /* TO_DO: Return read */
  return readerPointer->position.mark;
}

/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_i readerGetSize(ReaderPointer const readerPointer) {
  if (!readerPointer)
    return NULL;
  /* TO_DO: Return read */
  return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_i readerGetInc(ReaderPointer const readerPointer) {
  /* TO_DO: Defensive programming */
  /* TO_DO: Return increment */
  if (!readerPointer)
    return NULL;
  return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_i readerGetMode(ReaderPointer const readerPointer) {
  /* TO_DO: Defensive programming */
  /* TO_DO: Return mode */
  if (!readerPointer)
    return NULL;
  return readerPointer->mode;
}

/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_bt readerGetFlags(ReaderPointer const readerPointer) {
  /* TO_DO: Defensive programming */
  /* TO_DO: Return flags */
  if (!readerPointer)
    return NULL;
  return readerPointer->flags;
}

/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
nag_i readerShowStat(ReaderPointer const readerPointer) {
  /* TO_DO: Defensive programming */
  /* TO_DO: Updates the histogram */
  if (!readerPointer)
    return READER_ERROR;
  int sum = 0;
  for (int i = 0; i < NCHAR; i++)
    sum += readerPointer->histogram[i];

  return sum;
}
