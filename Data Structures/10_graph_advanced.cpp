#include <iostream>

using namespace std;

// 图的高级部分通常包括最小生成树、最短路径、拓扑排序和关键路径。
// 这些都是 408 综合题的高频来源。

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

    cout << "Prim:\n";
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
        cout << parent[k] << " - " << k << " : " << minCost << '\n';
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && graph[k][j] < lowCost[j]) {
                lowCost[j] = graph[k][j];
                parent[j] = k;
            }
        }
    }
}

void kruskalMST(Edge edges[], int n, int m) {
    sortEdges(edges, m);
    UnionFind uf(n);
    cout << "Kruskal:\n";
    int edgeCount = 0;
    for (int i = 0; i < m && edgeCount < n - 1; ++i) {
        if (uf.unite(edges[i].u, edges[i].v)) {
            cout << edges[i].u << " - " << edges[i].v << " : " << edges[i].w << '\n';
            ++edgeCount;
        }
    }
}

void printPath(int predecessor[], int v) {
    if (predecessor[v] == -1) {
        cout << v;
        return;
    }
    printPath(predecessor, predecessor[v]);
    cout << " -> " << v;
}

void dijkstra(const int graph[MAX_V][MAX_V], int n, int start) {
    int dist[MAX_V];
    int predecessor[MAX_V];
    bool visited[MAX_V] = {false};

    for (int i = 0; i < n; ++i) {
        dist[i] = graph[start][i];
        predecessor[i] = (graph[start][i] < INF && i != start) ? start : -1;
    }
    dist[start] = 0;
    visited[start] = true;

    for (int i = 1; i < n; ++i) {
        int minDist = INF;
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        visited[u] = true;
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && graph[u][v] < INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                predecessor[v] = u;
            }
        }
    }

    cout << "Dijkstra from " << start << ":\n";
    for (int v = 0; v < n; ++v) {
        cout << "to " << v << " distance = " << dist[v] << " path = ";
        printPath(predecessor, v);
        cout << '\n';
    }
}

bool topologicalSort(const int graph[MAX_V][MAX_V], int n, int topo[]) {
    int indegree[MAX_V] = {0};
    int stack[MAX_V];
    int top = -1;
    int count = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph[i][j] < INF && i != j) {
                ++indegree[j];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            stack[++top] = i;
        }
    }

    while (top >= 0) {
        int u = stack[top--];
        topo[count++] = u;
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] < INF && u != v) {
                --indegree[v];
                if (indegree[v] == 0) {
                    stack[++top] = v;
                }
            }
        }
    }

    return count == n;
}

void criticalPath(const int graph[MAX_V][MAX_V], int n) {
    int topo[MAX_V];
    if (!topologicalSort(graph, n, topo)) {
        cout << "graph has cycle\n";
        return;
    }

    int ve[MAX_V] = {0};
    int vl[MAX_V];
    for (int i = 0; i < n; ++i) {
        int u = topo[i];
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] < INF && u != v && ve[u] + graph[u][v] > ve[v]) {
                ve[v] = ve[u] + graph[u][v];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        vl[i] = ve[n - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        int u = topo[i];
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] < INF && u != v && vl[v] - graph[u][v] < vl[u]) {
                vl[u] = vl[v] - graph[u][v];
            }
        }
    }

    cout << "Critical Path:\n";
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] < INF && u != v) {
                int e = ve[u];
                int l = vl[v] - graph[u][v];
                if (e == l) {
                    cout << u << " -> " << v << " : " << graph[u][v] << '\n';
                }
            }
        }
    }
}

int main() {
    int undirectedGraph[MAX_V][MAX_V] = {
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

    int directedGraph[MAX_V][MAX_V] = {
        {0, 3, 2, INF, INF, INF},
        {INF, 0, INF, 2, 3, INF},
        {INF, INF, 0, 4, INF, INF},
        {INF, INF, INF, 0, INF, 2},
        {INF, INF, INF, INF, 0, 1},
        {INF, INF, INF, INF, INF, 0}
    };

    primMST(undirectedGraph, MAX_V);
    cout << '\n';
    kruskalMST(edges, MAX_V, sizeof(edges) / sizeof(edges[0]));
    cout << '\n';
    dijkstra(undirectedGraph, MAX_V, 0);
    cout << '\n';
    int topo[MAX_V];
    if (topologicalSort(directedGraph, MAX_V, topo)) {
        cout << "Topological Sort: ";
        for (int i = 0; i < MAX_V; ++i) {
            cout << topo[i] << ' ';
        }
        cout << "\n\n";
    }
    criticalPath(directedGraph, MAX_V);

    return 0;
}
