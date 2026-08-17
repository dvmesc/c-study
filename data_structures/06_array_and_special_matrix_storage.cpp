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

// 对称矩阵压缩存储：只保存下三角部分。
class SymmetricMatrix {
private:
    static const int N = 4;
    int data[N * (N + 1) / 2];

    int index(int row, int col) const {
        if (row < col) {
            int temp = row;
            row = col;
            col = temp;
        }
        return row * (row + 1) / 2 + col;
    }

public:
    SymmetricMatrix() : data() {}

    void set(int row, int col, int value) {
        if (row < 0 || row >= N || col < 0 || col >= N) {
            return;
        }
        data[index(row, col)] = value;
    }

    int get(int row, int col) const {
        if (row < 0 || row >= N || col < 0 || col >= N) {
            return -1;
        }
        return data[index(row, col)];
    }

    void print() const {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << get(i, j) << ' ';
            }
            cout << '\n';
        }
    }
};

// 三元组顺序表：适合保存稀疏矩阵中的非零元素。
struct Triple {
    int row;
    int col;
    int value;
};

class SparseMatrix {
private:
    static const int MAX_TERMS = 20;
    Triple terms[MAX_TERMS];
    int rows;
    int cols;
    int count;

public:
    SparseMatrix(int r, int c) : terms(), rows(r), cols(c), count(0) {}

    void addTerm(int row, int col, int value) {
        if (count >= MAX_TERMS || value == 0) {
            return;
        }
        terms[count].row = row;
        terms[count].col = col;
        terms[count].value = value;
        ++count;
    }

    void printTriples() const {
        for (int i = 0; i < count; ++i) {
            cout << "(" << terms[i].row << ", " << terms[i].col << ", " << terms[i].value << ")\n";
        }
    }

    void printMatrix() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int value = 0;
                for (int k = 0; k < count; ++k) {
                    if (terms[k].row == i && terms[k].col == j) {
                        value = terms[k].value;
                        break;
                    }
                }
                cout << value << ' ';
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

    cout << '\n';

    // 演示：对称矩阵压缩存储。
    SymmetricMatrix symmetricMatrix;
    symmetricMatrix.set(0, 0, 1);
    symmetricMatrix.set(1, 0, 2);
    symmetricMatrix.set(1, 1, 3);
    symmetricMatrix.set(2, 0, 4);
    symmetricMatrix.set(2, 1, 5);
    symmetricMatrix.set(2, 2, 6);
    symmetricMatrix.set(3, 0, 7);
    symmetricMatrix.set(3, 1, 8);
    symmetricMatrix.set(3, 2, 9);
    symmetricMatrix.set(3, 3, 10);
    symmetricMatrix.print();

    cout << '\n';

    // 演示：稀疏矩阵三元组压缩存储。
    SparseMatrix sparseMatrix(4, 5);
    sparseMatrix.addTerm(0, 1, 7);
    sparseMatrix.addTerm(1, 3, 5);
    sparseMatrix.addTerm(2, 0, 9);
    sparseMatrix.addTerm(3, 4, 2);
    sparseMatrix.printTriples();

    cout << '\n';
    sparseMatrix.printMatrix();
    return 0;
}
