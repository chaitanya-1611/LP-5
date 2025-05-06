#include <iostream>
#include <omp.h>
#include <stdlib.h>

using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    int temp[1000];

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (int i = left; i <= right; i++)
        arr[i] = temp[i];
}

void mergesort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergesort(arr, left, mid);

            #pragma omp section
            mergesort(arr, mid + 1, right);
        }

        merge(arr, left, mid, right);
    }
}

int main() {
    int *arr, n;

    cout << "Enter the number of elements: ";
    cin >> n;
    arr = new int[n];

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    mergesort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    delete[] arr;
    return 0;
}
