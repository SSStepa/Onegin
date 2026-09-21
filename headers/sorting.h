/**
 * @file soring.h
 * @brief sorting functions and comporators
 */
#ifndef SORTING_H
#define SORTING_H

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basic.h"
#include "fileWork.h"

/**
 * @brief my qsort realization
 * 
 * @param [out] arr data to sort
 * @param [in] arrLen amount of elements in arr
 * @param [in] elSize sizeof one element
 * @param [in] comp function to cumpare elements
 * 
 * @return result of work in terms of WORK_RES.
 */
WORK_RES my_qsort(void *arr, size_t arrLen, size_t elSize, int (* comp)(const void *, const void *));

/**
 * @brief swaps ellements in data
 * 
 * @param [out] firstPtr pointer to first element to change
 * @param [out] secondPtr pointer to second element to change
 * @param [in] size size of one element to swap
 * 
 * @return result of work in terms of WORK_RES.
 */
WORK_RES SwapElls(unsigned char *firstPtr, unsigned char *secondPtr, size_t size);

/**
 * @brief Partition for my qsort. Divides array to two: less or more than base element
 * 
 * @param [inout] LeftInd beginning of the array
 * @param [inout] RightInd end of the array
 * @param [in] elSize size one of element
 * @param [in] comp funciton to compare elements.
 * 
 * @return pointer to dividing element
 */
unsigned char *Partition(unsigned char *LeftInd,unsigned char *RightInd, size_t elSize, int (*comp)(const void *, const void *));                                                                                                                                                                                               

/**
 * @brief func to compare two strings ignoring letter from left to right
 * 
 * @param [in] firstLinePtr pointer to first string in terms of poiner to String
 * @param [in] secondLinePtr pointer to second string in terms of pointer to String
 * 
 * @return result of comporation as int
 */
int CompStrNormal(const void *firstLinePtr, const void *secondLinePtr);

/**
 * @brief func to compare two strings ignoring letter from right to left
 * 
 * @param [in] firstLinePtr pointer to first string in terms of poiner to String
 * @param [in] secondLinePtr pointer to second string in terms of pointer to String
 * 
 * @return result of comporation as int
 */
int CompStrReversed(const void *firstLinePtr, const void *secondLinePtr);

 /**
  * @brief changes two parts of mamory one with another
  * 
  *  Change happends as lements of type with using of buff( accepts that type(buff) == type)
  * first place to change has poiner firstPl and secondPl
  * 
  * increases firstPl and secondPl by sizeof(buff)
  * 
  * @param buff buffer to temporary storage of data
  * @param type type of buff
  * @param firstPl pointer to first place for change
  * @param secondPl pointer to second place for change
  */
#define MACRO_CHANGE_MAMORY(buff, type, firstPl, secondPl) \
    buff = *((type *) (firstPl)); \
    *((type *) (firstPl)) = *((type *) (secondPl)); \
    *((type *) (secondPl)) = buff; \
    firstPl += sizeof(buff); \
    secondPl += sizeof(buff);

#endif
