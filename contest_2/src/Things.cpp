#include "../include/Things.hpp"

#include <string>

// Helmet

Helmet::Helmet(std::string id, std::string name) : InventoryItem(id, name) {}
std::string Helmet::getDescription() const { return "Helmet. Name: " + name + ", id: " + id; }

// DockStation

DockStation::DockStation(std::string id, std::string name, double energy_consumption)
    : InventoryItem(id, name), EnergyConsumer(energy_consumption) {}
std::string DockStation::getDescription() const {
  return "DockStation. Name: " + name + ", id: " + id +
         ", energy_consumption: " + std::to_string(energy_consumption);
}