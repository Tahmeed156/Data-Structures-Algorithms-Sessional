#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

void printActivitiesData(int *a, int *b, int n) {
    cout << endl << "Activities :";
    for (int i=0; i<n; i++) {
        cout << setw(2) << i << " ";
    }
    cout << endl;
    cout << "Start time :";
    for (int i=0; i<n; i++) {
        cout << setw(2) << a[i] << " ";
    }
    cout << endl;
    cout << "End time   :";
    for (int i=0; i<n; i++) {
        cout << setw(2) << b[i] << " ";
    }
    cout << endl;
}

void printActivitiesVisual(int *a, int *b, int n) {
    cout << endl << "Acitivites: " << endl;
    for (int i=0; i<b[n-1]; i++) {
        cout << "-";
    }
    cout << endl;
    for (int i=0; i<n; i++) {
        cout << setw(a[i]) << i%10 << setw(b[i]-a[i]) << i%10 << endl;
    }
    for (int i=0; i<b[n-1]; i++) {
        cout << "-";
    }
    cout << endl;
}

void generateActivities(int *a, int *b, int n) {

    // Generates activities (1<=length<=5)
    // sorted by earliest finished time
    a[0] = 1, b[0] = 5;

    for (int i=1; i<n; i++) {
        b[i] = b[i-1] + rand()%5;
        a[i] = b[i] - rand()%4 - 2;
    }
}

int main () {

    int * startTime;
    int * endTime;
    int n;

    cout << "Enter number of activities: ";
    cin >> n;
    startTime = new int [n], endTime = new int [n];

    generateActivities(startTime, endTime, n);
    printActivitiesVisual(startTime, endTime, n);

    { // Activity Selection algorithm

        // Adding the first element into solution
        cout << "The first element: 0 ";

        for (int i=1, m=0; i<n; i++) {
            if (startTime[i] >= endTime[m]) {
                cout << i << " ";
                m = i;
            }
        }

    }

}
