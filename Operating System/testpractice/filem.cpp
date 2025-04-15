#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
const std::string filename = "example.txt";
const std::string directory = ".";

void ListDir() {
  for (const auto& entry: fs::directory_iterator(directory)) {
    std::cout << entry.path().string() << std::endl;
  }
}

void createFile() {
  std::ofstream file(filename);
  if (file.is_open()) {
    file.close();
    std::cout << "file created successfully" << std::endl;
  }
}

void writeFile() {
  std::ofstream file;
  file.open(filename);
  if (file.is_open()) {
    file << "this is text written to file" << std::endl;
    file.close();
  }
}

void readFile() {
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::cout << line << std::endl;
    }
    file.close();
  }
}

int main() {
  ListDir();
  createFile();
  writeFile();
  readFile();
  ListDir();
  return 0;
}