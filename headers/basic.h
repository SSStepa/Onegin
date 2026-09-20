/**
 * @file basic.h
 * @brief structs, consts and funcs i use daily.
 */
#ifndef BASIC_H
#define BASIC_H
/**
 * @brief Work of function avalible results.
 */
enum WORK_RES {
    OK = 0, // all good
    WRIN = 1, // function got bad args
    NOMEM = 2, // not enought memory
    FILEERR = 3 // no file to open.
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

#define toStr(str) #str

static void InfoPrintfInt      (int var, const char *varName, const char *file, int line);
static void InfoPrintfStr      (char *var, const char *varName, const char *file, int line);
static void InfoPrintfC        (char var, const char *varName, const char *file, int line);
static void InfoPrintfDouble   (double var, const char *varName, const char *file, int line);
static void InfoPrintfLlu      (size_t var, const char *varName, const char *file, int line);

static WORK_RES ErrorPrintf(const char *errMess, int line, const char *file, WORK_RES ErrCode);

#define $int(Varible) InfoPrintfInt(FunctionName, Varible, toStr(Varible), __LINE__, __FILE__)
#define $str(Varible) InfoPrintfStr(FunctionName, Varible, toStr(Varible), __LINE__, __FILE__)
#define $c  (Varible) InfoPrintfC(FunctionName, Varible, toStr(Varible), __LINE__, __FILE__)
#define $dbl(Varible) InfoPrintfDouble(FunctionName, Varible, toStr(Varible), __LINE__, __FILE__)
#define $llu(Varible) InfoPrintfLlu(FunctionName, Varible, toStr(Varible))
#define $err(ErrorMessage, ErrCode) ErrorPrintf(ErrorMessage, __LINE__, __FILE__, ErrCode)

static void InfoPrintfInt(int var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%d%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

static void InfoPrintfStr(char *var, const char *varName, const char *file, int line)
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
    fprintf(stderr, CYN "%s, %d: %s%s\n" COLOR_RESET, file, line, RED, errMess);
    exit(ErrCode);
}


#endif
