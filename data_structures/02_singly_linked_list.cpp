#include <iostream>

using namespace std;

// 单链表节点：只保存当前值和后继指针。
struct Node {
    int val;
    Node* next;

    explicit Node(int value) : val(value), next(nullptr) {}
};

// 单链表：适合练习指针移动、插入和删除。
class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    // 头插法：新节点直接成为新的头结点。
    void pushFront(int value) {
        Node* node = new Node(value);
        node->next = head;
        head = node;
    }

    // 尾插法：需要一路走到链表末尾。
    void pushBack(int value) {
        Node* node = new Node(value);
        if (head == nullptr) {
            head = node;
            return;
        }

        Node* cur = head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = node;
    }

    bool insertAfter(int target, int value) {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->val == target) {
                Node* node = new Node(value);
                node->next = cur->next;
                cur->next = node;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    bool removeValue(int value) {
        if (head == nullptr) {
            return false;
        }
        if (head->val == value) {
            Node* node = head;
            head = head->next;
            delete node;
            return true;
        }

        Node* cur = head;
        while (cur->next != nullptr) {
            if (cur->next->val == value) {
                Node* node = cur->next;
                cur->next = node->next;
                delete node;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    // 原地反转链表，重点是维护 prev / cur / next 三个指针。
    void reverse() {
        Node* prev = nullptr;
        Node* cur = head;
        while (cur != nullptr) {
            Node* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        head = prev;
    }

    bool find(int value) const {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->val == value) {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    void print() const {
        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->val << ' ';
            cur = cur->next;
        }
        cout << '\n';
    }
};

int main() {
    // 演示：头插、尾插、指定值后插入、删除和反转。
    SinglyLinkedList list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushFront(0);
    list.insertAfter(2, 99);
    list.print();

    list.removeValue(99);
    list.print();

    list.reverse();
    list.print();

    cout << "find 2: " << list.find(2) << '\n';
    return 0;
}
