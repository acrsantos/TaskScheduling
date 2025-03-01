#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <list>

using GraphType = std::vector<std::vector<int>>;
class Graph {
public:
    Graph(int task_num, int dependency_num) : m_taskNum(task_num), m_dependencyNum(dependency_num) {
        // graph = GraphType(task_num);
        graph.resize(task_num);
    }

    GraphType graph;
private:
    int m_taskNum;
    int m_dependencyNum;
};

bool* visited = new bool[100];
std::list<int> topological_sort {};

void DFS(GraphType& graph, int num) {
    if (visited[num] == true) return;
    visited[num] = true;
    for (const auto& node : graph[num]) { DFS(graph, node);
    }
    topological_sort.push_front(num);
}

int main() {
    Graph g(8, 10);

    std::vector<std::vector<int>> edges;
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            edges.push_back({i, j});
        }
    }

    std::random_device rd;
    std::mt19937 rdm(rd());
    std::shuffle(edges.begin(), edges.end(), rdm);

    for (const auto& edge : edges) {
        // std::cout << "EDGE: " << edge[0] << ' ' << edge[1] << '\n';
    }

    for (int i = 0; i < 10; i++) {
        int src  = edges[i][0];
        int dest = edges[i][1];
        g.graph[src].push_back(dest);
    }

    for (const auto& edge : g.graph) {
        std::cout << "EDGE: ";
        for (const auto& num : edge) {
            std::cout << num << ' ';
        }
        std::cout << '\n';
    }

    DFS(g.graph, 0);
    for (const auto& num : topological_sort) {
        std::cout << num << ' ';
    }

    return 0;
}
