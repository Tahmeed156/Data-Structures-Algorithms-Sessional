#include <bits/stdc++.h>
#define INF 99999
#define NIL -99999
using namespace std;


class Node {

public:

    Node * p;
    int key;
    int degree;
    Node * child;
    Node * sibling;

    Node (int _k) {
        p = NULL;
        child = NULL;
        sibling = NULL;
        degree = 0;
        key = _k;
    }

};

class BinomialHeap {

public:

    Node * head;

    BinomialHeap () {
        head=NULL;
    }

    BinomialHeap (Node * x) {
        head = x;
    }

    BinomialHeap (int k) {
        head = new Node(k);
    }

    // ====== UNION

    Node * binomialHeapMerge (BinomialHeap *h1, BinomialHeap *h2) {

        Node * p = h1->head;
        Node * q = h2->head;
        Node * prev = NULL;

        Node * head = NULL;
        if (p->degree <= q->degree) {
            head = p;
            prev = head;
            p = p->sibling;
        }
        else {
            head = q;
            prev = head;
            q = q->sibling;
        }
    //    cout << "head = " << head->key << endl;

        while (p != NULL || q != NULL) {
    //        if (p)
    //            cout <<"p = " << p->key << endl;
    //        if (q)
    //            cout << "q = " << q->key << endl;

            if (q==NULL || (p!=NULL && p->degree <= q->degree)) {
                prev->sibling = p;
                prev = p;
                p = p->sibling;
            }
            else {
                prev->sibling = q;
                prev = q;
                q = q->sibling;
            }
        }

        BinomialHeap *h = new BinomialHeap(head);
        return h->head;

    }

    void binomialLink (Node *y, Node *z) {
        y->p = z;
        y->sibling = z->child;

        z->child = y;
        z->degree = z->degree + 1;
    }

    void binomialHeapUnion (BinomialHeap * h1) {

        if (this->head == NULL) {
            head = h1->head;
            return;

        }
        if (h1->head == NULL) {
            // head = this->head;
            return;
        }

        head = binomialHeapMerge(this, h1);

        Node * prev = NULL;
        Node * cur = head;
        Node * next = cur->sibling;

        while (next != NULL) {

            if ((cur->degree != next->degree) ||
                (next->sibling != NULL && next->sibling->degree == cur->degree)) {
    //            cout << "case 1, 2" << endl;
                prev = cur;
                cur = next;
            }
            else {
                if (cur->key <= next->key) {
    //                cout << "case 3" << endl;
                    cur->sibling = next->sibling;
                    binomialLink(next, cur);
                }
                else {
    //                cout << "case 4" << endl;
                    if (prev == NULL)
                        head = next;
                    else
                        prev->sibling = next;

                    binomialLink(cur, next);
                    cur = next;
                }
            }
            next = cur->sibling;
        }
    }

    // ====== BASIC FUNCTIONS

    void insertHeap (int x) {
        BinomialHeap *h1 = new BinomialHeap(x);
        binomialHeapUnion(h1);
    }

    int findMin () {
        Node * y;
        int minimum = INF;

        for (Node *x=head; x != NULL; x=x->sibling) {
            if (x->key < minimum) {
                minimum = x->key;
                y = x;
            }
        }
        return minimum;
    }

    int extractMin () {

        // find min
        Node *x=NULL, *y=NULL, *yPrev=NULL, *xPrev=NULL;
        int minimum = INF;

        for (x=head; x != NULL; x=x->sibling) {
            if (x->key < minimum) {
                minimum = x->key;
                y = x;
                yPrev = xPrev;
            }
            xPrev = x;
        }

        // remove from root-list
        if (yPrev != NULL)
            yPrev->sibling = y->sibling;
        else
            head = y->sibling;

        // reverse order of children
        Node *cur = y->child;
        Node *prev = NULL;
        Node *next = NULL;

        while (cur != NULL) {
            next = cur->sibling;
            cur->sibling = prev;
            prev = cur;
            cur = next;
        }

        // new binomial-heap with children
        BinomialHeap *h1 = new BinomialHeap(cur);
        h1->head = prev;

        // union
        binomialHeapUnion(h1);

        return y->key;
    }

    // ====== I/O FUNCTIONS

    void printTrees (Node *n, int level, vector <int> * keys) {

        keys[level].push_back(n->key);

        if (n->child != NULL)
            printTrees(n->child, level+1, keys);

        if (n->sibling != NULL)
            printTrees(n->sibling, level, keys);

    }

    void printHeap () {

        cout << "Printing Binomial Heap..." << endl;

        for (Node *root = head; root!=NULL; root=root->sibling) {
            cout << "Binomial Tree, B" << root->degree << endl;

            // data structure to store nodes by levels
            vector <int> * keys;
            keys = new vector <int> [root->degree];

            // Recursively storing nodes
            if (root->child != NULL)
                printTrees(root->child, 0, keys);

            // Printing the heap
            cout << "Level 0 : " <<root->key << " " << endl;

            for (int i=0; i < root->degree; i++) {
                cout << "Level " << i+1 << " : ";

                for (int j=0; j<keys[i].size(); j++) {
                    cout << keys[i][j] << " ";
                }
                cout << endl;
            }
        }
    }

};


// ====== MAIN

int main () {

    string file = "../test/moodle/in1.txt";
    BinomialHeap * h = new BinomialHeap();

    char inp;
    int x;
    ifstream fin;

    fin.open(file, ios::in);

    // Vertices & Edges
    while (!fin.eof()) {

        fin >> inp;

        if (inp == 'F') {
            x = h->findMin();
            cout << "Find-min returned " << x << endl;
        }
        else if (inp == 'I') {
            fin >> x;
            h->insertHeap(x);
        }
        else if (inp == 'U') {
            BinomialHeap *h1 = new BinomialHeap();

            streampos oldpos;

            while (fin >> x) {
                h1->insertHeap(x);
                oldpos = fin.tellg();
            }
            fin.clear();
            fin.seekg(oldpos);

            h->binomialHeapUnion(h1);
        }
        else if (inp == 'E') {
            x = h->extractMin();
            cout << "Extract-min returned " << x << endl;
        }
        else if (inp == 'P') {
            h->printHeap();
        }
        else {
            break;
        }

        inp = ' ';
    }

    fin.close();

}
