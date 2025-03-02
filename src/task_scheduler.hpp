#pragma once
#include <list>
#include <vector>
#include <string>

class TaskScheduler {
public:
    TaskScheduler(int task_num, int dependency_num);
    void topological_sort();
    void generate_dgraph();
    void dfs_visit(int num);
    void print_adj_list();
private:
    int task_num;
    int dependency_num;
    std::vector<std::vector<int>> graph;
    std::vector<std::string> task_names;

    std::vector<bool> visited;
    std::list<int> top_sort;
    std::vector<bool> rec_stack;
    std::vector<bool> isolated;
    int start;
};
