#ifndef _UTIL_H_
#define _UTIL_H_

#include <adt/type.h>
#include <time.h>

#define SPENT_SEC(title, start)                                                \
    do {                                                                       \
        printf("\n%s spent %fs\n", title,                                      \
               (double)(clock() - start) / CLOCKS_PER_SEC);                    \
    } while (0)

void swap(element_t arr[], int a, int b);
void fill_array(element_t *arr, int len, int max);
void print_array(element_t arr[], int len, char *desc);

#endif