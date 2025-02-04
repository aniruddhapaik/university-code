#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void setPermissions(const std::string& filename) {
  try {
    fs::permissions(filename, 
      fs::perms::owner_read | fs::perms::owner_write |
      fs::perms::group_read | fs::perms::others_read,
      fs::perm_options::replace);

    // Explicitly remove unwanted permissions
    fs::permissions(filename, 
      fs::perms::group_write | fs::perms::others_write, 
      fs::perm_options::remove);

    std::cout << "Permissions set successfully.\n";
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Error setting permissions: " << e.what() << '\n';
  }
}

void checkPermissions(const std::string& filename) {
  try {
    if (!fs::exists(filename)) {
      throw fs::filesystem_error("File does not exist", std::error_code());
    }

    fs::perms p = fs::status(filename).permissions();
    
    std::cout << "Permissions for " << filename << ":\n";
    std::cout << "Owner: "
              << ((p & fs::perms::owner_read)  != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::owner_exec)  != fs::perms::none ? "x" : "-") << '\n';
    
    std::cout << "Group: "
              << ((p & fs::perms::group_read)  != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::group_exec)  != fs::perms::none ? "x" : "-") << '\n';
    
    std::cout << "Others: "
              << ((p & fs::perms::others_read)  != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::others_exec)  != fs::perms::none ? "x" : "-") << '\n';
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Error checking permissions: " << e.what() << '\n';
  }
}

int main() {
  std::string filename = "testfile.txt";
  
  // Create a file if it doesn't exist
  std::ofstream file(filename);
  if (!file) {
    std::cerr << "Error creating file: " << filename << '\n';
    return 1;
  }
  file.close();
  
  setPermissions(filename);
  checkPermissions(filename);
  
  return 0;
}
