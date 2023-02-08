/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@                                                               @@@@
@@          /       ==============================        /          @@
@         ////           @@       @@ #@                  ////         @
@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @
@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @
@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @
@     (((((/)))((    ------------------------------    ((((./////*    @
@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @
@    ///// / /////   ==============================  * ////* / ////   @
@     ///// ///// ((                               (( ///// /////     @
@    ((((   / , (((((                             (((((  //   /(((    @
@    (((((((/ . (((((                          (((((* / (((((((       @
@      (((((( //((((/((((                    *((((/((((/( (((((/      @
@       .//,   * /   (((((                   (((((  ///    .//.       @
@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @
@         //////// ,// ((( /////,     ////// ((( //  /////// *        @
@            (((((((((,// * /////     /////   (//(((((((((            @
@            ((((((((((((/////         //.///  (((((((((((.           @
@                   (///////// //(   (//.//////////                   @
@                  (/////////             //////////                  @
@                                                                     @
@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@
@@@@                                                               @@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Jan 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Reader (.c)
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
#include "Reader.h"
#endif


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

ReaderPointer readerCreate(ray_intg size, ray_intg increment, ray_intg mode) {
	ReaderPointer readerPointer;
	/* TO_DO: Defensive programming */

	/* TO_DO: Adjust the values according to parameters */
	if (!size)
		size = READER_DEFAULT_SIZE;
	    increment = READER_DEFAULT_INCREMENT;
	if (!increment) {
		mode = MODE_FIXED;
	}

	if (mode != MODE_FIXED && mode != MODE_ADDIT && mode != MODE_MULTI) {
		return NULL;
	}

	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return NULL;
	}
	else {
		readerPointer->content = (ray_char*)malloc(size);
		//if (!readerPointer->content) {
		//	free(readerPointer);
		//	return NULL;
		//}
		/* TO_DO: Defensive programming */
		/* TO_DO: Initialize the histogram */
		for(int i = 0; i < NCHAR; i++)
		readerPointer->histogram[i] = 0;

		readerPointer->size = size;
		readerPointer->increment = increment;
		readerPointer->mode = mode;
		/* TO_DO: Initialize flags */
		/* TO_DO: The created flag must be signalized as EMP */
		readerPointer->flags = SET_EMP_BIT;




		return readerPointer;
	}
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

ReaderPointer readerAddChar(ReaderPointer const readerPointer, ray_char ch) {
	ray_char* tempReader = NULL;
	ray_intg newSize = 0;
	int asciiCode = -1;
	/* TO_DO: Defensive programming: check buffer and valid char (increment numReaderErrors) */
	if (!readerPointer || !ch)
		return READER_ERROR;
	/* TO_DO: Reset Realocation */
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (ray_intg)sizeof(ray_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
		//Not sure if anything has to be added here......
	}
	else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags = RST_FUL_BIT;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			/* TO_DO: Defensive programming */
			newSize = readerPointer->size + readerPointer->increment;
			readerPointer->size = newSize;
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			readerPointer->size = newSize;
			/* TO_DO: Defensive programming */
		

			break;
		default:
			return NULL;
		}

		if (newSize < 0 || newSize > READER_MAX_SIZE) {
			readerPointer->flags = SET_FUL_BIT;
			return NULL;
		}
		/* TO_DO: New reader allocation */
		/* TO_DO: Defensive programming */
		/* TO_DO: Check Relocation */

		tempReader = readerPointer->content;
		tempReader = (ray_char*)realloc(tempReader, newSize);
		if (tempReader != readerPointer->content) {
			readerPointer->content = tempReader;
			readerPointer->flags = SET_REL_BIT;
		}
		else {
			readerPointer->flags = CHK_FUL_BIT;
		}
		if (!readerPointer->content)
			return NULL;
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TO_DO: Updates histogram */
	asciiCode = (int)ch;
	if (asciiCode < 0 || asciiCode > NCHAR) {
		readerPointer->numReaderErrors++;
	}
	else {
		readerPointer->histogram[asciiCode]++;
	}
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
ray_boln readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust flags original */
	if (!readerPointer) {
		
		return READER_ERROR; 
	}
	else {
		readerPointer->flags = READER_DEFAULT_FLAG;
		readerPointer->position.mark = 0;
		readerPointer->position.read = 0;
		readerPointer->position.wrte = 0;
		
	}
		return RAY_TRUE;
	
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
ray_boln readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Free pointers */
	if (!readerPointer){

		return READER_ERROR;
	}
	else {
		free(readerPointer); 
	
	}
	
	return RAY_TRUE;
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
ray_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is FUL */
	if (!readerPointer) {

		return READER_ERROR;
	}

	if(readerPointer->flags == CHK_FUL_BIT)
		return RAY_TRUE;

	return RAY_FALSE;
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
ray_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is EMP */
	if (!readerPointer) {

		return READER_ERROR;
	}

	if (readerPointer->flags == CHK_EMP_BIT)
		return RAY_TRUE;

	return RAY_FALSE;
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
ray_boln readerSetMark(ReaderPointer const readerPointer, ray_intg mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || mark<0 || mark > readerPointer->position.wrte)
		return RAY_FALSE;
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return RAY_TRUE;
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
ray_intg readerPrint(ReaderPointer const readerPointer) {
	ray_intg cont = 0;
	ray_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (cont < readerPointer->position.wrte) {
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
ray_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	ray_intg size = 0;
	ray_char c;
	/* TO_DO: Defensive programming */
	c = (ray_char)fgetc(fileDescriptor);
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
ray_boln readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Recover positions */
	if (!readerPointer) {
		return READER_ERROR; 
	}
	else {
		//Position pos; 
		readerPointer->position.read = 0;
		readerPointer->position.mark = 0;
		
	}
 
	return RAY_TRUE;
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
ray_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Retract (return 1 pos read) */
	if (!readerPointer){
		return READER_ERROR;
	}
	else if (readerPointer->position.read > 0) {
		readerPointer->position.read --;
	}
	return RAY_TRUE;
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
ray_boln readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Restore positions (read/mark) */
	if (!readerPointer) {
		return READER_ERROR;
	}
	else {
		readerPointer->position.read = readerPointer->position.mark;
	}
	return RAY_TRUE;
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
ray_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check condition to read/wrte */
	/* TO_DO: Set EOB flag */
	/* TO_DO: Reset EOB flag */
	if (!readerPointer) {
		return READER_ERROR;
	}else{
		if (readerPointer->position.read == readerPointer->position.wrte) {
			readerPointer->flags &= SET_END_BIT; 
		}
		else {
			readerPointer->flags |= RST_END_BIT; 
		}
	}
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
ray_char* readerGetContent(ReaderPointer const readerPointer, ray_intg pos) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return content (string) */
	if (!readerPointer) 
		return READER_ERROR;
	

	if(pos >= 0 && pos <= readerPointer->position.wrte )

		return &readerPointer->content[pos];

	return NULL;
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
ray_intg readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return read */
	if (!readerPointer)
		return READER_ERROR;
	else

		return readerPointer->position.read; 
		
	return 0; 
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
ray_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return wrte */
	if (!readerPointer)
		return READER_ERROR;
	else
		return readerPointer->position.wrte;

	return 0;
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
ray_intg readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mark */
	if (!readerPointer)
		return READER_ERROR;
	else
		return readerPointer->position.mark;

	return 0;
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
ray_intg readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return size */
	if (!readerPointer)
		return READER_ERROR;
	else
		return readerPointer->size;

	return 0;
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
ray_intg readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return increment */
	if (!readerPointer)
		return READER_ERROR;
	else
		return readerPointer->increment;
	return 0;
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
ray_intg readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mode */
	if (!readerPointer)
		return READER_ERROR;
	else
		return readerPointer->mode;
	return 0;
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
ray_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return flags */
	if (!readerPointer)
		return READER_ERROR;
	else
		return readerPointer->flags;
	return 0;
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
*	- Adjust for your LANGUAGE.
*************************************************************
*/
ray_intg readerShowStat(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Updates the histogram */
	int numChar = 0;
	if (!readerPointer)
		return READER_ERROR;
	else {
		for (int i = 0; i < NCHAR; i++) {

			if (readerPointer->histogram[i] > 0)
				numChar++;

		}
		return numChar;
	}
	return 0;
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
ray_intg readerNumErrors(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Updates the histogram */
	if (!readerPointer)
		return READER_ERROR;
	else
		return readerPointer->numReaderErrors; 
	
	return 0;
}
