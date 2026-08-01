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

    if (cmd == "SET") {
      std::string key, value;
      iss >> key >> value;
      std::cout << "would SET " << key << " = " << value << "\n";
    } else if (cmd == "GET") {
      std::string key; 
      iss >> key;
      std::cout << "would GET " << "\n";
    } else if (cmd == "DEL") {
      std::string key;
      iss >> key;
      std::cout << "would DEL " << "\n";
    } else if (cmd == "QUIT") {
      break;
    } else {
      std::cout << "unkown command\n";
    }
  }

  return 0;
}
