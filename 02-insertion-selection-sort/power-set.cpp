#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std::chrono;
using namespace std;

int n;

void insertion_sort(char arr[], int n) {

    int i, j;
    char num;

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


void powerset_generation(char arr[], char sub[], int i, int p) {

    // Breaking the loop
    if (i == n) {
        sub[p] = '\0';
        // cout << "{" << sub << "}" << endl;
        return;
    }
    sub[p] = arr[i];
    powerset_generation(arr, sub, i+1, p+1);
    // Skipping same characters
    while (arr[i] == arr[i+1])
        i++;
    powerset_generation(arr, sub, i+1, p);
    return;

}


int main () {

    srand (time(0));
    char *arr, *sub;
    int i, j, k;
    long long pow_time=0;

    for (n=0; n<30; n++) {

        // Generating an array of characters
        arr = new char[n];
        sub = new char[n];

        for (i=0; i<n; i++) {

            // Choosing between 0-9, A-Z, a-z
            j = rand()%3;

            if (j == 0)
                arr[i] = rand()%10 + '0';
            else if (j == 1)
                arr[i] = rand()%26 + 'A';
            else if (j == 2)
                arr[i] = rand()%26 + 'a';

        }

        // Sorting characters to generate unique subsets
        insertion_sort(arr, n);

        auto start = high_resolution_clock::now();
        powerset_generation(arr, sub, 0, 0);
        auto stop = high_resolution_clock::now();

        // Finding the time required from differences
        auto time = duration_cast <nanoseconds> (stop-start).count();
        pow_time += time;

        delete [] arr;
        delete [] sub;

        cout << "For n = " << n << ", time taken : " << pow_time/100 << " nanoseconds" << endl;

    }

    return 0;
}
