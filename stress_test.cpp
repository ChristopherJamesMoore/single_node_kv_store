#include "src/store.hpp"
#include <thread>
#include <iostream>
#include <vector>

int main() {
  Store store;
  store.openLog("stress.log");

  std::vector<std::thread> threads;

  for (int t = 0; t < 4; t++) {
    threads.emplace_back([&store, t]() {
      for (int i = 0; i < 1000; i++) {
        std::string key = "key" + std::to_string(i % 10);
        store.set(key, "vlaue_from_thread_" + std::to_string(t));
        store.get(key);
      }
    });
  }
  for (auto& th : threads) {
    th.join();
  }
  std::cout << "Stress test completed without crashing\n";
}
