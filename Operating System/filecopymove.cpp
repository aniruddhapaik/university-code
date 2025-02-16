#include <windows.h>
// -----------------
#include <io.h>  // for _access()
#define F_OK 0   // Check file existence
#include <iostream>
#include <limits>

std::string readline;

bool inputLineFailSafe(std::string& input) {
  std::cin.clear();
  // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

bool checkFileExists(const std::string& filename) {
  if (_access(filename.c_str(), F_OK) != 0) {
    return false;
  }
  return true;
}

void copyFile() {
  std::cout << "Enter source path: ";

  if (inputLineFailSafe(readline)) {
    std::cout << "Source: " << readline << '\n' << std::endl;

    if (not checkFileExists(readline)) {
      std::cerr << "[!] Source does not exist" << std::endl;
      return;
    };

    std::string readsource = readline;
    LPCSTR source = readsource.c_str();  // source path

    std::cout << "Enter destination path: ";
    if (inputLineFailSafe(readline)) {
      std::cout << "Destination: " << readline << '\n' << std::endl;

      std::string readdest = readline;
      LPCSTR dest = readdest.c_str();  // destination path

      if (CopyFile(source, dest, FALSE)) {
        std::cout << "File copied successfully.\n";
      } else {
        std::cerr << "Error copying file: " << GetLastError() << '\n';
      }
    }
  }
}

int main() {
  std::cout << "=== Copy File ===" << std::endl;
  copyFile();

  return 0;
}
