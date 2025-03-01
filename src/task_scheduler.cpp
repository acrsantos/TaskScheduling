#include "task_scheduler.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

TaskScheduler::TaskScheduler(int task_num, int dependency_num)
    : task_num_(task_num), dependency_num_(dependency_num) { 
    graph_ = std::vector<std::vector<int>>(task_num);
    graph_.resize(task_num);
    visited = std::vector<bool>(task_num, false);
    rec_stack = std::vector<bool>(task_num, false);
    for (size_t i = 0; i < task_num; i++) {
        task_names_.push_back("Task " + std::to_string(i + 1));
    }
}

void TaskScheduler::dfs_visit(int num) {
    if (rec_stack[num] == true) {
        std::cout << "Cycle detected at Task: " << num + 1 << '\n';
        return;
    }

    if (visited[num] == true) return;
    visited[num] = true;
    rec_stack[num] = true;
    std::cout << "Processing: " << num + 1 << '\n';
    for (const auto& node : graph_[num]) {
        dfs_visit(node);
    }
    top_sort.push_front(num);
    rec_stack[num] = false;
    std::cout << "\tFinished Processing: " << num << '\n';
    std::cout << "\tTopological sort: { ";
    for (const auto& i : top_sort) {
        std::cout << i + 1 << ' ';
    }
    std::cout << "}\n";
}

void TaskScheduler::generate_dgraph() {
    std::vector<int> num_permutation;
    for (int i = 0; i < task_num_; i++) {
        num_permutation.push_back(i);
    }

    std::random_device rd;
    std::mt19937 rdm(rd());
    std::shuffle(num_permutation.begin(), num_permutation.end(), rdm);

    start = num_permutation[0];

    int remaining_edges = dependency_num_ - 1;

    std::vector<std::pair<int, int>> existing_edges;
    for (int i = 1; i < task_num_; i++) {
        std::uniform_int_distribution<int> dist(0, i-1);
        int j = rand() % i;
        graph_[num_permutation[j]].push_back(num_permutation[i]);
        existing_edges.push_back({num_permutation[j], num_permutation[i]});
        if (remaining_edges < 1) {
            break;
        }
        remaining_edges--;
    }

    if (remaining_edges < 1)
        return;

    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < task_num_; i++) {
        for (int j = i + 1; j < task_num_; j++) {
            if (std::find(existing_edges.begin(), existing_edges.end(), std::pair<int, int>(num_permutation[i], num_permutation[j])) == existing_edges.end())
                edges.push_back({num_permutation[i], num_permutation[j]});
        }
    }
    std::shuffle(edges.begin(), edges.end(), rdm);
    for (int i = 0; i < remaining_edges; i++) {
        int src = edges[i].first;
        int dest = edges[i].second;
        graph_[src].push_back(dest);
    }
}

void TaskScheduler::topological_sort() {
    std::cout << "===============================================\n";
    std::cout << "                DFS Traversal                  \n";
    std::cout << "===============================================\n";
    std::cout << "Starting from Task: " << start + 1 << '\n';
    dfs_visit(start);
    std::cout << task_names_[start];
    for (const auto& i : top_sort) {
        if (i == start) continue;
        std::cout << " -> " << task_names_[i];
    }
    std::cout << std::endl;
}

void TaskScheduler::print_graph() {
    std::cout << std::endl;
    std::cout << "===============================================\n";
    std::cout << "Adjacency List Representation of Directed Graph\n";
    std::cout << "===============================================\n";
    for (size_t i = 0; i < graph_.size(); i++) {
        std::cout << task_names_[i] << " -> ";
        for (const auto& node : graph_[i]) {
            std::cout << task_names_[node] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
