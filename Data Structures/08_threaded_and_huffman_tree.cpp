#include <iostream>

using namespace std;

// 这一部分补充线索二叉树和哈夫曼树。
// 它们在 408 中经常考遍历优化思想和带权路径长度 WPL。

struct ThreadNode {
    char data;
    ThreadNode* left;
    ThreadNode* right;
    int ltag;
    int rtag;

    explicit ThreadNode(char value) : data(value), left(nullptr), right(nullptr), ltag(0), rtag(0) {}
};

class InorderThreadedBinaryTree {
private:
    ThreadNode* root;
    ThreadNode* pre;

    ThreadNode* buildSampleTree() {
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
};

struct HuffmanNode {
    int weight;
    int parent;
    int left;
    int right;
};

int selectMin(const HuffmanNode tree[], int end) {
    int minIndex = -1;
    for (int i = 1; i <= end; ++i) {
        if (tree[i].parent != 0) {
            continue;
        }
        if (minIndex == -1 || tree[i].weight < tree[minIndex].weight) {
            minIndex = i;
        }
    }
    return minIndex;
}

void createHuffmanTree(HuffmanNode tree[], const int weights[], int n) {
    int total = 2 * n - 1;
    for (int i = 1; i <= total; ++i) {
        tree[i].weight = 0;
        tree[i].parent = 0;
        tree[i].left = 0;
        tree[i].right = 0;
    }

    for (int i = 1; i <= n; ++i) {
        tree[i].weight = weights[i - 1];
    }

    for (int i = n + 1; i <= total; ++i) {
        int s1 = selectMin(tree, i - 1);
        tree[s1].parent = -1;
        int s2 = selectMin(tree, i - 1);
        tree[s2].parent = i;
        tree[s1].parent = i;
        tree[i].left = s1;
        tree[i].right = s2;
        tree[i].weight = tree[s1].weight + tree[s2].weight;
    }
}

int weightedPathLength(const HuffmanNode tree[], int n) {
    int result = 0;
    for (int i = 1; i <= n; ++i) {
        int depth = 0;
        int current = i;
        while (tree[current].parent != 0) {
            ++depth;
            current = tree[current].parent;
        }
        result += tree[i].weight * depth;
    }
    return result;
}

void printCodes(const HuffmanNode tree[], int n) {
    char code[100];
    code[n - 1] = '\0';
    for (int i = 1; i <= n; ++i) {
        int start = n - 1;
        int child = i;
        int parent = tree[child].parent;
        while (parent != 0) {
            if (tree[parent].left == child) {
                code[--start] = '0';
            } else {
                code[--start] = '1';
            }
            child = parent;
            parent = tree[child].parent;
        }
        cout << "weight " << tree[i].weight << " code: " << (code + start) << '\n';
    }
}

int main() {
    cout << "=== 中序线索二叉树 ===\n";
    InorderThreadedBinaryTree tree;
    tree.buildSample();
    tree.createInorderThread();
    tree.printInorderByThread();

    cout << "\n=== 哈夫曼树 ===\n";
    int weights[] = {5, 29, 7, 8, 14, 23, 3, 11};
    int n = sizeof(weights) / sizeof(weights[0]);
    HuffmanNode huffmanTree[2 * 8] = {};
    createHuffmanTree(huffmanTree, weights, n);
    printCodes(huffmanTree, n);
    cout << "WPL: " << weightedPathLength(huffmanTree, n) << '\n';

    return 0;
}
