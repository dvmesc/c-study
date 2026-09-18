#include <iostream>

using namespace std;

// 这一文件补完整排序体系，方便对照 408 常考排序。
// 重点关注时间复杂度、空间复杂度和稳定性。

void printArray(const int data[], int length) {
    for (int i = 0; i < length; ++i) {
        cout << data[i] << ' ';
    }
    cout << '\n';
}

void selectionSort(int data[], int length) {
    for (int i = 0; i < length - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < length; ++j) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        int temp = data[i];
        data[i] = data[minIndex];
        data[minIndex] = temp;
    }
}

void shellSort(int data[], int length) {
    for (int gap = length / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < length; ++i) {
            int current = data[i];
            int j = i;
            while (j >= gap && data[j - gap] > current) {
                data[j] = data[j - gap];
                j -= gap;
            }
            data[j] = current;
        }
    }
}

void heapAdjust(int data[], int root, int length) {
    int temp = data[root];
    int child = root * 2 + 1;
    while (child < length) {
        if (child + 1 < length && data[child + 1] > data[child]) {
            ++child;
        }
        if (temp >= data[child]) {
            break;
        }
        data[root] = data[child];
        root = child;
        child = root * 2 + 1;
    }
    data[root] = temp;
}

void heapSort(int data[], int length) {
    for (int i = length / 2 - 1; i >= 0; --i) {
        heapAdjust(data, i, length);
    }
    for (int i = length - 1; i > 0; --i) {
        int temp = data[0];
        data[0] = data[i];
        data[i] = temp;
        heapAdjust(data, 0, i);
    }
}

void merge(int data[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    while (i <= mid && j <= right) {
        if (data[i] <= data[j]) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = data[i++];
    }
    while (j <= right) {
        temp[k++] = data[j++];
    }
    for (int p = left; p <= right; ++p) {
        data[p] = temp[p];
    }
}

void mergeSort(int data[], int temp[], int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(data, temp, left, mid);
    mergeSort(data, temp, mid + 1, right);
    merge(data, temp, left, mid, right);
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

int getMaxValue(const int data[], int length) {
    int maxValue = data[0];
    for (int i = 1; i < length; ++i) {
        if (data[i] > maxValue) {
            maxValue = data[i];
        }
    }
    return maxValue;
}

void countingSortByDigit(int data[], int length, int exp) {
    int output[100];
    int count[10] = {0};
    for (int i = 0; i < length; ++i) {
        int digit = (data[i] / exp) % 10;
        ++count[digit];
    }
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }
    for (int i = length - 1; i >= 0; --i) {
        int digit = (data[i] / exp) % 10;
        output[count[digit] - 1] = data[i];
        --count[digit];
    }
    for (int i = 0; i < length; ++i) {
        data[i] = output[i];
    }
}

void radixSort(int data[], int length) {
    int maxValue = getMaxValue(data, length);
    for (int exp = 1; maxValue / exp > 0; exp *= 10) {
        countingSortByDigit(data, length, exp);
    }
}

int main() {
    int data1[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int data2[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int data3[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int data4[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int data5[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int data6[] = {329, 457, 657, 839, 436, 720, 355};
    int temp[8] = {0};
    int n = 8;
    int n2 = 7;

    selectionSort(data1, n);
    cout << "selection sort: ";
    printArray(data1, n);

    shellSort(data2, n);
    cout << "shell sort: ";
    printArray(data2, n);

    heapSort(data3, n);
    cout << "heap sort: ";
    printArray(data3, n);

    mergeSort(data4, temp, 0, n - 1);
    cout << "merge sort: ";
    printArray(data4, n);

    quickSort(data5, 0, n - 1);
    cout << "quick sort: ";
    printArray(data5, n);

    radixSort(data6, n2);
    cout << "radix sort: ";
    printArray(data6, n2);

    return 0;
}
