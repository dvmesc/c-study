#include <iostream>
#include <vector>

using namespace std;

// 并查集：常用于判断元素是否属于同一连通块。
class UnionFind {
private:
    vector<int> parent;
    vector<int> rankValue;

public:
    explicit UnionFind(int n) : parent(n), rankValue(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // 路径压缩：查找根节点时顺手压平树高。
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA == rootB) {
            return;
        }

        if (rankValue[rootA] < rankValue[rootB]) {
            parent[rootA] = rootB;
        } else if (rankValue[rootA] > rankValue[rootB]) {
            parent[rootB] = rootA;
        } else {
            parent[rootB] = rootA;
            ++rankValue[rootA];
        }
    }

    bool isConnected(int a, int b) {
        return find(a) == find(b);
    }
};

int main() {
    // 演示：合并集合和连通性判断。
    UnionFind uf(6);
    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(3, 4);

    cout << uf.isConnected(0, 2) << '\n';
    cout << uf.isConnected(0, 4) << '\n';

    uf.unite(2, 4);
    cout << uf.isConnected(0, 4) << '\n';

    return 0;
}
