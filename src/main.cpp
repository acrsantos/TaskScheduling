#include "task_scheduler.hpp"
#include <ios>
#include <iostream>
#include <limits>
#include <string_view>

int prompt_int(std::string_view prompt_msg);
void clear_screen();

int main() {
    int num_of_task, num_of_dependencies;
    clear_screen();
    while (true) {
        std::cout << "===============================================\n";
        std::cout << " Task Scheduling with Random Dependency Graphs \n";
        std::cout << "===============================================\n";
        num_of_task = prompt_int("Enter number of tasks");
        num_of_dependencies = prompt_int("Enter number of num_of_dependencies");
        int max_edge = (num_of_task * (num_of_task - 1))/2;
        if (num_of_dependencies < 1) {
            clear_screen();
            std::cout << "Error: number of dependecies must be greater than 0\n";
            continue;
        }

        if (num_of_dependencies <= max_edge) break;

        clear_screen();
        std::cout << "Error: Number of dependecies exceeds the maximum possible edge of graph with " << num_of_task << " number of tasks\n";
    }

    TaskScheduler ts {num_of_task, num_of_dependencies};
    ts.generate_dgraph();
    ts.print_graph();
    ts.topological_sort();
    return 0;
}
int prompt_int(std::string_view prompt_msg) {
    int num;
    while (true) {
        std::cout << prompt_msg << ": ";
        std::cin >> num;
        if (!std::cin.fail()) 
            return num;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
    }
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
