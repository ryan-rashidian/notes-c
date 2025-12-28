/* Demonstration of the selection sort algorithm. */

void selection_sort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_index])
                min_index = j;
        }
        int temp = a[i];
        a[i] = a[min_index];
        a[min_index] = temp;
    }
}

