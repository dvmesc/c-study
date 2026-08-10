#include <iostream>

using namespace std;

// 一维数组顺序存储：地址 = 基地址 + 下标 * 元素大小。
class OneDimArray {
private:
    int data[10];
    int length;

public:
    OneDimArray() : data(), length(10) {}

    void set(int index, int value) {
        if (index < 0 || index >= length) {
            return;
        }
        data[index] = value;
    }

    int get(int index) const {
        if (index < 0 || index >= length) {
            return -1;
        }
        return data[index];
    }

    void print() const {
        for (int i = 0; i < length; ++i) {
            cout << data[i] << ' ';
        }
        cout << '\n';
    }
};

// 二维数组按行优先存储到一维空间中。
class MatrixArray {
private:
    static const int ROWS = 3;
    static const int COLS = 4;
    int data[ROWS * COLS];

    int index(int row, int col) const {
        return row * COLS + col;
    }

public:
    MatrixArray() : data() {}

    void set(int row, int col, int value) {
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            return;
        }
        data[index(row, col)] = value;
    }

    int get(int row, int col) const {
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            return -1;
        }
        return data[index(row, col)];
    }

    void print() const {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                cout << get(i, j) << ' ';
            }
            cout << '\n';
        }
    }
};

int main() {
    // 演示：一维数组和二维数组的顺序存储。
    OneDimArray arr;
    for (int i = 0; i < 10; ++i) {
        arr.set(i, i * 10);
    }
    arr.print();

    MatrixArray matrix;
    int value = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix.set(i, j, value++);
        }
    }
    matrix.print();

    cout << "matrix[2][3] = " << matrix.get(2, 3) << '\n';
    return 0;
}
