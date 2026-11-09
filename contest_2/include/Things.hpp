#include "Inventory.hpp"

class Helmet : public InventoryItem {
 public:
  Helmet(std::string id, std::string name);
  std::string getDescription() const override;
};

class DockStation : public InventoryItem, public EnergyConsumer {
 public:
  DockStation(std::string id, std::string name, double energy_consumption);
  std::string getDescription() const override;
};