
template <typename T>
void swap(T *arr, int p, int r) {
    T temp = arr[p];
    arr[p] = arr[r];
    arr[r] = temp;
}


template <typename T>
int divide(T *arr, int p, int r) {
    T x = arr[r];

    int i = p;
    
    for (int j = p; j < r; j++) {
        if (arr[j] <= x) {
            swap(arr, i, j);
            i++; 
        }
    }


    swap(arr, i, r);

    return i;
}

template <typename T>
void quick_sort(T *arr, int p, int r) {
    if (p < r) {
        int q = divide(arr, p, r);
        quick_sort(arr, p, q - 1);
        quick_sort(arr, q + 1, r);
    }
};

