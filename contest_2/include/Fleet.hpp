#pragma once
#include <memory>
#include <vector>
#include "Inventory.hpp"
#include "ServiceCenter.hpp"


class Fleet {
 private:
  std::vector<std::shared_ptr<InventoryItem>> items;
  std::weak_ptr<InventoryItem> focus_item;
  ServiceCenter& service_center;

 public:
  Fleet(ServiceCenter& service_center);
  void addItem(std::unique_ptr<InventoryItem> item);

  void focus(std::string id);

  void printList();

  void printNovice() const;

  double getEnergy() const;
};