#include <iostream>

using namespace std;

// AVL 树节点：在二叉搜索树基础上额外维护高度。
struct Node {
    int val;
    int height;
    Node* left;
    Node* right;

    explicit Node(int value) : val(value), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalance(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    // 右旋用于修复左侧过高的情况。
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* t2 = x->right;

        x->right = y;
        y->left = t2;

        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // 左旋用于修复右侧过高的情况。
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* t2 = y->left;

        y->left = x;
        x->right = t2;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* insertNode(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->val) {
            node->left = insertNode(node->left, value);
        } else if (value > node->val) {
            node->right = insertNode(node->right, value);
        } else {
            return node;
        }

        updateHeight(node);
        int balance = getBalance(node);

        if (balance > 1 && value < node->left->val) {
            return rotateRight(node);
        }
        if (balance < -1 && value > node->right->val) {
            return rotateLeft(node);
        }
        if (balance > 1 && value > node->left->val) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && value < node->right->val) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->val << ' ';
        inorder(node->right);
    }

    void destroy(Node* node) {
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

int main() {
    // 演示：AVL 树插入后会自动保持平衡。
    AVLTree tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    tree.insert(25);
    tree.insert(40);
    tree.insert(50);

    tree.printInorder();
    return 0;
}
