#include <iostream>

using namespace std;

// 二叉搜索树节点：左子树小于根，右子树大于根。
struct BSTNode {
    int val;
    BSTNode* left;
    BSTNode* right;

    explicit BSTNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// 二叉搜索树：适合学习递归插入、查找和删除。
class BST {
private:
    BSTNode* root;

    // 递归插入，直到找到空位置。
    BSTNode* insertNode(BSTNode* node, int value) {
        if (node == nullptr) {
            return new BSTNode(value);
        }
        if (value < node->val) {
            node->left = insertNode(node->left, value);
        } else if (value > node->val) {
            node->right = insertNode(node->right, value);
        }
        return node;
    }

    bool searchNode(BSTNode* node, int value) const {
        if (node == nullptr) {
            return false;
        }
        if (node->val == value) {
            return true;
        }
        if (value < node->val) {
            return searchNode(node->left, value);
        }
        return searchNode(node->right, value);
    }

    void inorder(BSTNode* node) const {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->val << ' ';
        inorder(node->right);
    }

    BSTNode* findMin(BSTNode* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    BSTNode* deleteNode(BSTNode* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->val) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->val) {
            node->right = deleteNode(node->right, value);
        } else {
            if (node->left == nullptr) {
                BSTNode* rightNode = node->right;
                delete node;
                return rightNode;
            }
            if (node->right == nullptr) {
                BSTNode* leftNode = node->left;
                delete node;
                return leftNode;
            }

            BSTNode* minNode = findMin(node->right);
            node->val = minNode->val;
            node->right = deleteNode(node->right, minNode->val);
        }
        return node;
    }

    // 中序遍历会输出有序结果。
    void destroy(BSTNode* node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        destroy(root);
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    bool search(int value) const {
        return searchNode(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    void printInorder() const {
        inorder(root);
        cout << '\n';
    }
};

// AVL 树节点：在二叉搜索树基础上额外维护高度。
struct AVLNode {
    int val;
    int height;
    AVLNode* left;
    AVLNode* right;

    explicit AVLNode(int value) : val(value), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalance(AVLNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(AVLNode* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    // 右旋用于修复左侧过高的情况。
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* t2 = x->right;

        x->right = y;
        y->left = t2;

        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // 左旋用于修复右侧过高的情况。
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

    void inorder(AVLNode* node) const {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->val << ' ';
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

int main() {
    // 演示：BST 的插入、查找、删除和中序遍历。
    BST bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    cout << "BST inorder: ";
    bst.printInorder();
    cout << "BST search 6: " << bst.search(6) << '\n';
    bst.remove(7);
    cout << "BST after remove 7: ";
    bst.printInorder();

    // 演示：AVL 插入后会自动保持平衡。
    AVLTree avl;
    avl.insert(30);
    avl.insert(20);
    avl.insert(10);
    avl.insert(25);
    avl.insert(40);
    avl.insert(50);
    cout << "AVL inorder: ";
    avl.printInorder();

    return 0;
}
