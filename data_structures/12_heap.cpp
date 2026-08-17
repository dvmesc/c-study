#include <iostream>
#include <vector>

using namespace std;

// 大根堆：父节点始终不小于子节点。
class MaxHeap {
private:
    vector<int> data;

    // 新元素上浮，直到满足堆性质。
    void shiftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (data[parent] >= data[index]) {
                break;
            }
            swap(data[parent], data[index]);
            index = parent;
        }
    }

    // 堆顶下沉，恢复大根堆结构。
    void shiftDown(int index) {
        int n = static_cast<int>(data.size());
        while (true) {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int largest = index;

            if (left < n && data[left] > data[largest]) {
                largest = left;
            }
            if (right < n && data[right] > data[largest]) {
                largest = right;
            }
            if (largest == index) {
                break;
            }
            swap(data[index], data[largest]);
            index = largest;
        }
    }

public:
    // 插入一个元素，并通过上浮恢复堆性质。
    void push(int value) {
        data.push_back(value);
        shiftUp(static_cast<int>(data.size()) - 1);
    }

    // 删除堆顶元素，并通过下沉恢复堆性质。
    bool pop() {
        if (empty()) {
            return false;
        }
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) {
            shiftDown(0);
        }
        return true;
    }

    // 返回当前堆顶。
    int top() const {
        if (empty()) {
            return -1;
        }
        return data[0];
    }

    // 判断堆是否为空。
    bool empty() const {
        return data.empty();
    }

    // 直接输出底层数组，便于观察堆的存储方式。
    void print() const {
        for (int value : data) {
            cout << value << ' ';
        }
        cout << '\n';
    }
};

// 小根堆：父节点始终不大于子节点。
class MinHeap {
private:
    vector<int> data;

    // 新元素上浮，直到满足小根堆性质。
    void shiftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (data[parent] <= data[index]) {
                break;
            }
            swap(data[parent], data[index]);
            index = parent;
        }
    }

    // 堆顶下沉，恢复小根堆结构。
    void shiftDown(int index) {
        int n = static_cast<int>(data.size());
        while (true) {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int smallest = index;

            if (left < n && data[left] < data[smallest]) {
                smallest = left;
            }
            if (right < n && data[right] < data[smallest]) {
                smallest = right;
            }
            if (smallest == index) {
                break;
            }
            swap(data[index], data[smallest]);
            index = smallest;
        }
    }

public:
    // 插入一个元素，并通过上浮恢复堆性质。
    void push(int value) {
        data.push_back(value);
        shiftUp(static_cast<int>(data.size()) - 1);
    }

    // 删除堆顶元素，并通过下沉恢复堆性质。
    bool pop() {
        if (empty()) {
            return false;
        }
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) {
            shiftDown(0);
        }
        return true;
    }

    // 返回当前堆顶。
    int top() const {
        if (empty()) {
            return -1;
        }
        return data[0];
    }

    // 判断堆是否为空。
    bool empty() const {
        return data.empty();
    }

    // 输出底层数组，便于观察小根堆结构。
    void print() const {
        for (int value : data) {
            cout << value << ' ';
        }
        cout << '\n';
    }
};

int main() {
    // 演示：大根堆与小根堆的插入、取堆顶和删除堆顶。
    MaxHeap maxHeap;
    maxHeap.push(10);
    maxHeap.push(40);
    maxHeap.push(20);
    maxHeap.push(60);
    maxHeap.push(30);

    cout << "max heap: ";
    maxHeap.print();
    cout << "max top: " << maxHeap.top() << '\n';

    maxHeap.pop();
    cout << "max heap after pop: ";
    maxHeap.print();
    cout << "max top after pop: " << maxHeap.top() << '\n';

    MinHeap minHeap;
    minHeap.push(40);
    minHeap.push(10);
    minHeap.push(30);
    minHeap.push(5);
    minHeap.push(20);

    cout << "min heap: ";
    minHeap.print();
    cout << "min top: " << minHeap.top() << '\n';

    minHeap.pop();
    cout << "min heap after pop: ";
    minHeap.print();
    cout << "min top after pop: " << minHeap.top() << '\n';

    return 0;
}
