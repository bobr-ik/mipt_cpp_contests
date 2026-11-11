#include "../include/Things.hpp"

#include <string>

// Helmet

Helmet::Helmet(std::string id, std::string name) : InventoryItem(id, name) {}
std::string Helmet::getDescription() const { return "Helmet. id: " + id + ", name: " + name; }

// DockStation

DockStation::DockStation(std::string id, std::string name, double energy_consumption)
    : InventoryItem(id, name), EnergyConsumer(energy_consumption) {}
std::string DockStation::getDescription() const {
  std::string s_energy_consumption = std::to_string(energy_consumption);
  s_energy_consumption = s_energy_consumption.substr(0, s_energy_consumption.find('.') + 2);
  return "DockStation. id: " + id + ", name: " + name +
         ", energy_consumption: " + s_energy_consumption;
}

double DockStation::getEnergyConsumption() const {
  return energy_consumption;
}