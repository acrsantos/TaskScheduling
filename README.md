# Algorithm - Activity 3 - Task Scheduling with Random Dependency Graphs
## REQUIREMENTS
- Git
- C++ Compiler (g++) OR CMake

## Clone the repository
```
git clone https://github.com/acrsantos/TaskScheduling
```
## BUILD & RUN
### Using g++
```
cd TaskScheduling
g++ -o TaskScheduling src/main.cpp src/task_scheduler.cpp
./TaskScheduling
```
### Using CMake
```
cd TaskScheduling
cmake -B ./build/release -S . -D CMAKE_BUILD_TYPE=Release
cmake --build ./build/release
./build/release/TaskScheduling
```
#### Alternatively, run the build.sh script to generate compile_commands.json for clangd language server for development
```
cd TaskScheduling
./build.sh
```
