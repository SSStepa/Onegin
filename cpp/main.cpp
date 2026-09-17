#include <math.h>

#include "../headers/sorting.h"
#include "../headers/fileWork.h"

int main()
{
    const char *data1[] = {
   "My uncles goodness is extreme,\0",
   "If seriously he hath disease;\0",
   "He hath acquired the worlds esteem\0",
   "And nothing more important sees;\0",
   "A paragon of virtue he!\0",
   "But what a nuisance it will be,\0",
   "Chained to his bedside night and day\0",
   "Without a chance to slip away.\0",
   "Ye need dissimulation base\0",
   "A dying man with art to soothe,\0",
   "Beneath his head the pillow smooth,\0",
   "And physic bring with mournful face,\0",
   "To sigh and meditate alone:\0",
   "When will the devil take his own!\0"
    };

    size_t dataSize = 0;

    char **data = GetFileInLines("Onegin.txt", &dataSize);

    my_qsort(data, dataSize, sizeof(data[0]), CompStrNormal);

    for (size_t ind = 0; ind < dataSize; ind++) {
        printf("%s", data[ind]);
    }

    printf(GRN "START SECOND PART\n" COLOR_RESET);

    my_qsort(data, dataSize, sizeof(data[0]), CompStrReversed);
    for (size_t ind = 0; ind < dataSize; ind++) {
        printf("%s", data[ind]);
    }
}
