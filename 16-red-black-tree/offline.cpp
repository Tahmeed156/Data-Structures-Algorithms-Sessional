#include <bits/stdc++.h>
#define INF 99999

char RED = 'r';
char BLACK = 'b';

using namespace std;


class Node {

public:

    Node * left;
    Node * right;
    Node * p;
    int key;
    char color;

    Node () {
        key = INF;
        color = BLACK;
        p = this, left = this, right = this;
    }

    Node (int n, char c, Node * parent);

};

Node * nullNode = new Node();

Node::Node (int n, char c, Node * parent) {
    key = n;
    color = c;
    p = parent, left = nullNode, right = nullNode;
}


class RBT {

    Node * root;

public:

    RBT () {
        root = nullNode;
    }

    /// RBT Property Maintenance

    void delFixup (Node * x) {

        while (x->color == BLACK && root != x) {

            if (x == x->p->left) {
                Node * xp = x->p;
                Node * w = xp->right;

                if (w->color == RED) {
                    w->color = BLACK;
                    xp->color = RED;
                    leftRotate(xp);
                    w = xp->right;
                }


                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = xp;
                }
                else {

                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = xp->right;
                    }
                    w->color = xp->color;
                    xp->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(xp);
                    x = root;
                }
            }
            else {
                Node * xp = x->p;
                Node * w = xp->left;

                if (w->color == RED) {
                    w->color = BLACK;
                    xp->color = RED;
                    rightRotate(xp);
                    w = xp->left;
                }

                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = xp;
                }
                else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = xp->left;
                    }
                    w->color = xp->color;
                    xp->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(xp);
                    x = root;
                }
            }
        }

        x->color = BLACK;
    }

    void insertFixup (Node * z) {
        while (z->p->color == RED) {

            if (z->p->p->left == z->p) {
                Node * y = z->p->p->right;

                if (y->color == RED) {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                }
                else {
                    if (z == z->p->right) {
                        z = z->p;
                        leftRotate(z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    rightRotate(z->p->p);
                }
            }
            else {
                Node * y = z->p->p->left;

                if (y->color == RED) {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                }
                else {
                    if (z == z->p->left) {
                        z = z->p;
                        rightRotate(z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    leftRotate(z->p->p);
                }
            }
        }
        root->color = BLACK;
    }

    void leftRotate (Node * x) {
        Node * y = x->right;

        x->right = y->left;
        y->left->p = x;

        y->p = x->p;
        if (x->p == nullNode)
            root = y;
        else if (x->p->left == x)
            x->p->left = y;
        else
            x->p->right = y;

        y->left = x;
        x->p = y;

    }

    void rightRotate (Node * x) {

        Node * y = x->left;

        x->left = y->right;
        y->right->p = x;

        y->p = x->p;
        if (x->p == nullNode)
            root = y;
        else if (x->p->left == x)
            x->p->left = y;
        else
            x->p->right = y;

        y->right = x;
        x->p = y;

    }

    /// BST Functions

    Node * find (int n) {

        Node *cur = root;

        while (cur != nullNode) {

            if (n < cur->key)
                cur = cur->left;
            else if (n > cur->key)
                cur = cur->right;

            else if (n == cur->key)
                return cur;
        }

        return nullNode;
    }

    Node * del (Node * z) {
        Node * y, * x;
        if (z->left == nullNode || z->right == nullNode)
            y = z;
        else
            y = predecessor(z);

        if (y->left != nullNode)
            x = y->left;
        else
            x = y->right;

        x->p = y->p;
        if (y->p == nullNode)
            root = x;
        else if (y->p->left == y)
            y->p->left = x;
        else
            y->p->right = x;

        if (y != z)
            z->key = y->key;

        if (y->color == BLACK)
            delFixup(x);

        return y;
    }

    void insert (int n) {

        // y = parent/trailing node, x = testing node, z = new node
        Node *y = nullNode, *x = root, *z = new Node(n, RED, NULL);

        while (x != nullNode) {
            y = x;

            if (z->key < x->key) {
                x = x->left;
            }
            else if (z->key > x->key) {
                x = x->right;
            }
            else if (z->key == x->key) {
                cout << "Number already present!" << endl;
                return;
            }
        }

        z->p = y;
        if (y == nullNode) {
            root = z;
        }
        else if (z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }

        insertFixup (z);

    }

    Node * successor (Node * x) {
        if (x->right != nullNode) {
            x = x->right;
            while (x->left != nullNode)
                x = x->left;
            return x;
        }

        Node * y = x->p;
        while (y != nullNode && x == y->right) {
            x = y;
            y = y->p;
        }

        return y;
    }

    Node * predecessor (Node * x) {
        if (x->left != nullNode) {
            x = x->left;
            while (x->right != nullNode)
                x = x->right;
            return x;
        }

        Node * y = x->p;
        while (y != nullNode && x == y->left) {
            x = y;
            y = y->p;
        }

        return y;
    }

    /// I/O

    void printTree (Node *ptr=NULL) {

        if (ptr == NULL) {
            if (root == nullNode) {
                return;
            }
            else {
                ptr = root;
            }
        }

        cout << ptr->key << ":" << ptr->color;

        if (ptr->left == nullNode && ptr->right == nullNode)
            return;

        cout << "(";
        if (ptr->left != nullNode) {
            printTree(ptr->left);
        }
        cout << ")";

        cout << "(";
        if (ptr->right != nullNode) {
            printTree(ptr->right);
        }
        cout << ")";

    }

    void inputFile (string file) {

        char inp;
        int x;
        ifstream fin;


        fin.open(file, ios::in);

        // Vertices & Edges
        while (!fin.eof()) {

            fin >> inp;

            if (inp == 'F') {
                fin >> x;
                if (find(x) != nullNode)
                    cout << "True";
                else
                    cout << "False";
            }
            else if (inp == 'I') {
                fin >> x;
                insert(x);
                printTree();
            }
            else if (inp == 'D') {
                fin >> x;
                Node * z = find(x);
                del(z);
                printTree();
            }
            else {
                break;
            }

            cout << endl;
            inp = ' ';

        }


        fin.close();
    }

};

int main () {

    RBT b;
    b.inputFile("in.txt");

    return 0;
}

//
//int main () {
//
//    RBT b;
//
//    int x=1, inp;
//
//    while (x != 0) {
//
//        cout << "1. Insert" << endl;
//        cout << "2. Delete" << endl;
//        cout << "3. Find" << endl;
//        cout << "4. Left-Rotate" << endl;
//        cout << "5. Right-Rotate" << endl;
//        cin >> x;
//
//        if (x == 1) {
//            cin >> inp;
//            b.insert(inp);
//        }
//        else if (x == 2) {
//            cin >> inp;
//            Node * z = b.find(inp);
//            b.del(z);
//        }
//        else if (x == 3) {
//            cin >> inp;
//            if (b.find(inp) != nullNode)
//                cout << "True" << endl;
//            else
//                cout << "False" << endl;
//
//        }
//        else if (x == 4) {
//            cin >> inp;
//            Node * z = b.find(inp);
//            b.leftRotate(z);
//        }
//        else if (x == 5) {
//            cin >> inp;
//            Node * z = b.find(inp);
//            b.rightRotate(z);
//        }
//
//        b.printTree();
//        cout << endl;
//    }
//
//    return 0;
//
//}

