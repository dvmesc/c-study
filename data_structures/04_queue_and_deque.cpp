#include <iostream>

using namespace std;

// 循环队列：通过取模复用数组空间。
class CircularQueue {
private:
    int* data;
    int frontIndex;
    int rearIndex;
    int count;
    int capacity;

public:
    explicit CircularQueue(int cap = 10)
        : data(new int[cap]), frontIndex(0), rearIndex(0), count(0), capacity(cap) {}

    ~CircularQueue() {
        delete[] data;
    }

    // 入队时在 rear 位置写入，然后 rear 向后移动。
    bool push(int value) {
        if (full()) {
            return false;
        }
        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % capacity;
        ++count;
        return true;
    }

    bool pop() {
        if (empty()) {
            return false;
        }
        frontIndex = (frontIndex + 1) % capacity;
        --count;
        return true;
    }

    int front() const {
        if (empty()) {
            return -1;
        }
        return data[frontIndex];
    }

    bool empty() const {
        return count == 0;
    }

    bool full() const {
        return count == capacity;
    }
};

// 链式队列节点。
struct QueueNode {
    int val;
    QueueNode* next;

    explicit QueueNode(int value) : val(value), next(nullptr) {}
};

// 链式队列：head 指向队头，tail 指向队尾。
class LinkedQueue {
private:
    QueueNode* head;
    QueueNode* tail;

public:
    LinkedQueue() : head(nullptr), tail(nullptr) {}

    ~LinkedQueue() {
        while (head != nullptr) {
            QueueNode* node = head;
            head = head->next;
            delete node;
        }
    }

    void push(int value) {
        QueueNode* node = new QueueNode(value);
        if (tail == nullptr) {
            head = node;
            tail = node;
            return;
        }
        tail->next = node;
        tail = node;
    }

    bool pop() {
        if (empty()) {
            return false;
        }
        QueueNode* node = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
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

    bool empty() const {
        return head == nullptr;
    }
};

// 双端队列节点。
struct DequeNode {
    int val;
    DequeNode* prev;
    DequeNode* next;

    explicit DequeNode(int value) : val(value), prev(nullptr), next(nullptr) {}
};

// 双端队列：两端都可以插入和删除。
class Deque {
private:
    DequeNode* head;
    DequeNode* tail;

public:
    Deque() : head(nullptr), tail(nullptr) {}

    ~Deque() {
        DequeNode* cur = head;
        while (cur != nullptr) {
            DequeNode* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    bool empty() const {
        return head == nullptr;
    }

    void pushFront(int value) {
        DequeNode* node = new DequeNode(value);
        node->next = head;
        if (head != nullptr) {
            head->prev = node;
        } else {
            tail = node;
        }
        head = node;
    }

    void pushBack(int value) {
        DequeNode* node = new DequeNode(value);
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

        DequeNode* node = head;
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

        DequeNode* node = tail;
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
    // 对比循环队列、链式队列和双端队列的基本行为。
    CircularQueue circularQueue(5);
    circularQueue.push(1);
    circularQueue.push(2);
    circularQueue.push(3);
    cout << "CircularQueue front: " << circularQueue.front() << '\n';
    circularQueue.pop();
    cout << "CircularQueue front after pop: " << circularQueue.front() << '\n';

    LinkedQueue linkedQueue;
    linkedQueue.push(10);
    linkedQueue.push(20);
    linkedQueue.push(30);
    cout << "LinkedQueue front: " << linkedQueue.front() << '\n';
    linkedQueue.pop();
    cout << "LinkedQueue front after pop: " << linkedQueue.front() << '\n';

    Deque deque;
    deque.pushFront(2);
    deque.pushFront(1);
    deque.pushBack(3);
    deque.pushBack(4);
    cout << "Deque front: " << deque.front() << '\n';
    cout << "Deque back: " << deque.back() << '\n';
    deque.popFront();
    deque.popBack();
    cout << "Deque front after pop: " << deque.front() << '\n';
    cout << "Deque back after pop: " << deque.back() << '\n';

    return 0;
}
