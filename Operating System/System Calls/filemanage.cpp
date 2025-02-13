#include <windows.h>
// ------------------
#include <io.h>  // for _access()
#define F_OK 0   // Check file existence

#include <iostream>
#include <limits>
#include <string>

template <typename T>
bool inputFailSafe(T& input) {
  std::cin >> input;

  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input" << std::endl;
    return false;
  }
  return true;
}

template <typename T>
bool inputContentFailsafe(T& input) {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::getline(std::cin, input);

  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
  return true;
}

bool checkFileExists(const std::string& filename) {
  if (_access(filename.c_str(), F_OK) != 0) {
    return false;
  }
  return true;
}

void CreateFile(const std::string& filename) {
  if (checkFileExists(filename)) {
    std::cerr << "[!] File already exists: " << filename << std::endl;
    return;
  }

  HANDLE hFile = CreateFileA(filename.c_str(), GENERIC_WRITE, 0, NULL,
                             CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

  if (hFile == INVALID_HANDLE_VALUE) {
    std::cerr << "[!] Failed to create file. Error: " << GetLastError()
              << std::endl;
    return;
  }

  std::cout << "[+] File created successfully: " << filename << std::endl;
  CloseHandle(hFile);
}

void WriteToFile(const std::string& filename, const std::string& content,
                 bool append = true) {
  if (not checkFileExists(filename)) {
    std::cerr << "File does not exist!" << std::endl;
    return;
  }

  DWORD access_mode = append ? FILE_APPEND_DATA : GENERIC_WRITE;
  DWORD creation_mode = append ? OPEN_ALWAYS : CREATE_ALWAYS;

  HANDLE hFile = CreateFileA(filename.c_str(), access_mode, 0, NULL,
                             creation_mode, FILE_ATTRIBUTE_NORMAL, NULL);

  if (hFile == INVALID_HANDLE_VALUE) {
    std::cerr << "[!] Failed to open file for writing. Error: "
              << GetLastError() << std::endl;
    std::cerr << "[!] File name: " << filename << std::endl;
    return;
  }

  DWORD bytes_written;
  if (WriteFile(hFile, content.c_str(), content.size(), &bytes_written, NULL)) {
    std::cout << "[+] Written to file successfully: " << bytes_written
              << " bytes" << std::endl;
  } else {
    std::cerr << "[!] Failed to write to file. Error: " << GetLastError()
              << std::endl;
  }

  CloseHandle(hFile);
}

void ReadFromFile(const std::string& filename) {
  HANDLE hFile = CreateFileA(filename.c_str(), GENERIC_READ, 0, NULL,
                             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  if (hFile == INVALID_HANDLE_VALUE) {
    std::cerr << "[!] Failed to open file for reading. Error: "
              << GetLastError() << std::endl;
    return;
  }

  char buffer[1024] = {0};
  DWORD bytesRead;

  if (ReadFile(hFile, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
    std::cout << "[i] Read from file:\n" << buffer << std::endl;
  } else {
    std::cerr << "[!] Failed to read file. Error: " << GetLastError()
              << std::endl;
    std::cerr << "[!] File name: " << filename << std::endl;
  }

  CloseHandle(hFile);
}

void DeleteFile(const std::string& filename) {
  if (DeleteFileA(filename.c_str())) {
    std::cout << "[i] File deleted successfully: " << filename << std::endl;
  } else {
    std::cerr << "[!] Failed to delete file. Error: " << GetLastError()
              << std::endl;
    std::cerr << "[!] File name: " << filename << std::endl;
  }
}

void GetFileAttributesExample(const std::string& filename) {
  DWORD attributes = GetFileAttributesA(filename.c_str());

  if (attributes == INVALID_FILE_ATTRIBUTES) {
    std::cerr << "[!] Failed to get file attributes. Error: " << GetLastError()
              << std::endl;
    // std::cerr << "File name: " << filename << std::endl;
    return;
  }

  std::cout << "File attributes of " << filename << ":" << std::endl;
  if (attributes & FILE_ATTRIBUTE_DIRECTORY) std::cout << " - Directory\n";
  if (attributes & FILE_ATTRIBUTE_READONLY) std::cout << " - Read-only\n";
  if (attributes & FILE_ATTRIBUTE_HIDDEN) std::cout << " - Hidden\n";
  if (attributes & FILE_ATTRIBUTE_SYSTEM) std::cout << " - System File\n";
  if (attributes & FILE_ATTRIBUTE_ARCHIVE) std::cout << " - Archive\n";
  if (attributes & FILE_ATTRIBUTE_TEMPORARY) std::cout << " - Temporary\n";
  if (attributes & FILE_ATTRIBUTE_COMPRESSED) std::cout << " - Compressed\n";
  if (attributes & FILE_ATTRIBUTE_ENCRYPTED) std::cout << " - Encrypted\n";
}

void ListCurrentDirectory() {
  WIN32_FIND_DATAA findFileData;
  HANDLE hFind = FindFirstFileA("./*", &findFileData);
  // List all files and directories in the current folder

  if (hFind == INVALID_HANDLE_VALUE) {
    std::cerr << "[!] Failed to list directory contents. Error: "
              << GetLastError() << std::endl;
    return;
  }

  std::cout << "\n=== Files in Current Directory ===\n";
  do {
    std::string fileType =
        (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? "<DIR>"
                                                                   : "     ";
    LARGE_INTEGER file_size;
    file_size.LowPart = findFileData.nFileSizeLow;
    file_size.HighPart = findFileData.nFileSizeHigh;
    std::cout << fileType << " " << findFileData.cFileName << " - "
              << file_size.QuadPart << " bytes" << std::endl;
  } while (FindNextFileA(hFind, &findFileData));

  FindClose(hFind);
}

int main() {
  std::string filename = "example.txt";
  std::string content = "Hello, this is a test file.";
  bool append = true;

  int choice{};
  char yesno{'n'};

  while (true) {
    std::cout << "\n==== File Management ====\n";
    std::cout << "1. Create File\n";
    std::cout << "2. Write to File\n";
    std::cout << "3. Read from File\n";
    std::cout << "4. Delete File\n";
    std::cout << "5. Get File Attributes\n";
    std::cout << "6. List Directory\n";
    std::cout << "10. Exit\n";
    std::cout << std::string(10, '-') << '\n';
    std::cout << "Enter choice: ";
    if (inputFailSafe(choice)) {
      std::cin.ignore();  // Ignore newline character

      switch (choice) {
        case 1:
          std::cout << "Enter filename to create: ";
          if (inputFailSafe(filename)) {
            if (filename != "") {
              CreateFile(filename);
            } else {
              CreateFile(std::string("example.txt"));
            }
          }
          break;
        case 2:
          std::cout << "Enter filename to write: ";
          if (inputFailSafe(filename)) {
            std::cout << "Will open file named: " << filename << std::endl;
            std::cout << "1. Append to file\n";
            std::cout << "2. Overwrite file\n";
            std::cout << std::string(10, '-') << '\n';
            std::cout << "Enter choice: ";
            if (inputFailSafe(choice)) {
              if (choice == 1) {
                append = true;
              } else {
                append = false;
              }

              std::cout << "Enter line of content to write to file: \n";
              if (inputContentFailsafe(content)) {
                if (content != "") {
                  content = content + std::string("\n");
                  WriteToFile(filename, content, append);
                }
              }
            }
          }
          break;
        case 3:
          std::cout << "Enter filename to read: ";
          if (inputFailSafe(filename)) {
            ReadFromFile(filename);
          }
          break;
        case 4:
          std::cout << "Enter filename to delete: ";
          if (inputFailSafe(filename)) {
            std::cout << "Do you want to delete file: " << filename
                      << "\n  [y/n]?: ";
            if (inputFailSafe(yesno)) {
              if (yesno == 'y' or yesno == 'Y') {
                DeleteFile(filename);
              } else {
                std::cout << "[i] You chose not to delete" << std::endl;
              }
            }
          }
          break;
        case 5:
          std::cout << "Enter filename to find attributes: ";
          if (inputFailSafe(filename)) {
            GetFileAttributesExample(filename);
          }
          break;
        case 6:
          ListCurrentDirectory();
          break;
        case 10:
          return 0;
        default:
          std::cout << "[!] Invalid choice. Try again.\n";
      }
      filename = "";
      content = "";
      yesno = 'n';
      append = true;
      choice = 0;
    }
  }
}
