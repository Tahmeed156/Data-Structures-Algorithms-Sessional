#include <iostream>
using namespace std;
#define SIZE 10

class DisjointSet {

    int n;
    int * parents;
    int * ranks;

public:

    DisjointSet(int a=SIZE) {

        n = a+1;
        parents = new int [n+1];
        ranks = new int [n+1];

        for (int i=0; i<n; i++) {
            parents[i] = -1; // Indicates no parent
            ranks[i] = -1; // Indicates no existence
        }
    }

    ~DisjointSet() {
        delete [] parents;
        delete [] ranks;
    }

    //  ==================   OPERATIONS

    void makeSet(int a) {

        if (parents[a] < 0) {
            parents[a] = a;
            ranks[a] = 0;
        }
        else {
            cout << "Set already present :(" << endl;
        }
    }

    int findSet(int a) {

        if (parents[a] != a && parents[a] != -1)
            parents[a] = findSet(parents[a]);
        return parents[a];
    }

    void uni(int a, int b) {

        int repA = findSet(a);
        int repB = findSet(b);

        if (repA == repB) {
            cout << "No union necessary :(";
        }
        else {
            if (ranks[repA] == ranks[repB]) {
                ranks[repA]++;
            }

            if (ranks[repA] > ranks[repB]) {
                parents[repB] = repA;
            }
            else {
                parents[repA] = repB;
            }
        }
    }

    void print(int a) {
        a = parents[a];
        cout << "Elements: ";
        for (int i=0; i<n; i++) {
            if (findSet(i) == a)
                cout << i << " ";
        }
        cout << endl;
    }

    void printAll() {
        cout << "Element: ";
        for (int i=0; i<n; i++) {
            if (parents[i] > 0)
                cout << i << " ";
        }
        cout << endl;
        cout << "Parent : ";
        for (int i=0; i<n; i++) {
            if (parents[i] > 0)
                cout << parents[i] << " ";
        }
        cout << endl;
        cout << "Rank   : ";
        for (int i=0; i<n; i++) {
            if (parents[i] > 0)
                cout << ranks[i] << " ";
        }
        cout << endl << endl;
    }

};

int main () {

    cout << "Initializing Disjoint Set ...\n";
    DisjointSet D;
    int x, y;
    cout << "Setup Complete!\n\n";

    while (true) {

        cout << "What shall I do now?" << endl;
        cout << "1. Make Set" << endl;
        cout << "2. Find Set" << endl;
        cout << "3. Union" << endl;
        cout << "4. Print" << endl;
        cout << "5. Exit\n" << endl;

        cin >> x;

        switch (x) {

            case 1: { // Make Set a
                cout << "Enter element: ";
                cin >> x;
                D.makeSet(x);
                cout << "New set Created" << endl;
                break;
            }
            case 2: { // Find Set a
                cout << "Enter element: ";
                cin >> x;
                cout << "Set: " << D.findSet(x) << endl;
                break;
            }

            case 3: { // Union a, b
                cout << "Enter a, b: ";
                cin >> x >> y;
                D.uni(x, y);
                cout << "Sets united!\n";
                break;
            }

            case 4: { // Print a

                cout << "Enter element: ";
                cin >> x;
                D.print(x);
                break;
            }

            case 5: {
                return 0;
            }

        }

        cout << endl;
        D.printAll();

    }

    return 0;
}
