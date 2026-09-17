#ifndef FILEWORK_H
#define FILEWORK_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "basic.h"

const int MINNUM = 10;
const int MAXBUFF = 100;

char **GetFileInLines(const char *FileName, size_t *dataSize);

#endif