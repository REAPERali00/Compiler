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

  if (size == 0 || increment == 0 || mode == 0) {
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
  nag_ch *tempReader;
  nag_i newSize = 0;

  if (!readerPointer || ch < 0)
    return NULL;

  // Setting the allocatin back to 0, if needs to be reallocated the if
  // statement will set it
  readerPointer->flags = readerPointer->flags & ~READER_REL_FLAG;

  if (readerPointer->position.write * (nag_i)sizeof(nag_ch) >=
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

    tempReader = (char *)malloc(newSize);
    if (!tempReader)
      return NULL;
    strcpy(tempReader, readerPointer->content);
    readerPointer->content = tempReader;

    readerPointer->flags = readerPointer->flags & ~READER_FUL_FLAG;
    readerPointer->flags = readerPointer->flags | READER_REL_FLAG;
  }

  readerPointer->content[readerPointer->position.write++] = ch;
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
  if (!readerPointer)
    return nag_FALSE;

  // reset position conditions?
  readerPointer->position.mark = 0;
  readerPointer->position.read = 0;
  readerPointer->position.write = 0;

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
  if (!readerPointer)
    return nag_TRUE; // at the moment, the behavior is set to be true since,
                     // well, techincally it would be empty if pinter is null?
  return (readerPointer->flags & READER_EMP_FLAG);
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
  if (!readerPointer || mark < 0 || mark > readerPointer->position.write)
    return nag_FALSE;
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
  nag_ch c;
  if (!readerPointer)
    return 0;
  // check if the end of file is reached by checking the end flag
  while (!(readerPointer->flags & READER_END_FLAG)) {
    c = readerGetChar(readerPointer);
    printf("%c", c);
  }
  return readerPointer->position
      .read; // returning the number of characters read, which is the reader as
             // it increments
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
  if (!readerPointer)
    return nag_FALSE;

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
  if (!readerPointer)
    return nag_FALSE;

  if (readerPointer->position.read > 0)
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
    return '\0';

  // check if the end of buffer content has reached
  if (readerPointer->position.read == readerPointer->position.write)
    // setting the end flag
    readerPointer->flags = readerPointer->flags | READER_END_FLAG;
  else if (readerPointer->position.read < readerPointer->position.write)
    // unset the end flag
    readerPointer->flags = readerPointer->flags & ~READER_END_FLAG;
  else
    return '\0';

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
  if (!readerPointer || pos > readerPointer->position.write)
    return NULL;
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
    return 0;
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
    return 0;
  /* TO_DO: Return read */
  return readerPointer->position.write;
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
    return 0;
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
    return READER_ERROR;
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
  if (!readerPointer)
    return READER_ERROR;
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
  if (!readerPointer)
    return READER_ERROR;
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
  if (!readerPointer)
    return '\0';
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
  if (!readerPointer)
    return READER_ERROR;
  int sum = 0;
  for (int i = 0; i < NCHAR; i++)
    sum += readerPointer->histogram[i];
  return sum;
}
