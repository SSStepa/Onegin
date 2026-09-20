#ifndef FLAGS_H
#define FLAGS_H

#include <stdio.h>
#include <getopt.h>

#include "basic.h"

const char *const OPTS = "i:o:";

/**
 * @breif parses flags from command line
 * @param [in] argc amount of args
 * @param [in] argv list of args
 * @param FileToReadFrom file to read from name
 * @param FileToWriteTo file to write in name
 * 
 * @return result of work in terms of WORK_RES
 */
WORK_RES FlagsParse(int argc, char *argv[], const char **FileToReadFrom, const char **FileToWriteTo);

/**
 * @brief shows help about flags
 */
void ShowHelp();

#endif
