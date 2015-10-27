
/*
 * Search a key in an array which is sorted and rotated (left or right).
 *
 * It is does not matter whether the array is left or right rotated because
 * the order in which the original elements appeared, from smallest to largest,
 * in the rotated array would always be from left to right, in the case of wrap-around
 * largest element(s) would be on left before smallest elements.
 * Hemce, There are three cases or state of rotated array,
 * Case 1 : a[low] > a[up] and first(smallest) element is between a[mid] & a[up].
 * Case 2 : a[low] > a[up] and first(smallest) element is between a[low] & a[mid].
 * Case 3 : a[low] < a[up], Here array is not rorated.
 *          
 * @a : Array of ints which is sorted and rotated.
 * @key : Key that needs to be search.
 * @low : Lower bound  of a[].
 * @up : Upper bound of a[].
 */
int rotated_array_bsearch(int a[], int key, int low, int up)
{
    int mid = (low + up)/2;

    if (low > up)
    {
        //key not found.
        return -1;
    }
    else if (a[mid] == key)
    {
        //Key found.
        return mid;
    }
    //This array must be left or right rotated.
    else if (a[low] > a[up])
    {
        if (key > a[mid])
        {
            if (key > a[up])
            {
                // Case 1.
                return rotated_array_bsearch(a, key, low, mid - 1);
            }
            else
            {
                //Case 1 & 2.
                return rotated_array_bsearch(a, key, mid + 1, up);
            }
        }
        else
        {
            if (a[mid] < a[up] /* Case 1. */ ||
                key > a[up] /* Case 2. */)
            {
                return rotated_array_bsearch(a, key, low, mid - 1);
            }
            else
            {
                //case 2.
                return rotated_array_bsearch(a, key, mid + 1, up);
            }
        }
    }
    else
    {
        //Usual binary search, Case 3.
        if (key > a[mid])
        {
            return rotated_array_bsearch(a, key, mid + 1, up);
        }
        else
        {
            return rotated_array_bsearch(a, key, low, mid - 1);
        }
    }
}

/*
 * Sort array of ints using insertion sort.
 * Sort array by finding largest elements first to smallest element i.e from right to left
 * such that a[0] <= a[]1 <= a[2] ... <= a[length - 1].
 *
 * @a : Array of ints that needs to be sorted.
 * @length : Number of elements in the above array.
 */
void insertion_sort_right_to_left(int a[], int length)
{
    int i = 0; j = 0, key = 0;

    for (i = length - 2; i >= 0; i++)
    {
        key = a[i];
        j = i + 1;

        while (j < length && a[j] < key)
        {
            a[j - 1] = a[j];
            j++;
        }

        a[j - 1] = key;
    }
}

/*
 * Sort the array of ints using selection sort.
 * Sort the array by finding smallest element first then second smallest, third smallest
 * and so on to eventually sort the whole array.
 *
 * @a : Array of ints that needs to be sorted.
 * @length : Number of elements in the above array.
 */
void selection_sort(int a[], int length)
{
    int i = 0, j = 0, ith_smallest = 0, ith_smallest_index = 0;

    for (i = 0; i < n - 1; i++)
    {
        ith_smallest = a[i];
        ith_smallest_index = i;

        //As the array[i + 1 to n] in not sorted we need to check entire this range to find ith smallest.
        for (j = i + 1; j < n; j++)
        {
            if (ith_smallest > a[j])
            {
                ith_smallest = a[j];
                ith_smallest_index = j;
            }
        }

        a[ith_smallest_index] = a[i];
        a[i] = ith_smallest;
    }
}

/*
 * Merge two sorted array into one.
 *
 * @a : First sorted array.
 * @p : Number of elements in above array.
 * @b : Second sorted array.
 * @q : Number of elements in above array.
 * @c : Output array to store final merged elements.
 */ 
void array_merge(int a[], int p, int b[], int q, int c[])
{
    int i = 0, j = 0, k = 0;

    while (i < p && j < q)
    {
        if (a[i] <= b[j])
        {
            c[k] = a[i];
            i++;
        }
        else
        {
            c[k] = b[j];
            j++;
        }

        k++;
    }

    while (i < p)
    {
        c[k] = a[i];
        i++;
        k++;
    }

    while (j < q)
    {
        c[k] = b[j];
        j++;
        k++;
    }
}

