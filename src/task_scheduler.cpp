#include "task_scheduler.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

TaskScheduler::TaskScheduler(int task_num, int dependency_num)
    : task_num(task_num), dependency_num(dependency_num) { 

    // Default initialization of vectors
    graph = std::vector<std::vector<int>>(task_num);
    visited = std::vector<bool>(task_num, false);
    rec_stack = std::vector<bool>(task_num, false);
    isolated = std::vector<bool>(task_num, false);

    // Generate task names
    for (size_t i = 0; i < task_num; i++) {
        task_names.push_back("Task " + std::to_string(i + 1));
    }
}

void TaskScheduler::dfs_visit(int num) {
    // Check if there is a cycle in the graph by checking if the node is already in the recursion stack
    if (rec_stack[num] == true) {
        throw std::runtime_error("Error: Cycle detected in the graph");
        return;
    }
    // If the node has been previously visited, do not visit it again
    if (visited[num] == true) return;

    // Set the node as visited and add it to the recursion stack
    visited[num] = true;
    rec_stack[num] = true;

    std::cout << "Processing: " << num + 1 << '\n';

    // Visit all the nodes connected to the current node
    for (const auto& node : graph[num]) {
        dfs_visit(node);
    }

    // After visiting all the nodes connected to the current node, add it to the topological sort
    // and remove it from the recursion stack
    top_sort.push_front(num);
    rec_stack[num] = false;

    std::cout << "\tFinished Processing: " << num + 1 << '\n';
    std::cout << "\tTopological sort: { ";
    for (const auto& i : top_sort) {
        std::cout << i + 1 << ' ';
    }
    std::cout << "}\n";
}

void TaskScheduler::generate_dgraph() {
    // Vector to store numbers from 0 to task_num - 1
    std::vector<int> num_list;
    for (int i = 0; i < task_num; i++) {
        num_list.push_back(i);
    }

    // Shuffle the vector to get a random sequence of numbers
    std::random_device rd;
    std::mt19937 rdm(rd());
    std::shuffle(num_list.begin(), num_list.end(), rdm);

    // Set the start node as the first element of the shuffled vector
    start = num_list[0];

    // Track the number of remaining edges to be added
    int remaining_edges = dependency_num - 1;

    // Generate spanning tree to ensure that the graph is connected
    std::vector<std::pair<int, int>> existing_edges;
    for (int i = 1; i < task_num; i++) {
        // Generate a random number between 0 and i - 1
        std::uniform_int_distribution<int> dist(0, i-1);

        // Connect the current node to a random node from the previous nodes
        int j = dist(rdm);
        graph[num_list[j]].push_back(num_list[i]);
        existing_edges.push_back({num_list[j], num_list[i]});

        // If the specified number of dependencies has been reached, break
        if (remaining_edges < 1) {
            break;
        }
        remaining_edges--;
    }

    // If the specified number of dependencies has already been reached, do generate more edges
    if (remaining_edges < 1)
        return;

    // Generate edges using the generated random sequence of numbers
    std::vector<std::pair<int, int>> edges;

    // This algorithm generates all possible edges between the nodes, starting from the first number in the random sequnce of number
    // This will only generate edges (u, v) where u < v, which in this case, u = i and v = i + 1
    // This means that in the random sequence of number, the current iteration will generate edges
    // between the current number and all the numbers that come after it
    // This is to ensure that the graph that is generated is a directed acyclic graph
    for (int i = 0; i < task_num; i++) {
        for (int j = i + 1; j < task_num; j++) {
            // If the edge (i, j) already exists from generating the spanning tree, skip it from generating
            if (std::find(existing_edges.begin(), existing_edges.end(), std::pair<int, int>(num_list[i], num_list[j])) == existing_edges.end())
                edges.push_back({num_list[i], num_list[j]});
        }
    }
    // Shuffle the edges to get a random sequence of edges
    std::shuffle(edges.begin(), edges.end(), rdm);

    // Add the edge to the graph until the specified number of dependencies has been reached
    for (int i = 0; i < remaining_edges; i++) {
        int src = edges[i].first;
        int dest = edges[i].second;
        graph[src].push_back(dest);
    }
}

void TaskScheduler::topological_sort() {
    std::cout << "===============================================\n";
    std::cout << "                DFS Traversal                  \n";
    std::cout << "===============================================\n";
    std::cout << "Starting from Task: " << start + 1 << '\n';

    // Start the depth first search from the start node
    // The dfs_visit may throw an exception if a cycle is detected in the graph
    // The exception is caught and the program will print the error message
    try {
        dfs_visit(start);
        for (int i = 0; i < task_num; i++) {
            if (!visited[i]) {
                dfs_visit(i);
                isolated[i] = true;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    // Print the topological sort
    std::cout << "\nTask Order per Task component:\n";
    int ctr = 0;
    bool first = true;
    top_sort.reverse();
    for (const auto& i : top_sort) {
        if (!first) {
            if (isolated[i]) {
                std::cout << '\n';
            } else {
                std::cout << " -> ";
            }
        }
        first = false;
        std::cout << task_names[i];
    }
    std::cout << std::endl;
}

void TaskScheduler::print_adj_list() {
    std::cout << std::endl;
    std::cout << "===============================================\n";
    std::cout << "Adjacency List Representation of Directed Graph\n";
    std::cout << "===============================================\n";
    for (size_t i = 0; i < graph.size(); i++) {
        std::cout << "Task " << (i + 1) << " -> ";
        if (graph[i].empty()) {
            std::cout << "No dependencies";
        }
        for (const auto& node : graph[i]) {
            std::cout << "Task " << (node + 1) << " ";
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}
