#include <iostream>

using namespace std;

// 二叉搜索树节点：左子树小于根，右子树大于根。
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// 二叉搜索树：适合学习递归插入、查找和删除。
class BST {
private:
    TreeNode* root;

    // 递归插入，直到找到空位置。
    TreeNode* insertNode(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }
        if (value < node->val) {
            node->left = insertNode(node->left, value);
        } else if (value > node->val) {
            node->right = insertNode(node->right, value);
        }
        return node;
    }

    bool searchNode(TreeNode* node, int value) const {
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

    void inorder(TreeNode* node) const {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->val << ' ';
        inorder(node->right);
    }

    TreeNode* findMin(TreeNode* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode* deleteNode(TreeNode* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->val) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->val) {
            node->right = deleteNode(node->right, value);
        } else {
            if (node->left == nullptr) {
                TreeNode* rightNode = node->right;
                delete node;
                return rightNode;
            }
            if (node->right == nullptr) {
                TreeNode* leftNode = node->left;
                delete node;
                return leftNode;
            }

            TreeNode* minNode = findMin(node->right);
            node->val = minNode->val;
            node->right = deleteNode(node->right, minNode->val);
        }
        return node;
    }

    // 中序遍历会输出有序结果。
    void destroy(TreeNode* node) {
        if (node == nullptr) {
            return;
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

int main() {
    // 演示：插入、查找、删除和中序遍历。
    BST tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    tree.printInorder();
    cout << "search 6: " << tree.search(6) << '\n';

    tree.remove(7);
    tree.printInorder();

    return 0;
}
