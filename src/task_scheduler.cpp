#include "task_scheduler.hpp"
#include <algorithm>
#include <vector>
#include <random>

TaskScheduler::TaskScheduler(int task_num, int dependency_num)
    : task_num_(task_num), dependency_num_(dependency_num) {
    graph_ = std::vector<std::vector<int>>(task_num);
    graph_.resize(task_num);
    visited = std::vector<bool>(task_num, false);
}

void TaskScheduler::dfs_visit(int num) {
    if (visited[num] == true) return;
    visited[num] = true;
    for (const auto& node : graph_[num]) {
        dfs_visit(node);
    }
    top_sort.push_back(num);
}

void TaskScheduler::generate_dgraph() {
    std::vector<std::pair<int, int>> edges;
    for (size_t i = 0; i < task_num_; i++) {
        for (size_t j = i + 1; j < task_num_; j++) {
            edges.push_back({i, j});
        }
    }
    std::random_device rd;
    std::mt19937 rdm(rd());
    std::shuffle(edges.begin(), edges.end(), rdm);

    for (size_t i = 0; i < dependency_num_; i++) {
        int src = edges[i].first;
        int dest = edges[i].second;
        graph_[src].push_back(dest);
    }
}

void TaskScheduler::topological_sort() {
    for (size_t i = 0; i < graph_.size(); i++) {
        dfs_visit(i);
    }
}
