#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std::chrono;
using namespace std;

int linear_search_tmd (int x, int arr [], int n) {
    int loc = -1;

    for (int i=0; i<n; i++) {
        if (arr[i] == x) {
            loc = i;
            break;
        }
    }
    return loc;
}


int binary_search_tmd (int x, int arr [], int n) {

    int i=0, j=n-1;
    int m, loc = -1;
    while (i<=j) {
        m = (i+j)/2;
        if (arr[m] == x) {
            loc = m;
            break;
        }
        else if (arr[m] > x) {
            j = m-1;
        }
        else {
            i = m+1;
        }
    }
    return loc;
}

int main () {
    int n[] = {10, 100, 200, 500, 1000, 2000, 5000, 10000};

    int *arr, index;
    int dur_lin, dur_bin;
    srand (time(0));

    // Looping over all values of n (size of array)
    for (int j=0; j<8; j++) {

		dur_lin = 0;
		dur_bin = 0;

		cout << "Values for n=" << n[j] << endl;

        // Taking average of five values for each value of n
        for (int k=0; k<1000; k++) {

            // Filing the array with numbers
            arr = new int [n[j]];
            arr[0] = 1;
            for (int i=1; i<n[j]; i++) {
                arr[i] = arr[i-1] + rand()%10 + 1;
            }

            // Randomly generating a number to search for
            int number = rand()%100;

            // Starting clock and the searching process
            auto start = high_resolution_clock::now();

            {
                // Perform LINEAR SEARCH
                index = linear_search_tmd(number, arr, n[j]);
            }

            // Mid step
            auto mid = high_resolution_clock::now();

            {
                // Perform BINARY SEARCH
                index = binary_search_tmd(number, arr, n[j]);
            }

            // Ending clock
            auto stop = high_resolution_clock::now();

            // Finding the time required from differences
            auto lin = duration_cast <nanoseconds> (mid-start).count();
            auto bin = duration_cast <nanoseconds> (stop-mid).count();

			dur_lin += lin;
			dur_bin += bin;

            delete [] arr;

        }

        cout << "Linear time: " << dur_lin/1000 << endl;
        cout << "Binary time: " << dur_bin/1000 << endl;

    }

    return 0;
}

