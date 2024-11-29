#include <iostream>
#include <cstdlib>

using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int randomizedPartition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

int randomizedSelect(int arr[], int low, int high, int i) {
    if (low == high) {
        return arr[low];
    }

    int pivotIndex = randomizedPartition(arr, low, high);
    int k = pivotIndex - low + 1;

    if (i == k) {
        return arr[pivotIndex];
    } else if (i < k) {
        return randomizedSelect(arr, low, pivotIndex - 1, i);
    } else {
        return randomizedSelect(arr, pivotIndex + 1, high, i - k);
    }
}

void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int n, i;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter the elements of the array:\n";
    for (int j = 0; j < n; j++) {
        cin >> arr[j];
    }

    cout << "Enter the value of i (to find the i-th smallest element): ";
    cin >> i;

    if (i < 1 || i > n) {
        cout << "Invalid input! i should be between 1 and " << n << ".\n";
        return 1;
    }

    srand(0);
    int ithSmallest = randomizedSelect(arr, 0, n - 1, i);

    cout << "The " << i << "-th smallest element is: " << ithSmallest << endl;

    return 0;
}

