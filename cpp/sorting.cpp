#include "../headers/sorting.h"

WORK_RES my_qsort(void *arr, size_t arrLen, size_t elSize, int (* comp)(const void *, const void *))
{
    assert(arr != NULL);
    assert(elSize > 0);
    assert(comp != NULL);
    
    if (arrLen < 2) 
        return OK;

    unsigned char *divider = Partition((unsigned char *) arr, (unsigned char *) arr + (arrLen - 1) * elSize, elSize, comp);
   
    if (divider > (unsigned char *) arr)
        my_qsort(arr, (divider - (unsigned char *) arr)/elSize , elSize, comp);

    if (arrLen > 2 && (divider <= (unsigned char *) arr + arrLen * elSize))
        my_qsort((void *) divider, arrLen - (divider - (unsigned char *) arr)/elSize, elSize, comp);

    return OK;
}

unsigned char *Partition(unsigned char *LeftPtr, unsigned char *RightPtr, size_t elSize, int (*comp)(const void *, const void *))
{
    assert(LeftPtr != NULL);
    assert(RightPtr != NULL);
    assert(comp != NULL);
    assert(elSize > 0);

    unsigned char *BaseElPtr = LeftPtr + ((RightPtr - LeftPtr)/2/elSize) * elSize; // /elSize * elSize to have num of ells 

    while (LeftPtr < RightPtr) {
        while (LeftPtr <= RightPtr && (*comp)((void *) LeftPtr, (void *) BaseElPtr) < 0)
            LeftPtr += elSize;

        while (RightPtr >= LeftPtr && (*comp)((void *) RightPtr, (void *) BaseElPtr) > 0)
            RightPtr -= elSize;

        if (LeftPtr >= RightPtr) break;

        if      (LeftPtr  == BaseElPtr) BaseElPtr = RightPtr;
        else if (RightPtr == BaseElPtr) BaseElPtr = LeftPtr;

        SwapElls(LeftPtr, RightPtr, elSize);

        LeftPtr += elSize;
        RightPtr -= elSize; // can point to element not in arr
    }

    return LeftPtr;
}

WORK_RES SwapElls(unsigned char *firstPtr, unsigned char *secondPtr, size_t elSize)
{
    assert(firstPtr != NULL);
    assert(secondPtr != NULL);
    assert(elSize > 0);

    unsigned long long buff = 0;
    int buffInt = 0;
    short buffShort = 0;
    char buffChar = 0;

    // first stage - fill main part
    while (elSize/sizeof(buff) > 0) {
        MacroChangeMamory(buff, unsigned long long, firstPtr, secondPtr);       
        elSize -= sizeof(buff);
    }

    // second stage - fill last part (max 7 bites)
    if (elSize >= sizeof(int)) {
        MacroChangeMamory(buffInt, int, firstPtr, secondPtr);
        elSize -= sizeof(int);
    }

    if (elSize >= sizeof(short)) {
        MacroChangeMamory(buffShort, short, firstPtr, secondPtr);
        elSize -= sizeof(short);
    }

    if (elSize == sizeof(char)) {
        MacroChangeMamory(buffChar, char, firstPtr, secondPtr);
    }

    return OK;
}

int CompStrNormal(const void *firstLinePtr, const void *secondLinePtr)
{
    assert(firstLinePtr != NULL);
    assert(secondLinePtr != NULL);

    const String fLineInf = *(const String *) firstLinePtr;
    const String sLineInf = *(const String *) secondLinePtr;

    char *fLine = fLineInf.str;
    char *sLine = sLineInf.str;
    
    size_t fInd = 0;
    size_t sInd = 0;

    while(fLine[fInd] != '\0') {
        while (fLine[fInd] != '\0' && !isalpha(fLine[fInd])) fInd++;
        while (sLine[sInd] != '\0' && !isalpha(sLine[sInd])) sInd++;

        if (tolower(fLine[fInd]) != tolower(sLine[sInd]))
            break;

        fInd++;
        sInd++;
    }

    return tolower(fLine[fInd]) - tolower(sLine[sInd]);
}


int CompStrReversed(const void *firstLinePtr, const void *secondLinePtr)
{
    assert(firstLinePtr != NULL);
    assert(secondLinePtr != NULL);

    const String fLineInf = *(const String *) firstLinePtr;
    const String sLineInf = *(const String *) secondLinePtr;
    
    char *fLine = fLineInf.str;
    char *sLine = sLineInf.str;
    
    size_t fInd = fLineInf.len;
    size_t sInd = sLineInf.len;

    while(fInd > 0 && sInd > 0) {
        do {
            fInd--;
        } while (fInd > 0 && !isalpha(fLine[fInd]));
        do {
            sInd--;
        } while (sInd > 0 && !isalpha(sLine[sInd]));
        
        if (tolower(fLine[fInd]) != tolower(sLine[sInd])) {
            return tolower(fLine[fInd]) - tolower(sLine[sInd]);
        }
    }

    if (fInd == sInd) return  0;
    if (fInd == 0)    return -1;
    
    return  1;
}
