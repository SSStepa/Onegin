#include "../headers/fileWork.h"

FileData GetFileFull(const char *FileName) 
{
    assert(FileName != NULL);

    int fileDes = open(FileName, O_RDONLY, 0);
    if (fileDes == -1) $err("NO FILE TO READ FROM IN GetFileFull", FILEERR);

    struct stat st;
    if (fstat(fileDes, &st)) $err("ERROR IN FILE WHILE TRYING TO fstat", FILEERR);

    FileData data = {};

    data.dataPtr = (char *) calloc(st.st_size + 1, sizeof(char));
    if (data.dataPtr == NULL) $err("NOT ENOUGHT MEMORY TO READ FILE AS FULL", NOMEM);

    int fileLen = read(fileDes, (void *) data.dataPtr, st.st_size);
    if (fileLen < 0) $err("ERROR WHILE READING FROM FILE", FILEERR);

    data.dataPtr = (char *) realloc(data.dataPtr, fileLen + 1);
    *(data.dataPtr + fileLen) = '\0';
    
    data.dataLen = (size_t) fileLen;

    data.indexDyn = (String *) calloc(MINNUM, sizeof(String));
    size_t indMax = MINNUM;
    if (data.indexDyn == NULL) $err("NOT ENOUGHT MEMORY FOR INDEX", NOMEM);
    
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
                if (temp == NULL) $err("NOT ENOUGHT MEMORY FOR INDEX RESYZE", NOMEM);
                
                data.indexDyn = temp;
            }
        }
    }
    (data.indexDyn + data.indLen - 1) -> len = lineLen;

    close(fileDes);

    return data;
}

WORK_RES WriteStringsToFile(int fileDes, String *data, size_t elNum)
{
    assert(data != NULL);

    if (fileDes < 0) $err("WRONG FILE DESCRIPTOR", WRIN);

    for (size_t ind = 0; ind < elNum; ind++) {
        ((data + ind) -> str)[(data + ind)->len - 1] = '\n';
        write(fileDes, (data + ind) -> str, (unsigned int) ((data + ind) -> len));
        ((data + ind) -> str)[(data + ind)->len - 1] = '\0';
    }
    write(fileDes, "\n", 1);

    return OK;
}

WORK_RES WriteTextToFile(int fileDes, char* data, size_t dataLen)
{
    assert(data != NULL);

    if (fileDes < 0) $err("WRONG FILE DESCRIPTOR", WRIN);

    for (size_t ind = 0; ind < dataLen; ind++) {
        if (data[ind] == '\0') data[ind] = '\n';
    }
    write(fileDes, data, (unsigned int) dataLen);

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
