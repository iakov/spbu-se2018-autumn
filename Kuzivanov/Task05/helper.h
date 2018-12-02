void swap_in_array(int i, int j, int* a)
{
    int h = a[i];
    a[i] = a[j];
    a[j] = h;
}

void shift_in_array(int i, int j, int* a)
{
    int h = a[j], k;
    for (k = j; k > i; k--) a[k] = a[k-1];
    a[i] = h;
}
