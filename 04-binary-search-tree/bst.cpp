#include <iostream>
using namespace std;

class Node {

public:

    Node * left;
    Node * right;
    Node * p;
    int key;

    Node () {
        p = NULL, left = NULL, right = NULL;
    }

    Node (int n) {
        key = n;
        p = NULL, left = NULL, right = NULL;
    }

    Node (int n, Node * parent) {
        key = n;
        p = parent, left = NULL, right = NULL;
    }


};

class BST {

    Node * head;

public:

    BST () {
        head = NULL;
    }

    BST (int n) {
        head = new Node(n);
    }

    bool sch(int n) {

        Node *cur = head;

        while (cur != NULL) {
            // Till iterator hits a null node
            if (n < cur->key) {
                cur = cur->left;
            }
            else if (n > cur->key) {
                cur = cur->right;
            }
            else if (n == cur->key) {
                return true;
            }
        }
        return false;
    }

    void ins (int n) {

        Node *prev=NULL, *cur = head;
        enum position {LEFT=1, RIGHT=2} pos;

        while (cur != NULL) {
            // Previous pointer
            prev = cur;
            // Till iterator hits a null node
            if (n < cur->key) {
                cur = cur->left;
                pos = LEFT;
            }
            else if (n > cur->key) {
                cur = cur->right;
                pos = RIGHT;
            }
            else if (n == cur->key) {
                cout << "Number already present!" << endl;
                return;
            }
        }
        cur = new Node(n, prev);
        if (prev == NULL) {
            head = cur;
            return;
        }
        else if (pos == LEFT) {
            prev->left=cur;
        }
        else {
            prev->right=cur;
        }

    }

    void del (int n) {

        Node *cur = head;
        enum position {LEFT=1, RIGHT=2} pos;

        while (cur != NULL) {
            // Till iterator hits a null node
            if (n < cur->key) {
                cur = cur->left;
                pos = LEFT;
            }
            else if (n > cur->key) {
                cur = cur->right;
                pos = RIGHT;
            }
            else if (n == cur->key) {
                rem(cur, cur->p);
                cout << "Number Deleted" << endl;
                delete cur;
                return;
            }
        }
        cout << "Number not present :(" << endl;

    }

    void rem (Node * cur, Node * prev) {
        if (cur->left == NULL) {
            // cout << "LEFT node NULL" << endl;

            if (cur->right != NULL)
                cur->right->p = prev;

            if (prev == NULL) {
                // Tree is empty
                head = cur->right;
                return;
            }
            else if (prev->left == cur) {
                prev->left = cur->right;
            }
            else {
                prev->right = cur->right;
            }
        }
        else if (cur->right == NULL) {
            // cout << "RIGHT node NULL" << endl;

            cur->left->p = prev;

            if (prev == NULL) {
                // Tree is empty
                head = cur->left;
                return;
            }
            if (prev->left == cur) {
                prev->left = cur->left;
            }
            else {
                prev->right = cur->left;
            }
        }
        else {
            cout << "NO nodes NULL" << endl;

            // Finding the minimum from right (successor)
            Node * temp = cur->right;
            while (temp->left != NULL)
                temp = temp->left;
            // Pointing new node to parent of current node
            temp->p = prev;

            // trans(cur, temp);
            if (prev == NULL) {
                // Tree is empty
                head = temp;
            }
            else if (prev->left == cur) {
                prev->left = temp;
            }
            else {
                prev->right = temp;
            }

            temp->left = cur->left;
            temp->left->p = temp;

        }

    }

    void inorderTraversal (Node *ptr=NULL) {

        // In the first call to the function
        if (ptr==NULL) {
            cout << "Inorder Traversal: " << endl;
            ptr = head;
        }

        // Recursively call all left nodes
        if (ptr->left != NULL)
            inorderTraversal(ptr->left);
        // Display your own data
        cout << ptr->key << " ";
        // Recursively call all right nodes
        if (ptr->right != NULL)
            inorderTraversal(ptr->right);

    }

    void preorderTraversal (Node *ptr=NULL) {

        // In the first call to the function
        if (ptr==NULL) {
            cout << "Pre-order Traversal: " << endl;
            ptr = head;
        }

        // Display your own data
        cout << ptr->key << " ";
        // Recursively call all left nodes
        if (ptr->left != NULL)
            inorderTraversal(ptr->left);
        // Recursively call all right nodes
        if (ptr->right != NULL)
            inorderTraversal(ptr->right);

    }

};

int main () {

    BST b;

    int x=1, inp;

    while (x != 0) {

        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Search" << endl;
        cout << "4. Inorder Traversal" << endl;
        cout << "5. Preorder Traversal" << endl;
        cin >> x;

        if (x == 1) {
            cin >> inp;
            b.ins(inp);
        }
        else if (x == 2) {
            cin >> inp;
            b.del(inp);
            b.inorderTraversal();
            cout << endl;
        }
        else if (x == 3) {
            cin >> inp;
            if (b.sch(inp))
                cout << "Number Found!" << endl;
            else
                cout << "Number not present :(" << endl;

        }
        else if (x == 4) {
            b.inorderTraversal();
            cout << endl;
        }
        else if (x == 5) {
            b.preorderTraversal();
            cout << endl;
        }
    }

    return 0;

}
