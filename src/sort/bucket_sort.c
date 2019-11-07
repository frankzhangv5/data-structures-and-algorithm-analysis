#include <sort/sort.h>
#include <stdlib.h>
#include <string.h>

void bucket_sort(element_t unsorted[], int len, int max) {
    int i, j;

    if (!unsorted || len < 1)
        return;

    int size = (max + 1) * sizeof(element_t);
    element_t *bucket = (element_t *)malloc(size);

    if (!bucket)
        return;

    memset(bucket, 0, size);

    for (i = 0; i < len; i++)
        bucket[unsorted[i]]++;

    j = 0;
    for (i = 0; i < (max + 1); i++) {
        while (bucket[i]--)
            unsorted[j++] = i;
    }

    free(bucket);
}