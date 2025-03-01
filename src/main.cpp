#include "task_scheduler.hpp"

int main() {
    TaskScheduler ts {8, 10};
    ts.generate_dgraph();
    ts.topological_sort();
    ts.print_graph();
    return 0;
}
