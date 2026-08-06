#pragma once
#include <string>
#include <unordered_map>
#include <optional>
#include <fstream>
#include <shared_mutex>

class Store {
  public:
    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const;
    bool remove(const std::string& key);
    void save(const std::string& filename) const;
    void load(const std::string& filename);
    void openLog(const std::string& filename);
    void replayLog(const std::string& filename);
    void snapshot(const std::string& snapshotFile, const std::string& logFile);

  private:
    std::unordered_map<std::string, std::string> data_;
    std::ofstream log_;
    mutable std::shared_mutex mutex_;
};
