#include <cstdio>
#include <iostream>
#include <ctime>

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
    int insert(int);
    int remove(int);
    bool contains(int);
    void inOrder(node*);
    void printInOrder();
};

BinarySearchTree::BinarySearchTree () {
    root = NULL;
}

bool BinarySearchTree::isEmpty() {
    return root == NULL;
}

int BinarySearchTree::insert(int n) {
    int nt = 0;
    node *newNode = new node;
    node *parent;
    newNode->value = n;
    newNode->left = NULL;
    newNode->right = NULL;
    parent = NULL;
    if (isEmpty()) {
        root = newNode;
        return 0;
    }
    node *curr = root;
    while(curr) {
        parent = curr;
        if (n > curr->value) curr = curr->right;
        else curr = curr->left;
        nt++;
    }
    if (n > parent->value) parent->right = newNode;
    else parent->left = newNode;
    return nt;
}

int BinarySearchTree::remove(int n) {
    int nt = 0;
    bool found = false;
    if (isEmpty()) {
        printf("[!] %i could not be found as the tree was empty\n", n);
        return 0;
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
            nt++;
        }
    }
    if (!found) {
        printf("\n[!] %i could not be deleted as it was not found\n", n);
        return nt;
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
        nt++;
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
        nt++;
    } else {
        // node has no children
        delete curr;
    }
    return nt;
}

bool BinarySearchTree::contains(int n) {
    bool found = false;
    if (isEmpty()) {
        printf("[!] %i could not be found as tree is empty!\n", n);
        return false;
    }
    node *curr;
    node *parent;
    curr = root;
    while (curr) {
        if (curr->value == n) {
            found = true;
            break;
        }
        parent = curr;
        if (curr->value < n) curr = curr->right;
        else curr = curr->left;
    }
    return found;
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
    _search,
    _delete,
    _error,
    _exit,
    clear,
    help
};

Operation hashOp(string s) {
    if (s == "print") return print;
    if (s == "insert") return insert;
    if (s == "search") return _search;
    if (s == "delete") return _delete;
    if (s == "clear") return clear;
    if (s == "exit") return _exit;
    if (s == "help") return help;
    return _error;
}

void handlePrint(BinarySearchTree *bst) {
    int n;
    long double t;
    clock_t begin, end;
    printf("[*] Preparing to print in order...\n");
    begin = clock();
    bst->printInOrder();
    end = clock();
    t = (long double)(end - begin) / CLOCKS_PER_SEC * 1000;
    printf("[+] Print in order complete...\n");
    printf("[*] Time: %Lfms\n", t);
}

void handleInsert(BinarySearchTree *bst) {
    int n, nt;
    long double t;
    clock_t begin, end;
    printf("[*] Please enter an integer to insert: ");
    scanf("%i", &n);
    begin = clock();
    nt = bst->insert(n);
    end = clock();
    t = (long double)(end - begin) / CLOCKS_PER_SEC * 1000;
    printf("[+] Inserted %i to tree...\n", n);
    printf("[*] Time: %Lfms; Traversals: %i\n", t, nt);
}

void handleDelete(BinarySearchTree *bst) {
    int n, nt;
    long double t;
    clock_t begin, end;
    printf("[*] Please enter an integer to remove: ");
    scanf("%i", &n);
    begin = clock();
    nt = bst->remove(n);
    end = clock();
    t = (long double)(end - begin) / CLOCKS_PER_SEC * 1000;
    printf("[-] Deleted %i from the tree...\n", n);
    printf("[*] Time: %Lfms; Traversals: %i\n", t, nt);
}

void handleSearch(BinarySearchTree *bst) {
    int n;
    bool contains;
    long double t;
    clock_t begin, end;
    printf("[*] Please enter an integer to search for: ");
    scanf("%i", &n);
    begin = clock();
    contains = bst->contains(n);
    end = clock();
    t = (long double)(end - begin) / CLOCKS_PER_SEC * 1000;
    if (contains) printf("[+] the tree does contain %i...\n", n);
    else printf("[-] the tree does not contain %i...\n", n);
    printf("[*] Time: %LFms\n", t);
}

void handleExit() {
    printf("Goodbye! (:\n\n");
    exit(0);
}

void handleHelp() {
    printf("[*] commands: \n\n");
    printf("\t'clear': Clears screen.\n");
    printf("\t'delete': Deletes [int] from bts (first-occurance basis).\n");
    printf("\t'exit': Exits CLI with status code 0.\n");
    printf("\t'help': Displays list of available commands.\n");
    printf("\t'insert': Inserts [int] into bts.\n");
    printf("\t'print': Prints each node in bts (in order; post-sort).\n");
    printf("\t'search': Returns boolean representation of tree[int].\n\n");
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
            case _search:
                handleSearch(&bst);
                break;
            case _delete:
                handleDelete(&bst);
                break;
            case help:
                handleHelp();
                break;
            case clear:
                system("clear");
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

