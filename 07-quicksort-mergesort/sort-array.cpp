#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#define INF 999999

using namespace std::chrono;
using namespace std;

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

int main()
{
    int n, choice;
    int * arr;
    int iter=10;
    long long time_taken;

    while(1)
    {
        printf("1. Generate average case\n");
        printf("2. Generate best case\n");
        printf("3. Generate worst case\n");
        printf("4. Apply Merge sort\n");
        printf("5. Apply Quicksort\n");
        printf("6. Print array\n");
        printf("> ");
        scanf("%d", &choice);

        switch(choice) {

        case 1:
            //      ============================    AVERAGE CASE
            printf("Number of elements: ");
            scanf("%d", &n);

            // Generating array numbers randomly
            arr = new int [n];
            for (int i=0; i<n; i++) {
                arr[i] = rand()%1000;
            }

            break;

        case 2:
            //      ============================    BEST CASE
            printf("Number of elements: ");
            scanf("%d", &n);

            // Generating a sorted array
            arr = new int [n];
            arr[0] = 1;
            for (int i=1; i<n; i++) {
                arr[i] = arr[i-1] + rand()%10 + 1;
            }

            break;

        case 3:
            //      ============================    WORST CASE
            printf("Number of elements: ");
            scanf("%d", &n);

            arr = new int [n];
            arr[n-1] = 1;
            for (int i=n-2; i>=0; i--) {
                arr[i] = arr[i+1] + rand()%10 + 1;
            }

            break;

        case 4:
            {
                printf("Applying mergesort ... \n");

                mergesort_tmd(arr, 0, n-1);

                auto start = high_resolution_clock::now();
                printf("");
                auto stop = high_resolution_clock::now();

                auto time_taken = duration_cast <nanoseconds> (stop-start).count();

                cout << "Sorting Done! Time taken: " << time_taken << " nanoseconds" << endl;
            }

            break;

        case 5:
            {
                printf("Applying quicksort ... \n");

                quicksort_tmd(arr, 0, n-1);

                auto start = high_resolution_clock::now();
                printf("");
                auto stop = high_resolution_clock::now();

                auto time_taken = duration_cast <nanoseconds> (stop-start).count();

                cout << "Sorting Done! Time taken: " << time_taken << " nanoseconds" << endl;
            }

            break;

        case 6:
            printf("Array\n");

            for (int i=0; i<n; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");

            break;
        }
    }
}

// ONLINE COMPILER         https://www.onlinegdb.com/online_c_compiler

