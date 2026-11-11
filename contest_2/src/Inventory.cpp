#include "../include/Inventory.hpp"
#include "../include/Errors.hpp"

InventoryItem::InventoryItem(std::string id, std::string name) : id(id), name(name) {}

std::string InventoryItem::getId() const { return id; }
std::string InventoryItem::getName() const { return name; }
bool InventoryItem::isForNovice() const { return false; }

std::ostream& operator<<(std::ostream& os, const InventoryItem& item) {
  os << item.getDescription();
  return os;
}

bool InventoryItem::operator<(const InventoryItem& other) const { return id < other.id; }


EnergyConsumer::EnergyConsumer(double energy_consumption) : energy_consumption(energy_consumption) {
  if (energy_consumption < 0) {
    throw InvalidArgument("Energy consumption can not be less then 0");
  }
}