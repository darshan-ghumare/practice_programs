
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
 * Find three closest elements from given three sorted arrays
 * Given three sorted arrays A[], B[] and C[], find 3 elements i, j and
 * k from A, B and C respectively such that max(abs(A[i] – B[j]), abs(B[j] – C[k]),
 * abs(C[k] – A[i])) is minimized. Here abs() indicates absolute value.
 *
 *  Example :
 *
 *  Input: A[] = {1, 4, 10}
 *  B[] = {2, 15, 20}
 *  C[] = {10, 12}
 *  Output: 10 15 10
 *  10 from A, 15 from B and 10 from C
 *
 *  Input: A[] = {20, 24, 100}
 *  B[] = {2, 19, 22, 79, 800}
 *  C[] = {10, 12, 23, 24, 119}
 *  Output: 24 22 23
 *  24 from A, 22 from B and 23 from C
 *
 *  Source : http://www.geeksforgeeks.org/find-three-closest-elements-from-given-three-sorted-arrays/
 *
 *  Algo:
 *  1) Start with i=0, j=0 and k=0 (Three index variables for A,
 *     B and C respectively)
 *
 *  //  p, q and r are sizes of A[], B[] and C[] respectively.
 *  2)  Do following while i < p and j < q and k < r
 *      a) Find min and maximum of A[i], B[j] and C[k]
 *      b) Compute diff = max(X, Y, Z) - min(A[i], B[j], C[k]).
 *      c) If new result is less than current result, change 
 *      it to the new result.
 *      d) Increment the pointer of the array which contains 
 *      the minimum.
 */
void findClosest(int A[], int B[], int C[], int p, int q, int r)
{

    int diff = INT_MAX;  // Initialize min diff

    // Initialize result
    int res_i =0, res_j = 0, res_k = 0;

    // Traverse arrays
    int i=0,j=0,k=0;
    while (i < p && j < q && k < r)
    {
        // Find minimum and maximum of current three elements
        int minimum = min(A[i], min(B[j], C[k]));
        int maximum = max(A[i], max(B[j], C[k]));

        // Update result if current diff is less than the min
        // diff so far
        if (maximum-minimum < diff)
        {
            res_i = i, res_j = j, res_k = k;
            diff = maximum - minimum;
        }

        // We can't get less than 0 as values are absolute
        if (diff == 0) break;

        // Increment index of array with smallest value
        if (A[i] == minimum) i++;
        else if (B[j] == minimum) j++;
        else k++;
    }

    // Print result
    cout << A[res_i] << " " << B[res_j] << " " << C[res_k];
}

