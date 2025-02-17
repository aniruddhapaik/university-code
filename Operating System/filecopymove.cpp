#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>

namespace fs = std::filesystem;

std::string readline;

bool inputLineFailSafe(std::string& input) {
  std::getline(std::cin, input);

  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Error occurred while reading" << std::endl;
    return false;
  } else {
    return true;
  }
}

template <typename T>
bool inputFailsafe(T& input) {
  std::cin >> input;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Input Error" << std::endl;
    return false;
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return true;
}

void copyFile() {
  try {
    std::cout << "* Copying file* " << std::endl;
    std::cout << "Enter source path: ";
    if (inputLineFailSafe(readline)) {
      fs::path source = readline;
      if (fs::exists(source)) {
        std::cout << "Source: " << source.string() << " exists\n" << std::endl;
      } else {
        return;
      }

      std::cout << "[i] Will copy file only if file does not exist already"
                << std::endl;
      std::cout << "Enter destination path: ";
      if (inputLineFailSafe(readline)) {
        fs::path destination = readline;
        if (not fs::exists(destination)) {
          std::cout << "Destination: " << destination.string()
                    << " does not exists\ncreating..." << std::endl;
          fs::copy_file(source, destination);
          std::cout << "File copied successfully." << std::endl;
        } else {
          return;
        }
      }
    }
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

bool createFile(const std::string& filename) {
  std::ofstream file(filename);  // Create the file
  if (file.is_open()) {
    file.close();
    std::cout << "File created successfully.\n";
    return true;
  } else {
    std::cerr << "Error creating file.\n";
  }
  return false;
}

void moveFile() {
  try {
    std::cout << "* Moving file *\n";
    std::cout << "Enter source: ";
    if (inputLineFailSafe(readline)) {
      fs::path source = readline;
      if (fs::exists(source)) {
        std::cout << "Source: " << source.string() << " exists\n" << std::endl;
      } else {
        return;
      }

      std::cout << "[i] Will move file only if file does not exist already"
                << std::endl;
      std::cout << "Enter destination: ";
      if (inputLineFailSafe(readline)) {
        fs::path destination = readline;
        if (not fs::exists(destination)) {
          std::cout << "Destination: " << destination.string()
                    << " does not exists\nmoving...";
          if (createFile(destination.string())) {
            fs::rename(source, destination);
            std::cout << "File moved successfully." << std::endl;
          }
        } else {
          return;
        }
      }
    }
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void listDir() {
  std::string directory(".");
  std::cout << "Enter directory to list\n"
            << "(default is current working directory): " << std::flush;
  if (inputLineFailSafe(directory)) {
    if (directory == std::string("")) {
      directory = std::string(".");
    }
    for (const auto& entry : fs::directory_iterator(directory)) {
      if (entry.is_directory()) {
        std::cout << "DIR  " << entry.path().string() << std::endl;
      } else {
        std::cout << "     " << entry.path().string() << std::endl;
      }
    }
  }
}

int main() {
  int choice;

  while (true) {
    std::cout << "=== Copy or Move File ===\n";
    std::cout << "1. Copy\n";
    std::cout << "2. Move\n";
    std::cout << "3. List Directory\n";
    std::cout << "4. Exit\n";
    std::cout << std::string(10, '-') << '\n';
    std::cout << "Enter choice: ";
    if (inputFailsafe(choice)) {
      switch (choice) {
        case 1:
          copyFile();
          break;
        case 2:
          moveFile();
          break;
        case 3:
          listDir();
          break;
        case 4:
          return 0;
        default:
          std::cout << "Invalid choice" << std::endl;
      }
    }
    std::cout << std::endl;
  }

  return 0;
}
