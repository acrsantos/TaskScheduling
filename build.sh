#!/usr/bin/bash

if [ "$1" == "-g" ]; then
    cmake -B ./build/Debug -S . -D CMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1
    if [ -f "compile_commands.json" ]; then
        rm compile_commands.json
    fi

    ln -s build/Debug/compile_commands.json .
fi


cmake --build ./build/Debug
