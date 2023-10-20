#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <filesystem>
#include <unistd.h>
#include <termios.h>
#include <iomanip>

void changeDirectory(const std::string &directory) {
    std::filesystem::path newDir(directory);
    if (std::filesystem::exists(newDir) && std::filesystem::is_directory(newDir)) {
        std::filesystem::current_path(newDir);
        std::cout << "Changed directory to: " << std::filesystem::current_path() << '\n';
    } else {
        std::cerr << "Invalid directory.\n";
    }
}

void goBackOneDirectory() {
    std::filesystem::current_path(std::filesystem::current_path().parent_path());
    std::cout << "Changed directory to: " << std::filesystem::current_path() << '\n';
}

void createFile() {
    std::string filename;
    std::cout << "Enter the filename: ";
    std::cin >> filename;

    std::ofstream file(filename);
    if (file.is_open()) {
        std::cout << "File created successfully\n";
        file.close();
    } else {
        std::cerr << "Error creating file\n";
    }
}

void readFile() {
    std::string filename;
    std::cout << "Enter the filename to read: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }
        file.close();
    } else {
        std::cerr << "Error opening file. Make sure the file exists and you have read permissions.\n";
    }
}

void writeFile() {
    std::string filename;
    std::cout << "Enter the filename to write to: ";
    std::cin >> filename;

    std::ofstream file(filename, std::ios_base::app);
    if (file.is_open()) {
        std::cout << "Enter content to write to the file (type 'exit' to stop):\n";
        std::string line;
        std::cin.ignore();
        while (std::getline(std::cin, line)) {
            if (line == "exit") {
                break;
            }
            file << line << '\n';
        }
        file.close();
    } else {
        std::cerr << "Error opening file. Make sure you have write permissions.\n";
    }
}

void deleteFile() {
    std::string filename;
    std::cout << "Enter the filename to delete: ";
    std::cin >> filename;

    if (std::remove(filename.c_str()) == 0) {
        std::cout << "File deleted successfully\n";
    } else {
        std::cerr << "Error deleting file. Make sure the file exists and you have delete permissions.\n";
    }
}

void listFiles() {
    std::cout << "\033[2J\033[1;1H"; // Clear screen
    std::cout << "List of files in the current directory:\n";

    for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
        if (!entry.is_directory()) {
            std::cout << entry.path().filename().string() << '\n';
        }
    }
}


void listFiles(std::vector<std::string>& entries, int& index) {
    std::vector<std::string> fileNames;
    for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
        std::string prefix = (entry.is_directory() && index == fileNames.size()) ? "> " : "  ";
        if (entry.is_directory()) {
            std::cout << prefix << u8"\U0001F4C1 ";
        } else {
            std::cout << prefix << u8"\U0001F4C4 ";
        }
        std::cout << entry.path().filename().string() << '\n';
        entries.push_back(entry.path().string());
        fileNames.push_back(entry.path().filename().string());
    }
}

int fileNavigation() {
    int index = 0;

    // Change terminal settings
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::filesystem::path currentDir = std::filesystem::current_path();

    while (true) {
        std::cout << "\033[2J\033[1;1H"; // Clear screen
        std::cout << "\nCurrent Directory: " << currentDir << '\n';
        std::cout << "-----------------------------\n";
        std::cout << "[\u2191] Up  [\u2193] Down  [Enter] Select  [\u2190] Back  [q] Quit\n";
        std::cout << "-----------------------------\n";

        std::vector<std::string> entries;
        listFiles(entries, index);

        char c = getchar();

        if (c == 'q') { // Press 'q' to quit
            break;
        } else if (c == '\033') { // Arrow key escape sequence
            getchar(); // Skip the '[' character
            switch (getchar()) {
                case 'A': // Up arrow
                    if (index > 0) index--;
                    break;
                case 'B': // Down arrow
                    if (index < entries.size() - 1) {
                        index++;
                    } else {
                        index = 0; // Wrap around to the first file
                    }
                    break;
                case 'C': // Right arrow
                    if (std::filesystem::is_directory(entries[index])) {
                        changeDirectory(entries[index]);
                        index = 0;
                    } else {
                        std::cout << "Make sure it is a directory...Z\n";
                    }

                case 'D': // Left arrow
                    std::filesystem::path parentDir = std::filesystem::current_path().parent_path();
                    changeDirectory(parentDir.string());
                    index = 0;
                    break;
            }
        } else if (c == '\n' && !entries.empty()) { // Enter key
            if (std::filesystem::is_directory(entries[index])) {
                changeDirectory(entries[index]);
                index = 0;
            } else {
                std::cout << "Do you want to read this file? [Press Enter to proceed or Escape to cancel]\n";
                while (true) {
                    char decision = getchar();
                    if (decision == '\n') { // Enter key
                        std::ifstream file(entries[index]);
                        if (file) {
                            std::string line;
                            while (std::getline(file, line)) {
                                std::cout << line << '\n';
                            }
                            file.close();
                            std::cout << "Press any key to return to the file list...\n";
                            getchar(); // Wait for any key
                        } else {
                            std::cerr << "Could not open the file.\n";
                            std::cout << "Press any key to return to the file list...\n";
                            getchar(); // Wait for any key
                        }
                        break; // Exit the inner loop
                    } else if (decision == 27) { // Escape key
                        break; // Exit the inner loop
                    }
                }
            }
        }
    }

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}


int main() {
    int choice;
    while (true) {
        std::cout << "\n\n";
        std::cout << "\nFile Terminal Program\n";
        std::cout << "1. Create a file\n";
        std::cout << "2. Read a file\n";
        std::cout << "3. Write to a file\n";
        std::cout << "4. Delete a file\n";
        std::cout << "5. List files\n";
        std::cout << "6. Navigate files\n";
        std::cout << "7. Go back one directory\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                readFile();
                break;
            case 3:
                writeFile();
                break;
            case 4:
                deleteFile();
                break;
            case 5:
                listFiles();
                break;
            case 6:
                fileNavigation();
                break;
            case 7:
                goBackOneDirectory();
                break;
            case 8:
                std::cout << "Exiting program...\n";
                return 0;
            default:
                std::cerr << "Invalid choice. Please enter a number between 1 and 8.\n";
                break;
        }
    }

    return 0;
}

