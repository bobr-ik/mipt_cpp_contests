#include "../include/Transport.hpp"

//  Transport

Transport::Transport(std::string id, std::string name, double difficulty_score)
    : InventoryItem(id, name), difficulty_score(difficulty_score) {}

bool Transport::isForNovice() const { return difficulty_score <= 5; }

double Transport::getScore() const { return difficulty_score; }

// Bike

Bike::Bike(std::string id, std::string name, double difficulty_score)
    : Transport(id, name, difficulty_score) {}

std::string Bike::getDescription() const {
  return "Bike. id: " + id + ", name: " + name +
         ", difficulty_score: " + std::to_string(difficulty_score);
}

// EBike

EBike::EBike(std::string id, std::string name, double difficulty_score, double energy_consumption)
    : Bike(id, name, difficulty_score), EnergyConsumer(energy_consumption) {}

double EBike::getEnergyConsumption() const { return energy_consumption; }

std::string EBike::getDescription() const {
  return "EBike. id: " + id + ", name: " + name +
         ", difficulty_score: " + std::to_string(difficulty_score) +
         ", energy_consumption: " + std::to_string(energy_consumption);
}

// Scooter

Scooter::Scooter(std::string id, std::string name, double difficulty_score,
                 double energy_consumption)
    : Transport(id, name, difficulty_score), EnergyConsumer(energy_consumption) {}

double Scooter::getEnergyConsumption() const { return energy_consumption; }

std::string Scooter::getDescription() const {
  return "Scooter. id: " + id + ", name: " + name +
         ", difficulty_score: " + std::to_string(difficulty_score) +
         ", energy_consumption: " + std::to_string(energy_consumption);
}