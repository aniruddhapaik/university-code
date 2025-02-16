#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>

namespace fs = std::filesystem;

template <typename T>
bool inputFailsafe(T& input) {
  std::cin >> input;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Error reading input" << std::endl;
    return false;
  }
  return true;
}

bool inputLineFailsafe(std::string& input) {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::getline(std::cin, input);
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Error reading input" << std::endl;
    return false;
  }
  return true;
}

void createFile(const std::string& filename) {
  std::ofstream file(filename);  // Create the file
  if (file.is_open()) {
    file.close();
    std::cout << "File created successfully.\n";
  } else {
    std::cerr << "Error creating file.\n";
  }
}

void writeFile(const std::string& filename, const std::string& content) {
  std::ofstream file(filename);
  if (file.is_open()) {
    file << content;  // Write to file
    std::cout << "File written successfully.\n";
  } else {
    std::cerr << "Error creating file.\n";
  }
}

void readFile(const std::string& filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {  // Read line by line
      std::cout << line << '\n';
    }
    file.close();
  } else {
    std::cerr << "Error opening file.\n";
  }
}

void listFiles(const std::string& directory) {
  for (const auto& entry : std::filesystem::directory_iterator(directory)) {
    std::cout << entry.path() << '\n';
  }
}

void deleteFile(const std::string& filename) {
  if (std::filesystem::remove(filename)) {
    std::cout << "File deleted successfully.\n";
  } else {
    std::cerr << "Error deleting file.\n";
  }
}

int main() {
  std::string filename;
  std::string content;
  int choice;

  while (true) {
    std::cout << "=== File Management ===\n";
    std::cout << "1. Create file\n";
    std::cout << "2. Write file\n";
    std::cout << "3. Read file\n";
    std::cout << "4. Delete file\n";
    std::cout << "5. List Directory\n";
    std::cout << "6. Clear screen\n";
    std::cout << "10. Exit\n";
    std::cout << std::string(10, '-') << '\n';
    std::cout << "Enter choice: ";

    if (inputFailsafe(choice)) {
      switch (choice) {
        case 1:
          std::cout << "Enter filename: ";
          if (inputFailsafe(filename)) {
            createFile(filename);
          }
          break;
        case 2:
          std::cout << "Enter filename: ";
          if (inputFailsafe(filename)) {
            std::cout << "\nEnter one line to be written: ";
            if (inputLineFailsafe(content)) {
              writeFile(filename, content);
            }
          }
          break;
        case 3:
          std::cout << "Enter filename: ";
          if(inputFailsafe(filename)) {
            readFile(filename);
          }
          break;
        case 4:
          std::cout << "Enter filename: ";
          if(inputFailsafe(filename)) {
            deleteFile(filename);
          }
          break;
        case 5:
          std::cout << "Current directory list:" << std::endl;
          listFiles(".");
          break;
        case 6:
          system("cls");
          break;
        case 10:
          return 0;
        default:
          std::cerr << "[!] Invalid choice" << std::endl;
      }
    }

    std::cout << std::endl;
  }

  return 0;
}
