
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

