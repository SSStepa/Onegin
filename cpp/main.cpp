#include <math.h>
#include <fcntl.h>

#include "../headers/sorting.h"
#include "../headers/fileWork.h"
#include "../headers/basic.h"

int main()
{
    FileData data = GetFileFull("Onegin.txt");

    int fileOut = open("output.txt", O_WRONLY, 0);
    if (fileOut == -1) $err("NO FILE FOR OUTPUT", FILEERR);

    my_qsort(data.indexDyn, data.indLen, sizeof(data.indexDyn[0]), CompStrNormal);
    WriteStringsToFile(fileOut, data.indexDyn, data.indLen);

    qsort(data.indexDyn, data.indLen, sizeof(data.indexDyn[0]), CompStrReversed);
    WriteStringsToFile(fileOut, data.indexDyn, data.indLen);

    WriteTextToFile(fileOut, data.dataPtr, data.dataLen);

    ClearFileData(&data);

    close(fileOut);

    return 0;
}
