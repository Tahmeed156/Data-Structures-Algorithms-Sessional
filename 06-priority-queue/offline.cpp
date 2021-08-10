#include <iostream>
#define MAX 10
using namespace std;

class PriorityQ {

    int *arr;
    int len;

public:

    PriorityQ() {
        arr = new int [MAX+1];
        arr[0] = -1;
        len = 0;
    }

    int FindMax() {
        if (len == 0) {
            cout << "No element present :(" << endl;
            return -1;
        }
        else {
            return arr[1];
        }
    }

    int ExtractMax() {
        if (len == 0) {
            cout << "No element present" << endl;
            return -1;
        }
        else {
            int num = arr[1];
            arr[1] = arr[len--];
            Heapify(1);
            return num;
        }
    }

    int getKey(int i) {
        return arr[i];
    }

    void IncreaseKey(int i, int key) {
        if (key < arr[i]) {
            cout << "New key is smaller :(" << endl;
        }
        else {
            arr[i] = key;
            // Loop until no parent left
            while (i>1 && arr[i/2]<arr[i]) {
                // Exchange key with parent
                exchange(&arr[i/2], &arr[i]);
                i /= 2;
            }
        }
    }

    void exchange(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    void DecreaseKey(int i, int key) {
        if (key > arr[i]) {
            cout << "New key is greater :(" << endl;
        }
        else {
            arr[i] = key;
            Heapify(i);
        }
    }

    int left(int i) {
        return 2*i;
    }

    int right(int i) {
        return 2*i + 1;
    }

    void Heapify(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if ( l<=len && arr[l]>arr[i] )
            largest = l;
        if ( r<=len && arr[r]>arr[largest] )
            largest = r;
        if (largest != i) {
            exchange(&arr[i], &arr[largest]);
            Heapify(largest);
        }
    }

    void ins (int key) {
        if (len == MAX) {
            // The turn when array becomes full
            int * temp = new int [len+MAX+1];
            for (int i=0; i<=len; i++) {
                temp[i] = arr[i];
            }

            delete [] arr;
            arr = temp;
        }
        // Adds an element to the last of queue
        arr[++len] = key-1;
        // Bottom-up approach
        IncreaseKey(len, key);
    }

    void Print() {
        cout << "The Priority Queue: " << endl;
        for (int i=1; i<=len; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void Size() {
        cout << "Size: " << len << endl;
    }

};

int main(void)
{
    cout << "Setting up a priority queue ..." << endl;
    PriorityQ Q;
    int a, b;
    cout << "Setup complete!\n";

    while(1)
    {
        cout << "\n1. Insert \n";
        cout << "2. Find Max \n";
        cout << "3. Extract Max \n";
        cout << "4. Increase Key \n";
        cout << "5. Decrease Key \n";
        cout << "6. Print \n";
        cout << "0. Quit \n\n";

        int ch;
        cin >> ch;

        if(ch==1)
        {
            cin >> a;
            Q.ins(a);
            Q.Print();
        }
        else if(ch==2)
        {
            cout << "The maximum: " << Q.FindMax() << endl;
        }
        else if(ch==3)
        {
            cout << "The maximum: " << Q.ExtractMax() << endl;
            Q.Print();
        }
        else if (ch == 4)
        {
            cin >> a;
            cout << "Increase key from " << Q.getKey(a) << " to: ";
            cin >> b;
            Q.IncreaseKey(a, b);
            Q.Print();
        }
        else if(ch==5)
        {
            cin >> a;
            cout << "Decrease key from " << Q.getKey(a) << " to: ";
            cin >> b;
            Q.DecreaseKey(a, b);
            Q.Print();
        }
        else if (ch == 6) {
            Q.Print();
        }
        else if (ch == 7)
        {
            break;
        }
        else if (ch == 0) {
            break;
        }
        else
        {
            Q.Print();
            Q.Size();
        }

    }

}

