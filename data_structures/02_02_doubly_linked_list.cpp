#include <iostream>

using namespace std;

// 双向链表节点：同时保存前驱和后继指针。
struct Node {
    int val;
    Node* prev;
    Node* next;

    explicit Node(int value) : val(value), prev(nullptr), next(nullptr) {}
};

// 双向链表：比单链表更适合双向移动和尾部删除。
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    void pushFront(int value) {
        Node* node = new Node(value);
        node->next = head;
        if (head != nullptr) {
            head->prev = node;
        } else {
            tail = node;
        }
        head = node;
    }

    void pushBack(int value) {
        Node* node = new Node(value);
        node->prev = tail;
        if (tail != nullptr) {
            tail->next = node;
        } else {
            head = node;
        }
        tail = node;
    }

    bool removeValue(int value) {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->val == value) {
                if (cur->prev != nullptr) {
                    cur->prev->next = cur->next;
                } else {
                    head = cur->next;
                }

                if (cur->next != nullptr) {
                    cur->next->prev = cur->prev;
                } else {
                    tail = cur->prev;
                }

                delete cur;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    void printForward() const {
        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->val << ' ';
            cur = cur->next;
        }
        cout << '\n';
    }

    void printBackward() const {
        Node* cur = tail;
        while (cur != nullptr) {
            cout << cur->val << ' ';
            cur = cur->prev;
        }
        cout << '\n';
    }
};

int main() {
    // 演示：头插、尾插、删除、正向和反向遍历。
    DoublyLinkedList list;
    list.pushFront(2);
    list.pushFront(1);
    list.pushBack(3);
    list.pushBack(4);

    cout << "forward: ";
    list.printForward();

    cout << "backward: ";
    list.printBackward();

    list.removeValue(3);
    cout << "after remove 3: ";
    list.printForward();

    return 0;
}
