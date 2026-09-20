#include "../headers/flags.h"

WORK_RES FlagsParse(int argc, char *argv[], const char **FileToReadFrom, const char **FileToWriteTo)
{
    int arg = 0;

    while((arg = getopt(argc, argv, OPTS)) != -1) {
        switch (arg)
        {
        case 'i':
            *FileToReadFrom = optarg;
            break;

        case 'o':
            *FileToWriteTo = optarg;
            break;
        
        default:
            $err("BAD FLAGS IN CALL", WRIN);
        }
    }

    return OK;
}
