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

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'F', /* Fixed mode (constant size) */
	MODE_ADDIT = 'A', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'M'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */

#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */

/*BIT 7: FUL: full*/
#define SET_FUL_BIT 0x80		  /* (1000.0000)_2 = (128)_10 = (0X80)_16*/
#define RST_FUL_BIT 0x7F       /* (0111.1111)_2 = (127)_10 = (0X7F)_16*/
#define CHK_FUL_BIT SET_FUL_BIT

/* TO_DO: BIT 6: EMP: Empty */
#define SET_EMP_BIT 0x40		/* (0100.0000)_2 = (64)_10 = (0X40)_16*/
#define RST_EMP_BIT 0xBF	/* (1011.1111)_2 = (191)_10 = (0XBF)_16*/
#define CHK_EMP_BIT SET_EMP_BIT

/* TO_DO: BIT 5: REL = Relocation */
#define SET_REL_BIT 0x20	/* (0010.0000)_2 = (32)_10 = (0X20)_16*/
#define RST_REL_BIT 0xDF	/* (1101.1111)_2 = (191)_10 = (0XBF)_16*/
#define CHK_REL_BIT 0x20

/* TO_DO: BIT 4: END = EndOfBuffer */
#define SET_END_BIT 0x10	/* (0001.0000)_2 = (16)_10 = (0X10)_16*/
#define RST_END_BIT 0xEF			/* (1110.1111)_2 = (191)_10 = (0XEF)_16*/
#define CHK_END_BIT 0x10

#define NCHAR				128			/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	ray_intg mark;			/* the offset to the mark position (in chars) */
	ray_intg read;			/* the offset to the get a char position (in chars) */
	ray_intg wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	ray_char*	content;			/* pointer to the beginning of character array (character buffer) */
	ray_intg		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	ray_intg		increment;			/* character array increment factor */
	ray_intg		mode;				/* operational mode indicator */
	ray_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;			/* Offset / position field */
	ray_intg		histogram[NCHAR];	/* Statistics of chars */
	ray_intg		numReaderErrors;	/* Number of errors from Reader */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(ray_intg, ray_intg, ray_intg);
ReaderPointer	readerAddChar		(ReaderPointer const, ray_char);
ray_boln		readerClear		    (ReaderPointer const);
ray_boln		readerFree		    (ReaderPointer const);
ray_boln		readerIsFull		(ReaderPointer const);
ray_boln		readerIsEmpty		(ReaderPointer const);
ray_boln		readerSetMark		(ReaderPointer const, ray_intg);
ray_intg		readerPrint		    (ReaderPointer const);
ray_intg		readerLoad			(ReaderPointer const, FILE* const);
ray_boln		readerRecover		(ReaderPointer const);
ray_boln		readerRetract		(ReaderPointer const);
ray_boln		readerRestore		(ReaderPointer const);
/* Getters */
ray_char		readerGetChar		(ReaderPointer const);
ray_char*	readerGetContent	(ReaderPointer const, ray_intg);
ray_intg		readerGetPosRead	(ReaderPointer const);
ray_intg		readerGetPosWrte	(ReaderPointer const);
ray_intg		readerGetPosMark	(ReaderPointer const);
ray_intg		readerGetSize		(ReaderPointer const);
ray_intg		readerGetInc		(ReaderPointer const);
ray_intg		readerGetMode		(ReaderPointer const);
ray_byte		readerGetFlags		(ReaderPointer const);
ray_intg		readerShowStat		(ReaderPointer const);
ray_intg		readerNumErrors		(ReaderPointer const);

#endif
