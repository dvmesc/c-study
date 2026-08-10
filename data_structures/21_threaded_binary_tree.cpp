#include <iostream>

using namespace std;

struct ThreadNode {
    char data;
    ThreadNode* left;
    ThreadNode* right;
    int ltag;
    int rtag;

    explicit ThreadNode(char value)
        : data(value), left(nullptr), right(nullptr), ltag(0), rtag(0) {}
};

class InorderThreadedBinaryTree {
private:
    ThreadNode* root;
    ThreadNode* pre;

    ThreadNode* buildSampleTree() {
        //        A
        //      /   \
        //     B     C
        //    / \     \
        //   D   E     F
        ThreadNode* a = new ThreadNode('A');
        ThreadNode* b = new ThreadNode('B');
        ThreadNode* c = new ThreadNode('C');
        ThreadNode* d = new ThreadNode('D');
        ThreadNode* e = new ThreadNode('E');
        ThreadNode* f = new ThreadNode('F');

        a->left = b;
        a->right = c;
        b->left = d;
        b->right = e;
        c->right = f;
        return a;
    }

    void inorderThread(ThreadNode* node) {
        if (node == nullptr) {
            return;
        }

        inorderThread(node->left);

        if (node->left == nullptr) {
            node->ltag = 1;
            node->left = pre;
        }
        if (pre != nullptr && pre->right == nullptr) {
            pre->rtag = 1;
            pre->right = node;
        }
        pre = node;

        inorderThread(node->right);
    }

    ThreadNode* firstNode(ThreadNode* node) const {
        while (node != nullptr && node->ltag == 0) {
            node = node->left;
        }
        return node;
    }

    ThreadNode* nextNode(ThreadNode* node) const {
        if (node->rtag == 1) {
            return node->right;
        }
        return firstNode(node->right);
    }

    void destroy(ThreadNode* node) {
        if (node == nullptr) {
            return;
        }
        if (node->ltag == 0) {
            destroy(node->left);
        }
        if (node->rtag == 0) {
            destroy(node->right);
        }
        delete node;
    }

public:
    InorderThreadedBinaryTree() : root(nullptr), pre(nullptr) {}

    ~InorderThreadedBinaryTree() {
        destroy(root);
    }

    void buildSample() {
        root = buildSampleTree();
    }

    void createInorderThread() {
        pre = nullptr;
        inorderThread(root);
        if (pre != nullptr && pre->right == nullptr) {
            pre->rtag = 1;
        }
    }

    void printInorderByThread() const {
        for (ThreadNode* current = firstNode(root); current != nullptr; current = nextNode(current)) {
            cout << current->data << ' ';
        }
        cout << '\n';
    }

    void printThreadInfo() const {
        for (ThreadNode* current = firstNode(root); current != nullptr; current = nextNode(current)) {
            cout << current->data << ": ";
            if (current->ltag == 1 && current->left != nullptr) {
                cout << "pre=" << current->left->data << ' ';
            } else {
                cout << "pre=# ";
            }

            if (current->rtag == 1 && current->right != nullptr) {
                cout << "next=" << current->right->data;
            } else {
                cout << "next=#";
            }
            cout << '\n';
        }
    }
};

int main() {
    // 演示：中序线索化以及利用线索遍历。
    InorderThreadedBinaryTree tree;
    tree.buildSample();
    tree.createInorderThread();

    cout << "inorder by thread: ";
    tree.printInorderByThread();

    cout << "thread info:\n";
    tree.printThreadInfo();
    return 0;
}
