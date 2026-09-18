#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// 树和二叉树是 408 的高频重点。
// 这一文件演示二叉树的构造、递归遍历、层序遍历以及结点统计。

struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(char value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

    TreeNode* buildSampleTree() {
        //        A
        //      /   \
        //     B     C
        //    / \     \
        //   D   E     F
        TreeNode* a = new TreeNode('A');
        TreeNode* b = new TreeNode('B');
        TreeNode* c = new TreeNode('C');
        TreeNode* d = new TreeNode('D');
        TreeNode* e = new TreeNode('E');
        TreeNode* f = new TreeNode('F');

        a->left = b;
        a->right = c;
        b->left = d;
        b->right = e;
        c->right = f;
        return a;
    }

    void preorder(TreeNode* node) const {
        if (node == nullptr) {
            return;
        }
        cout << node->data << ' ';
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(TreeNode* node) const {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->data << ' ';
        inorder(node->right);
    }

    void postorder(TreeNode* node) const {
        if (node == nullptr) {
            return;
        }
        postorder(node->left);
        postorder(node->right);
        cout << node->data << ' ';
    }

    int countNodes(TreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        return countNodes(node->left) + countNodes(node->right) + 1;
    }

    int countLeaves(TreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }
        return countLeaves(node->left) + countLeaves(node->right);
    }

    int height(TreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    void destroy(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        destroy(root);
    }

    void buildSample() {
        root = buildSampleTree();
    }

    void printPreorder() const {
        preorder(root);
        cout << '\n';
    }

    void printInorder() const {
        inorder(root);
        cout << '\n';
    }

    void printPostorder() const {
        postorder(root);
        cout << '\n';
    }

    void printLevelOrder() const {
        if (root == nullptr) {
            return;
        }
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            cout << current->data << ' ';

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        cout << '\n';
    }

    void printPreorderNonRecursive() const {
        if (root == nullptr) {
            return;
        }
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode* current = st.top();
            st.pop();
            cout << current->data << ' ';
            if (current->right != nullptr) {
                st.push(current->right);
            }
            if (current->left != nullptr) {
                st.push(current->left);
            }
        }
        cout << '\n';
    }

    void printInorderNonRecursive() const {
        stack<TreeNode*> st;
        TreeNode* current = root;
        while (current != nullptr || !st.empty()) {
            while (current != nullptr) {
                st.push(current);
                current = current->left;
            }
            current = st.top();
            st.pop();
            cout << current->data << ' ';
            current = current->right;
        }
        cout << '\n';
    }

    void printPostorderNonRecursive() const {
        if (root == nullptr) {
            return;
        }
        stack<TreeNode*> st1;
        stack<TreeNode*> st2;
        st1.push(root);
        while (!st1.empty()) {
            TreeNode* current = st1.top();
            st1.pop();
            st2.push(current);
            if (current->left != nullptr) {
                st1.push(current->left);
            }
            if (current->right != nullptr) {
                st1.push(current->right);
            }
        }
        while (!st2.empty()) {
            cout << st2.top()->data << ' ';
            st2.pop();
        }
        cout << '\n';
    }

    int nodeCount() const {
        return countNodes(root);
    }

    int leafCount() const {
        return countLeaves(root);
    }

    int treeHeight() const {
        return height(root);
    }
};

int main() {
    BinaryTree tree;
    tree.buildSample();

    cout << "preorder: ";
    tree.printPreorder();
    cout << "inorder: ";
    tree.printInorder();
    cout << "postorder: ";
    tree.printPostorder();
    cout << "level order: ";
    tree.printLevelOrder();
    cout << "preorder non-recursive: ";
    tree.printPreorderNonRecursive();
    cout << "inorder non-recursive: ";
    tree.printInorderNonRecursive();
    cout << "postorder non-recursive: ";
    tree.printPostorderNonRecursive();

    cout << "node count: " << tree.nodeCount() << '\n';
    cout << "leaf count: " << tree.leafCount() << '\n';
    cout << "height: " << tree.treeHeight() << '\n';

    return 0;
}
