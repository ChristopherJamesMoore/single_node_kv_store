#include <iostream>
#include <string>
#include <sstream>

int main() {
  std::string line;

  std::cout << "kvstore: ";
  while(std::getline(std::cin, line)) {
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    std::cout << "command was: " << cmd << "\n";
    std::cout << "kvstore> ";
  }

  return 0;
}
