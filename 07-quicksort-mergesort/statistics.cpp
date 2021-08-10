#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>

using namespace std::chrono;
using namespace std;

#define INF 999999

void exchange(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

int partition_tmd(int arr[], int p, int q) {

    int j=p-1;

    // Setting the left side of pivot
    for (int i=p; i<=q; i++) {
        if (arr[i] < arr[q])
            exchange(&arr[++j], &arr[i]);
    }

    // Setting the pivot
    exchange(&arr[++j], &arr[q]);
    return j;
}

void quicksort_tmd(int arr[], int p, int q) {

    if (p < q) {
        // Fixes q as pivot and separates into two sections
        int mid = partition_tmd(arr, p, q);
        // Left part
        quicksort_tmd(arr, p, mid-1);
        // Right part
        quicksort_tmd(arr, mid+1, q);
    }

}

void merge_tmd(int arr[], int p, int q, int r) {

    int n = r-p+1;
    int n1 = q-p+1;
    int n2 = r-q;

    int arr_left[n1+1];
    for (int i=0; i<n1; i++) {
        arr_left[i] = arr[p+i];
    }

    int arr_right[n2+1];
    for (int j=0; j<n2; j++) {
        arr_right[j] = arr[q+1+j];
    }

    // Aids copying remaining elements
    arr_left[n1] = INF;
    arr_right[n2] = INF;

    for (int i=0, j=0; p<=r; p++) {

        if (arr_left[i] <= arr_right[j]) {
            arr[p] = arr_left[i++];
        }

        else {
            arr[p] = arr_right[j++];
        }

    }

}

void mergesort_tmd(int arr[], int p, int r) {
    if (p < r) {
        int q = (p+r)/2;
        mergesort_tmd(arr, p, q);
        mergesort_tmd(arr, q+1, r);
        merge_tmd(arr, p, q, r);
    }
}

enum complexity {BEST=1, WORST=2, AVERAGE=3} comp;

int main () {
    int n[] = {10, 100, 500, 1000, 4000, 8000, 10000, 15000, 35000, 50000};

    int *arr1, *arr2, index;
    int x;
    long long qck_sort, mer_sort;
    srand (time(0));

    // Taking input
    cout << "Which complexity do you want?" << endl;
    cout << "1. Sorted" << endl;
    cout << "2. Reverse Sorted" << endl;
    cout << "3. Random" << endl;
    cin >> x;
    comp = static_cast <complexity> (x);

    // Looping over all values of n (size of array)
    for (int j=0; j<10; j++) {

		mer_sort = 0;
		qck_sort = 0;

		cout << "Values for n = " << n[j] << "\n";

        // Taking average of five values for each value of n
        for (int k=0; k<100; k++) {

            // Filing the array with numbers
            if (comp == AVERAGE) {
                // Generating array numbers randomly
                arr1 = new int [n[j]];
                arr2 = new int [n[j]];
                for (int i=0; i<n[j]; i++) {
                    arr1[i] = rand()%10000;
                    arr2[i] = rand()%10000;
                }
            }
            else if (comp == WORST) {
                // Generating array in reverse order
                arr1 = new int [n[j]];
                arr2 = new int [n[j]];
                arr1[n[j]-1] = 1;
                arr2[n[j]-1] = 1;
                for (int i=n[j]-2; i>=0; i--) {
                    arr1[i] = arr1[i+1] + rand()%10 + 1;
                    arr2[i] = arr2[i+1] + rand()%10 + 1;
                }
            }
            else if (comp == BEST) {
                // Generating a sorted array
                arr1 = new int [n[j]];
                arr1[0] = 1;
                arr2 = new int [n[j]];
                arr2[0] = 1;
                for (int i=1; i<n[j]; i++) {
                    arr1[i] = arr1[i-1] + rand()%10 + 1;
                    arr2[i] = arr2[i-1] + rand()%10 + 1;
                }
            }

            // Starting clock and the searching process
            auto start = high_resolution_clock::now();

            {
                // Performs SELECTION SORT
                quicksort_tmd(arr1, 0, n[j]-1);
            }

            // Mid step
            auto mid = high_resolution_clock::now();

            {
                // Performs INSERTION SORT
                mergesort_tmd(arr2, 0, n[j]-1);
            }

            // Ending clock
            auto stop = high_resolution_clock::now();

            // Finding the time required from differences
            auto qck = duration_cast <nanoseconds> (mid-start).count();
            auto mer = duration_cast <nanoseconds> (stop-mid).count();

			qck_sort += qck;
			mer_sort += mer;

            delete [] arr1;
            delete [] arr2;

        }

        cout << "Quick Sort: " << qck_sort/100 << " nanoseconds" << endl;
        cout << "Merge Sort: " << mer_sort/100 << " nanoseconds" << endl;

    }

    return 0;
}

