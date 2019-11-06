#include <sort/util.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(element_t arr[], int a, int b) {
    if (!arr)
        return;

    element_t tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

void fill_array(element_t *arr, int len, int max) {
    if (!arr || len < 1)
        return;

    srand((unsigned int)time(NULL));

    int i;
    for (i = 0; i < len; i++)
        arr[i] = rand() % max;
}

void print_array(element_t arr[], int len, char *title) {
    if (!arr || len < 1)
        return;

    if (title)
        printf("\n%s:\n", title);

    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);

    printf("\n");
}
