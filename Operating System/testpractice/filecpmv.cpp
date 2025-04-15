#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

const std::string filename = "sample.txt";
const std::string copydest = "copied.txt";
const std::string movedest = "movedest.txt";

void copyFile() {
  try {
    fs::path source = filename;
    fs::path destination = copydest;
    if (not fs::exists(source)) { std::ofstream file(filename); file.close(); }
    if (fs::exists(destination)) { fs::remove(destination); }
    fs::copy_file(source, destination);
  } catch (fs::filesystem_error& e) { std::cerr << "Error: " << e.what() << std::endl; }
}

void moveFile() {
  try {
    fs::path source = filename;
    fs::path destination = movedest;
    if (not fs::exists(source)) { std::ofstream file(filename); file.close(); }
    if (fs::exists(destination)) { fs::remove(destination); }
    fs::rename(source, destination);
  } catch (fs::filesystem_error& e) { std::cerr << "Error: " << e.what() << std::endl; }
}

int main() {
  copyFile();
  moveFile();
  return 0;
}