#include <iostream>

using namespace std;

// 查找部分重点是查找效率和适用条件。
// 这里演示顺序查找、折半查找和二叉排序树的插入与查找。

int sequentialSearch(const int data[], int length, int key) {
    for (int i = 0; i < length; ++i) {
        if (data[i] == key) {
            return i;
        }
    }
    return -1;
}

int binarySearch(const int data[], int length, int key) {
    int left = 0;
    int right = length - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (data[mid] == key) {
            return mid;
        }
        if (data[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;

    explicit BSTNode(int value) : key(value), left(nullptr), right(nullptr) {}
};

class BSTree {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, int key) {
        if (node == nullptr) {
            return new BSTNode(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        return node;
    }

    bool search(BSTNode* node, int key) const {
        if (node == nullptr) {
            return false;
        }
        if (node->key == key) {
            return true;
        }
        if (key < node->key) {
            return search(node->left, key);
        }
        return search(node->right, key);
    }

    void inorder(BSTNode* node) const {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->key << ' ';
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

    void insert(int key) {
        root = insert(root, key);
    }

    bool search(int key) const {
        return search(root, key);
    }

    void printInorder() const {
        inorder(root);
        cout << '\n';
    }
};

int main() {
    int orderedData[] = {10, 20, 30, 40, 50, 60};
    int length = sizeof(orderedData) / sizeof(orderedData[0]);

    cout << "sequential search 40: " << sequentialSearch(orderedData, length, 40) << '\n';
    cout << "binary search 50: " << binarySearch(orderedData, length, 50) << '\n';

    BSTree tree;
    tree.insert(45);
    tree.insert(20);
    tree.insert(60);
    tree.insert(10);
    tree.insert(30);
    tree.insert(50);
    tree.insert(70);

    cout << "BST inorder: ";
    tree.printInorder();
    cout << "BST search 30: " << (tree.search(30) ? "true" : "false") << '\n';

    return 0;
}
