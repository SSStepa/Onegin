#include "../headers/fileWork.h"

char **GetFileInLines(const char *FileName, size_t *dataSize)
{
    FILE *file = fopen(FileName, "r");
    if (file == NULL) {
        printf(RED "ERROR: NO FILE\n" COLOR_RESET);
        exit(NOFILE);
    }

    size_t dataLen = MINNUM;
    char **data = (char **) calloc(dataLen, sizeof(char *));
    if (data == NULL) {
        printf(RED "ERROR: NOT ENOUGH MEMORY\n" COLOR_RESET);
        exit(NOMEM);
    }

    size_t ind = 0;

    char buff[MAXBUFF] = "";

    while (fgets(buff, MAXBUFF, file)) {
        data[ind++] = strdup(buff);
        if (ind == dataLen) {
            dataLen *= 2;
            char **temp = (char **) realloc(data, dataLen*sizeof(char *));
            
            if (data == NULL) {
            printf(RED "ERROR: NOT ENOUGH MEMORY\n" COLOR_RESET);
            exit(NOMEM);
            }
            data = temp;
        }
    }

    data = (char **) realloc(data, ind*sizeof(char *));
    *dataSize = ind;

    return data;

}