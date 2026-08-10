#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 邻接表图：适合表示稀疏图。
class Graph {
private:
    int n;
    vector<vector<int>> adj;

    // 深度优先遍历会沿着一条路径一直往下走。
    void dfsImpl(int u, vector<bool>& visited) const {
        visited[u] = true;
        cout << u << ' ';
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfsImpl(v, visited);
            }
        }
    }

public:
    // 初始化指定顶点数的邻接表图。
    explicit Graph(int vertices) : n(vertices), adj(vertices) {}

    // 默认添加无向边，便于学习 BFS / DFS。
    void addEdge(int u, int v, bool undirected = true) {
        adj[u].push_back(v);
        if (undirected) {
            adj[v].push_back(u);
        }
    }

    // 从起点开始做深度优先遍历。
    void dfs(int start) const {
        vector<bool> visited(n, false);
        dfsImpl(start, visited);
        cout << '\n';
    }

    // 从起点开始做广度优先遍历。
    void bfs(int start) const {
        vector<bool> visited(n, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << ' ';

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << '\n';
    }
};

// 邻接矩阵图：适合学习图的另一种基本存储方式。
class MatrixGraph {
private:
    static const int MAX_V = 6;
    int vertexCount;
    int matrix[MAX_V][MAX_V];

    // 邻接矩阵上的 DFS 递归实现。
    void dfsImpl(int u, bool visited[]) const {
        visited[u] = true;
        cout << u << ' ';
        for (int v = 0; v < vertexCount; ++v) {
            if (matrix[u][v] != 0 && !visited[v]) {
                dfsImpl(v, visited);
            }
        }
    }

public:
    // 初始化指定顶点数的邻接矩阵图。
    explicit MatrixGraph(int n) : vertexCount(n), matrix() {}

    // 添加一条无向边。
    void addEdge(int u, int v) {
        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }

    // 从起点开始做深度优先遍历。
    void dfs(int start) const {
        bool visited[MAX_V] = {false};
        dfsImpl(start, visited);
        cout << '\n';
    }

    // 从起点开始做广度优先遍历。
    void bfs(int start) const {
        bool visited[MAX_V] = {false};
        int queue[MAX_V];
        int front = 0;
        int rear = 0;

        visited[start] = true;
        queue[rear++] = start;

        while (front < rear) {
            int u = queue[front++];
            cout << u << ' ';

            for (int v = 0; v < vertexCount; ++v) {
                if (matrix[u][v] != 0 && !visited[v]) {
                    visited[v] = true;
                    queue[rear++] = v;
                }
            }
        }
        cout << '\n';
    }

    // 输出整个邻接矩阵。
    void printMatrix() const {
        for (int i = 0; i < vertexCount; ++i) {
            for (int j = 0; j < vertexCount; ++j) {
                cout << matrix[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};

int main() {
    // 演示：邻接表与邻接矩阵两种图存储方式的 DFS 和 BFS。
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    cout << "DFS: ";
    g.dfs(0);

    cout << "BFS: ";
    g.bfs(0);

    MatrixGraph mg(5);
    mg.addEdge(0, 1);
    mg.addEdge(0, 2);
    mg.addEdge(1, 3);
    mg.addEdge(2, 4);

    cout << "matrix:\n";
    mg.printMatrix();

    cout << "matrix dfs: ";
    mg.dfs(0);

    cout << "matrix bfs: ";
    mg.bfs(0);

    return 0;
}
