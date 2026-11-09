#include "../include/Fleet.hpp"

#include <algorithm>
#include <memory>
#include <string>

#include "../include/Errors.hpp"

void Fleet::addItem(std::shared_ptr<InventoryItem> item) { items.push_back(item); }

void Fleet::focus(const std::string id) {
  for (const auto& item : items) {
    if (item->getId() == id) {
      focus_item = item;
      return;
    }
  }
  throw FocusError("No such element with id " + id);
}

void Fleet::printList() {
  std::sort(items.begin(), items.end());
  for (const auto& item : items) {
    std::cout << item << '\n';
  }
}

void Fleet::printNovice() const {
  bool is_empty = true;
  for (const auto& item : items) {
    if (item->isForNovice()) {
      is_empty = false;
      std::cout << item << '\n';
    }
  }
  if (is_empty) {
    std::cout << "No such products found\n";
  }
}

double Fleet::getEnergy() const {
  double total_energy_consumption{};
  for (const auto& item : items) {
    if (auto consumer = std::dynamic_pointer_cast<EnergyConsumer>(item)) {
      total_energy_consumption += consumer->getEnergyConsumption();
    }
  }
  return total_energy_consumption;
}