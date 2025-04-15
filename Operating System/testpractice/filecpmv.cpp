#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

const std::string filename = "example.txt";
const std::string copydest = "copied.txt";
const std::string movedest = "moved.txt"; 

void copyFile() {
  try {
    std::cout << "\nChecking source file" << std::endl;
    fs::path source = filename;
    if (not fs::exists(source)) { std::ofstream file(filename); file.close(); }
    if (fs::exists(source)) { std::cout << "source file exists." << std::endl; }

    std::cout << "Copying source file" << std::endl;
    fs::path destination = copydest;
    if (fs::exists(destination)) { fs::remove(destination); }
    fs::copy_file(source, destination);
    std::cout << "File copied successfully" << std::endl;
  } catch (fs::filesystem_error& e) { std::cerr << "Error: " << e.what() << std::endl; }
}

void moveFile() {
  try {
    std::cout << "\nChecking source file" << std::endl;
    fs::path source = filename;
    if (not fs::exists(source)) { std::ofstream file(filename); file.close(); }
    if (fs::exists(source)) { std::cout << "source file exists." << std::endl; }

    std::cout << "Moving file" << std::endl;
    fs::path destination = movedest;
    if (fs::exists(destination)) { fs::remove(destination); }
    fs::rename(source, destination);
    std::cout << "Moved file successfully" << std::endl;
  } catch (fs::filesystem_error& e) { std::cerr << "Error: " << e.what() << std::endl; }
}

int main() {
  copyFile();
  moveFile();
  return 0;
}