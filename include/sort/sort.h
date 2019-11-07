#ifndef _SORT_H_
#define _SORT_H_

#include <adt/type.h>

void insertion_sort(element_t unsorted[], int len);
void shell_sort(element_t unsorted[], int len);
void merge_sort(element_t unsorted[], int len);
void heap_sort(element_t unsorted[], int len);
void quick_sort(element_t unsorted[], int len);
void bucket_sort(element_t unsorted[], int len, int max);

#endif
