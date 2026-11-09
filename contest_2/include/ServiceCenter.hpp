#pragma once
#include <string>

#include "Inventory.hpp"

class ServiceCenter {
 private:
  std::string banword;

  bool containsCaseInsensitive(const std::string& str, const std::string& substr);

 public:
  ServiceCenter(std::string banword);

  void inspect(const InventoryItem& item);
};