#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define n 10000 //maximum size of array
void fillArray()
{
    //code to fill the array
}

void swap(int* a,int* b)
{
    int temp = *a;
    *a = *b;
    *b=temp;
}

void insertionSort(int arr[], int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= start && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int medianOfThree(int arr[], int start, int end) {
    int mid = (start + end) / 2;
    if (arr[start] > arr[mid]) swap1(&arr[start], &arr[mid]);
    if (arr[start] > arr[end]) swap1(&arr[start], &arr[end]);
    if (arr[mid] > arr[end]) swap1(&arr[mid], &arr[end]);
    swap1(&arr[mid], &arr[end - 1]); // Place pivot at second-to-last position
    return arr[end - 1]; // Return the pivot value
}

void ZeiteSort(int arr[], int start, int end, int maxDepth) { //maxDepth = 2*(int)log2(n) is best to use for optimal in varied range of datasets
    if (start >= end) return;

    // Use insertion sort for small segments
    if (end - start < 10) {
        insertionSort(arr, start, end);
        return;
    }

    // Use median of three for better pivot selection
    int pivot = medianOfThree(arr, start, end);
    int i = start, j = end - 1;

    while (1) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i < j) swap(&arr[i], &arr[j]);
        else break;
    }
    swap(&arr[i], &arr[end - 1]); // Restore pivot

    // Recurse into the two halves
    // Prevent stack overflow by limiting recursion depth
    if (!(maxDepth == 0)) {
        ZeiteSort(arr, start, j, maxDepth - 1);
        ZeiteSort(arr, i + 1, end, maxDepth - 1);
    } else {
        // Fallback to insertion sort if depth is exceeded
        insertionSort(arr, start, end);
    }
}

//sample ZeiteSort caller function
void doZeiteSort(int arr[],int n)
{
    ZeiteSort(arr,0,n-1,2*(int)log2(n)); //2*(int)log2(n) is best for maxdepth to achive optimal performance among varied datasets because of efficient recursion stack management 
}

//sample main function to demonstrate ZeiteSort call
int main()
{
    int arr[];
    fillArray(arr); //custom function to the array
    doZeiteSort(arr,n);
}
