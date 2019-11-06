#include <sort/sort.h>

void shell_sort(element_t unsorted[], int len) {
    int i, j, increcement;
    element_t tmp;

    if (!unsorted || len < 1)
        return;

    for (increcement = len / 2; increcement > 0; increcement /= 2) {
        for (i = increcement; i < len; i++) {
            tmp = unsorted[i];

            for (j = i; j >= increcement; j -= increcement) {
                if (tmp < unsorted[j - increcement])
                    unsorted[j] = unsorted[j - increcement];
                else
                    break;
            }
            unsorted[j] = tmp;
        }
    }
}