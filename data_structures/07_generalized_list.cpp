#include <iostream>

using namespace std;

// 广义表节点类型：原子或子表。
enum NodeType {
    ATOM,
    SUBLIST
};

struct GNode {
    NodeType type;
    char atom;
    GNode* sublist;
    GNode* next;

    explicit GNode(char value) : type(ATOM), atom(value), sublist(nullptr), next(nullptr) {}

    explicit GNode(GNode* list) : type(SUBLIST), atom('\0'), sublist(list), next(nullptr) {}
};

class GeneralizedList {
private:
    GNode* head;

    void printNode(GNode* node) const {
        cout << '(';
        GNode* cur = node;
        while (cur != nullptr) {
            if (cur->type == ATOM) {
                cout << cur->atom;
            } else {
                printNode(cur->sublist);
            }
            if (cur->next != nullptr) {
                cout << ',';
            }
            cur = cur->next;
        }
        cout << ')';
    }

    int depthOf(GNode* node) const {
        if (node == nullptr) {
            return 1;
        }

        int maxDepth = 1;
        GNode* cur = node;
        while (cur != nullptr) {
            if (cur->type == SUBLIST) {
                int childDepth = depthOf(cur->sublist) + 1;
                if (childDepth > maxDepth) {
                    maxDepth = childDepth;
                }
            }
            cur = cur->next;
        }
        return maxDepth;
    }

    void destroy(GNode* node) {
        while (node != nullptr) {
            GNode* next = node->next;
            if (node->type == SUBLIST) {
                destroy(node->sublist);
            }
            delete node;
            node = next;
        }
    }

public:
    GeneralizedList() : head(nullptr) {}

    ~GeneralizedList() {
        destroy(head);
    }

    void buildSample() {
        // 构造广义表：(a,(b,c),d)
        GNode* a = new GNode('a');
        GNode* b = new GNode('b');
        GNode* c = new GNode('c');
        b->next = c;

        GNode* sub = new GNode(b);
        GNode* d = new GNode('d');

        a->next = sub;
        sub->next = d;
        head = a;
    }

    void print() const {
        printNode(head);
        cout << '\n';
    }

    int depth() const {
        return depthOf(head);
    }
};

int main() {
    // 演示：广义表输出和深度计算。
    GeneralizedList glist;
    glist.buildSample();

    glist.print();
    cout << "depth: " << glist.depth() << '\n';
    return 0;
}
