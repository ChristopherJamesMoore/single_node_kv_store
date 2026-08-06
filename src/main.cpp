#include <iostream>
#include <string>
#include <sstream>
#include "store.hpp"

int main() {
  std::string line;
  Store store;
  store.openLog("kvstore.log");
  store.replayLog("kvstore.log");
  store.load("kvstore.snapshot");

  std::cout << "kvstore> ";
  while(std::getline(std::cin, line)) {
    std::istringstream iss(line);
    std::string cmd;
    iss >> cmd;

    if (cmd == "SET") {
      std::string key, value;
      iss >> key >> value;
      store.set(key, value); 
      std::cout << "OK\n";
    } else if (cmd == "GET") {
      std::string key; 
      iss >> key;
      if (auto val = store.get(key)) {
        std::cout << *val << "\n";
      } else {
        std::cout << "(nil)\n";
      }
    } else if (cmd == "DEL") {
      std::string key;
      iss >> key;
      std::cout << (store.remove(key) ? "OK\n" : "(nil)\n");
    } else if (cmd == "SNAPSHOT") {
      store.snapshot("kvstore.snapshot", "kvstore.log");
      std::cout << "OK\n";
    } else if (cmd == "QUIT") {
      break;
    } else {
      std::cout << "unknown command\n";
    }
    std::cout << "kvstore> ";
  }

  return 0;
}
