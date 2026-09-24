#include <math.h>
#include <fcntl.h>

#include "../headers/sorting.h"
#include "../headers/fileWork.h"
#include "../headers/basic.h"
#include "../headers/flags.h"

// const argv
int main(int argc, char *const argv[])
{
    SetUpLog();

    WORK_RES status = OK;
    const char *FileToRead  = "Onegin.txt";
    const char *FileToWrite = "output.txt";

    FlagsParse(argc, argv, &FileToRead, &FileToWrite);

    FileData data = GetFileFull(FileToRead);

    if (data.ErrCode != OK)
        return data.ErrCode;

    int fileOut = open(FileToWrite, O_WRONLY, 0);
    if (fileOut == -1) {
        $err("NO FILE FOR OUTPUT", FILEERR);
        return FILEERR;
    }

    my_qsort(data.indexDyn, data.indLen, sizeof(data.indexDyn[0]), CompStrNormal);
    if ((status = WriteStringsToFile(fileOut, data.indexDyn, data.indLen)) != OK) {
        return status;
    }

    qsort(data.indexDyn, data.indLen, sizeof(data.indexDyn[0]), CompStrReversed);
    if((status = WriteStringsToFile(fileOut, data.indexDyn, data.indLen)) != OK) {
        return status;
    }

    WriteTextToFile(fileOut, data.dataPtr, data.dataLen);

    ClearFileData(&data);

    close(fileOut);

    return 0;
}
