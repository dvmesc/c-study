#include <iostream>

using namespace std;

// 顺序栈：用数组模拟“后进先出”。
class ArrayStack {
private:
    int* data;
    int topIndex;
    int capacity;

public:
    explicit ArrayStack(int cap = 100) : data(new int[cap]), topIndex(-1), capacity(cap) {}

    ~ArrayStack() {
        delete[] data;
    }

    // 入栈时元素放到栈顶的下一个位置。
    bool push(int value) {
        if (topIndex + 1 >= capacity) {
            return false;
        }
        data[++topIndex] = value;
        return true;
    }

    bool pop() {
        if (empty()) {
            return false;
        }
        --topIndex;
        return true;
    }

    int top() const {
        if (empty()) {
            return -1;
        }
        return data[topIndex];
    }

    bool empty() const {
        return topIndex == -1;
    }
};

// 链式栈节点。
struct Node {
    int val;
    Node* next;

    explicit Node(int value) : val(value), next(nullptr) {}
};

// 链式栈：头结点就是栈顶，入栈和出栈都在表头完成。
class LinkedStack {
private:
    Node* head;

public:
    LinkedStack() : head(nullptr) {}

    ~LinkedStack() {
        while (head != nullptr) {
            Node* node = head;
            head = head->next;
            delete node;
        }
    }

    void push(int value) {
        Node* node = new Node(value);
        node->next = head;
        head = node;
    }

    bool pop() {
        if (empty()) {
            return false;
        }
        Node* node = head;
        head = head->next;
        delete node;
        return true;
    }

    int top() const {
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
    // 对比顺序栈和链式栈的基本操作。
    ArrayStack arrayStack;
    arrayStack.push(10);
    arrayStack.push(20);
    arrayStack.push(30);
    cout << "ArrayStack top: " << arrayStack.top() << '\n';
    arrayStack.pop();
    cout << "ArrayStack top after pop: " << arrayStack.top() << '\n';

    LinkedStack linkedStack;
    linkedStack.push(100);
    linkedStack.push(200);
    linkedStack.push(300);
    cout << "LinkedStack top: " << linkedStack.top() << '\n';
    linkedStack.pop();
    cout << "LinkedStack top after pop: " << linkedStack.top() << '\n';

    return 0;
}
