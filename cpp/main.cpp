#include <math.h>

#include "../headers/sorting.h"

int main()
{
    const char *data[] = {
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
   "When will the devil take his own\0!"
    };

    int Num = sizeof(data)/sizeof(data[0]);

    my_qsort(data, Num, sizeof(data[0]), CompStrNormal);

    for (size_t ind = 0; ind < Num; ind++) {
        printf("<%s>\n", data[ind]);
    }

    printf(GRN "START SECOND PART" COLOR_RESET);

    my_qsort(data, Num, sizeof(data[0]), CompStrReversed);
    for (size_t ind = 0; ind < Num; ind++) {
        printf("<%s>\n", data[ind]);
    }
}
