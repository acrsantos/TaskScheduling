#pragma once
#include <vector>
#include <string>

class TaskScheduler {
public:
    TaskScheduler(int task_num, int dependency_num);
    void topological_sort();
    void generate_dgraph();
    void dfs_visit(int num);
private:
    int task_num_;
    int dependency_num_;
    std::vector<std::vector<int>> graph_;
    std::vector<std::string> task_names_;

    std::vector<bool> visited;
    std::vector<int> top_sort;
};
