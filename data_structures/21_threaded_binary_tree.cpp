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

    // 构造一棵用于线索化演示的样例树。
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

    // 递归完成中序线索化。
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

    // 找到中序遍历下的第一个结点。
    ThreadNode* firstNode(ThreadNode* node) const {
        while (node != nullptr && node->ltag == 0) {
            node = node->left;
        }
        return node;
    }

    // 找到当前结点在线索二叉树中的后继。
    ThreadNode* nextNode(ThreadNode* node) const {
        if (node->rtag == 1) {
            return node->right;
        }
        return firstNode(node->right);
    }

    // 释放整棵线索二叉树。
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
    // 初始化为空树。
    InorderThreadedBinaryTree() : root(nullptr), pre(nullptr) {}

    // 析构时释放树结点。
    ~InorderThreadedBinaryTree() {
        destroy(root);
    }

    // 构造样例树。
    void buildSample() {
        root = buildSampleTree();
    }

    // 对当前树执行中序线索化。
    void createInorderThread() {
        pre = nullptr;
        inorderThread(root);
        if (pre != nullptr && pre->right == nullptr) {
            pre->rtag = 1;
        }
    }

    // 使用线索直接做中序遍历。
    void printInorderByThread() const {
        for (ThreadNode* current = firstNode(root); current != nullptr; current = nextNode(current)) {
            cout << current->data << ' ';
        }
        cout << '\n';
    }

    // 输出每个结点的前驱和后继信息。
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
