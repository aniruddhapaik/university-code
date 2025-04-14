#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

const std::string filename = "example.txt";
const std::string directory = ".";

void createFile() {
  std::ofstream file(filename);
  if (file.is_open()) {
    file.close();
    std::cout << "Created file successfully" << std::endl;
  } else { std::cerr << "Error creating file" << std::endl; }
}

void writeFile() {
  std::ofstream file;
  file.open(filename);
  if (file.is_open()) {
    file << "Dummy text written to file!" << std::endl;
    file.close();
    std::cout << "File written successfully." << std::endl;
  } else { std::cerr << "Error opening file." << std::endl; }
}

void readFile() {
  std::ifstream file;
  file.open(filename);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::cout << line << std::endl;
    }
  } else { std::cerr << "Error opening file" << std::endl; }
}

void listDir() {
  std::cout << "\nListing directory" << std::endl;
  for (const auto& entry: fs::directory_iterator(directory)) {
    std::cout << entry.path().string() << std::endl;
  }
}

int main() {
  listDir();
  createFile();
  writeFile();
  readFile();
  listDir();
  return 0;
}