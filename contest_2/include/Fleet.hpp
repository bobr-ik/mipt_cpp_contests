#pragma once
#include <memory>
#include <vector>

#include "Inventory.hpp"
#include "Registry.hpp"
#include "ServiceCenter.hpp"

class Fleet {
 private:
  std::vector<std::shared_ptr<InventoryItem>> items;
  std::weak_ptr<InventoryItem> focus_item;
  ServiceCenter& service_center;

  Registry<std::string, 5> event_log;
  Registry<std::shared_ptr<InventoryItem>, 3> recent_items;

 public:
  Fleet(ServiceCenter& service_center);
  void addItem(std::unique_ptr<InventoryItem> item);

  void focus(const std::string id);

  void printList();

  void printNovice() const;

  double getEnergy() const;

  std::weak_ptr<InventoryItem> getFocusItem() const;

  void remove(const std::string& id);

  void printLog() const;
  void printRecent() const;
};