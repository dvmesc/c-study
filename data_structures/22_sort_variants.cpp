#include <iostream>

using namespace std;

// 冒泡排序：每一轮把当前最大值“冒”到末尾。
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// 选择排序：每一轮从未排序区间里选出最小值。
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// 插入排序：将当前元素插入前面已排序区间的正确位置。
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// 快速排序：选一个基准，把小的放左边，大的放右边。
void quickSort(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;
    int pivot = arr[left];

    while (i < j) {
        while (i < j && arr[j] >= pivot) {
            --j;
        }
        while (i < j && arr[i] <= pivot) {
            ++i;
        }
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }

    arr[left] = arr[i];
    arr[i] = pivot;

    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
}

// 合并两个有序子区间。
void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (int p = left; p <= right; ++p) {
        arr[p] = temp[p];
    }
}

// 归并排序：先分治拆开，再有序合并。
void mergeSort(int arr[], int temp[], int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeSort(arr, temp, left, mid);
    mergeSort(arr, temp, mid + 1, right);
    merge(arr, temp, left, mid, right);
}

// 调整以 root 为根的子树，使其满足大根堆性质。
void heapAdjust(int arr[], int root, int length) {
    int temp = arr[root];
    int child = root * 2 + 1;

    while (child < length) {
        if (child + 1 < length && arr[child + 1] > arr[child]) {
            ++child;
        }
        if (temp >= arr[child]) {
            break;
        }
        arr[root] = arr[child];
        root = child;
        child = root * 2 + 1;
    }
    arr[root] = temp;
}

// 堆排序：先建大根堆，再不断把最大值放到末尾。
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapAdjust(arr, i, n);
    }

    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapAdjust(arr, 0, i);
    }
}

// 希尔排序：按缩小增量分组做插入排序。
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

// 找到数组中的最大值，供基数排序确定最高位数。
int getMaxValue(const int arr[], int n) {
    int maxValue = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }
    return maxValue;
}

// 按当前位 exp 做一次稳定计数排序。
void countingSortByDigit(int arr[], int n, int exp) {
    int output[100];
    int count[10] = {0};

    for (int i = 0; i < n; ++i) {
        int digit = (arr[i] / exp) % 10;
        ++count[digit];
    }

    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        --count[digit];
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

// 基数排序：按个位、十位、百位依次做稳定排序。
void radixSort(int arr[], int n) {
    int maxValue = getMaxValue(arr, n);
    for (int exp = 1; maxValue / exp > 0; exp *= 10) {
        countingSortByDigit(arr, n, exp);
    }
}

// 输出数组内容。
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}

int main() {
    // 对比基础排序、高级排序和补充排序的结果。
    int a1[] = {5, 1, 4, 2, 8};
    int a2[] = {5, 1, 4, 2, 8};
    int a3[] = {5, 1, 4, 2, 8};
    int a4[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int a5[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int a6[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int a7[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int a8[] = {329, 457, 657, 839, 436, 720, 355};
    int temp[8] = {0};
    int n = 5;
    int n2 = 8;
    int n3 = 7;

    bubbleSort(a1, n);
    selectionSort(a2, n);
    insertionSort(a3, n);
    quickSort(a4, 0, n2 - 1);
    mergeSort(a5, temp, 0, n2 - 1);
    heapSort(a6, n2);
    shellSort(a7, n2);
    radixSort(a8, n3);

    cout << "bubbleSort: ";
    printArray(a1, n);

    cout << "selectionSort: ";
    printArray(a2, n);

    cout << "insertionSort: ";
    printArray(a3, n);

    cout << "quickSort: ";
    printArray(a4, n2);

    cout << "mergeSort: ";
    printArray(a5, n2);

    cout << "heapSort: ";
    printArray(a6, n2);

    cout << "shellSort: ";
    printArray(a7, n2);

    cout << "radixSort: ";
    printArray(a8, n3);

    return 0;
}
