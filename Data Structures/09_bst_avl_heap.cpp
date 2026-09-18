#include <iostream>

using namespace std;

// 这一文件补二叉排序树、AVL 树和堆。
// 三者都和“高效查找”或“优先级处理”密切相关。

struct BSTNode {
    int value;
    BSTNode* left;
    BSTNode* right;

    explicit BSTNode(int data) : value(data), left(nullptr), right(nullptr) {}
};

class BSTree {
private:
    BSTNode* root;

    BSTNode* insertNode(BSTNode* node, int value) {
        if (node == nullptr) {
            return new BSTNode(value);
        }
        if (value < node->value) {
            node->left = insertNode(node->left, value);
        } else if (value > node->value) {
            node->right = insertNode(node->right, value);
        }
        return node;
    }

    bool searchNode(BSTNode* node, int value) const {
        if (node == nullptr) {
            return false;
        }
        if (node->value == value) {
            return true;
        }
        if (value < node->value) {
            return searchNode(node->left, value);
        }
        return searchNode(node->right, value);
    }

    void inorder(BSTNode* node) const {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->value << ' ';
        inorder(node->right);
    }

    void destroy(BSTNode* node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BSTree() : root(nullptr) {}

    ~BSTree() {
        destroy(root);
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    bool search(int value) const {
        return searchNode(root, value);
    }

    void printInorder() const {
        inorder(root);
        cout << '\n';
    }
};

struct AVLNode {
    int value;
    int height;
    AVLNode* left;
    AVLNode* right;

    explicit AVLNode(int data) : value(data), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node) const {
        return node == nullptr ? 0 : node->height;
    }

    int getBalance(AVLNode* node) const {
        return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(AVLNode* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* t2 = x->right;
        x->right = y;
        y->left = t2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* t2 = y->left;
        y->left = x;
        x->right = t2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* insertNode(AVLNode* node, int value) {
        if (node == nullptr) {
            return new AVLNode(value);
        }
        if (value < node->value) {
            node->left = insertNode(node->left, value);
        } else if (value > node->value) {
            node->right = insertNode(node->right, value);
        } else {
            return node;
        }

        updateHeight(node);
        int balance = getBalance(node);
        if (balance > 1 && value < node->left->value) {
            return rotateRight(node);
        }
        if (balance < -1 && value > node->right->value) {
            return rotateLeft(node);
        }
        if (balance > 1 && value > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && value < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    void inorder(AVLNode* node) const {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->value << ' ';
        inorder(node->right);
    }

    void destroy(AVLNode* node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        destroy(root);
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    void printInorder() const {
        inorder(root);
        cout << '\n';
    }
};

class MaxHeap {
private:
    static const int MAX_SIZE = 20;
    int data[MAX_SIZE];
    int size;

public:
    MaxHeap() : data{}, size(0) {}

    void insert(int value) {
        if (size >= MAX_SIZE) {
            return;
        }
        int index = size++;
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (data[parent] >= value) {
                break;
            }
            data[index] = data[parent];
            index = parent;
        }
        data[index] = value;
    }

    bool removeMax(int& value) {
        if (size == 0) {
            return false;
        }
        value = data[0];
        int lastValue = data[--size];
        int parent = 0;
        int child = 1;
        while (child < size) {
            if (child + 1 < size && data[child + 1] > data[child]) {
                ++child;
            }
            if (lastValue >= data[child]) {
                break;
            }
            data[parent] = data[child];
            parent = child;
            child = parent * 2 + 1;
        }
        if (size > 0) {
            data[parent] = lastValue;
        }
        return true;
    }
};

int main() {
    cout << "=== BST ===\n";
    BSTree bst;
    bst.insert(45);
    bst.insert(20);
    bst.insert(60);
    bst.insert(10);
    bst.insert(30);
    bst.printInorder();
    cout << "search 30: " << (bst.search(30) ? "true" : "false") << '\n';

    cout << "\n=== AVL ===\n";
    AVLTree avl;
    avl.insert(30);
    avl.insert(20);
    avl.insert(10);
    avl.insert(25);
    avl.insert(40);
    avl.insert(50);
    avl.printInorder();

    cout << "\n=== 大根堆 ===\n";
    MaxHeap heap;
    heap.insert(30);
    heap.insert(50);
    heap.insert(20);
    heap.insert(70);
    int value = 0;
    while (heap.removeMax(value)) {
        cout << value << ' ';
    }
    cout << '\n';

    return 0;
}
