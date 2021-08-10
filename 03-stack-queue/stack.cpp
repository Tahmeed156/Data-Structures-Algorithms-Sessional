#include <iostream>
#define SIZE 10
using namespace std;

class Stack {

    int siz;
    int * arr;
    int pos;

public:

    Stack (int s=SIZE) {
        siz = SIZE;
        pos = 0;
        arr = new int[SIZE];
    }

    int pop () {
        if (pos == 0) {
            cout << "Stack is empty!" << endl;
            return 0;
        }
        else {
            return arr[--pos];
        }
    }

    void push (int x) {

        arr[pos++] = x;

        if (pos == siz) {
            // Increase array size
            siz += SIZE;
            int *temp = new int[siz];
            for (int i=0; i<pos; i++)
                temp[i] = arr[i];
            delete arr;
            arr = temp;
            cout << "Stack size increased to: " << siz << endl;
        }
    }

    bool empty () {
        return !pos;
    }

    int size () {
        return pos;
    }

    int *top () {
        if (empty()) {
            cout << "Stack is empty!" << endl;
            return 0;
        }
        else {
            return &arr[pos-1];
        }
    }

    void show () {
        cout << "The stack: ";
        for (int i=0; i<pos; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

};

int main () {

    Stack mainstack;
    int c, temp, n, *loc;

    while(1) {

        cout << "1: Push" << endl;
        cout << "2: Pop" << endl;
        cout << "3: Top" << endl;
        cout << "4: Size" << endl;
        cout << "5: Empty" << endl;
        cout << "6: Show" << endl;
        cout << "0: Exit" << endl;

        cin >> c;

        if(c == 1) {
            cin >> temp;
            mainstack.push(temp);
            mainstack.show();
        }
        else if(c == 2) {
            temp = mainstack.pop();
            if (temp)
                cout << "Popped element: " << temp << endl;
            mainstack.show();
        }
        else if(c == 3) {
            loc = mainstack.top();
            if (loc)
                cout << "Top element: " << *loc << endl;
        }
        else if(c == 4) {
            cout << "Size of the stack: " << mainstack.size() << endl;
        }
        else if (c == 5) {
            if (mainstack.empty())
                cout << "Stack is empty!" << endl;
            else
                cout << "Stack is NOT empty" << endl;
        }
        else if (c == 6) {
            mainstack.show();
        }
        else if(c == 0) {
            n = mainstack.size();
            cout << "Elements : " << endl;

            for(int i=0; i<n; i++) {
                cout << mainstack.pop() << endl;
            }
            break;
        }

    }

    return 0;

}
