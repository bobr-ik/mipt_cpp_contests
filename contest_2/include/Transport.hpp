#pragma once
#include <string>

#include "Inventory.hpp"

class Transport : public InventoryItem {
 protected:
  double difficulty_score;

 public:
  Transport(std::string id, std::string name, double difficulty_score);
  bool isForNovice() const override;

  double getScore() const;

  virtual ~Transport() = default;
};

class Bike : public Transport {
 public:
  Bike(std::string id, std::string name, double difficulty_score);

  std::string getDescription() const override;
};

class EBike : public Bike, public EnergyConsumer {
 public:
  EBike(std::string id, std::string name, double difficulty_score, double energy_consumption);

  double getEnergyConsumption() const override;

  std::string getDescription() const override;
};

class Scooter : public Transport, public EnergyConsumer {
 public:
  Scooter(std::string id, std::string name, double difficulty_score, double energy_consumption);

  double getEnergyConsumption() const override;

  std::string getDescription() const override;
};