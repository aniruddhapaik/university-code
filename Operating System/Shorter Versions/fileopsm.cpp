#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

const std::string filename("example.txt");
const std::string directory(".");

void createFile() {
  std::ofstream file(filename);
  if(file.is_open()) {
    file.close();
    std::cout << "File created successfully" << std::endl;
  } else {
    std::cerr << "Error creating file" << std::endl;
  }
}

void writeFile() {
  std::ofstream file;
  file.open(filename);
  if(file.is_open()) {
    file << "Dummy text input...";
    file.close();
    std::cout << "file written successfully" << std::endl;
  } else {
    std::cerr << "Error opening file " << std::endl;
  }
}

void readFile() {
  std::cout << "\nReading file: " << std::endl;
  std::ifstream file(filename);
  if(file.is_open()) {
    std::string line;
    while(std::getline(file, line)) {
      std::cout << line << std::endl;
    }
  } else { std::cerr << "Error reading file" << std::endl; }
  std::cout << std::endl;
}

void listDir() {
  std::cout << "\nListing Directory: " << std::endl;
  for (const auto& entry : fs::directory_iterator(directory)) {
    std::cout << entry.path().string() << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  listDir();
  createFile();
  writeFile();
  readFile();
  listDir();

  return 0;
}