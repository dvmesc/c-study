#include <iostream>

using namespace std;

// 动态顺序表：底层使用连续内存，支持扩容。
class SeqList {
private:
    int* data;
    int size;
    int capacity;

    // 空间满了以后，将容量扩大为原来的 2 倍。
    void expand() {
        int newCapacity = capacity * 2;
        int* newData = new int[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    explicit SeqList(int cap = 10) : data(new int[cap]), size(0), capacity(cap) {}

    ~SeqList() {
        delete[] data;
    }

    int length() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    // 尾插是顺序表最常见的插入方式。
    void pushBack(int value) {
        if (size == capacity) {
            expand();
        }
        data[size++] = value;
    }

    bool insert(int index, int value) {
        if (index < 0 || index > size) {
            return false;
        }
        if (size == capacity) {
            expand();
        }
        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size;
        return true;
    }

    bool removeAt(int index) {
        if (index < 0 || index >= size) {
            return false;
        }
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
        return true;
    }

    int find(int value) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }

    int get(int index) const {
        if (index < 0 || index >= size) {
            return -1;
        }
        return data[index];
    }

    // 顺序输出当前表中的所有元素。
    void print() const {
        for (int i = 0; i < size; ++i) {
            cout << data[i] << ' ';
        }
        cout << '\n';
    }
};

int main() {
    // 演示：尾插、按位置插入、删除、查找。
    SeqList list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.insert(1, 15);
    list.print();

    cout << "find 20: " << list.find(20) << '\n';
    list.removeAt(2);
    list.print();

    return 0;
}
