#include <iostream>

using namespace std;

const int MAX_V = 6;
const int INF = 1000000000;

struct Edge {
    int u;
    int v;
    int w;
};

class UnionFind {
private:
    int parent[MAX_V];

public:
    explicit UnionFind(int n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) {
            return false;
        }
        parent[rootY] = rootX;
        return true;
    }
};

void sortEdges(Edge edges[], int m) {
    for (int i = 0; i < m - 1; ++i) {
        for (int j = 0; j < m - 1 - i; ++j) {
            if (edges[j].w > edges[j + 1].w) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

void primMST(const int graph[MAX_V][MAX_V], int n) {
    int lowCost[MAX_V];
    int parent[MAX_V];
    bool visited[MAX_V] = {false};

    for (int i = 0; i < n; ++i) {
        lowCost[i] = graph[0][i];
        parent[i] = 0;
    }
    visited[0] = true;

    int totalWeight = 0;
    cout << "prim edges:\n";

    for (int i = 1; i < n; ++i) {
        int minCost = INF;
        int k = -1;

        for (int j = 0; j < n; ++j) {
            if (!visited[j] && lowCost[j] < minCost) {
                minCost = lowCost[j];
                k = j;
            }
        }

        visited[k] = true;
        totalWeight += minCost;
        cout << parent[k] << " - " << k << " : " << minCost << '\n';

        for (int j = 0; j < n; ++j) {
            if (!visited[j] && graph[k][j] < lowCost[j]) {
                lowCost[j] = graph[k][j];
                parent[j] = k;
            }
        }
    }

    cout << "prim total weight: " << totalWeight << '\n';
}

void kruskalMST(Edge edges[], int n, int m) {
    sortEdges(edges, m);
    UnionFind uf(n);
    int totalWeight = 0;
    int edgeCount = 0;

    cout << "kruskal edges:\n";
    for (int i = 0; i < m && edgeCount < n - 1; ++i) {
        if (uf.unite(edges[i].u, edges[i].v)) {
            cout << edges[i].u << " - " << edges[i].v << " : " << edges[i].w << '\n';
            totalWeight += edges[i].w;
            ++edgeCount;
        }
    }
    cout << "kruskal total weight: " << totalWeight << '\n';
}

int main() {
    // 演示：Prim 和 Kruskal 最小生成树。
    int graph[MAX_V][MAX_V] = {
        {0, 6, 1, 5, INF, INF},
        {6, 0, 5, INF, 3, INF},
        {1, 5, 0, 5, 6, 4},
        {5, INF, 5, 0, INF, 2},
        {INF, 3, 6, INF, 0, 6},
        {INF, INF, 4, 2, 6, 0}
    };

    Edge edges[] = {
        {0, 1, 6}, {0, 2, 1}, {0, 3, 5},
        {1, 2, 5}, {1, 4, 3},
        {2, 3, 5}, {2, 4, 6}, {2, 5, 4},
        {3, 5, 2}, {4, 5, 6}
    };

    primMST(graph, MAX_V);
    kruskalMST(edges, MAX_V, sizeof(edges) / sizeof(edges[0]));
    return 0;
}
