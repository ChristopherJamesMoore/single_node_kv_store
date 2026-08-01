#include <iostream>
#include <string>

int main() {
  std::string line;

  std::cout << "kvstore: ";
  while(std::getline(std::cin, line)) {
    std::cout << "you typed: " << line << "\n";
    std::cout << "kvstore> ";
  }

  return 0;
}
