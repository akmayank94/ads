#include <iostream>
#include <cstdlib> // For rand()

using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high, int &comparisons) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int randomizedPartition(int arr[], int low, int high, int &comparisons) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high, comparisons);
}

void randomizedQuickSort(int arr[], int low, int high, int &comparisons) {
    if (low < high) {
        int pivotIndex = randomizedPartition(arr, low, high, comparisons);
        randomizedQuickSort(arr, low, pivotIndex - 1, comparisons);
        randomizedQuickSort(arr, pivotIndex + 1, high, comparisons);
    }
}

void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n], comparisons = 0;
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Original array: ";
    displayArray(arr, n);

    srand(0); // Fixed seed for consistent results (remove this for variable randomness)
    randomizedQuickSort(arr, 0, n - 1, comparisons);

    cout << "Sorted array: ";
    displayArray(arr, n);
    cout << "Total comparisons: " << comparisons << endl;

    return 0;
}

//best avg
// RR: T(n) = 2T(n/2) + O(n)
// TC: O(nlogn)

//worst O(n^2)
//Sc: O(logn)

//adv: rand reduce worst case+ faster than classix+ no addinal memory req
// dis: recusrtion can lead to stack overflow for large arrays
// edge case: all element me o of nsquare lagta to compare every element and single element me sidha termination

