#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
const std::string filename = "example.txt";

void ListDir() {
  std::cout << "\nListing Directory" << std::endl;
  for (const auto& entry: fs::directory_iterator(std::string("."))) {
    std::cout << entry.path().string() << std::endl;
  }
  std::cout << std::endl;
}

void CreateFile() {
  std::cout << "\nCreating example.txt" << std::endl;
  std::ofstream file(filename);
  if(file.is_open()) {
    file.close();
    std::cout << "File created successfully" << std::endl;
  } else { std::cerr << "Error creating file" << std::endl; }
}

int main() {
  ListDir();
  CreateFile();
  ListDir();
  return 0;
}