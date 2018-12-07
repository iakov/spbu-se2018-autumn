void swap_in_array(int i, int j, int* arr)
{
    int h = arr[i];
    arr[i] = arr[j];
    arr[j] = h;
}

void shift_in_array(int i, int j, int* arr)
{
    int h = arr[j], k;
    for (k = j; k > i; k--) arr[k] = arr[k-1];
    arr[i] = h;
}
