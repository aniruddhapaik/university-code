#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>

namespace fs = std::filesystem;

void copyFile() {
  try {
    std::cout << "* Copying file* " << std::endl;
    fs::path source = "example.txt";
    if (fs::exists(source)) {
      std::cout << "Source: " << source.string() << " exists\n" << std::endl;
    } else { std::ofstream file(source); file.close(); }

    fs::path destination = "copied.txt";
    if (not fs::exists(destination)) {
      std::cout << "Destination: " << destination.string()
                << " does not exist" << std::endl;
      fs::copy_file(source, destination);
      std::cout << "File copied successfully." << std::endl;
    } else { return; }
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void moveFile() {
  try {
    std::cout << "* Moving file *\n";
    fs::path source = "example.txt";
    if (fs::exists(source)) {
      std::cout << "Source: " << source.string() << " exists\n" << std::endl;
    } else { return; }

    fs::path destination = "moved.txt";
    if (not fs::exists(destination)) {
      std::cout << "Destination: " << destination.string() << " does not exist\nmoving...";
      fs::rename(source, destination);
      std::cout << "File moved successfully." << std::endl;
    } else { return; }
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

int main() {
  copyFile();
  moveFile();
  return 0;
}