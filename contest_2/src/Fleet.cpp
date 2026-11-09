#include "../include/Fleet.hpp"

#include <algorithm>
#include <memory>
#include <string>

#include "../include/Errors.hpp"
#include "../include/ServiceCenter.hpp"

Fleet::Fleet(ServiceCenter& service_center) : service_center(service_center) {}

void Fleet::addItem(std::unique_ptr<InventoryItem> item) {
  service_center.inspect(*item);
  items.push_back(std::shared_ptr<InventoryItem>(std::move(item)));
}

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