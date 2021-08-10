#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std::chrono;
using namespace std;

void insertion_sort(int arr[], int n) {

    int i, j, num;

    // Adds a new element to the already sorted part of array
    for (i=1; i<n; i++) {

        j=i-1;
        num = arr[i];

        // Iterating over all elements bigger than the new element
        while (j>=0 && arr[j]>num) {
            // Shifting element forward
            arr[j+1] = arr[j];
            j--;
        }

        // Inserting the new element in position
        arr[j+1] = num;
    }

    return;
}

void selection_sort(int arr[], int n) {

    int i, j, idx, temp;

    // Adds a new minimum to the sorted part every time
    for (i=0; i < n-1; i++) {

        // Iterating through the unsorted part
        for (j=i+1, idx=i; j<n; j++) {

            if (arr[j] < arr[idx]) {
                // Swap minimum number with the first one
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }

        }

    }
}

enum complexity {BEST=1, WORST=2, AVERAGE=3} comp;

int main () {
    int n[] = {10, 100, 200, 500, 1000, 2000, 5000, 10000};

    int *arr1, *arr2, index, x;
    long long sel_sort, ins_sort;
    srand (time(0));

    // Taking input
    cout << "Which complexity do you want?" << endl;
    cout << "1. Best case" << endl;
    cout << "2. Worst case" << endl;
    cout << "3. Average case" << endl;
    cout << "Enter your response: ";
    cin >> x;
    comp = static_cast <complexity> (x);

    // Looping over all values of n (size of array)
    for (int j=0; j<8; j++) {

		ins_sort = 0;
		sel_sort = 0;

		cout << "Values for n = " << n[j] << "\t";

        // Taking average of five values for each value of n
        for (int k=0; k<1000; k++) {

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
                selection_sort(arr1, n[j]);
            }

            // Mid step
            auto mid = high_resolution_clock::now();

            {
                // Performs INSERTION SORT
                insertion_sort(arr2, n[j]);
            }

            // Ending clock
            auto stop = high_resolution_clock::now();

            // Finding the time required from differences
            auto sel = duration_cast <nanoseconds> (mid-start).count();
            auto ins = duration_cast <nanoseconds> (stop-mid).count();

			sel_sort += sel;
			ins_sort += ins;

            delete [] arr1;
            delete [] arr2;

        }

        cout << "Selection Sort: " << sel_sort/1000 << " nanoseconds" << endl;
        cout << "\t\t\tInsertion Sort: " << ins_sort/1000 << " nanoseconds" << endl;

    }

    return 0;
}
