# File Terminal Program

## Description

This is a simple terminal-based file explorer and manager written in C++. The program provides a text-based user interface through which users can perform various file operations such as creating, reading, writing, and deleting files. It also allows users to navigate through directories and read files in navigation mode.

## Requirements

- C++ compiler with support for C++17 (e.g., g++ or clang++)
- Terminal for running the program
- Linux or macOS operating system

## Compilation

To compile the program, navigate to the directory containing the source code and execute the following command:

On Linux:

```sh
g++ -std=c++17 -o file_terminal main.cpp -lstdc++fs
```
On macOS (assuming you are using the Clang compiler):

```sh
 clang++ -std=c++17 -o file_terminal main.cpp -lc++fs
 ```

> Note: This application is designed for Linux and macOS and might not work properly on Windows.
Running the Program

After successfully compiling the source code, you can run the program by executing the following command in your terminal:

```sh
./file_terminal
```

