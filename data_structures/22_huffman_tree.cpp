#include <iostream>

using namespace std;

struct HuffmanNode {
    int weight;
    int parent;
    int left;
    int right;
};

// 在当前未被合并的结点中选出权值最小的一个。
int selectMin(const HuffmanNode tree[], int end) {
    int minIndex = -1;
    for (int i = 1; i <= end; ++i) {
        if (tree[i].parent != 0) {
            continue;
        }
        if (minIndex == -1 || tree[i].weight < tree[minIndex].weight) {
            minIndex = i;
        }
    }
    return minIndex;
}

// 根据权值数组构造哈夫曼树。
void createHuffmanTree(HuffmanNode tree[], const int weights[], int n) {
    int total = 2 * n - 1;
    for (int i = 1; i <= total; ++i) {
        tree[i].weight = 0;
        tree[i].parent = 0;
        tree[i].left = 0;
        tree[i].right = 0;
    }

    for (int i = 1; i <= n; ++i) {
        tree[i].weight = weights[i - 1];
    }

    for (int i = n + 1; i <= total; ++i) {
        int s1 = selectMin(tree, i - 1);
        tree[s1].parent = -1;
        int s2 = selectMin(tree, i - 1);
        tree[s2].parent = i;
        tree[s1].parent = i;
        tree[i].left = s1;
        tree[i].right = s2;
        tree[i].weight = tree[s1].weight + tree[s2].weight;
    }
}

// 输出哈夫曼树的顺序存储结构。
void printHuffmanTree(const HuffmanNode tree[], int total) {
    cout << "index weight parent left right\n";
    for (int i = 1; i <= total; ++i) {
        cout << i << "     "
             << tree[i].weight << "      "
             << tree[i].parent << "      "
             << tree[i].left << "    "
             << tree[i].right << '\n';
    }
}

// 从叶子回溯到根，输出每个结点的哈夫曼编码。
void printCodes(const HuffmanNode tree[], int n) {
    char code[100];
    code[n - 1] = '\0';

    for (int i = 1; i <= n; ++i) {
        int start = n - 1;
        int child = i;
        int parent = tree[child].parent;

        while (parent != 0) {
            if (tree[parent].left == child) {
                code[--start] = '0';
            } else {
                code[--start] = '1';
            }
            child = parent;
            parent = tree[child].parent;
        }

        cout << "node " << i << " weight " << tree[i].weight
             << " code: " << (code + start) << '\n';
    }
}

// 计算哈夫曼树的带权路径长度 WPL。
int weightedPathLength(const HuffmanNode tree[], int n) {
    int result = 0;

    for (int i = 1; i <= n; ++i) {
        int depth = 0;
        int current = i;
        while (tree[current].parent != 0) {
            ++depth;
            current = tree[current].parent;
        }
        result += tree[i].weight * depth;
    }
    return result;
}

int main() {
    // 演示：哈夫曼树构造、哈夫曼编码和带权路径长度。
    int weights[] = {5, 29, 7, 8, 14, 23, 3, 11};
    int n = sizeof(weights) / sizeof(weights[0]);
    HuffmanNode tree[2 * 8] = {};

    createHuffmanTree(tree, weights, n);

    cout << "huffman tree:\n";
    printHuffmanTree(tree, 2 * n - 1);

    cout << "codes:\n";
    printCodes(tree, n);

    cout << "weighted path length: " << weightedPathLength(tree, n) << '\n';
    return 0;
}
