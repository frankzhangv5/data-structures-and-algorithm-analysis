#include <sort/sort.h>
#include <sort/util.h>

static element_t median3(element_t unsorted[], int left, int right) {
    int center = (left + right) / 2;

    if (unsorted[left] > unsorted[center])
        swap(unsorted, left, center);

    if (unsorted[left] > unsorted[right])
        swap(unsorted, left, right);

    if (unsorted[center] > unsorted[right])
        swap(unsorted, center, right);

    swap(unsorted, center, right - 1);

    return unsorted[right - 1];
}

static void quick_sort_inner(element_t unsorted[], int left, int right) {
    if (left + 3 <= right) {
        int pivot = median3(unsorted, left, right);

        int i, j;
        i = left;
        j = right - 1;
        for (;;) {

            while (unsorted[++i] < pivot) {
            }
            while (unsorted[--j] > pivot) {
            }
            if (i < j)
                swap(unsorted, i, j);
            else
                break;
        }
        swap(unsorted, i, right - 1);

        quick_sort_inner(unsorted, left, i - 1);
        quick_sort_inner(unsorted, i + 1, right);
    } else {
        insertion_sort(unsorted + left, right - left + 1);
    }
}

void quick_sort(element_t unsorted[], int len) {
    if (!unsorted || len < 1)
        return;

    int center = len / 2;
    quick_sort_inner(unsorted, 0, center);
    quick_sort_inner(unsorted, center + 1, len - 1);
}