#include <iostream>

using namespace std;

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
    // 演示：对称矩阵压缩存储。
    SymmetricMatrix matrix;
    matrix.set(0, 0, 1);
    matrix.set(1, 0, 2);
    matrix.set(1, 1, 3);
    matrix.set(2, 0, 4);
    matrix.set(2, 1, 5);
    matrix.set(2, 2, 6);
    matrix.set(3, 0, 7);
    matrix.set(3, 1, 8);
    matrix.set(3, 2, 9);
    matrix.set(3, 3, 10);
    matrix.print();

    cout << '\n';

    // 演示：稀疏矩阵三元组压缩存储。
    SparseMatrix sparse(4, 5);
    sparse.addTerm(0, 1, 7);
    sparse.addTerm(1, 3, 5);
    sparse.addTerm(2, 0, 9);
    sparse.addTerm(3, 4, 2);
    sparse.printTriples();

    cout << '\n';
    sparse.printMatrix();
    return 0;
}
