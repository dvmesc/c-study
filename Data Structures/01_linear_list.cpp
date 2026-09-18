#include <iostream>

using namespace std;

// 线性表是最基础的线性结构。
// 408 中通常要求掌握顺序存储和链式存储两种实现方式，
// 以及插入、删除、查找等基本操作的时间复杂度。

class SeqList {
private:
    static const int MAX_SIZE = 20;
    int data[MAX_SIZE];
    int length;

public:
    SeqList() : data{}, length(0) {}

    int size() const {
        return length;
    }

    bool get(int index, int& value) const {
        if (index < 0 || index >= length) {
            return false;
        }
        value = data[index];
        return true;
    }

    bool insert(int index, int value) {
        if (index < 0 || index > length || length >= MAX_SIZE) {
            return false;
        }
        // 顺序表插入需要整体后移。
        for (int i = length; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++length;
        return true;
    }

    bool removeAt(int index) {
        if (index < 0 || index >= length) {
            return false;
        }
        // 顺序表删除后需要整体前移。
        for (int i = index; i < length - 1; ++i) {
            data[i] = data[i + 1];
        }
        --length;
        return true;
    }

    int find(int value) const {
        for (int i = 0; i < length; ++i) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }

    void print() const {
        for (int i = 0; i < length; ++i) {
            cout << data[i] << ' ';
        }
        cout << '\n';
    }
};

struct ListNode {
    int data;
    ListNode* next;

    explicit ListNode(int value) : data(value), next(nullptr) {}
};

class SinglyLinkedList {
private:
    ListNode* head;

public:
    SinglyLinkedList() : head(new ListNode(0)) {}

    ~SinglyLinkedList() {
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    bool insertAfterPosition(int position, int value) {
        if (position < 0) {
            return false;
        }
        ListNode* current = head;
        for (int i = 0; i < position; ++i) {
            if (current->next == nullptr) {
                return false;
            }
            current = current->next;
        }
        ListNode* newNode = new ListNode(value);
        newNode->next = current->next;
        current->next = newNode;
        return true;
    }

    bool headInsert(int value) {
        ListNode* newNode = new ListNode(value);
        newNode->next = head->next;
        head->next = newNode;
        return true;
    }

    bool tailInsert(int value) {
        ListNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        ListNode* newNode = new ListNode(value);
        current->next = newNode;
        return true;
    }

    bool deleteValue(int value) {
        ListNode* current = head;
        while (current->next != nullptr) {
            if (current->next->data == value) {
                ListNode* node = current->next;
                current->next = node->next;
                delete node;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int find(int value) const {
        ListNode* current = head->next;
        int index = 0;
        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            ++index;
        }
        return -1;
    }

    int length() const {
        int count = 0;
        ListNode* current = head->next;
        while (current != nullptr) {
            ++count;
            current = current->next;
        }
        return count;
    }

    void reverse() {
        ListNode* current = head->next;
        ListNode* reversedHead = nullptr;
        while (current != nullptr) {
            ListNode* nextNode = current->next;
            current->next = reversedHead;
            reversedHead = current;
            current = nextNode;
        }
        head->next = reversedHead;
    }

    void print() const {
        ListNode* current = head->next;
        while (current != nullptr) {
            cout << current->data << ' ';
            current = current->next;
        }
        cout << '\n';
    }
};

int main() {
    cout << "=== 顺序表 ===\n";
    SeqList seqList;
    seqList.insert(0, 10);
    seqList.insert(1, 20);
    seqList.insert(1, 15);
    seqList.print();
    cout << "find 20: " << seqList.find(20) << '\n';
    cout << "size: " << seqList.size() << '\n';
    int seqValue = 0;
    if (seqList.get(1, seqValue)) {
        cout << "get(1): " << seqValue << '\n';
    }
    seqList.removeAt(1);
    seqList.print();

    cout << "\n=== 单链表 ===\n";
    SinglyLinkedList linkedList;
    linkedList.headInsert(100);
    linkedList.headInsert(80);
    linkedList.tailInsert(200);
    linkedList.insertAfterPosition(1, 150);
    linkedList.print();
    cout << "find 150: " << linkedList.find(150) << '\n';
    cout << "length: " << linkedList.length() << '\n';
    linkedList.deleteValue(200);
    linkedList.print();
    cout << "reverse: ";
    linkedList.reverse();
    linkedList.print();

    return 0;
}
