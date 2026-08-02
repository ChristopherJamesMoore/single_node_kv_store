#include "store.hpp"
#include <fstream>

void Store::set(const std::string& key, const std::string& value) {
  data_[key] = value;
}

std::optional<std::string> Store::get(const std::string& key) const {
  auto it = data_.find(key);
  if (it == data_.end()) {
    return std::nullopt;
  }
  return it->second;
}

bool Store::remove(const std::string& key) {
  return data_.erase(key) > 0;
}

void Store::save(const std::string& filename)const {
  std::ofstream out(filename);
  for(const auto& [key, value] : data_) {
    out << key << " " << value << "\n";
  }
}

void Store::load(const std::string& filename) {
  std::ifstream in (filename);
  if (!in) return;

  std::string key, value;
  while (in >> key >> value ) {
    data_[key] = value;
  }
}
