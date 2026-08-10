#include <iostream>

using namespace std;

const int MAX_V = 6;
const int INF = 1000000000;

// 拓扑排序：输出一个合法的顶点先后顺序。
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

// 关键路径：求 AOE 网中的关键活动。
void criticalPath(const int graph[MAX_V][MAX_V], int n) {
    int topo[MAX_V];
    if (!topologicalSort(graph, n, topo)) {
        cout << "graph has a cycle\n";
        return;
    }

    cout << "topological order: ";
    for (int i = 0; i < n; ++i) {
        cout << topo[i] << ' ';
    }
    cout << '\n';

    int ve[MAX_V] = {0};
    int vl[MAX_V];

    for (int i = 0; i < n; ++i) {
        int u = topo[i];
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] < INF && u != v) {
                if (ve[u] + graph[u][v] > ve[v]) {
                    ve[v] = ve[u] + graph[u][v];
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        vl[i] = ve[n - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        int u = topo[i];
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] < INF && u != v) {
                if (vl[v] - graph[u][v] < vl[u]) {
                    vl[u] = vl[v] - graph[u][v];
                }
            }
        }
    }

    cout << "critical activities:\n";
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] < INF && u != v) {
                int e = ve[u];
                int l = vl[v] - graph[u][v];
                if (e == l) {
                    cout << u << " -> " << v << " duration " << graph[u][v] << '\n';
                }
            }
        }
    }
}

int main() {
    // 演示：拓扑排序与关键路径。
    int graph[MAX_V][MAX_V] = {
        {0, 3, 2, INF, INF, INF},
        {INF, 0, INF, 2, 3, INF},
        {INF, INF, 0, 4, INF, INF},
        {INF, INF, INF, 0, INF, 2},
        {INF, INF, INF, INF, 0, 1},
        {INF, INF, INF, INF, INF, 0}
    };

    int topo[MAX_V];
    if (topologicalSort(graph, MAX_V, topo)) {
        cout << "topological sort result: ";
        for (int i = 0; i < MAX_V; ++i) {
            cout << topo[i] << ' ';
        }
        cout << '\n';
    }

    criticalPath(graph, MAX_V);
    return 0;
}
