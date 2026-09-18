#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 图部分通常考存储方式、遍历、最小生成树、最短路径和拓扑排序。
// 这里先给出最基础的邻接表、DFS 和 BFS。

class Graph {
private:
    vector<vector<int>> adj;

    void dfsImpl(int vertex, vector<bool>& visited) const {
        visited[vertex] = true;
        cout << vertex << ' ';
        for (int next : adj[vertex]) {
            if (!visited[next]) {
                dfsImpl(next, visited);
            }
        }
    }

public:
    explicit Graph(int vertexCount) : adj(vertexCount) {}

    void addEdge(int from, int to) {
        // 这里演示无向图，所以双向建边。
        adj[from].push_back(to);
        adj[to].push_back(from);
    }

    void dfs(int start) const {
        vector<bool> visited(adj.size(), false);
        dfsImpl(start, visited);
        cout << '\n';
    }

    void bfs(int start) const {
        vector<bool> visited(adj.size(), false);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << ' ';

            for (int next : adj[current]) {
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        cout << '\n';
    }
};

int main() {
    Graph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);

    cout << "DFS: ";
    graph.dfs(0);

    cout << "BFS: ";
    graph.bfs(0);

    return 0;
}
