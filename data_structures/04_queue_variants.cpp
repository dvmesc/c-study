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
struct Node {
    int val;
    Node* next;

    explicit Node(int value) : val(value), next(nullptr) {}
};

// 链式队列：head 指向队头，tail 指向队尾。
class LinkedQueue {
private:
    Node* head;
    Node* tail;

public:
    LinkedQueue() : head(nullptr), tail(nullptr) {}

    ~LinkedQueue() {
        while (head != nullptr) {
            Node* node = head;
            head = head->next;
            delete node;
        }
    }

    void push(int value) {
        Node* node = new Node(value);
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
        Node* node = head;
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

int main() {
    // 对比循环队列和链式队列的基本行为。
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

    return 0;
}
