#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
const std::string filename = "fileperm.txt";

void checkPermissions() {
  try {
    fs::path source = filename;
    if (not fs::exists(source)) { std::ofstream file(filename); file.close(); }
    fs::perms p = fs::status(filename).permissions();
    std::cout << "\nPermissions: " << filename << std::endl;
    std::cout << "Owner: " << ((p & fs::perms::owner_read) != fs::perms::none ? "r":"-")
                           << ((p & fs::perms::owner_write) != fs::perms::none ? "w":"-")
                           << ((p & fs::perms::owner_exec) != fs::perms::none ? "x":"-") << std::endl;
    std::cout << "Group: " << ((p & fs::perms::group_read) != fs::perms::none ? "r":"-")
                           << ((p & fs::perms::group_write) != fs::perms::none ? "w":"-")
                           << ((p & fs::perms::group_exec) != fs::perms::none ? "x":"-") << std::endl;
    std::cout << "Others: " << ((p & fs::perms::others_read) != fs::perms::none ? "r":"-")
                           << ((p & fs::perms::others_write) != fs::perms::none ? "w":"-")
                           << ((p & fs::perms::others_exec) != fs::perms::none ? "x":"-") << std::endl;
  } catch (fs::filesystem_error& e) { std::cerr << "Error: " << e.what() << std::endl; } 
}

void setPermissions() {
  try {
    fs::path source = filename;
    if (not fs::exists(source)) { std::ofstream file(filename); file.close(); }
    std::cout << "\nSetting permissions" << std::endl;
    fs::permissions(filename, fs::perms::owner_all | fs::perms::group_all | fs::perms::others_all, fs::perm_options::replace);
    checkPermissions();
    std::cout << "\nSetting permissions" << std::endl;
    fs::permissions(filename, fs::perms::owner_write | fs::perms::owner_exec | fs::perms::group_all | fs::perms::others_all, fs::perm_options::remove);
  } catch (fs::filesystem_error& e) { std::cerr << "Error: " << e.what() << std::endl; }
}

int main() {
  checkPermissions();
  setPermissions();
  checkPermissions();
  return 0;
}