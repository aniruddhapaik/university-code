#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

const std::string filename = "example.txt";
const std::string directory = ".";

void ListDir() {
  std::cout << "Listing Directory: \n";
  for (const auto& entry : fs::directory_iterator(directory)) {
	std::cout << entry.path().string() << std::endl;
  }
}

void CreateFile() {
	std::ofstream file(filename);
	if (file.is_open()) {
		file.close();
		std::cout << "File created successfully" << std::endl;
	} else { std::cerr << "Error creating file" << std::endl; }
}

void WriteFile() {
  std::ofstream file;
	file.open(filename);
	if (file.is_open()) {
		file << "Dummy text written to file" << std::endl;
		file.close();
		std::cout << "Written to file successfully" << std::endl;
	} else { std::cerr << "Error opening file" << std::endl; }
}

void ReadFile() {
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string line;
		while(std::getline(file, line)) {
			std::cout << line << std::endl;
		}
		file.close();
	} else { std::cerr << "Error opening file" << std::endl; }
}

int main() {
	ListDir();
	CreateFile();
	WriteFile();
	ReadFile();
	ListDir();
	return 0;
}