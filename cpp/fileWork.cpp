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

    int fileLen = read(fileDes, (void *) data.dataPtr, st.st_size);
    if (fileLen < 0) {
        printf(RED "GetFileFull: ERROR WHILE READING FROM FILE\n" COLOR_RESET);
        exit(FILEERR);
    }

    data.dataPtr = (char *) realloc(data.dataPtr, fileLen + 1);
    *(data.dataPtr + fileLen) = '\0';
    
    data.dataLen = (size_t) fileLen;

    data.indexDyn = (String *) calloc(MINNUM, sizeof(String));
    size_t indMax = MINNUM;
    if (data.indexDyn == NULL) {
        printf(RED "GetFileFull: NOT ENOUGHT MEMORY FOR INDEX\n" COLOR_RESET);
        exit(NOMEM);
    }
    *data.indexDyn = {.str = data.dataPtr};
    data.indLen++;

    size_t lineLen = 1;
    for (size_t ind = 0; ind < (size_t) fileLen; ind++, lineLen++){
        if (data.dataPtr[ind] == '\n') {
            data.dataPtr[ind] = '\0';
            
            (data.indexDyn + data.indLen - 1) -> len = lineLen;
            lineLen = 0;

            // point to new line
            (data.indexDyn + data.indLen++) -> str = &data.dataPtr[ind + 1];

            if (indMax == data.indLen) {
                indMax *= 2;
                String *temp = (String *) realloc(data.indexDyn, indMax * sizeof(String));
                if (temp == NULL) {
                    printf(RED "GetFileFull: NOT ENOUGHT MEMORY FOR INDEX RESYZE\n" COLOR_RESET);
                    exit(NOMEM);
                }
                data.indexDyn = temp;
            }
        }
    }
    (data.indexDyn + data.indLen - 1) -> len = lineLen;

    close(fileDes);

    return data;
}

WORK_RES WriteToFile(int fileDes, String *data, size_t elNum)
{
    assert(data != NULL);

    if (fileDes < 0) {
        printf(RED "WriteToFile: WRONG FILE DESCRIPTOR" COLOR_RESET);
        exit(WRIN);
    }

    for (size_t ind = 0; ind < elNum; ind++) {
        ((data + ind) -> str)[(data + ind)->len - 1] = '\n'; // TODO normal readible form
        write(fileDes, (data + ind) -> str, (unsigned int) ((data + ind) -> len));
    }
    write(fileDes, "\n", 1);

    return OK;
}

WORK_RES ClearFileData(FileData *data)
{
    assert(data != NULL);

    free(data -> firstLine);
    free(data -> dataPtr);

    return OK;
}

char **GetFileInLines(const char *FileName, size_t *dataSize)
{
    assert(FileName != NULL);
    assert(dataSize != NULL);

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
