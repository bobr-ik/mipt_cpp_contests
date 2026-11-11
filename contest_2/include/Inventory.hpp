#pragma once
#include <iostream>
#include <string>

class InventoryItem {
 protected:
  std::string id;
  std::string name;

 public:
  InventoryItem(std::string id, std::string name);
  virtual std::string getId() const;
  virtual std::string getName() const;
  virtual bool isForNovice() const;

  virtual std::string getDescription() const = 0;
  virtual ~InventoryItem() = default;
  friend std::ostream& operator<<(std::ostream& os, const InventoryItem& item);
  bool operator<(const InventoryItem& other) const;
};

class EnergyConsumer {
 protected:
  double energy_consumption;

 public:
  EnergyConsumer(double energy_consumption);
  virtual double getEnergyConsumption() const = 0;
  virtual ~EnergyConsumer() = default;
};