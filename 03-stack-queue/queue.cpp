#include <iostream>
#define SIZE 10
using namespace std;

class Queue {

    int * arr;
    int head, tail, siz;

public:

    Queue (int s=SIZE) {
        siz = s;
        head = tail = 0;
        arr = new int [siz];
    }

    int size () {
        return (tail-head+siz)%siz;
    }
    bool empty () {
        return head == tail;
    }
    void enqueue (int x) {
        if ((tail+1)%siz == head) {
            siz += SIZE;

            int * temp = new int [siz];
            for (int i=0, j=0; i<siz; i++, j++) {

                if (j == head)
                    head = i;
                else if (j == tail)
                    tail = i;

                if (i == tail)
                    i += SIZE;
                temp[i] = arr[j];
            }

            delete arr;
            arr = temp;
            cout << "Queue size increased to: " << siz << endl;;
        }
        arr[tail++] = x;
        tail = tail%siz;
    }
    int dequeue () {
        if (empty()) {
            cout << "Queue is empty!" << endl;
            return 0;
        }
        else {
            int temp = arr[head++];
            head %= siz;
            return temp;
        }
    }
    int * front() {
        if (empty()) {
            cout << "Queue is empty!" << endl;
            return 0;
        }
        else {
            return &arr[head];
        }
    }
    int * rear() {
        if (empty()) {
            cout << "Queue is empty!" << endl;
            return 0;
        }
        else {
            return &arr[tail-1];
        }
    }
    void show () {
        cout << "The Queue: ";
        for (int i=head; i!=tail; i=(i+1)%siz) {
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << "head=" << head << ", tail=" << tail << endl;
    }

};

int main () {

    Queue q;
    int c, temp, n, *loc;

    while(1) {

        cout << "1: Enqueue" << endl;
        cout << "2: Dequeue" << endl;
        cout << "3: Front" << endl;
        cout << "4: Rear" << endl;
        cout << "5: Size" << endl;
        cout << "6: Empty" << endl;
        cout << "7: Show" << endl;
        cout << "0: Exit" << endl;

        cin >> c;

        if(c == 1) {
            cin >> temp;
            q.enqueue(temp);
            q.show();
        }
        else if(c == 2) {
            temp = q.dequeue();
            if (temp)
                cout << "Popped element: " << temp << endl;
            q.show();
        }
        else if(c == 3) {
            loc = q.front();
            if (loc)
                cout << "Front element: " << *loc << endl;
        }
        else if(c == 4) {
            loc = q.rear();
            if (loc)
                cout << "Rear element: " << *loc << endl;
        }
        else if(c == 5) {
            cout << "Size of the stack: " << q.size() << endl;
        }
        else if (c == 6) {
            if (q.empty())
                cout << "Queue is empty!" << endl;
            else
                cout << "Queue is NOT empty" << endl;
        }
        else if (c == 7) {
            q.show();
        }
        else if(c == 0) {
            n = q.size();
            cout << "Elements : " << endl;

            for(int i=0; i<n; i++) {
                cout << q.dequeue() << endl;
            }
            break;
        }

    }

    return 0;

}
