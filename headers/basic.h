/**
 * @file basic.h
 * @brief structs, consts and funcs i use daily.
 */
#ifndef BASIC_H
#define BASIC_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

/**
 * @brief Work of function avalible results.
 */
enum WORK_RES {
    OK = 0, // all good
    WRIN = 1, // function got bad args
    NOMEM = 2, // not enought memory
    FILEERR = 4 // no file to open.
};

/**
 * @brief struct to store info about string: length and pointer to first element
 * str - pointer to the first element of the string
 * len - length of the string (with no \0)
 */
struct String {
    char *str;
    size_t len;
};


//------------------------------------------------------------- COLORS ------------------------------------------------------------------------
/**
 * Basic colors
 */
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define COLOR_RESET "\e[0m"

//----------------------------------------------------- PRINTING VARS AND ERRORS ------------------------------------------------------------------------


#define TO_STR(str) #str

const char * const LOG_FILE = "log.txt";

static void InfoPrintfInt      (int var, const char *varName, const char *file, int line);
static void InfoPrintfStr      (const char *var, const char *varName, const char *file, int line);
static void InfoPrintfC        (char var, const char *varName, const char *file, int line);
static void InfoPrintfDouble   (double var, const char *varName, const char *file, int line);
static void InfoPrintfLlu      (size_t var, const char *varName, const char *file, int line);
static WORK_RES SetUpLog();

static WORK_RES ErrorPrintf(const char *errMess, int line, const char *file, WORK_RES ErrCode);

#define $int(Varible) InfoPrintfInt(Varible, TO_STR(Varible), __FILE__, __LINE__)
#define $str(Varible) InfoPrintfStr(Varible, TO_STR(Varible), __FILE__, __LINE__)
#define $c(Varible) InfoPrintfC(Varible, TO_STR(Varible), __FILE__, __LINE__)
#define $dbl(Varible) InfoPrintfDouble(Varible, TO_STR(Varible), __FILE__, __LINE__)
#define $llu(Varible) InfoPrintfLlu(Varible, TO_STR(Varible), __FILE__, __LINE__)
#define $err(ErrorMessage, ErrCode) ErrorPrintf(ErrorMessage, __LINE__, __FILE__, ErrCode)

static void InfoPrintfInt(int var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%d%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

static void InfoPrintfStr(const char *var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%s%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

static void InfoPrintfC(char var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%c%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

static void InfoPrintfLlu(size_t var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%llu%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}


static void InfoPrintfDouble(double var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%lg%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

static WORK_RES ErrorPrintf(const char *errMess, int line, const char *file, WORK_RES ErrCode)
{
    FILE *fileLog = fopen(LOG_FILE, "a"); 
    fprintf(stderr, CYN "%s, %d:%s %s:%d %s%s\n" COLOR_RESET, file, line, COLOR_RESET, TO_STR(ErrCode), ErrCode, RED, errMess);
    fprintf(fileLog, "%s, %d: %s:%d %s\n", file, line, TO_STR(ErrCode), ErrCode, errMess);

    fclose(fileLog);
    return ErrCode;
}

static WORK_RES SetUpLog()
{
    FILE *fileLog = fopen(LOG_FILE, "w");
    if (fileLog == NULL) return $err("PROBLEM WITH LOG FILE", FILEERR);
    fclose(fileLog);
    return OK;
}

#endif
