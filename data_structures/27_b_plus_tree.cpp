#include <iostream>

using namespace std;

// 这里用手工构造的 B+ 树示例，重点演示叶子链和区间查找。
struct BPlusNode {
    bool isLeaf;
    int keyCount;
    int keys[4];
    BPlusNode* children[5];
    BPlusNode* next;

    explicit BPlusNode(bool leaf)
        : isLeaf(leaf), keyCount(0), keys{0}, children{nullptr}, next(nullptr) {}
};

class BPlusTreeDemo {
private:
    BPlusNode* root;

    // 手工构造一棵示例 B+ 树。
    BPlusNode* buildSampleTree() {
        //              [20 | 40]
        //            /     |      \
        //   [5 10 15] [20 25 30] [40 45 50]
        BPlusNode* r = new BPlusNode(false);
        BPlusNode* l1 = new BPlusNode(true);
        BPlusNode* l2 = new BPlusNode(true);
        BPlusNode* l3 = new BPlusNode(true);

        r->keyCount = 2;
        r->keys[0] = 20;
        r->keys[1] = 40;
        r->children[0] = l1;
        r->children[1] = l2;
        r->children[2] = l3;

        l1->keyCount = 3;
        l1->keys[0] = 5;
        l1->keys[1] = 10;
        l1->keys[2] = 15;

        l2->keyCount = 3;
        l2->keys[0] = 20;
        l2->keys[1] = 25;
        l2->keys[2] = 30;

        l3->keyCount = 3;
        l3->keys[0] = 40;
        l3->keys[1] = 45;
        l3->keys[2] = 50;

        l1->next = l2;
        l2->next = l3;
        return r;
    }

    // 释放整棵 B+ 树。
    void destroy(BPlusNode* node) {
        if (node == nullptr) {
            return;
        }
        if (!node->isLeaf) {
            for (int i = 0; i <= node->keyCount; ++i) {
                destroy(node->children[i]);
            }
        }
        delete node;
    }

    // 根据关键字找到应落入的叶子结点。
    BPlusNode* findLeaf(int key) const {
        BPlusNode* current = root;
        while (current != nullptr && !current->isLeaf) {
            int i = 0;
            while (i < current->keyCount && key >= current->keys[i]) {
                ++i;
            }
            current = current->children[i];
        }
        return current;
    }

public:
    // 初始化为空树。
    BPlusTreeDemo() : root(nullptr) {}

    // 析构时释放结点。
    ~BPlusTreeDemo() {
        destroy(root);
    }

    // 构造样例树。
    void buildSample() {
        root = buildSampleTree();
    }

    // 演示单关键字查找。
    void search(int key) const {
        BPlusNode* leaf = findLeaf(key);
        cout << "search " << key << " in leaf: ";
        for (int i = 0; i < leaf->keyCount; ++i) {
            cout << leaf->keys[i] << ' ';
        }
        cout << '\n';

        for (int i = 0; i < leaf->keyCount; ++i) {
            if (leaf->keys[i] == key) {
                cout << "found " << key << '\n';
                return;
            }
        }
        cout << "not found " << key << '\n';
    }

    // 演示区间查询。
    void rangeQuery(int left, int right) const {
        cout << "range [" << left << ", " << right << "]: ";
        BPlusNode* current = findLeaf(left);

        while (current != nullptr) {
            for (int i = 0; i < current->keyCount; ++i) {
                if (current->keys[i] >= left && current->keys[i] <= right) {
                    cout << current->keys[i] << ' ';
                }
                if (current->keys[i] > right) {
                    cout << '\n';
                    return;
                }
            }
            current = current->next;
        }
        cout << '\n';
    }

    // 输出叶子结点链表。
    void printLeafChain() const {
        BPlusNode* current = root->children[0];
        cout << "leaf chain: ";
        while (current != nullptr) {
            cout << '[';
            for (int i = 0; i < current->keyCount; ++i) {
                cout << current->keys[i] << ' ';
            }
            cout << "] ";
            current = current->next;
        }
        cout << '\n';
    }
};

int main() {
    // 演示：B+ 树查找、叶子链和区间查询。
    BPlusTreeDemo tree;
    tree.buildSample();

    tree.printLeafChain();
    tree.search(25);
    tree.search(28);
    tree.rangeQuery(12, 45);
    return 0;
}
