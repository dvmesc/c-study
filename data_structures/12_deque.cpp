#include <iostream>

using namespace std;

// 双端队列节点。
struct Node {
    int val;
    Node* prev;
    Node* next;

    explicit Node(int value) : val(value), prev(nullptr), next(nullptr) {}
};

// 双端队列：两端都可以插入和删除。
class Deque {
private:
    Node* head;
    Node* tail;

public:
    Deque() : head(nullptr), tail(nullptr) {}

    ~Deque() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    bool empty() const {
        return head == nullptr;
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

    bool popFront() {
        if (empty()) {
            return false;
        }

        Node* node = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete node;
        return true;
    }

    bool popBack() {
        if (empty()) {
            return false;
        }

        Node* node = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete node;
        return true;
    }

    int front() const {
        if (empty()) {
            return -1;
        }
        return head->val;
    }

    int back() const {
        if (empty()) {
            return -1;
        }
        return tail->val;
    }
};

int main() {
    // 演示：双端队列从两端进出元素。
    Deque dq;
    dq.pushFront(2);
    dq.pushFront(1);
    dq.pushBack(3);
    dq.pushBack(4);

    cout << "front: " << dq.front() << '\n';
    cout << "back: " << dq.back() << '\n';

    dq.popFront();
    dq.popBack();

    cout << "front after pop: " << dq.front() << '\n';
    cout << "back after pop: " << dq.back() << '\n';

    return 0;
}