/*
 * Given an array find a subarray such that sum of all its elements is maximum among all subarray.
 * This takes O(n^2) time, in CLR ch 2 same is solved with O(n log n).
 *
 * @a[] : Array of ints.
 # @length : Number of elements in the above array.
 * @max_sub_array_start : Starting index of max subarray found as output param.
 * @max_subarray_end : Ending index of max subarray found as output param.
 * @max_subarray : Sum of all elements of max subarray as output param.
 */
void array_find_max_subarray_n2(int a[], int length, int *max_sub_array_start, int *max_subarray_end, int *max_subarray)
{
    if (length == 1)
    {
        *max_sub_array_start = *max_subarray_end = 0;
        *max_subarray = a[0];
        return 0;
    }

    //Init, also n > 1.
    *max_subarray = a[0];
    *max_subarray_start = *max_subarray_end = 0;

    for (i = 0; i < n; i++)
    {
        //Init before finding max subarray at ith index.
        ith_max_subarray = a[i];

        for (j = i + 1; j < n; j++)
        {
            ith_max_subarray += a[j];
            if (ith_max_subarray > *max_subarray)
            {
                *max_subarray = ith_max_subarray;
                *max_subarray_start = i;
                *max_subarray_end = j;
            }
        }
    }
}

/*
 * Given an array find a subarray such that sum of all its elements is maximum among all subarray.
 * This takes O(n^2) time, in CLR ch 2 same is solved with O(n log n).
 *
 * @a[] : Array of ints.
 # @length : Number of elements in the above array.
 * @max_sub_array_start : Starting index of max subarray found as output param.
 * @max_subarray_end : Ending index of max subarray found as output param.
 * @max_subarray : Sum of all elements of max subarray as output param.
 */
void array_find_max_subarray_nlogn(int a[], int length, int *max_sub_array_start, int *max_subarray_end, int *max_subarray)
{
    if (length == 1)
    {
        *max_sub_array_start = *max_subarray_end = 0;
        *max_subarray = a[0];
        return 0;
    }

    //Init, also n > 1.
    *max_subarray = a[0];
    *max_subarray_start = *max_subarray_end = 0;

    for (j = 1; j < n; j++)
    {
        ith_max_subarray += a[j];
        if (ith_max_subarray > *max_subarray)
        {
            *max_subarray = ith_max_subarray;
            *max_subarray_start = i;
            *max_subarray_end = j;
        }
    }

    for (i = 0; i < n; i++)
    {
        //Init before finding max subarray at ith index.
        ith_max_subarray = a[i];

        for (j = i + 1; j < n; j++)
        {
            ith_max_subarray += a[j];
            if (ith_max_subarray > *max_subarray)
            {
                *max_subarray = ith_max_subarray;
                *max_subarray_start = i;
                *max_subarray_end = j;
            }
        }
    }
}

/*
 * Build max-heap from ith node in the heap.
 * Heap starts from a[1].
 * Retuns 0 on success and 1 on failure.
 *
 * @a : Array of ints represents max-heap.
 * @i : Starting element to buid max-heap.
 * @n : Size of the max-heap.
 */

#define HEAP_LEFT_CHILD(X)      (2U * (X))
#define HEAP_RIGHT_CHILD(X)     ((2U * (X)) + 1)
#define HEAP_PARENT(X)          ((X) / 2)

int array_max_heapify(int a[], unsigned i, unsigned n)
{
    unsigned left_child = 0, right_child = 0, largest = 0;
    unsigned temp = 0;

    if (i > n)
    {
        return 1;
    }

    while (i < n)
    {
        left_child = HEAP_LEFT_CHILD(i);
        right_child = HEAP_RIGHT_CHILD(i);

        //Find largest among left_child, right_child of ith element and ith element itself.
        largest = (left_child <= n && a[left_child] > a[i])? left_child: i;
        largest = (right_child <= n && a[right_child] > a[largest])? right_child: largest;

        if (i == largest)
        {
            //Done.
            break;
        }

        //Swap ith element with largest element to satisfy heap property.
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        //Re-max-heapify from largest element, new ith element.
        i = largest;
    }

    return 0;
}

