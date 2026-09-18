#include <iostream>

using namespace std;

// 排序是 408 的稳定高频内容。
// 这里给出插入排序、冒泡排序和快速排序，方便比较不同算法的思想。

void printArray(const int data[], int length) {
    for (int i = 0; i < length; ++i) {
        cout << data[i] << ' ';
    }
    cout << '\n';
}

void insertionSort(int data[], int length) {
    for (int i = 1; i < length; ++i) {
        int current = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > current) {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = current;
    }
}

void bubbleSort(int data[], int length) {
    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - 1 - i; ++j) {
            if (data[j] > data[j + 1]) {
                int temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

int partition(int data[], int left, int right) {
    int pivot = data[left];
    while (left < right) {
        while (left < right && data[right] >= pivot) {
            --right;
        }
        data[left] = data[right];
        while (left < right && data[left] <= pivot) {
            ++left;
        }
        data[right] = data[left];
    }
    data[left] = pivot;
    return left;
}

void quickSort(int data[], int left, int right) {
    if (left >= right) {
        return;
    }
    int pivotIndex = partition(data, left, right);
    quickSort(data, left, pivotIndex - 1);
    quickSort(data, pivotIndex + 1, right);
}

int main() {
    int data1[] = {49, 38, 65, 97, 76, 13, 27};
    int data2[] = {49, 38, 65, 97, 76, 13, 27};
    int data3[] = {49, 38, 65, 97, 76, 13, 27};
    int length = sizeof(data1) / sizeof(data1[0]);

    insertionSort(data1, length);
    cout << "insertion sort: ";
    printArray(data1, length);

    bubbleSort(data2, length);
    cout << "bubble sort: ";
    printArray(data2, length);

    quickSort(data3, 0, length - 1);
    cout << "quick sort: ";
    printArray(data3, length);

    return 0;
}
