#pragma once
#include <string>
#include <unordered_map>
#include <optional>

class Store {
  public:
    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const;
    bool remove(const std::string& key);
    void save(const std::string& filename) const;
    void load(const std::string& filename);

  private:
    std::unordered_map<std::string, std::string> data_;
};
