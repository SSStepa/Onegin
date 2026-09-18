#include "../headers/fileWork.h"

FileData GetFileFull(const char *FileName) 
{
    assert(FileName != NULL);

    int fileDes = open(FileName, O_RDONLY, 0);
    if (fileDes == -1) {
        printf(RED "GetFileFull: NO FILE TO READ FROM IN GetFileFull\n" COLOR_RESET);
        exit(FILEERR);
    }

    struct stat st;
    if (fstat(fileDes, &st)) {
        printf(RED "GetFileFull: ERROR IN FILE WHILE TRYING TO fstat\n" COLOR_RESET);
        exit(FILEERR);
    }

    FileData data = {};

    data.dataPtr = (char *) calloc(st.st_size + 1, sizeof(char));
    if (data.dataPtr == NULL) {
        printf(RED "GetFileFull: NOT ENOUGHT MEMORY TO READ FILE AS FULL\n" COLOR_RESET);
        exit(NOMEM);
    }

    // printf(CYN "I've created data buffer\n" COLOR_RESET);
    // fflush(stdout);

    long fileLen = read(fileDes, (void *) data.dataPtr, st.st_size);
    data.dataPtr = (char *) realloc(data.dataPtr, fileLen + 1);
    *(data.dataPtr + fileLen) = '\0';
    
    // printf(CYN "I've read data from file\n" COLOR_RESET);
    // printf("It starts <%c>\n", data.dataPtr[0]);
    // fflush(stdout);

    data.indexDyn = (String *) calloc(MINNUM, sizeof(String));
    size_t indMax = MINNUM;
    if (data.indexDyn == NULL) {
        printf(RED "GetFileFull: NOT ENOUGHT MEMORY FOR INDEX\n" COLOR_RESET);
        exit(NOMEM);
    }
    *data.indexDyn = {.str = data.dataPtr};
    data.indLen++;

    // printf(CYN "I added pointer to first line and it has second symb: <%c>\n" COLOR_RESET, (data.indexDyn -> str)[1]);
    // fflush(stdout);

    size_t lineLen = 0;
    for (size_t ind = 0; ind < fileLen; ind++, lineLen++){
        // printf(YEL "I'm in cucle number <%llu>\n" COLOR_RESET, ind);
        // printf(BLU "And it is <%c>\n" COLOR_RESET, data.dataPtr[ind]);
        // fflush(stdout);

        if (data.dataPtr[ind] == '\n') {
            data.dataPtr[ind] = '\0';
            // printf(YEL "And now it is <%c>\n" COLOR_RESET, data.dataPtr[ind]);
            // fflush(stdout);

            // printf(GRN "Now indLen is <%llu>" COLOR_RESET, data.indLen);
            // length of previous
            (data.indexDyn + data.indLen - 1) -> len = lineLen;
            lineLen = 0;

            // printf(CYN "Now i know previous datalen and it is <%llu>\n" COLOR_RESET, (data.indexDyn + data.indLen -1) -> len);
            // fflush(stdout);

            // point to new line
            (data.indexDyn + data.indLen++) -> str = &data.dataPtr[ind + 1];
            // printf(CYN "I've complitted line:\n" COLOR_RESET);
            // printf("%s\n", (data.indexDyn + data.indLen - 1) -> str);
            // fflush(stdout);

            if (indMax == data.indLen) {
                indMax *= 2;
                String *temp = (String *) realloc(data.indexDyn, indMax * sizeof(String));
                if (temp == NULL) {
                    // printf(RED "GetFileFull: NOT ENOUGHT MEMORY FOR INDEX RESYZE\n" COLOR_RESET);
                    // exit(NOMEM);
                }
                data.indexDyn = temp;
            }
        }
    }

    return data;
}

char **GetFileInLines(const char *FileName, size_t *dataSize)
{
    FILE *file = fopen(FileName, "r");
    if (file == NULL) {
        printf(RED "ERROR: NO FILE\n" COLOR_RESET);
        exit(FILEERR);
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
