#include <iostream>

using namespace std;

const int MAX_V = 5;
const int INF = 1000000000;

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

    cout << "dijkstra from " << start << ":\n";
    for (int v = 0; v < n; ++v) {
        cout << "to " << v << " distance = " << dist[v] << ", path = ";
        printPath(predecessor, v);
        cout << '\n';
    }
}

void floyd(int graph[MAX_V][MAX_V], int n) {
    int dist[MAX_V][MAX_V];
    int path[MAX_V][MAX_V];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = graph[i][j];
            path[i][j] = (i != j && graph[i][j] < INF) ? i : -1;
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }

    cout << "floyd distance matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] >= INF) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << ' ';
            }
        }
        cout << '\n';
    }
}

int main() {
    // 演示：Dijkstra 单源最短路径和 Floyd 多源最短路径。
    int graph[MAX_V][MAX_V] = {
        {0, 10, INF, 30, 100},
        {INF, 0, 50, INF, INF},
        {INF, INF, 0, INF, 10},
        {INF, INF, 20, 0, 60},
        {INF, INF, INF, INF, 0}
    };

    dijkstra(graph, MAX_V, 0);
    floyd(graph, MAX_V);
    return 0;
}
