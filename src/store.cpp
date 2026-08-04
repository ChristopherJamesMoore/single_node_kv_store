#include "store.hpp"
#include <fstream>

void Store::set(const std::string& key, const std::string& value) {
  log_ << "SET" << " " << key << " " << value << "\n";
  log_.flush();
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
  log_ << "DEL" << " " << key << "\n";
  log_.flush();
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

void Store::openLog(const std::string& filename) {
  log_.open(filename, std::ios::app);
}

void Store::replayLog(const std::string& filename) {
  std::ifstream in(filename);
  std::string op, key, value;

  while (in >> op) {
    if (op == "SET") {
      in >> key >> value;
      data_[key] = value;
    } else if (op == "DEL") {
      in >> key;
       data_.erase(key);
    }    
  }
}

void Store::snapshot(const std::string& snapshotFile, const std::string& logFile) {
  save(snapshotFile);

  log_.close();
  std::ofstream clear(logFile, std::ios::trunc);
  clear.close();
  openLog(logFile);
}
