#include <iostream>
#include <cstring> 
using namespace std;

struct TreeNode {
    char data;
    TreeNode *left, *right;
};

class ExpressionTree {
    char expressionInput[20];

public:
    TreeNode *root;
    void buildTreeFromPrefix(char[]);
    void postOrderTraversal(TreeNode *);
    void displayTree(TreeNode *);
    void deleteTree(TreeNode *);
};

class Stack {
    TreeNode *stackData[30];
    int topIndex;

public:
    Stack() {
        topIndex = -1;
    }
    bool isEmpty() {
        return topIndex == -1;
    }
    void push(TreeNode *node) {
        stackData[++topIndex] = node;
    }
    TreeNode *pop() {
        return stackData[topIndex--];
    }
};

void ExpressionTree::buildTreeFromPrefix(char prefixExpr[]) {
    char currentChar;
    Stack stack;
    TreeNode *leftNode, *rightNode;
    int length = strlen(prefixExpr);

    cout << "\nConstructing Expression Tree Step-by-Step:\n";

    for (int i = length - 1; i >= 0; i--) {
        root = new TreeNode;
        root->left = root->right = nullptr;

        if (isalpha(prefixExpr[i])) { // Operand
            root->data = prefixExpr[i];
            stack.push(root);
            cout << "Inserted operand node: " << prefixExpr[i] << endl;
        } else if (prefixExpr[i] == '+' || prefixExpr[i] == '-' || 
                   prefixExpr[i] == '*' || prefixExpr[i] == '/') { // Operator
            leftNode = stack.pop();
            rightNode = stack.pop();
            root->data = prefixExpr[i];
            root->left = leftNode;
            root->right = rightNode;
            stack.push(root);
            cout << "Created operator node '" << prefixExpr[i] << "' with left child '" 
                 << leftNode->data << "' and right child '" << rightNode->data << "'\n";
        }
    }
    root = stack.pop();

    cout << "Expression Tree Constructed Successfully\n";
}

void ExpressionTree::postOrderTraversal(TreeNode *root) {
    Stack stack1, stack2;
    TreeNode *currentNode = root;

    cout << "\nPostorder Traversal: ";
    stack1.push(currentNode);

    while (!stack1.isEmpty()) {
        currentNode = stack1.pop();
        stack2.push(currentNode);

        if (currentNode->left != nullptr) {
            stack1.push(currentNode->left);
        }
        if (currentNode->right != nullptr) {
            stack1.push(currentNode->right);
        }
    }

    while (!stack2.isEmpty()) {
        currentNode = stack2.pop();
        cout << currentNode->data << " ";
    }
    cout << endl;
}

void ExpressionTree::deleteTree(TreeNode *node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    cout << "Deleting Node: " << node->data << endl;
    delete node;
}

int main() {
    char prefixExpression[20];
    ExpressionTree expressionTree;

    cout << "Enter Prefix Expression: ";
    cin >> prefixExpression;

    expressionTree.buildTreeFromPrefix(prefixExpression);
    expressionTree.postOrderTraversal(expressionTree.root);
    expressionTree.deleteTree(expressionTree.root);

    return 0;
}
