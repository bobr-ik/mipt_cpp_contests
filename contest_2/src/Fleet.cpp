#include "../include/Fleet.hpp"

#include <algorithm>
#include <memory>
#include <string>

#include "../include/Errors.hpp"
#include "../include/ServiceCenter.hpp"

Fleet::Fleet(ServiceCenter& service_center) : service_center(service_center) {}

void Fleet::addItem(std::unique_ptr<InventoryItem> item) {
  if (item == nullptr) {
    throw InvalidArgument("Cannot add nullptr");
  }

  service_center.inspect(*item);
  items.push_back(std::shared_ptr<InventoryItem>(std::move(item)));
  auto shared_item = items.back();

  event_log.add("Added: " + shared_item->getId());
  recent_items.add(shared_item);
}

void Fleet::focus(const std::string id) {
  for (const auto& item : items) {
    if (item->getId() == id) {
      focus_item = item;
      event_log.add("Focused: " + id);
      recent_items.add(item);

      return;
    }
  }
  throw FocusError("No such element with id " + id);
}

void Fleet::printList() {
  std::sort(items.begin(), items.end(), [](const auto& a, const auto& b) { return *a < *b; });
  for (const auto& item : items) {
    std::cout << *item << '\n';
  }
}

void Fleet::printNovice() const {
  bool is_empty = true;
  for (const auto& item : items) {
    if (item->isForNovice()) {
      is_empty = false;
      std::cout << *item << '\n';
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

std::weak_ptr<InventoryItem> Fleet::getFocusItem() const { return focus_item; }

void Fleet::remove(const std::string& id) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    if ((*it)->getId() == id) {
      items.erase(it);
      event_log.add("Removed: " + id);
      return;
    }
  }

  throw RemoveError("No such element with id " + id);
}

void Fleet::printLog() const {
  std::cout << "--- Event Log ---\n";
  std::cout << event_log;
  std::cout << "-----------------\n";
}

void Fleet::printRecent() const {
    std::cout << "--- Recent Items ---\n";
    for (int i = 0; i < recent_items.size(); ++i) {
        std::cout << *recent_items[i] << "\n"; 
    }
    std::cout << "--------------------\n";
}