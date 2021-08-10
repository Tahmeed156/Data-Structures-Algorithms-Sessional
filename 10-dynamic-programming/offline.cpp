#include <iostream>
using namespace std;

int max (int a, int b) {
    return (b > a) ? b: a;
}

int ** lengthLCS(string x, string y) {

    int lenX = x.length();
    int lenY = y.length();

    // Initializing 2D array
    int ** c = new int * [lenX+1];
    for (int i=0; i<=lenX; i++)
        c[i] = new int [lenY+1];

    // First element of every row -> 0
    for (int i=0; i<=lenX; i++)
        c[i][0] = 0;
    // Every element of first row -> 0
    for (int j=0; j<=lenY; j++)
        c[0][j] = 0;

    for (int i=1; i<=lenX; i++) {

        for (int j=1; j<=lenY; j++) {
            // Increase number if same character
            if (x[i-1] == y[j-1])
                c[i][j] = c[i-1][j-1] + 1;
            // Otherwise choose max
            else
                c[i][j] = max(c[i-1][j], c[i][j-1]);
        }
    }

    return c;
}

void printLCS (int ** l, string x, string y, int i, int j) {

    if (i==0 || j==0)
        return;

    if (x[i-1] == y[j-1]) {
        printLCS(l, x, y, i-1, j-1);
        cout << x[i-1];
    }
    else {
        if (l[i][j-1] >= l[i-1][j])
            printLCS(l, x, y, i, j-1);
        else
            printLCS(l, x, y, i-1, j);
    }
}

void printLength(int ** lengths, string a, string b) {

    int lenA = a.length();
    int lenB = b.length();

    cout << "\nThe length matrix: \n";

    cout << "  Y ";
    for (int i=0; i<lenB; i++) {
        cout << b[i] << " ";
    }
    cout << endl << "X ";
    for (int j=0; j<=lenB; j++)
        cout << lengths[0][j] << " ";
    cout << endl;
    for (int i=1; i<=lenA; i++) {
        cout << a[i-1] << " ";
        for (int j=0; j<=lenB; j++)
            cout << lengths[i][j] << " ";
        cout << endl;
    }
    cout << endl;

}

int main () {

    string a, b;
    cout << "STRING a: ";
    cin >> a;    cout << "STRING b: ";
    cin >> b;

    // Gets the length 2D array
    int ** lengths = lengthLCS(a, b);

    printLength(lengths, a, b);

    cout << "Solution: ";
    printLCS(lengths, a, b, a.length(), b.length());
    cout << endl;

    return 0;
}
