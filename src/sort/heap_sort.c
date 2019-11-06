#include <sort/sort.h>
#include <sort/util.h>

static void percolate_down(element_t unsorted[], int i, int len) {

    element_t tmp = unsorted[i];
    int child;

    for (tmp = unsorted[i]; (2 * i + 1) < len; i = child) {
        child = i * 2 + 1;
        if (child + 1 <= len && unsorted[child] < unsorted[child + 1])
            child++;
        if (tmp < unsorted[child])
            swap(unsorted, i, child);
        else
            break;
    }
    unsorted[i] = tmp;
}

void heap_sort(element_t unsorted[], int len) {
    int i;

    if (!unsorted || len < 1)
        return;

    // build max heap
    for (i = len / 2; i >= 0; i--)
        percolate_down(unsorted, i, len);

    // delete max
    for (i = len - 1; i >= 0; i--) {
        swap(unsorted, 0, i);
        percolate_down(unsorted, 0, i);
    }
}