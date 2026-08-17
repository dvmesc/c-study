#include <iostream>

using namespace std;

// 循环单链表：尾节点的 next 指回头结点。
struct Node {
    int val;
    Node* next;

    explicit Node(int value) : val(value), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* tail;

public:
    CircularLinkedList() : tail(nullptr) {}

    ~CircularLinkedList() {
        if (tail == nullptr) {
            return;
        }

        Node* head = tail->next;
        tail->next = nullptr;
        while (head != nullptr) {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }

    void pushBack(int value) {
        Node* node = new Node(value);
        if (tail == nullptr) {
            tail = node;
            tail->next = tail;
            return;
        }

        node->next = tail->next;
        tail->next = node;
        tail = node;
    }

    void pushFront(int value) {
        Node* node = new Node(value);
        if (tail == nullptr) {
            tail = node;
            tail->next = tail;
            return;
        }

        node->next = tail->next;
        tail->next = node;
    }

    bool removeValue(int value) {
        if (tail == nullptr) {
            return false;
        }

        Node* prev = tail;
        Node* cur = tail->next;
        do {
            if (cur->val == value) {
                if (cur == prev) {
                    delete cur;
                    tail = nullptr;
                    return true;
                }

                prev->next = cur->next;
                if (cur == tail) {
                    tail = prev;
                }
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        } while (cur != tail->next);

        return false;
    }

    void print() const {
        if (tail == nullptr) {
            cout << '\n';
            return;
        }

        Node* head = tail->next;
        Node* cur = head;
        do {
            cout << cur->val << ' ';
            cur = cur->next;
        } while (cur != head);
        cout << '\n';
    }
};

int main() {
    // 演示：循环链表的头插、尾插和删除。
    CircularLinkedList list;
    list.pushBack(2);
    list.pushBack(3);
    list.pushFront(1);
    list.print();

    list.removeValue(2);
    list.print();

    return 0;
}
