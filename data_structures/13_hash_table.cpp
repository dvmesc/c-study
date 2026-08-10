#include <iostream>
#include <vector>

using namespace std;

// 哈希桶中的节点，使用链地址法解决冲突。
struct Node {
    int key;
    int value;
    Node* next;

    Node(int k, int v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    vector<Node*> buckets;

    int hash(int key) const {
        return key % static_cast<int>(buckets.size());
    }

public:
    explicit HashTable(int bucketCount = 7) : buckets(bucketCount, nullptr) {}

    ~HashTable() {
        for (Node* head : buckets) {
            while (head != nullptr) {
                Node* next = head->next;
                delete head;
                head = next;
            }
        }
    }

    void put(int key, int value) {
        int index = hash(key);
        Node* cur = buckets[index];
        while (cur != nullptr) {
            if (cur->key == key) {
                cur->value = value;
                return;
            }
            cur = cur->next;
        }

        Node* node = new Node(key, value);
        node->next = buckets[index];
        buckets[index] = node;
    }

    bool get(int key, int& value) const {
        int index = hash(key);
        Node* cur = buckets[index];
        while (cur != nullptr) {
            if (cur->key == key) {
                value = cur->value;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    bool remove(int key) {
        int index = hash(key);
        Node* cur = buckets[index];
        Node* prev = nullptr;

        while (cur != nullptr) {
            if (cur->key == key) {
                if (prev != nullptr) {
                    prev->next = cur->next;
                } else {
                    buckets[index] = cur->next;
                }
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    void print() const {
        for (int i = 0; i < static_cast<int>(buckets.size()); ++i) {
            cout << "bucket " << i << ": ";
            Node* cur = buckets[i];
            while (cur != nullptr) {
                cout << "(" << cur->key << ", " << cur->value << ") ";
                cur = cur->next;
            }
            cout << '\n';
        }
    }
};

int main() {
    // 演示：插入、查找、更新、删除。
    HashTable table;
    table.put(1, 100);
    table.put(8, 200);
    table.put(15, 300);
    table.print();

    int value = 0;
    if (table.get(8, value)) {
        cout << "get 8: " << value << '\n';
    }

    table.put(8, 250);
    table.remove(1);
    table.print();

    return 0;
}
