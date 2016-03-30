//
// Created by Demon on 31/03/16.
//

#ifndef EMAILPARSER_SOURCE_FILE_H
#define EMAILPARSER_SOURCE_FILE_H

#define LOCAL_EXIST     0                                       // checks if local exists in email
#define DOMAIN_EXIST    1                                       // checks if domain exists in email
#define LOCAL_CHECK     2                                       // checks if local cardinality is valid
#define DOMAIN_CHECK    3                                       // checks if domain cardinality is valid
#define WORD_SANITY     4                                       // check for sanity of all Words
#define INSANE          31                                      // if (INSANE & FLAG) then something is wrong

#define MAX_SIZE        128
#define true    1
#define false   0


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctype.h"

typedef int bool;

void mark(unsigned char* FLAG, unsigned char position);

/*
 * copies from [str,end)
 * Memory Allocated     : str
 * Memory Deallocated   : none
 */
char* copyString(const char* str,const char* end);

/*
 * CheckWord()
 * - checks the sanity of word.
 */
bool checkWord(const char* w, unsigned char* FLAG);

/*
 * returns number of words in the sequence
 * seperated by '.'
 * - returns -1 IF any word is insane
 *   or any size of any word <= 0
 */
int checkWordSequence(const char* s, unsigned char* FLAG);

/*
 * pareser()
 */
unsigned char parser(const char* email);

/*
 * shows error marked in flag
 */
void showErrors(unsigned char FLAG);

#endif //EMAILPARSER_SOURCE_FILE_H
