#include <math.h>
#include <fcntl.h>

#include "../headers/sorting.h"
#include "../headers/fileWork.h"

int main()
{
    FileData data = GetFileFull("Onegin.txt");

    int fileOut = open("output.txt", O_WRONLY, 0);

    my_qsort(data.indexDyn, data.indLen, sizeof(data.indexDyn[0]), CompStrNormal);
    WriteToFile(fileOut, data.indexDyn, data.indLen);

    qsort(data.indexDyn, data.indLen, sizeof(data.indexDyn[0]), CompStrReversed);
    WriteToFile(fileOut, data.indexDyn, data.indLen);

    // TODO create function
    write(fileOut, data.dataPtr, (unsigned int) data.dataLen);

    ClearFileData(&data);

    return 0;
}
