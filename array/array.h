#ifndef __ARRAY_H__

#define  __ARRAY_H__

int rotated_array_bsearch(int a[], int key, int low, int up);
void insertion_sort_right_to_left(int a[], int length);
void selection_sort(int a[], int length);
void array_merge(int a[], int p, int b[], int q, int c[]);
void array_find_max_subarray_n2(int a[], int length, int *max_sub_array_start, int *max_subarray_end, int *max_subarray);
void array_find_max_subarray_nlogn(int a[], int length, int *max_sub_array_start, int *max_subarray_end, int *max_subarray);
int array_max_heapify(int a[], unsigned i, unsigned n);
int array_min_heapify(int a[], unsigned i, unsigned n);
void array_build_min_heap(int a[], unsigned n);
int array_extract_min(int a[], unsigned n);
int array_decrease_key(int a[], unsigned i, unsigned new_key, unsigned n);
int array_min_heap_insert(int a[], unsigned n, int new_key);

#endif // __ARRAY_H__
