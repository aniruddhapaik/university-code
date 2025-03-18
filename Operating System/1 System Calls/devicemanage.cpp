#include <windows.h>
//------------------
#include <iostream>
#include <vector>

// Function to list all logical drives
void ListDrives() {
  DWORD drives = GetLogicalDrives();
  if (drives == 0) {
    std::cerr << "Failed to get logical drives: " << GetLastError()
              << std::endl;
    return;
  }

  std::cout << "Available Drives:" << std::endl;
  for (char letter = 'A'; letter <= 'Z'; ++letter) {
    if (drives & (1 << (letter - 'A'))) {
      std::cout << letter << ":\\" << std::endl;
    }
  }
}

// Function to get device information
void GetDriveInfo(const std::string& drive) {
  char volumeName[MAX_PATH] = {0};
  char fileSystemName[MAX_PATH] = {0};
  DWORD serialNumber = 0, maxComponentLength = 0, fileSystemFlags = 0;

  if (GetVolumeInformationA(drive.c_str(), volumeName, MAX_PATH, &serialNumber,
                            &maxComponentLength, &fileSystemFlags,
                            fileSystemName, MAX_PATH)) {
    std::cout << "Drive: " << drive << std::endl;
    std::cout << "Volume Name: " << volumeName << std::endl;
    std::cout << "File System: " << fileSystemName << std::endl;
    std::cout << "Serial Number: " << serialNumber << std::endl;
  } else {
    std::cerr << "Failed to get drive info: " << GetLastError() << std::endl;
  }
}

int main() {
  ListDrives();

  std::string drive = "C:\\";  // Change to an actual removable drive letter
  std::cout << std::endl;
  GetDriveInfo(drive);

  return 0;
}
