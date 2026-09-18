/**
 * @file fileWork.h
 * @brief functions to read/write to file.
 */
#ifndef FILEWORK_H
#define FILEWORK_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "basic.h"

/** 
 * minimum size of array for dynamic mamory.
 */

 const int MINNUM = 10;
/**
 * maximum size of buffer to store lines.
 */
const int MAXBUFF = 100;

/**
 * @brief struct to work with file data. Stores:
 * 
 * dataPtr pointer to dynamic array with lines NEEDS FREE.
 * 
 * indexDyn  pointer to dynamic array of strings of String NEEDS FREE (free from firstLine);
 * 
 * firstLine pointer to beginning of index. used for FREE
 * 
 * indLen amount of lines.
 */
struct FileData {
    char   *dataPtr;
    String *firstLine;
    String *indexDyn;
    size_t    indLen; 
};

/**
 * @brief old variant of file coping as lines. uses coping by lines and callocs each line
 * 
 * @param [in] FileName name of file to read from.
 * 
 * @param [out] dataSize pointer to varible to set amount of lines.
 * 
 * @return pointer to first line pointer.
 */
char **GetFileInLines(const char *FileName, size_t *dataSize);

/**
 * @brief funcion to read file as bull and then parse it into lines.
 * 
 * takes file at one read, changes all "\n" to "\0". sets up pointer to each string begining, string size, amount of strings in terms of FileData.
 * 
 * @param [in] FileName name of file to read from.
 * @return struct FileData.
 */
FileData GetFileFull(const char *FileName);
#endif