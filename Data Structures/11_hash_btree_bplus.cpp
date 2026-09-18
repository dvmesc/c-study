#include <iostream>
#include <vector>

using namespace std;

// 这一部分补散列表、B 树、B+ 树。
// 408 常考它们的结构特点、查找路径和适用场景。

struct HashNode {
    int key;
    int value;
    HashNode* next;

    HashNode(int k, int v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    vector<HashNode*> buckets;

    int hash(int key) const {
        return key % static_cast<int>(buckets.size());
    }

public:
    explicit HashTable(int bucketCount = 7) : buckets(bucketCount, nullptr) {}

    ~HashTable() {
        for (HashNode* head : buckets) {
            while (head != nullptr) {
                HashNode* nextNode = head->next;
                delete head;
                head = nextNode;
            }
        }
    }

    void put(int key, int value) {
        int index = hash(key);
        HashNode* current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }
        HashNode* node = new HashNode(key, value);
        node->next = buckets[index];
        buckets[index] = node;
    }

    bool get(int key, int& value) const {
        int index = hash(key);
        HashNode* current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

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

    BTreeNode* buildSampleTree() {
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

public:
    BTreeDemo() : root(nullptr) {}

    ~BTreeDemo() {
        destroy(root);
    }

    void buildSample() {
        root = buildSampleTree();
    }

    void search(int target) const {
        BTreeNode* current = root;
        cout << "B-Tree search " << target << ": ";
        while (current != nullptr) {
            int i = 0;
            while (i < current->keyCount && target > current->keys[i]) {
                ++i;
            }
            if (i < current->keyCount && target == current->keys[i]) {
                cout << "found\n";
                return;
            }
            if (current->isLeaf) {
                cout << "not found\n";
                return;
            }
            current = current->children[i];
        }
        cout << "not found\n";
    }
};

struct BPlusNode {
    bool isLeaf;
    int keyCount;
    int keys[4];
    BPlusNode* children[5];
    BPlusNode* next;

    explicit BPlusNode(bool leaf) : isLeaf(leaf), keyCount(0), keys{0}, children{nullptr}, next(nullptr) {}
};

class BPlusTreeDemo {
private:
    BPlusNode* root;

    BPlusNode* buildSampleTree() {
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
    BPlusTreeDemo() : root(nullptr) {}

    ~BPlusTreeDemo() {
        destroy(root);
    }

    void buildSample() {
        root = buildSampleTree();
    }

    void rangeQuery(int left, int right) const {
        cout << "B+ range [" << left << ", " << right << "]: ";
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
};

int main() {
    cout << "=== Hash Table ===\n";
    HashTable table;
    table.put(1, 100);
    table.put(8, 200);
    table.put(15, 300);
    int value = 0;
    if (table.get(8, value)) {
        cout << "get 8: " << value << '\n';
    }

    cout << "\n=== B-Tree ===\n";
    BTreeDemo bTree;
    bTree.buildSample();
    bTree.search(30);
    bTree.search(27);

    cout << "\n=== B+ Tree ===\n";
    BPlusTreeDemo bPlusTree;
    bPlusTree.buildSample();
    bPlusTree.rangeQuery(12, 45);

    return 0;
}
