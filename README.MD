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

# Adding Executable to Path
Modify .bashrc for Bash or .zshrc for Zsh
Modify .bashrc for Bash or .zshrc for Zsh

#### For Bash users: Open your .bashrc file by running:

    nano ~/.bashrc

Add the following line at the end:

    export PATH=$PATH:/path/to/your/executable/directory

Replace ```/path/to/your/executable/directory``` with the path you copied earlier.

Save the file and exit nano by pressing Ctrl+X, then Y, then Enter.

#### For Zsh users: Open your .zshrc file by running:

    nano ~/.zshrc

Add the following line at the end:

    export PATH=$PATH:/path/to/your/executable/directory

Replace /path/to/your/executable/directory with the path you copied earlier.

Save the file and exit nano by pressing Ctrl+X, then Y, then Enter.

Reload Your Shell Configuration

To make the changes take effect, you'll need to reload your shell's configuration file:

For Bash:

    source ~/.bashrc

For Zsh:

    source ~/.zshrc

Now, you should be able to run file_terminal from anywhere in your terminal.