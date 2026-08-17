#include <iostream>

using namespace std;

// 这里用一个手工构造的 3 阶 B 树示例，重点演示结点结构与查找过程。
struct BTreeNode {
    int keyCount;
    int keys[3];
    BTreeNode* children[4];
    bool isLeaf;

    explicit BTreeNode(bool leaf) : keyCount(0), keys{0}, children{nullptr}, isLeaf(leaf) {}
};

class BTreeDemo {
private:
    BTreeNode* root;

    // 手工构造一棵示例 B 树。
    BTreeNode* buildSampleTree() {
        //             [18 | 35]
        //           /     |      \
        //      [5|10] [20|30] [40|50]
        BTreeNode* r = new BTreeNode(false);
        BTreeNode* c0 = new BTreeNode(true);
        BTreeNode* c1 = new BTreeNode(true);
        BTreeNode* c2 = new BTreeNode(true);

        r->keyCount = 2;
        r->keys[0] = 18;
        r->keys[1] = 35;
        r->children[0] = c0;
        r->children[1] = c1;
        r->children[2] = c2;

        c0->keyCount = 2;
        c0->keys[0] = 5;
        c0->keys[1] = 10;

        c1->keyCount = 2;
        c1->keys[0] = 20;
        c1->keys[1] = 30;

        c2->keyCount = 2;
        c2->keys[0] = 40;
        c2->keys[1] = 50;

        return r;
    }

    // 释放整棵 B 树。
    void destroy(BTreeNode* node) {
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

    // 输出一个结点中的关键字。
    void printNode(BTreeNode* node) const {
        cout << '[';
        for (int i = 0; i < node->keyCount; ++i) {
            cout << node->keys[i];
            if (i + 1 < node->keyCount) {
                cout << " | ";
            }
        }
        cout << ']';
    }

public:
    // 初始化为空树。
    BTreeDemo() : root(nullptr) {}

    // 析构时释放结点。
    ~BTreeDemo() {
        destroy(root);
    }

    // 构造样例树。
    void buildSample() {
        root = buildSampleTree();
    }

    // 演示 B 树查找路径。
    void search(int target) const {
        BTreeNode* current = root;
        cout << "search " << target << ": ";

        while (current != nullptr) {
            printNode(current);
            cout << ' ';

            int i = 0;
            while (i < current->keyCount && target > current->keys[i]) {
                ++i;
            }

            if (i < current->keyCount && target == current->keys[i]) {
                cout << "-> found\n";
                return;
            }

            if (current->isLeaf) {
                cout << "-> not found\n";
                return;
            }

            current = current->children[i];
        }

        cout << "-> not found\n";
    }

    // 输出根结点和第一层孩子。
    void printStructure() const {
        cout << "root: ";
        printNode(root);
        cout << '\n';

        cout << "children: ";
        for (int i = 0; i <= root->keyCount; ++i) {
            printNode(root->children[i]);
            cout << ' ';
        }
        cout << '\n';
    }
};

int main() {
    // 演示：B 树结点结构与查找路径。
    BTreeDemo tree;
    tree.buildSample();

    tree.printStructure();
    tree.search(30);
    tree.search(18);
    tree.search(27);
    tree.search(50);
    return 0;
}
