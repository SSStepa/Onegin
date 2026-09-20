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
        case 'h':
            ShowHelp();
            exit(0);
        
        default:
            $err("BAD FLAGS IN CALL", WRIN);
        }
    }

    return OK;
}

void ShowHelp()
{
    printf("[-i]  Name of file to read from\n");
    printf("[-o]  Name of file to write to");
}
