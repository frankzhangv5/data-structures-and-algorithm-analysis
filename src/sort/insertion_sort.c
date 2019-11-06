#include <sort/sort.h>

void insertion_sort(element_t unsorted[], int len) {
    int i, j;
    element_t tmp;

    if (!unsorted || len < 1)
        return;

    for (i = 1; i < len; i++) {
        tmp = unsorted[i];

        for (j = i; j >= 0; j--) {
            if (tmp < unsorted[j - 1])
                unsorted[j] = unsorted[j - 1];
            else
                break;
        }
        unsorted[j] = tmp;
    }
}