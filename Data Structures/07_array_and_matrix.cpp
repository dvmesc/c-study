#include <iostream>

using namespace std;

// 数组和特殊矩阵主要考顺序存储与压缩存储。
// 常见题目包括地址计算、对称矩阵压缩、稀疏矩阵三元组表示。

class MatrixArray {
private:
    static const int ROWS = 3;
    static const int COLS = 4;
    int data[ROWS * COLS];

    int index(int row, int col) const {
        return row * COLS + col;
    }

public:
    MatrixArray() : data{} {}

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
    SymmetricMatrix() : data{} {}

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
    SparseMatrix(int rowCount, int colCount) : terms{}, rows(rowCount), cols(colCount), count(0) {}

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
    cout << "=== 二维数组按行优先存储 ===\n";
    MatrixArray matrix;
    int value = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix.set(i, j, value++);
        }
    }
    matrix.print();
    cout << "matrix[2][3] = " << matrix.get(2, 3) << '\n';

    cout << "\n=== 对称矩阵压缩存储 ===\n";
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

    cout << "\n=== 稀疏矩阵三元组 ===\n";
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
