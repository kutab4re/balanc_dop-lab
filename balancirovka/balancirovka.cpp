#include <iostream>
using namespace std;

// Node structure for the AVL tree
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Function to get the height of a node
int height(Node* n) {
    return n ? n->height : 0;
}

// Function to get the balance factor of a node
int get_balance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// Function to create a new node
Node* new_node(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

// Right rotation around node y
Node* right_rotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Print rotation information
    cout << "Right rotation around node " << y->key << endl;

    return x;
}

// Left rotation around node x
Node* left_rotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Print rotation information
    cout << "Left rotation around node " << x->key << endl;

    return y;
}

// Insert a node into the AVL tree and balance it
Node* insert(Node* node, int key) {
    // Insert the node as in a regular BST
    if (!node)
        return new_node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // duplicate keys are not allowed
        return node;

    // Update the height of the ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of the ancestor node to check if it became unbalanced
    int balance = get_balance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        cout << "Balancing (Left Left Case) for node " << node->key << endl;
        return right_rotate(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        cout << "Balancing (Right Right Case) for node " << node->key << endl;
        return left_rotate(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        cout << "Balancing (Left Right Case) for node " << node->key << endl;
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        cout << "Balancing (Right Left Case) for node " << node->key << endl;
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

// Function to print the tree in pre-order
void pre_order(Node* root) {
    if (root) {
        cout << root->key << " ";
        pre_order(root->left);
        pre_order(root->right);
    }
}

// Main function
int main() {
    setlocale(LC_ALL, "ru");
    Node* root = nullptr;

    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    cout << "Введите элементы: ";
    for (int i = 0; i < n; ++i) {
        int key;
        cin >> key;
        root = insert(root, key);
        cout << "Inserted: " << key << ", PreOrder: ";
        pre_order(root);
        cout << endl;
    }

    cout << "Balanced AVL tree: ";
    pre_order(root);
    cout << endl;

    return 0;
}
