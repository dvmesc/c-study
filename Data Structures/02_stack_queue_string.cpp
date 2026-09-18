#include <iostream>
#include <string>

using namespace std;

// 这一部分涵盖栈、队列和串。
// 它们在 408 中经常结合应用题出现，例如括号匹配、表达式处理、KMP 模式匹配等。

class SeqStack {
private:
    static const int MAX_SIZE = 20;
    int data[MAX_SIZE];
    int top;

public:
    SeqStack() : data{}, top(-1) {}

    bool empty() const {
        return top == -1;
    }

    bool push(int value) {
        if (top == MAX_SIZE - 1) {
            return false;
        }
        data[++top] = value;
        return true;
    }

    bool pop(int& value) {
        if (top == -1) {
            return false;
        }
        value = data[top--];
        return true;
    }

    bool getTop(int& value) const {
        if (top == -1) {
            return false;
        }
        value = data[top];
        return true;
    }
};

class CircularQueue {
private:
    static const int MAX_SIZE = 6;
    int data[MAX_SIZE];
    int front;
    int rear;

public:
    CircularQueue() : data{}, front(0), rear(0) {}

    bool empty() const {
        return front == rear;
    }

    bool enqueue(int value) {
        if ((rear + 1) % MAX_SIZE == front) {
            return false;
        }
        data[rear] = value;
        rear = (rear + 1) % MAX_SIZE;
        return true;
    }

    bool dequeue(int& value) {
        if (front == rear) {
            return false;
        }
        value = data[front];
        front = (front + 1) % MAX_SIZE;
        return true;
    }
};

struct QueueNode {
    int data;
    QueueNode* next;

    explicit QueueNode(int value) : data(value), next(nullptr) {}
};

class LinkedQueue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;

public:
    LinkedQueue() : frontNode(nullptr), rearNode(nullptr) {}

    ~LinkedQueue() {
        while (frontNode != nullptr) {
            QueueNode* nextNode = frontNode->next;
            delete frontNode;
            frontNode = nextNode;
        }
    }

    bool enqueue(int value) {
        QueueNode* newNode = new QueueNode(value);
        if (rearNode == nullptr) {
            frontNode = rearNode = newNode;
            return true;
        }
        rearNode->next = newNode;
        rearNode = newNode;
        return true;
    }

    bool dequeue(int& value) {
        if (frontNode == nullptr) {
            return false;
        }
        QueueNode* node = frontNode;
        value = node->data;
        frontNode = node->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete node;
        return true;
    }
};

void buildNext(const string& pattern, int next[]) {
    // next[i] 表示模式串在 i 位置失配时，应跳回的位置。
    next[0] = -1;
    int i = 0;
    int j = -1;
    while (i < static_cast<int>(pattern.size()) - 1) {
        if (j == -1 || pattern[i] == pattern[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

void buildNextVal(const string& pattern, int nextVal[]) {
    int next[50];
    buildNext(pattern, next);
    nextVal[0] = -1;
    for (int i = 1; i < static_cast<int>(pattern.size()); ++i) {
        if (next[i] != -1 && pattern[i] == pattern[next[i]]) {
            nextVal[i] = nextVal[next[i]];
        } else {
            nextVal[i] = next[i];
        }
    }
}

int kmpSearch(const string& text, const string& pattern) {
    if (pattern.empty()) {
        return 0;
    }
    int next[50];
    buildNext(pattern, next);

    int i = 0;
    int j = 0;
    while (i < static_cast<int>(text.size()) && j < static_cast<int>(pattern.size())) {
        if (j == -1 || text[i] == pattern[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    if (j == static_cast<int>(pattern.size())) {
        return i - j;
    }
    return -1;
}

bool bracketMatch(const string& text) {
    SeqStack stack;
    for (char ch : text) {
        if (ch == '(' || ch == '[' || ch == '{') {
            stack.push(static_cast<int>(ch));
        } else if (ch == ')' || ch == ']' || ch == '}') {
            int topValue = 0;
            if (!stack.pop(topValue)) {
                return false;
            }
            char leftBracket = static_cast<char>(topValue);
            if ((leftBracket == '(' && ch != ')') ||
                (leftBracket == '[' && ch != ']') ||
                (leftBracket == '{' && ch != '}')) {
                return false;
            }
        }
    }
    return stack.empty();
}

int main() {
    cout << "=== 顺序栈 ===\n";
    SeqStack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    int topValue = 0;
    if (stack.getTop(topValue)) {
        cout << "top: " << topValue << '\n';
    }
    int stackValue = 0;
    while (stack.pop(stackValue)) {
        cout << stackValue << ' ';
    }
    cout << '\n';

    cout << "\n=== 循环队列 ===\n";
    CircularQueue queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    int queueValue = 0;
    while (queue.dequeue(queueValue)) {
        cout << queueValue << ' ';
    }
    cout << '\n';

    cout << "\n=== 链队列 ===\n";
    LinkedQueue linkedQueue;
    linkedQueue.enqueue(100);
    linkedQueue.enqueue(200);
    linkedQueue.enqueue(300);
    while (linkedQueue.dequeue(queueValue)) {
        cout << queueValue << ' ';
    }
    cout << '\n';

    cout << "\n=== KMP 模式匹配 ===\n";
    string text = "ababcabcacbab";
    string pattern = "abcac";
    cout << "match index: " << kmpSearch(text, pattern) << '\n';
    int nextVal[50];
    buildNextVal(pattern, nextVal);
    cout << "nextval: ";
    for (int i = 0; i < static_cast<int>(pattern.size()); ++i) {
        cout << nextVal[i] << ' ';
    }
    cout << '\n';

    cout << "\n=== 括号匹配 ===\n";
    cout << "{[()()]} -> " << (bracketMatch("{[()()]}") ? "true" : "false") << '\n';
    cout << "{[(])} -> " << (bracketMatch("{[(])}") ? "true" : "false") << '\n';

    return 0;
}
