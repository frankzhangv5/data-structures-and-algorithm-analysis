#include <sort/sort.h>
#include <stdlib.h>
#include <string.h>

static void merge_inner(element_t unsorted[], element_t tmp_arr[], int left,
                        int right_start, int right_end) {
    int i;
    int len = right_end - left + 1;
    int tmp_pos = left;
    int left_end = right_start - 1;

    while (left <= left_end && right_start <= right_end) {
        if (unsorted[left] < unsorted[right_start])
            tmp_arr[tmp_pos++] = unsorted[left++];
        else
            tmp_arr[tmp_pos++] = unsorted[right_start++];
    }

    while (left <= left_end)
        tmp_arr[tmp_pos++] = unsorted[left++];

    while (right_start <= right_end)
        tmp_arr[tmp_pos++] = unsorted[right_start++];

    for (i = 0; i < len; i++) {
        unsorted[right_end] = tmp_arr[right_end];
        right_end--;
    }
}

static void merge_sort_inner(element_t unsorted[], element_t tmp_arr[],
                             int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        merge_sort_inner(unsorted, tmp_arr, left, center);
        merge_sort_inner(unsorted, tmp_arr, center + 1, right);
        merge_inner(unsorted, tmp_arr, left, center + 1, right);
    }
}

void merge_sort(element_t unsorted[], int len) {

    if (!unsorted || len < 1)
        return;

    int size = sizeof(element_t) * len;
    element_t *tmp_arr = (element_t *)malloc(size);
    if (!tmp_arr)
        return;

    memset(tmp_arr, 0, size);

    merge_sort_inner(unsorted, tmp_arr, 0, len - 1);
    free(tmp_arr);
}