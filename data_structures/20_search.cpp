#include <iostream>

using namespace std;

// 顺序查找：从头到尾逐个比较。
int sequentialSearch(const int arr[], int n, int target) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// 折半查找：要求数组已经有序。
int binarySearch(const int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// 分块查找的简单示例：先定位块，再在块内顺序查找。
int blockSearch(const int arr[], const int indexArr[], int blockSize, int blockCount, int target) {
    int block = -1;
    for (int i = 0; i < blockCount; ++i) {
        if (target <= indexArr[i]) {
            block = i;
            break;
        }
    }
    if (block == -1) {
        return -1;
    }

    int start = block * blockSize;
    int end = start + blockSize;
    for (int i = start; i < end; ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int main() {
    // 演示：顺序查找、折半查找、分块查找。
    int arr[] = {3, 8, 12, 15, 19, 21, 27, 30, 34};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "sequential search 19: " << sequentialSearch(arr, n, 19) << '\n';
    cout << "binary search 21: " << binarySearch(arr, n, 21) << '\n';

    int blockArr[] = {5, 8, 12, 17, 23, 28, 31, 36, 40};
    int indexArr[] = {12, 28, 40};
    cout << "block search 23: " << blockSearch(blockArr, indexArr, 3, 3, 23) << '\n';
    return 0;
}
