#include <cstdio>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;

struct node {
    int value;
    node *left;
    node *right;
};

class BinarySearchTree {
    node *root;
    public:
    BinarySearchTree();
    bool isEmpty();
    void insert(int);
    void remove(int);
    void inOrder(node*);
    void printInOrder();
};

BinarySearchTree::BinarySearchTree () {
    root = NULL;
}

bool BinarySearchTree::isEmpty() {
    return root == NULL;
}

void BinarySearchTree::insert(int n) {
    node *newNode = new node;
    node *parent;
    newNode->value = n;
    newNode->left = NULL;
    newNode->right = NULL;
    parent = NULL;
    if (isEmpty()) {
        root = newNode;
        return;
    }
    node *curr = root;
    while(curr) {
        parent = curr;
        if (n > curr->value) curr = curr->right;
        else curr = curr->left;
    }
    if (n > parent->value) parent->right = newNode;
    else parent->left = newNode;
}

void BinarySearchTree::remove(int n) {
    bool found = false;
    if (isEmpty()) {
        printf("[!] %i could not be found as the tree was empty\n", n);
        return;
    }
    node *curr;
    node *parent;
    curr = root;
    while (curr != NULL) {
        if (curr->value == n) {
            found = true;
            break;
        } else {
            // search further down
            parent = curr;
            if (n > curr->value) curr = curr->right;
            else curr = curr-> left;
        }
    }
    if (!found) {
        printf("[!] %i could not be deleted as it was not found\n", n);
        return;
    }
    if (((curr->left == NULL) && (curr->right != NULL)) || ((curr->left != NULL) && (curr->right != NULL))) {
        // node has a single child
        if ((curr->left == NULL) && (curr->right != NULL)) {
            // right child; no left child
            if (parent->left == curr) {
                // parent was less than ancestor
                parent->left = curr->right;
                delete curr;
            } else {
                // parent was greater than ancestor
                parent->right = curr->right;
                delete curr;
            }
        } else {
            // left child; no right child
            if (parent->left == curr) {
                // parent was less than ancestor
                parent->left = curr->left;
                delete curr;
            } else {
                // parent was greater than ancestor
                parent->right = curr->left;
                delete curr;
            }
        }
    } else if ((curr->left != NULL) && (curr->right != NULL)) {
        // node has two children
        node *chk;
        chk = curr->right;
        if ((chk->left == NULL) && (chk->right == NULL)) {
            // right child has no children
            curr = chk;
            delete chk;
            curr->right = NULL;
        } else {
            // right child has children
            if ((curr->right)->left != NULL) {
                // right->left child present
                node *lcurr; // left current
                node *lcurrp; // left current's parent
                lcurrp = curr->right;
                lcurr = (curr->right)->left;
                while (lcurr->left != NULL) {
                    lcurrp = lcurr;
                    lcurr = lcurr->left;
                }
                // bubble up left child
                curr->value = lcurr->value;
                delete lcurr;
                lcurrp->left = NULL;
            } else {
                node *tmp;
                tmp = curr->right;
                curr->value = tmp->value;
                curr->right = tmp->right;
                delete tmp;
            }
        }
    } else {
        // node has no children
        delete curr;
    }
}

void BinarySearchTree::inOrder(node *n) {
    if (!n) return;
    inOrder(n->left);
    printf("[+] **Current node: %i** \n", n->value);
    inOrder(n->right);
}

void BinarySearchTree::printInOrder() {
    if (root == NULL) {
        printf("[!] Could not print as tree is empty!\n");
        return;
    }
    inOrder(root);
}

enum Operation {
    print,
    insert,
    _delete,
    _error,
    _exit,
    help
};

Operation hashOp(string s) {
    if (s == "print") return print;
    if (s == "insert") return insert;
    if (s == "delete") return _delete;
    if (s == "exit") return _exit;
    if (s == "help") return help;
    return _error;
}

void handlePrint(BinarySearchTree *bst) {
    stringstream ss;
    printf("[*] Preparing to print in order...\n");
    clock_t start;
    bst->printInOrder();
    ss << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << "ms";
    printf("[+] Print in order complete...\n");
    cout << "[*] Time: " << ss.str() << "; Traversals: " << 2 << endl;
}

void handleInsert(BinarySearchTree *bst) {
    int n;
    printf("[*] Please enter an integer to insert: ");
    scanf("%i", &n);
    bst->insert(n);
    printf("[+] Inserted %i to tree...\n", n);
    // todo time and output specs
}

void handleDelete(BinarySearchTree *bst) {
    int n;
    printf("[*] Please enter a valid number to delete: ");
    scanf("%i", &n);
    bst->remove(n);
    printf("[-] Removed %i from tree...\n", n);
    // todo time and output specs
}

void handleExit() {
    printf("Goodbye! (:\n\n");
    exit(0);
}

void handleHelp() {
    printf("[*] options include: print, insert, delete and exit...\n");
}

int main() {
    // setup binary search tree
    printf("Welcome the binary search tree playground...\n");
    BinarySearchTree bst;
    string input;
    while (true) {
        printf("[*] Please enter a command: ");
        cin >> input;
        Operation op = hashOp(input);
        switch (op) {
            case print:
                handlePrint(&bst);
                break;
            case insert:
                handleInsert(&bst);
                break;
            case _delete:
                handleDelete(&bst);
                break;
            case _exit:
                handleExit();
                break;
            default :
                printf("[!] Error\n");
        }
    }
    return 0;
}