/*
 * Build min-heap from ith node in the heap.
 * Heap starts from a[1].
 * Retuns 0 on success and 1 on failure.
 *
 * @a : Array of ints represents min-heap.
 * @i : Starting element to buid min-heap.
 * @n : Size of the max-heap.
 */
int array_min_heapify(int a[], unsigned i, unsigned n)
{
    unsigned left_child = 0, right_child = 0, smallest = 0;
    unsigned temp = 0;

    if (i > n)
    {
        return 1;
    }

    while (i < n)
    {
        left_child = HEAP_LEFT_CHILD(i);
        right_child = HEAP_RIGHT_CHILD(i);

        //Find smallest among left_child, right_child of ith element and ith element.
        smallest = (left_child <= n && a[left_child] < a[i])? left_child: i;
        smallest = (right_child <= n && a[right_child] < a[smallest])? right_child: smallest;

        if (i == smallest)
        {
            //Done.
            break;
        }

        //Swap ith element with smallest element to satisfy heap property.
        temp = a[i];
        a[i] = a[smallest];
        a[smallest] = temp;

        //Re-min-heapify from smallest element, new ith element.
        i = smallest;
    }

    return 0;
}

/*
 * Build min-heap..
 *
 * @a: Array of ints representing min-heap.
 * @: Size of the min-heap.
 */
void array_build_min_heap(int a[], unsigned n)
{
    assert(n > 0);

    /*
     * For any i, 0 > i <= n, is a leaf node if i >= n/2 otherwise its childrens must at 2 * i, 2 * i <= n
     * i.e. (n /2 )th node is the last parent in the heap wich has atleast one child.
     * By above theorem n / 2 must have atlest one child which is a leaf node, this is starting point, and
     * (n / 2) + 1 must be a leaf node.
     */
    for (i = (n / 2); i > 1; i--)
    {
        assert(array_min_heapify(a, i, n) == 0);
    }
}

/*
 * Remove topmost element from Min-Heap then Re-heapify it to put next smallest element at the top.
 * Heap starts from a[1].
 * Retuns smallest element from the heap.
 *
 * @a: Array of ints representing min-heap.
 * @: Size of the min-heap.
 */
int array_extract_min(int a[], unsigned n)
{
    int smallest = 0;

    assert(n > 0)

    smallest = a[1];
    a[1] = a[n];
    n--;
    array_build_min_heap(a, n);

    return smallest;
}

/*
 * Decrease value of existing key and then re-heapify min-heap.
 * After decreasing key then all element before it may or may not be <= new key but
 * all elements after it must be >= new key value so we just need to re-heapify from 1 to key.
 * Returns 0 on success and 1 on failure.
 *
 * @a : Array on ints represents min-heap.
 * @i : ith element in min-heap.
 * @new_key : New key value for ith element.
 * @n : Size of min-heap.
 */
int array_decrease_key(int a[], unsigned i, unsigned new_key, unsigned n)
{
    if (i > n ||  n == 0 || new_key >= a[i])
    {
        return 1;
    }

    a[i] = new_key;

    while (i > 1 && a[HEAP_PARENT(i)] > a[i])
    {
        temp = a[HEAP_PARENT(i)];
        a[HEAP_PARENT(i)] = a[i];
        a[i] = temp;
        i = HEAP_PARENT(i);
    }

    return 0;
}
/*
 * Insert new key into the min-heap.
 * Increase the size of the heap and add new key as last element then re-heapify from n to 1.
 *
 * @a : Array on ints represents min-heap.
 * @new_key : New element.
 * @n : Size of min-heap.
 */
int array_min_heap_insert(int a[], unsigned n, int new_key)
{
    n++;
    a[n] = new_key;
    array_build_min_heap(a, n);

    return 0;
}

