#include <iostream>
using namespace std;

class Node {
public:
    string key, meaning;
    Node *left, *right;
    int height;
};

class AVL {
    Node *root;

    int getHeight(Node *node) {
        return node ? node->height : 0;
    }

    int getBalance(Node *node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node* rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insert(Node *node, string key, string meaning) {
        if (!node) {
            Node *newNode = new Node{key, meaning, nullptr, nullptr, 1};
            return newNode;
        }

        if (key < node->key)
            node->left = insert(node->left, key, meaning);
        else if (key > node->key)
            node->right = insert(node->right, key, meaning);
        else
            return node; // duplicate keys not allowed

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Balancing
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrder(Node *node) {
        if (node) {
            inOrder(node->left);
            cout << node->key << " : " << node->meaning << endl;
            inOrder(node->right);
        }
    }

    Node* minValueNode(Node *node) {
        Node *current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node *root, string key) {
        if (!root) return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node *temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node *temp = minValueNode(root->right);
                root->key = temp->key;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root) return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    bool search(Node *node, string key) {
        if (!node) return false;
        if (node->key == key) return true;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

public:
    AVL() { root = nullptr; }

    void insertWord() {
        string key, meaning;
        cout << "Enter keyword: ";
        cin >> key;
        cout << "Enter meaning: ";
        cin >> meaning;
        root = insert(root, key, meaning);
    }

    void display() {
        cout << "\nDictionary (In-order Traversal):\n";
        inOrder(root);
    }

    void deleteWord() {
        string key;
        cout << "Enter keyword to delete: ";
        cin >> key;
        root = deleteNode(root, key);
    }

    void searchWord() {
        string key;
        cout << "Enter keyword to search: ";
        cin >> key;
        if (search(root, key))
            cout << "Keyword found.\n";
        else
            cout << "Keyword not found.\n";
    }
};

int main() {
    AVL dict;
    int choice;
    char cont;

    do {
        cout << "\n1. Insert keyword\n2. Display dictionary\n3. Delete keyword\n4. Search keyword\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: dict.insertWord(); break;
            case 2: dict.display(); break;
            case 3: dict.deleteWord(); break;
            case 4: dict.searchWord(); break;
            default: cout << "Invalid choice\n";
        }

        cout << "Continue? (y/n): ";
        cin >> cont;
    } while (cont == 'y' || cont == 'Y');

    return 0;
}